#!/usr/bin/env python3
"""Generate small, scan-specific STM32 register-test profile fragments."""

from __future__ import annotations

import argparse
import re
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, Iterable, List, Sequence, Tuple


CATALOG_MAGIC = "RGBMATRIX_SPWM_PROFILES_V4"
SOURCE_REVISION = "f9dc4d0a8c25"
SUPPORTED_CATALOGS = {
    "fm6353": "fixed",
    "fm6363": "fixed",
    "fm6373": "rgb",
    "icnd1065l": "rgb",
    "sm16380sh": "rgb",
}


@dataclass(frozen=True)
class Profile:
    catalog_index: int
    source_name: str
    description: str
    scans: Tuple[int, ...]
    channel_words: Tuple[Tuple[int, ...], ...]

    @property
    def word_count(self) -> int:
        return len(self.channel_words[0])


def fail(path: Path, line_number: int, message: str) -> ValueError:
    return ValueError(f"{path}:{line_number}: {message}")


def parse_word(path: Path, line_number: int, text: str) -> int:
    if re.fullmatch(r"[0-9a-fA-F]{1,4}", text) is None:
        raise fail(path, line_number, f"invalid uint16 word {text!r}")
    return int(text, 16)


def parse_scans(path: Path, line_number: int, text: str) -> Tuple[int, ...]:
    scans: List[int] = []
    for field in text.split(","):
        match = re.fullmatch(r"Scan_([0-9]+)", field)
        if match is None:
            raise fail(path, line_number, f"invalid scan membership {field!r}")
        scan = int(match.group(1))
        if scan <= 0 or scan > 255:
            raise fail(path, line_number, f"scan rate {scan} is outside 1..255")
        if scan in scans:
            raise fail(path, line_number, f"duplicate Scan_{scan} membership")
        scans.append(scan)
    if not scans:
        raise fail(path, line_number, "profile has no scan memberships")
    return tuple(scans)


def parse_rgb_payload(
    path: Path, line_number: int, payload: str
) -> Tuple[Tuple[int, ...], ...]:
    fields = payload.split("|")
    if len(fields) != 4 or fields[0] != "3":
        raise fail(path, line_number, "RGB payload must target logical slot 3")

    channels = tuple(
        tuple(parse_word(path, line_number, word) for word in field.split(","))
        for field in fields[1:]
    )
    word_count = len(channels[0])
    if word_count == 0 or word_count > 255:
        raise fail(path, line_number, "RGB word count is outside 1..255")
    if any(len(channel) != word_count for channel in channels):
        raise fail(path, line_number, "RGB channels have different word counts")
    return channels


def parse_fixed_payload(
    path: Path, line_number: int, payload: str
) -> Tuple[Tuple[int, ...], ...]:
    slots: Dict[int, Tuple[int, int, int]] = {}
    for entry in payload.split(";"):
        fields = entry.split(",")
        if len(fields) != 4 or re.fullmatch(r"[0-9]+", fields[0]) is None:
            raise fail(path, line_number, "fixed entry must contain slot,R,G,B")
        slot = int(fields[0])
        if slot in slots:
            raise fail(path, line_number, f"duplicate fixed logical slot {slot}")
        slots[slot] = tuple(
            parse_word(path, line_number, field) for field in fields[1:]
        )

    expected_slots = set(range(1, 6))
    if set(slots) != expected_slots:
        raise fail(path, line_number, "fixed payload must contain slots 1..5 once")

    # Store logical slots 1..5 for each RGB lane. The FM6363 adapter applies
    # its chip-specific transmission order when loading them.
    return tuple(
        tuple(slots[slot][channel] for slot in range(1, 6))
        for channel in range(3)
    )


