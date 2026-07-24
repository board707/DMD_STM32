# SPWM register test

## Run the test

1. Set `DMD_SPWM_REGISTER_TEST_ENABLED` to `1` in `dmd_spwm_panel.ino`.
2. Select the matching `DMD_RGB_<chip>` and panel template.
3. Choose the `GRADIENT` or `ALIGN` test pattern.
4. In `register_test_config.h`, uncomment one or more matching scan headers.
5. Compile and upload.

Multiple scan headers are tested in include order:

```cpp
#include "profiles/fm6373/fm6373_scan_21.h"
#include "profiles/fm6373/fm6373_scan_32.h"
```

- STM32: briefly press KEY for the next profile. Hold KEY for 1.2 seconds to
  keep it and enter the normal demo; the choice lasts until reset or power-off.
- RP2040: each profile remains visible for 3 seconds after it is applied, then
  the test advances and wraps indefinitely. Note the preferred `REG N`, then
  compile it as an override; RP2040 test mode does not enter the normal demo.

`REG N` is the original source `regtypeN` number, not its position in the
combined list.

## Controls

- Generic STM32F407V: active-low KEY0 on PE4.
- Blackpill F401/F411: active-low KEY on PA0.
- RP2040: no button is required. Change
  `DMD_SPWM_REGISTER_TEST_AUTO_ADVANCE_MS` in `register_test_config.h` if a
  different automatic interval is needed.

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
