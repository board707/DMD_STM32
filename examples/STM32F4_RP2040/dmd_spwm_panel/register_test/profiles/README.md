# Register-test profiles

Each chip subfolder contains generated register profiles split by scan rate.
Uncomment matching `*_scan_N.h` files in `register_test_config.h`; they are
combined in include order.

The interactive test and `DMD_SPWM_REGISTER_OVERRIDE` use the same profiles.
An override therefore requires the scan header containing that `regtypeN` to
remain uncommented. Missing register numbers produce a compile-time error.

## ICND2055

The `icnd2055` catalogue accepts exact modern XML ChipCode 107 packages and
older `Chip_ICND2055` packages when they use the ICND2055 RGB property type.
Filename-only matches are ignored. Some packages add one trailing non-register
storage slot; after removing it, both formats provide the same 47-register
address layout. The runtime driver remains `DMD_RGB_ICN2055`.

## DP3264 family

The `dp3264` catalogue covers exact XML ChipCode 219 packages and older
`Chip_DP3264` packages. Some qualifying package filenames also contain DP3269, DP3256, DP3356, or DP3364. Those labels also occur with other chip
identities, so a filename alone is never used to include a profile. The
runtime driver and wire protocol remain `DMD_RGB_DP3264`.

DP3264 source packages declare 11-, 12-, 13-, or 14-bit `GrayDepth`, which is
recorded beside each profile. The current STM32 and RP2040 DP3264 drivers keep
their pixel data path at 13 bits, so a non-13-bit source profile does not by
itself retune grayscale packing.
