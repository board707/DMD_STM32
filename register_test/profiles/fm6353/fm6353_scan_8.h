#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_8_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_8_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6353 register profiles. Only Scan_8 profiles are present.

#ifndef DMD_SPWM_FM6353_REGTYPE_12_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_12_INCLUDED
    // fm6353_regtype12: P6 - FM6353 - ICN2053 schema - RUC7258D - 1/8
    // Scan membership: Scan_8
    {
        12, 5,
        {
            {
                0x0008, 0x47f8, 0x7f9c, 0x4017, 0x0040
            },
            {
                0x0008, 0x47f8, 0x739c, 0x4017, 0x0040
            },
            {
                0x0008, 0x47f8, 0x5f9c, 0x4017, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_12_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_8_H
