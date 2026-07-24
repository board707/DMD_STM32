#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_19_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_19_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6363
#error "Register-test profile fragment is in the wrong chip array"
#endif

// Generated from lib/spwm/registertest/data/fm6363.profiles at
// Raspberry Pi revision f9dc4d0a8c25. Only Scan_19 profiles are present.

#ifndef DMD_SPWM_FM6363_REGTYPE_55_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_55_INCLUDED
    // fm6363_regtype55: P3.79 - FM6363 - 1/19
    // Source scan membership: Scan_19
    {
        55, 5,
        {
            {
                0x12b0, 0xf39c, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x12b0, 0xe79c, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x12b0, 0xd79c, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_55_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_19_H
