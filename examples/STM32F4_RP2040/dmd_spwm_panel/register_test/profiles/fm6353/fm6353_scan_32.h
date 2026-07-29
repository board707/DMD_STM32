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
    // fm6353_regtype2: P2.5 - FM6353 - 7559 - 1/32
    // Scan membership: Scan_32
    {
        2, 5,
        {
            {
                0x0000, 0x1fb8, 0x639c, 0x40f7, 0x0070
            },
            {
                0x0000, 0x1fb8, 0x4b9c, 0x40f7, 0x0070
            },
            {
                0x0000, 0x1fb8, 0x439c, 0x40f7, 0x0070
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_2_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_3_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_3_INCLUDED
    // fm6353_regtype3: P3 - FM6353 - 74HC138 - 1/32
    // Scan membership: Scan_32
    {
        3, 5,
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
#endif  // DMD_SPWM_FM6353_REGTYPE_3_INCLUDED

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

#ifndef DMD_SPWM_FM6353_REGTYPE_5_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_5_INCLUDED
    // fm6353_regtype5: P? - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        5, 5,
        {
            {
                0x0000, 0x1ff8, 0x679a, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff8, 0x4b9a, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff8, 0x439a, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_5_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_6_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_6_INCLUDED
    // fm6353_regtype6: P1.6 - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        6, 5,
        {
            {
                0x0000, 0x5ff8, 0x539c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x5ff8, 0x5b9c, 0x4007, 0x4040
            },
            {
                0x0000, 0x5ff8, 0x5f9c, 0x4007, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_6_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_7_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_7_INCLUDED
    // fm6353_regtype7: P2.5 - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        7, 5,
        {
            {
                0x0000, 0x1f70, 0x5f9c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1f70, 0x539c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1f70, 0x579c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_7_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_8_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_8_INCLUDED
    // fm6353_regtype8: P1.25 - FM6353 - 5958 - 1/32
    // Scan membership: Scan_32
    {
        8, 5,
        {
            {
                0x0000, 0x5f70, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x5f70, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x5f70, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_8_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_9_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_9_INCLUDED
    // fm6353_regtype9: P2.5 - FM6353 - 5166 - 1/32
    // Scan membership: Scan_32
    {
        9, 5,
        {
            {
                0x0000, 0x1f70, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1f70, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1f70, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_9_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_12_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_12_INCLUDED
    // fm6353_regtype12: P4 - FM6353 - RUC7258D - 1/32
    // Scan membership: Scan_32
    {
        12, 5,
        {
            {
                0x0001, 0x1ff8, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1ff8, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1ff8, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_12_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_15_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_15_INCLUDED
    // fm6353_regtype15: P? - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        15, 5,
        {
            {
                0x0001, 0x1ff0, 0x62c7, 0x4047, 0x4000
            },
            {
                0x0001, 0x1ff0, 0x5293, 0x4027, 0x4000
            },
            {
                0x0001, 0x1ff0, 0x358d, 0x4037, 0x4000
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_15_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_16_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_16_INCLUDED
    // fm6353_regtype16: P? - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        16, 5,
        {
            {
                0x0001, 0x1ff0, 0x6ed2, 0x40f7, 0x4040
            },
            {
                0x0001, 0x1ff0, 0x6292, 0x40d7, 0x4040
            },
            {
                0x0001, 0x1ff0, 0x3eb8, 0x40c7, 0x4050
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_16_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_19_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_19_INCLUDED
    // fm6353_regtype19: P? - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        19, 5,
        {
            {
                0x0000, 0x1ff0, 0x0f55, 0x40f7, 0x0000
            },
            {
                0x0000, 0x1ff0, 0x3327, 0x40e7, 0x4000
            },
            {
                0x0000, 0x1ff0, 0x32b6, 0x40b7, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_19_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_21_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_21_INCLUDED
    // fm6353_regtype21: P? - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        21, 5,
        {
            {
                0x0000, 0x1ff8, 0x76e0, 0x40f7, 0x0070
            },
            {
                0x0000, 0x1ff8, 0x66c6, 0x40f7, 0x0060
            },
            {
                0x0000, 0x1ff8, 0x62aa, 0x40f7, 0x0060
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_21_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_23_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_23_INCLUDED
    // fm6353_regtype23: P? - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        23, 5,
        {
            {
                0x0000, 0x5ff0, 0x3f4e, 0x4007, 0x0000
            },
            {
                0x0000, 0x5ff0, 0x3334, 0x4007, 0x4000
            },
            {
                0x0000, 0x5ff0, 0x234e, 0x4007, 0x4000
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_23_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_24_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_24_INCLUDED
    // fm6353_regtype24: P? - FM6353 - 74HC138 - 1/32
    // Scan membership: Scan_32
    {
        24, 5,
        {
            {
                0x0000, 0x1ff8, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff8, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff8, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_24_INCLUDED

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

#ifndef DMD_SPWM_FM6353_REGTYPE_27_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_27_INCLUDED
    // fm6353_regtype27: P? - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        27, 5,
        {
            {
                0x0000, 0x1ff8, 0x5b9d, 0x40c7, 0x4000
            },
            {
                0x0000, 0x1ff8, 0x439d, 0x4047, 0x4040
            },
            {
                0x0000, 0x1ff8, 0x339d, 0x4007, 0x4000
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_27_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_33_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_33_INCLUDED
    // fm6353_regtype33: P? - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        33, 5,
        {
            {
                0x0000, 0x1ff8, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff8, 0x639d, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff8, 0x5b9d, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_33_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_34_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_34_INCLUDED
    // fm6353_regtype34: P? - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        34, 5,
        {
            {
                0x0000, 0x1ff0, 0x7f98, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff0, 0x6798, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff0, 0x5f98, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_34_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_37_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_37_INCLUDED
    // fm6353_regtype37: P? - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        37, 5,
        {
            {
                0x0000, 0x1ff0, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff0, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff0, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_37_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_45_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_45_INCLUDED
    // fm6353_regtype45: P? - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        45, 5,
        {
            {
                0x0000, 0x1ff0, 0x7f9a, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff0, 0x679a, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff0, 0x5f9a, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_45_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_60_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_60_INCLUDED
    // fm6353_regtype60: P? - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        60, 5,
        {
            {
                0x0001, 0x1ff8, 0x7f8c, 0x40f7, 0x4000
            },
            {
                0x0001, 0x1ff8, 0x738d, 0x4027, 0x0070
            },
            {
                0x0001, 0x1ff8, 0x678d, 0x4017, 0x0070
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_60_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_61_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_61_INCLUDED
    // fm6353_regtype61: P? - FM6353 - ICN2012 - 1/32
    // Scan membership: Scan_32
    {
        61, 5,
        {
            {
                0x0001, 0x1ff8, 0x7f9d, 0x4017, 0x0040
            },
            {
                0x0001, 0x1ff8, 0x679d, 0x4017, 0x0070
            },
            {
                0x0001, 0x1ff8, 0x5f9d, 0x4017, 0x0070
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_61_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_71_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_71_INCLUDED
    // fm6353_regtype71: P? - FM6353 - 74HC138 - 1/32
    // Scan membership: Scan_32
    {
        71, 5,
        {
            {
                0x0000, 0x1ff8, 0x5380, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff8, 0x3f62, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff8, 0x376a, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_71_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_72_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_72_INCLUDED
    // fm6353_regtype72: P? - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        72, 5,
        {
            {
                0x0001, 0x1ff0, 0x62e0, 0x40f7, 0x4040
            },
            {
                0x0001, 0x1ff0, 0x3ece, 0x40b7, 0x4040
            },
            {
                0x0001, 0x1ff0, 0x36a0, 0x4077, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_72_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_82_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_82_INCLUDED
    // fm6353_regtype82: P? - FM6353 - 74HC138 - 1/32
    // Scan membership: Scan_32
    {
        82, 5,
        {
            {
                0x0000, 0x1ff8, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff8, 0x739c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff8, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_82_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_83_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_83_INCLUDED
    // fm6353_regtype83: P1.2 - FM6353 - 5958 - 1/32
    // Scan membership: Scan_32
    {
        83, 5,
        {
            {
                0xffff, 0x1fb8, 0x5f05, 0x40f7, 0x0000
            },
            {
                0xffff, 0x1fb8, 0x3ae9, 0x4007, 0x4040
            },
            {
                0xffff, 0x1fb8, 0x32e9, 0x4007, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_83_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_91_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_91_INCLUDED
    // fm6353_regtype91: P2 - FM6353 - 5958 - 1/32
    // Scan membership: Scan_32
    {
        91, 5,
        {
            {
                0x0001, 0x1ff8, 0x5768, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1ff8, 0x4372, 0x4017, 0x4040
            },
            {
                0x0001, 0x1ff8, 0x2f72, 0x4017, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_91_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_92_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_92_INCLUDED
    // fm6353_regtype92: P2 - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        92, 5,
        {
            {
                0x0001, 0x1f70, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1f70, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1f70, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_92_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_93_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_93_INCLUDED
    // fm6353_regtype93: P2.5 - FM6353 - 74HC138 - 1/32
    // Scan membership: Scan_32
    {
        93, 5,
        {
            {
                0x0000, 0x1ff8, 0x7f54, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff8, 0x7b5a, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff8, 0x6770, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_93_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_95_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_95_INCLUDED
    // fm6353_regtype95: P2.5 - FM6353 - 5166 - 1/32
    // Scan membership: Scan_32
    {
        95, 5,
        {
            {
                0x0001, 0x1ff8, 0x7ffe, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1ff8, 0x67fe, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1ff8, 0x5ffe, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_95_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_96_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_96_INCLUDED
    // fm6353_regtype96: P2.5 - FM6353 - 5166 - 1/32
    // Scan membership: Scan_32
    {
        96, 5,
        {
            {
                0x0000, 0x1f70, 0x7ffe, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1f70, 0x67fe, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1f70, 0x5ffe, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_96_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_97_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_97_INCLUDED
    // fm6353_regtype97: P2.5 - FM6353 - 5166 - 1/32
    // Scan membership: Scan_32
    {
        97, 5,
        {
            {
                0x0001, 0x1f70, 0x7ffe, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1f70, 0x67fe, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1f70, 0x5ffe, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_97_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_98_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_98_INCLUDED
    // fm6353_regtype98: P2.5 - FM6353 - 5166 - 1/32
    // Scan membership: Scan_32
    {
        98, 5,
        {
            {
                0x0000, 0x1ff8, 0x7ffe, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff8, 0x67fe, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff8, 0x5ffe, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_98_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_99_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_99_INCLUDED
    // fm6353_regtype99: P2.5 - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        99, 5,
        {
            {
                0x0000, 0x1f70, 0x7ffe, 0x4007, 0x0040
            },
            {
                0x0000, 0x1f70, 0x67fe, 0x4007, 0x0040
            },
            {
                0x0000, 0x1f70, 0x5ffe, 0x4007, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_99_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_102_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_102_INCLUDED
    // fm6353_regtype102: P3 - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        102, 5,
        {
            {
                0x0001, 0x1ff8, 0x4f3a, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1ff8, 0x434c, 0x4017, 0x4040
            },
            {
                0x0001, 0x1ff8, 0x2f72, 0x4017, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_102_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_103_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_103_INCLUDED
    // fm6353_regtype103: P3 - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        103, 5,
        {
            {
                0xffff, 0x1f70, 0x7ffe, 0x40f7, 0x0040
            },
            {
                0xffff, 0x1f70, 0x67fe, 0x40f7, 0x0040
            },
            {
                0xffff, 0x1f70, 0x5ffe, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_103_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_120_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_120_INCLUDED
    // fm6353_regtype120: P3 - FM6353 - RUC7258D - 1/32
    // Scan membership: Scan_32
    {
        120, 5,
        {
            {
                0x0001, 0x1ff0, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1ff0, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1ff0, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_120_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_130_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_130_INCLUDED
    // fm6353_regtype130: P? - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        130, 5,
        {
            {
                0x0001, 0x1f70, 0x7fd4, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1f70, 0x672a, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1f70, 0x5ec6, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_130_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_135_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_135_INCLUDED
    // fm6353_regtype135: P? - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        135, 5,
        {
            {
                0x0001, 0x1ff8, 0x5b9d, 0x40c7, 0x4000
            },
            {
                0x0001, 0x1ff8, 0x439d, 0x4047, 0x4040
            },
            {
                0x0001, 0x1ff8, 0x339d, 0x4007, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_135_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_140_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_140_INCLUDED
    // fm6353_regtype140: P? - FM6353 - 74HC138 - 1/32
    // Scan membership: Scan_32
    {
        140, 5,
        {
            {
                0x0001, 0x1ff8, 0x6795, 0x40f7, 0x0000
            },
            {
                0x0001, 0x1ff8, 0x3f75, 0x4007, 0x4000
            },
            {
                0x0001, 0x1ff8, 0x377f, 0x40f7, 0x0000
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_140_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_142_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_142_INCLUDED
    // fm6353_regtype142: P? - FM6353 - 74HC138 - 1/32
    // Scan membership: Scan_32
    {
        142, 5,
        {
            {
                0x0000, 0x1ff8, 0x5391, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff8, 0x3f95, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff8, 0x3785, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_142_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_146_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_146_INCLUDED
    // fm6353_regtype146: P? - FM6353 - 74HC138 - 1/32
    // Scan membership: Scan_32
    {
        146, 5,
        {
            {
                0x0000, 0x1ff8, 0x52fa, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff8, 0x3ee8, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff8, 0x36ec, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_146_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_151_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_151_INCLUDED
    // fm6353_regtype151: P? - FM6353 - 74HC138 - 1/32
    // Scan membership: Scan_32
    {
        151, 5,
        {
            {
                0x0000, 0x1ff8, 0x53d1, 0x40f7, 0x4040
            },
            {
                0x0000, 0x1ff8, 0x37a3, 0x40f7, 0x4040
            },
            {
                0x0000, 0x1ff8, 0x2bc3, 0x40f7, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_151_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_152_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_152_INCLUDED
    // fm6353_regtype152: P2 - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        152, 5,
        {
            {
                0x0000, 0x1ff8, 0x735c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff8, 0x3f54, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1ff8, 0x375a, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_152_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_155_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_155_INCLUDED
    // fm6353_regtype155: P2.5 - FM6353 - 1/32
    // Scan membership: Scan_32
    {
        155, 5,
        {
            {
                0x0001, 0x1f70, 0x7f9a, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1f70, 0x679a, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1f70, 0x5f9a, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_155_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_158_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_158_INCLUDED
    // fm6353_regtype158: P? - FM6353 - 74HC138 - 1/32
    // Scan membership: Scan_32
    {
        158, 5,
        {
            {
                0x0000, 0x1f70, 0xff80, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1f70, 0xf380, 0x40f7, 0x0050
            },
            {
                0x0000, 0x1f70, 0xdf80, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_158_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_164_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_164_INCLUDED
    // fm6353_regtype164: FM6353 register profile
    // Scan membership: Scan_32
    {
        164, 5,
        {
            {
                0x0001, 0x1f70, 0x7ffe, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1f70, 0x67dc, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1f70, 0x5f18, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_164_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_166_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_166_INCLUDED
    // fm6353_regtype166: FM6353 register profile
    // Scan membership: Scan_32
    {
        166, 5,
        {
            {
                0x0001, 0x1ff8, 0x6ec0, 0x40f7, 0x4040
            },
            {
                0x0001, 0x1ff8, 0x61fc, 0x40d7, 0x4040
            },
            {
                0x0001, 0x1ff8, 0x3ea0, 0x40c7, 0x4050
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_166_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_171_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_171_INCLUDED
    // fm6353_regtype171: FM6353 register profile
    // Scan membership: Scan_32
    {
        171, 5,
        {
            {
                0x0001, 0x1f70, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1f70, 0x679c, 0x40f7, 0x0070
            },
            {
                0x0001, 0x1f70, 0x5f9c, 0x40f7, 0x0070
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_171_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_176_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_176_INCLUDED
    // fm6353_regtype176: FM6353 register profile
    // Scan membership: Scan_32
    {
        176, 5,
        {
            {
                0x0000, 0x5f70, 0x7f00, 0x0007, 0x4000
            },
            {
                0x0000, 0x5f70, 0x6700, 0x0007, 0x4000
            },
            {
                0x0000, 0x5f70, 0x5f00, 0x0007, 0x4000
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_176_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_187_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_187_INCLUDED
    // fm6353_regtype187: FM6353 register profile
    // Scan membership: Scan_32
    {
        187, 5,
        {
            {
                0x0000, 0x1f70, 0x7f98, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1f70, 0x7398, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1f70, 0x5f98, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_187_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_32_H
