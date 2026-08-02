#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_13_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_13_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6353 register profiles. Only Scan_13 profiles are present.

#ifndef DMD_SPWM_FM6353_REGTYPE_10_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_10_INCLUDED
    // fm6353_regtype10: P4.81 - FM6353 - ICN2053 schema - 1/13
    // Scan membership: Scan_13
    {
        10, 5,
        {
            {
                0x0008, 0x0c70, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0008, 0x0c70, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0008, 0x0c70, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_10_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_13_H
