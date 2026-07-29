#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_27_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_27_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6353 register profiles. Only Scan_27 profiles are present.

#ifndef DMD_SPWM_FM6353_REGTYPE_4_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_4_INCLUDED
    // fm6353_regtype4: P3.076 - FM6353 - 1/13
    // Scan membership: Scan_2,Scan_4,Scan_5,Scan_6,Scan_7,Scan_8,Scan_10,Scan_12,Scan_13,Scan_15,Scan_16,Scan_18,Scan_20,Scan_21,Scan_23,Scan_24,Scan_25,Scan_26,Scan_27,Scan_28,Scan_30,Scan_31,Scan_32
    {
        4, 5,
        {
            {
                0x0000, 0x0000, 0xff9c, 0x0000, 0x0000
            },
            {
                0x0000, 0x0000, 0xf39c, 0x0000, 0x0000
            },
            {
                0x0000, 0x0000, 0xdf9c, 0x0000, 0x0000
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_4_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_25_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_25_INCLUDED
    // fm6353_regtype25: P? - FM6353 - 5958 - 1/27
    // Scan membership: Scan_27
    {
        25, 5,
        {
            {
                0x0000, 0x1ab8, 0x7f96, 0x40f7, 0x0060
            },
            {
                0x0000, 0x1ab8, 0x3796, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ab8, 0x3396, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_25_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_50_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_50_INCLUDED
    // fm6353_regtype50: P? - FM6353 - 74HC138 - 1/27
    // Scan membership: Scan_27
    {
        50, 5,
        {
            {
                0x0000, 0x1af8, 0x7f6a, 0x40f7, 0x4040
            },
            {
                0x0000, 0x1af8, 0x676e, 0x40f7, 0x4040
            },
            {
                0x0000, 0x1af8, 0x5f94, 0x40f7, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_50_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_132_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_132_INCLUDED
    // fm6353_regtype132: P? - FM6353 - 74HC138 - 1/27
    // Scan membership: Scan_27
    {
        132, 5,
        {
            {
                0x0000, 0x1af8, 0x7f9c, 0x40f3, 0x0040
            },
            {
                0x0000, 0x1af8, 0x739c, 0x40f3, 0x0040
            },
            {
                0x0000, 0x1af8, 0x5f9c, 0x40f3, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_132_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_141_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_141_INCLUDED
    // fm6353_regtype141: P? - FM6353 - 74HC138 - 1/27
    // Scan membership: Scan_27
    {
        141, 5,
        {
            {
                0x0000, 0x1a70, 0x7f70, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1a70, 0x6770, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1a70, 0x5f70, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_141_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_143_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_143_INCLUDED
    // fm6353_regtype143: P? - FM6353 - 74HC138 - 1/27
    // Scan membership: Scan_27
    {
        143, 5,
        {
            {
                0x0000, 0x5a70, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x5a70, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x5a70, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_143_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_145_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_145_INCLUDED
    // fm6353_regtype145: P? - FM6353 - 5958 - 1/27
    // Scan membership: Scan_27
    {
        145, 5,
        {
            {
                0x0000, 0x5af8, 0x52ff, 0x40f7, 0x0000
            },
            {
                0x0000, 0x5af8, 0x3eff, 0x40f7, 0x0000
            },
            {
                0x0000, 0x5af8, 0x36ff, 0x40f7, 0x0000
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_145_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_147_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_147_INCLUDED
    // fm6353_regtype147: P? - FM6353 - 74HC138 - 1/27
    // Scan membership: Scan_27
    {
        147, 5,
        {
            {
                0x0000, 0x1af8, 0x52fe, 0x40f7, 0x0070
            },
            {
                0x0000, 0x1af8, 0x3efe, 0x40f7, 0x0070
            },
            {
                0x0000, 0x1af8, 0x36fe, 0x40f7, 0x0070
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_147_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_27_H
