# SPWM register test

## Run the test

1. Set `DMD_SPWM_REGISTER_TEST_ENABLED` to `1` in `dmd_spwm_panel.ino`.
2. Select the matching `DMD_RGB_<chip>` and panel template.
3. Choose the `GRADIENT`, `ALIGN`, or `TEXTSCROLL` test pattern.
4. In `register_test_config.h`, uncomment one or more matching scan headers.
5. Compile and upload.

Multiple scan headers are tested in include order:

```cpp
#include "register_test/profiles/fm6373/fm6373_scan_21.h"
#include "register_test/profiles/fm6373/fm6373_scan_32.h"
```

- STM32: briefly press KEY for the next profile. Hold KEY for 1.2 seconds to
  keep it and enter the normal demo; the choice lasts until reset or power-off.
- RP2040: `GRADIENT` and `ALIGN` remain visible for 3 seconds after each
  profile is applied. `TEXTSCROLL` remains visible for at least 3 seconds and
  changes REG at the end of the bottom-band pass as the marquee wraps back to
  the top. Later changes occur one complete top/middle/bottom cycle apart at
  that same position. The test wraps indefinitely. Note the preferred `REG N`, 
  then compile it as an override; RP2040 test mode does not enter the normal demo.

`REG N` is the original source `regtypeN` number, not its position in the
combined list.

## Patterns

DMD_SPWM_REGISTER_TEST_PATTERN

- `GRADIENT`: check color transitions, brightness levels, dark-area flicker,
  and visible banding.
- `ALIGN`: check panel edges, row alignment, scan mapping, and diagonal
  continuity.
- `TEXTSCROLL`: check register stability during repeated animated frame
  updates. The text moves through the top, middle, and bottom thirds in turn.
  Adjust `DMD_SPWM_REGISTER_TEST_TEXT_SCROLL_INTERVAL_MS` in
  `dmd_spwm_panel.ino` to change the frame interval, and
  `DMD_SPWM_REGISTER_TEST_TEXT_SCROLL_STEP_PIXELS` to select how many pixels
  the text moves per frame. One pixel is smoothest; larger values move faster.

## Controls

- Generic STM32F407V: active-low KEY0 on PE4.
- Blackpill F401/F411: active-low KEY on PA0.
- RP2040: no button is required. Change
  `DMD_SPWM_REGISTER_TEST_AUTO_ADVANCE_MS` in `register_test_config.h` if a
  different minimum automatic interval is needed. For `TEXTSCROLL`, a full
  three-band cycle can make the actual interval longer.

The example uses PA7 for panel R0 so PA0 remains available. For another board,
change the button pin or polarity in `register_test_config.h`. Never share a
button pin with a panel signal.

## Keep a working profile after reboot

After finding a working `REG N`:

1. Set `DMD_SPWM_REGISTER_TEST_ENABLED` to `0`.
2. Set `DMD_SPWM_REGISTER_OVERRIDE` to `N`.
3. Keep the same driver, panel template and scan header selected.
4. Recompile and upload.

Set the override back to `0` to use the driver's normal configuration. The test
and override cannot be enabled together, and compilation fails if the selected
scan headers do not contain the requested `REG N`.

## Notes

- Profile data uses flash, not another framebuffer; include only the scan
  catalogues you need.
- `register_test_driver.h` is the single shared adapter. It delegates each
  register protocol to the native driver.
- `DMD_SPWM_REGISTER_TEST_USE_RGB_CHANNEL_DATA=0` broadcasts the profile's Red
  words to all three physical RGB lanes; it does not send only to the Red LEDs.
- Setting it to `1` sends the profile's separate Red, Green and Blue words to
  their matching lanes. This applies to both testing and fixed overrides.
- Only register payloads are channel-specific. Native protocol framing and
  command words remain broadcast, and equal R/G/B arrays behave identically.