def parse_catalog(path: Path, expected_chip: str, expected_kind: str) -> List[Profile]:
    lines = path.read_text(encoding="ascii").splitlines()
    if not lines:
        raise ValueError(f"{path}: empty profile catalog")

    header = lines[0].split("\t")
    if len(header) != 4 or header[0] != CATALOG_MAGIC:
        raise fail(path, 1, "invalid profile catalog header")
    if header[1] != expected_chip or header[2] != expected_kind:
        raise fail(
            path,
            1,
            f"expected {expected_chip}/{expected_kind}, got {header[1]}/{header[2]}",
        )
    try:
        declared_count = int(header[3])
    except ValueError as error:
        raise fail(path, 1, f"invalid declared profile count {header[3]!r}") from error

    profiles: List[Profile] = []
    seen_indexes = set()
    for line_number, line in enumerate(lines[1:], start=2):
        fields = line.split("\t")
        if len(fields) != 4:
            raise fail(path, line_number, "profile record must contain four tab fields")
        source_name, description, scan_field, payload = fields
        match = re.fullmatch(re.escape(expected_chip) + r"_regtype([0-9]+)", source_name)
        if match is None:
            raise fail(path, line_number, f"invalid source profile name {source_name!r}")
        catalog_index = int(match.group(1))
        if catalog_index <= 0 or catalog_index > 0xFFFF:
            raise fail(path, line_number, "catalog index is outside uint16 range")
        if catalog_index in seen_indexes:
            raise fail(path, line_number, f"duplicate catalog index {catalog_index}")
        seen_indexes.add(catalog_index)

        if expected_kind == "rgb":
            channel_words = parse_rgb_payload(path, line_number, payload)
        else:
            channel_words = parse_fixed_payload(path, line_number, payload)

        profiles.append(
            Profile(
                catalog_index=catalog_index,
                source_name=source_name,
                description=description,
                scans=parse_scans(path, line_number, scan_field),
                channel_words=channel_words,
            )
        )

    if len(profiles) != declared_count:
        raise fail(
            path,
            1,
            f"declares {declared_count} profiles but contains {len(profiles)}",
        )
    if seen_indexes != set(range(1, declared_count + 1)):
        raise fail(path, 1, "catalog indexes are not contiguous from 1")
    return profiles


def format_words(words: Sequence[int]) -> List[str]:
    lines: List[str] = []
    for offset in range(0, len(words), 8):
        chunk = words[offset : offset + 8]
        suffix = "," if offset + len(chunk) < len(words) else ""
        lines.append("                " + ", ".join(f"0x{word:04x}" for word in chunk) + suffix)
    return lines


def render_profile(chip: str, profile: Profile) -> List[str]:
    scans = ",".join(f"Scan_{scan}" for scan in profile.scans)
    profile_guard = (
        f"DMD_SPWM_{chip.upper()}_REGTYPE_{profile.catalog_index}_INCLUDED"
    )
    lines = [
        f"#ifndef {profile_guard}",
        f"#define {profile_guard}",
        f"    // {profile.source_name}: {profile.description}",
        f"    // Source scan membership: {scans}",
        "    {",
        f"        {profile.catalog_index}, {profile.word_count},",
        "        {",
    ]
    for channel_index, channel in enumerate(profile.channel_words):
        lines.append("            {")
        lines.extend(format_words(channel))
        comma = "," if channel_index < 2 else ""
        lines.append(f"            }}{comma}")
    lines.extend(["        }", "    },", f"#endif  // {profile_guard}"])
    return lines


def render_header(chip: str, scan: int, profiles: Iterable[Profile]) -> str:
    guard = f"DMD_SPWM_REGISTER_TEST_PROFILES_{chip.upper()}_SCAN_{scan}_H"
    profile_chip = f"DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_{chip.upper()}"
    lines = [
        f"#ifndef {guard}",
        f"#define {guard}",
        "",
        "#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY",
        '#error "Register-test profile fragments must be included inside the profile array"',
        "#endif",
        "",
        f"#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != {profile_chip}",
        '#error "Register-test profile fragment is in the wrong chip array"',
        "#endif",
        "",
        f"// Generated from lib/spwm/registertest/data/{chip}.profiles at",
        f"// Raspberry Pi revision {SOURCE_REVISION}. Only Scan_{scan} profiles are present.",
        "",
    ]
    for profile in profiles:
        lines.extend(render_profile(chip, profile))
        lines.append("")
    lines.append(f"#endif  // {guard}")
    return "\n".join(lines) + "\n"


