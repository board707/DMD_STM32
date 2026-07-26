#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_25_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_25_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// Generated from lib/spwm/registertest/data/fm6353.profiles at
// Raspberry Pi revision f9dc4d0a8c25. Only Scan_25 profiles are present.

#ifndef DMD_SPWM_FM6353_REGTYPE_73_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_73_INCLUDED
    // fm6353_regtype73: P? - FM6353 - 1/25
    // Source scan membership: Scan_25
    {
        73, 5,
        {
            {
                0x0001, 0x1870, 0x7ff8, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1870, 0x6774, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1870, 0x5fba, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_73_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_25_H
