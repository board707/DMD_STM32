#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_32_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_32_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6353 register profiles. Only Scan_32 profiles are present.

#ifndef DMD_SPWM_FM6353_REGTYPE_1_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_1_INCLUDED
    // fm6353_regtype1: built-in main FM6353 register config
    // Scan membership: Scan_32
    {
        1, 5,
        {
            {
                0x0008, 0x1f70, 0x6707, 0x40f7, 0x0040
            },
            {
                0x0008, 0x1f70, 0x6707, 0x40f7, 0x0040
            },
            {
                0x0008, 0x1f70, 0x6707, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_1_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_2_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_2_INCLUDED
    // fm6353_regtype2: P3 - FM6353 - 74HC138 - 1/32
    // Scan membership: Scan_32
    {
        2, 5,
        {
            {
                0x0008, 0x5ff0, 0x5fcd, 0x6846, 0x4a00
            },
            {
                0x0008, 0x5ff0, 0x5bcd, 0x6846, 0x4a30
            },
            {
                0x0008, 0x5ff0, 0x57cd, 0x6846, 0x4a30
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_2_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_3_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_3_INCLUDED
    // fm6353_regtype3: P2.5 - FM6353 - ICN2053 schema - 7559 - 1/32
    // Scan membership: Scan_32
    {
        3, 5,
        {
            {
                0x0008, 0x1fb8, 0x639c, 0x40f7, 0x0070
            },
            {
                0x0008, 0x1fb8, 0x4b9c, 0x40f7, 0x0070
            },
            {
                0x0008, 0x1fb8, 0x439c, 0x40f7, 0x0070
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_3_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_4_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_4_INCLUDED
    // fm6353_regtype4: P? - FM6353 - ICN2053 schema - 1/32
    // Scan membership: Scan_32
    {
        4, 5,
        {
            {
                0x0008, 0x1ff8, 0x679a, 0x40f7, 0x0040
            },
            {
                0x0008, 0x1ff8, 0x4b9a, 0x40f7, 0x0040
            },
            {
                0x0008, 0x1ff8, 0x439a, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_4_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_5_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_5_INCLUDED
    // fm6353_regtype5: P? - FM6353 - ICN2053 schema - 1/32
    // Scan membership: Scan_32
    {
        5, 5,
        {
            {
                0x0008, 0x5ff8, 0x539c, 0x40f7, 0x0040
            },
            {
                0x0008, 0x5ff8, 0x5b9c, 0x4007, 0x4040
            },
            {
                0x0008, 0x5ff8, 0x5f9c, 0x4007, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_5_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_6_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_6_INCLUDED
    // fm6353_regtype6: P? - FM6353 - ICN2053 schema - 1/32
    // Scan membership: Scan_32
    {
        6, 5,
        {
            {
                0x0008, 0x1f70, 0x5f9c, 0x40f7, 0x0040
            },
            {
                0x0008, 0x1f70, 0x539c, 0x40f7, 0x0040
            },
            {
                0x0008, 0x1f70, 0x579c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_6_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_7_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_7_INCLUDED
    // fm6353_regtype7: P1.25 - FM6353 - ICN2053 schema - 5958 - 1/32
    // Scan membership: Scan_32
    {
        7, 5,
        {
            {
                0x0008, 0x5f70, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0008, 0x5f70, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0008, 0x5f70, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_7_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_8_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_8_INCLUDED
    // fm6353_regtype8: P2.5 - FM6353 - ICN2053 schema - 5166 - 1/32
    // Scan membership: Scan_32
    {
        8, 5,
        {
            {
                0x0008, 0x1f70, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0008, 0x1f70, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0008, 0x1f70, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_8_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_11_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_11_INCLUDED
    // fm6353_regtype11: P4 - FM6353 - ICN2053 schema - RUC7258D - 1/32
    // Scan membership: Scan_32
    {
        11, 5,
        {
            {
                0x0008, 0x1ff8, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0008, 0x1ff8, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0008, 0x1ff8, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_11_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_32_H
