#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_45_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_45_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6363
#error "Register-test profile fragment is in the wrong chip array"
#endif

// Generated from lib/spwm/registertest/data/fm6363.profiles at
// Raspberry Pi revision f9dc4d0a8c25. Only Scan_45 profiles are present.

#ifndef DMD_SPWM_FM6363_REGTYPE_67_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_67_INCLUDED
    // fm6363_regtype67: P1.25 - FM6363 - 1/45
    // Source scan membership: Scan_45
    {
        67, 5,
        {
            {
                0x2cf0, 0xff9d, 0x60b6, 0x5a10, 0x7e08
            },
            {
                0x2cf0, 0xff9d, 0x60b6, 0x5a50, 0x7e08
            },
            {
                0x2cf0, 0xff9d, 0x60b6, 0x5a50, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_67_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_45_H
