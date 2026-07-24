#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_3_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_3_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// Generated from lib/spwm/registertest/data/fm6353.profiles at
// Raspberry Pi revision f9dc4d0a8c25. Only Scan_3 profiles are present.

#ifndef DMD_SPWM_FM6353_REGTYPE_56_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_56_INCLUDED
    // fm6353_regtype56: P? - FM6353 - 74HC138 - 1/3
    // Source scan membership: Scan_3
    {
        56, 5,
        {
            {
                0x0001, 0x0270, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0270, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0270, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_56_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_3_H
