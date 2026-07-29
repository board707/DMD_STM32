#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_29_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_29_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6353 register profiles. Only Scan_29 profiles are present.

#ifndef DMD_SPWM_FM6353_REGTYPE_22_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_22_INCLUDED
    // fm6353_regtype22: P? - FM6353 - 1/29
    // Scan membership: Scan_29
    {
        22, 5,
        {
            {
                0x0000, 0x1cf8, 0x4f04, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1cf8, 0x2e9c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1cf8, 0x22d6, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_22_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_88_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_88_INCLUDED
    // fm6353_regtype88: P1.83 - FM6353 - 5958 - 1/29
    // Scan membership: Scan_29
    {
        88, 5,
        {
            {
                0x0000, 0x1c70, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1c70, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1c70, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_88_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_131_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_131_INCLUDED
    // fm6353_regtype131: P? - FM6353 - 1/29
    // Scan membership: Scan_29
    {
        131, 5,
        {
            {
                0x0000, 0x1cf8, 0x7f9c, 0x40f7, 0x4070
            },
            {
                0x0000, 0x1cf8, 0x679c, 0x40f7, 0x4070
            },
            {
                0x0000, 0x1cf8, 0x5f9c, 0x40f7, 0x4070
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_131_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_29_H
