#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_2_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_2_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6353 register profiles. Only Scan_2 profiles are present.

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

#ifndef DMD_SPWM_FM6353_REGTYPE_18_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_18_INCLUDED
    // fm6353_regtype18: P? - FM6353 - 1/2
    // Scan membership: Scan_2
    {
        18, 5,
        {
            {
                0x0001, 0x0170, 0x7eca, 0x40f4, 0x0040
            },
            {
                0x0001, 0x0170, 0x66e0, 0x40f4, 0x0040
            },
            {
                0x0001, 0x0170, 0x5eae, 0x40f4, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_18_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_26_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_26_INCLUDED
    // fm6353_regtype26: P? - FM6353 - 1/32
    // Scan membership: Scan_2,Scan_4,Scan_8,Scan_10,Scan_13,Scan_16,Scan_20,Scan_32
    {
        26, 5,
        {
            {
                0x0000, 0x0000, 0x0000, 0x0000, 0x0000
            },
            {
                0x0000, 0x0000, 0x0000, 0x0000, 0x0000
            },
            {
                0x0000, 0x0000, 0x0000, 0x0000, 0x0000
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_26_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_31_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_31_INCLUDED
    // fm6353_regtype31: P? - FM6353 - 1/2
    // Scan membership: Scan_2
    {
        31, 5,
        {
            {
                0x0001, 0x0170, 0x7f2e, 0x00f7, 0x0040
            },
            {
                0x0001, 0x0170, 0x6732, 0x00f7, 0x0040
            },
            {
                0x0001, 0x0170, 0x5f0e, 0x00f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_31_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_32_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_32_INCLUDED
    // fm6353_regtype32: P? - FM6353 - 1/2
    // Scan membership: Scan_2
    {
        32, 5,
        {
            {
                0x0001, 0x0170, 0x7f58, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0170, 0x6788, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0170, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_32_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_53_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_53_INCLUDED
    // fm6353_regtype53: P? - FM6353 - 74HC138 - 1/2
    // Scan membership: Scan_2
    {
        53, 5,
        {
            {
                0x0000, 0x0170, 0x7f8e, 0x40f7, 0x0040
            },
            {
                0x0000, 0x0170, 0x67aa, 0x40f7, 0x0040
            },
            {
                0x0000, 0x0170, 0x5f8e, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_53_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_62_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_62_INCLUDED
    // fm6353_regtype62: P? - FM6353 - 1/2
    // Scan membership: Scan_2
    {
        62, 5,
        {
            {
                0x0001, 0x0170, 0x7eca, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0170, 0x66ec, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0170, 0x5eb2, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_62_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_63_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_63_INCLUDED
    // fm6353_regtype63: P? - FM6353 - 1/2
    // Scan membership: Scan_2
    {
        63, 5,
        {
            {
                0x0001, 0x0170, 0x7f18, 0x00f7, 0x0040
            },
            {
                0x0001, 0x0170, 0x675e, 0x00f7, 0x0040
            },
            {
                0x0001, 0x0170, 0x5ee8, 0x00f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_63_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_89_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_89_INCLUDED
    // fm6353_regtype89: P10 - FM6353 - 1/2
    // Scan membership: Scan_2
    {
        89, 5,
        {
            {
                0x0000, 0x0170, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x0170, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x0170, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_89_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_90_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_90_INCLUDED
    // fm6353_regtype90: P10 - FM6353 - 1/2
    // Scan membership: Scan_2
    {
        90, 5,
        {
            {
                0x0001, 0x0170, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0170, 0x679c, 0x40f7, 0x0040
            },
            {
                0x8001, 0x0170, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_90_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_167_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_167_INCLUDED
    // fm6353_regtype167: FM6353 register profile
    // Scan membership: Scan_2
    {
        167, 5,
        {
            {
                0x0001, 0x0170, 0x7fb2, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0170, 0x67b2, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0170, 0x5fb2, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_167_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_168_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_168_INCLUDED
    // fm6353_regtype168: FM6353 register profile
    // Scan membership: Scan_2
    {
        168, 5,
        {
            {
                0x0001, 0x0170, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0170, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0170, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_168_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_2_H