def validate_guarded_entries(headers: Dict[Path, str]) -> None:
    """Catch generator regressions that could reintroduce cross-scan entries."""
    for relative_path, contents in headers.items():
        chip = relative_path.parts[0]
        prefix = f"DMD_SPWM_{chip.upper()}_REGTYPE_"
        entry_indexes = re.findall(
            rf"^    // {re.escape(chip)}_regtype([0-9]+):", contents, re.MULTILINE
        )
        guard_indexes = re.findall(
            rf"^#ifndef {re.escape(prefix)}([0-9]+)_INCLUDED$",
            contents,
            re.MULTILINE,
        )
        define_indexes = re.findall(
            rf"^#define {re.escape(prefix)}([0-9]+)_INCLUDED$",
            contents,
            re.MULTILINE,
        )
        closing_indexes = re.findall(
            rf"^#endif  // {re.escape(prefix)}([0-9]+)_INCLUDED$",
            contents,
            re.MULTILINE,
        )
        if not (
            entry_indexes == guard_indexes == define_indexes == closing_indexes
        ):
            raise ValueError(
                f"internal error: initializer guard mismatch in {relative_path}"
            )


def expected_headers(source_dir: Path) -> Tuple[Dict[Path, str], int]:
    headers: Dict[Path, str] = {}
    source_profile_count = 0
    for chip, kind in SUPPORTED_CATALOGS.items():
        profiles = parse_catalog(source_dir / f"{chip}.profiles", chip, kind)
        source_profile_count += len(profiles)
        scans = sorted({scan for profile in profiles for scan in profile.scans})
        for scan in scans:
            selected = [profile for profile in profiles if scan in profile.scans]
            relative_path = Path(chip) / f"{chip}_scan_{scan}.h"
            headers[relative_path] = render_header(chip, scan, selected)
    validate_guarded_entries(headers)
    return headers, source_profile_count


def check_headers(output_dir: Path, headers: Dict[Path, str]) -> bool:
    expected_paths = set(headers)
    actual_paths = {
        path.relative_to(output_dir)
        for chip in SUPPORTED_CATALOGS
        for path in (output_dir / chip).glob(f"{chip}_scan_*.h")
    }
    problems: List[str] = []
    for relative_path, expected in sorted(headers.items()):
        path = output_dir / relative_path
        if not path.is_file():
            problems.append(f"missing: {relative_path}")
        elif path.read_text(encoding="ascii") != expected:
            problems.append(f"out of date: {relative_path}")
    for relative_path in sorted(actual_paths - expected_paths):
        problems.append(f"unexpected: {relative_path}")
    for problem in problems:
        print(problem, file=sys.stderr)
    return not problems


def write_headers(output_dir: Path, headers: Dict[Path, str]) -> None:
    for relative_path, contents in sorted(headers.items()):
        path = output_dir / relative_path
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(contents, encoding="ascii")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source_dir", type=Path, help="directory containing *.profiles")
    parser.add_argument(
        "--output-dir",
        type=Path,
        default=Path(__file__).resolve().parents[1] / "profiles",
        help="profile header root (default: register_test/profiles)",
    )
    parser.add_argument(
        "--check", action="store_true", help="verify generated files without changing them"
    )
    args = parser.parse_args()

    try:
        headers, source_profile_count = expected_headers(args.source_dir)
    except (OSError, ValueError) as error:
        print(error, file=sys.stderr)
        return 1

    profile_instances = sum(text.count("\n    {\n") for text in headers.values())
    if args.check:
        if not check_headers(args.output_dir, headers):
            return 1
        action = "verified"
    else:
        write_headers(args.output_dir, headers)
        action = "generated"

    print(
        f"{action} {len(headers)} headers with {profile_instances} scan-profile "
        f"entries from {source_profile_count} source profiles"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
