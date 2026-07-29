#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_26_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_26_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6353 register profiles. Only Scan_26 profiles are present.

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

#ifndef DMD_SPWM_FM6353_REGTYPE_20_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_20_INCLUDED
    // fm6353_regtype20: P? - FM6353 - 1/26
    // Scan membership: Scan_26
    {
        20, 5,
        {
            {
                0x0000, 0x59f8, 0x5294, 0x40f7, 0x0000
            },
            {
                0x0000, 0x59f8, 0x3dec, 0x40f7, 0x0000
            },
            {
                0x0000, 0x59f8, 0x5dca, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_20_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_28_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_28_INCLUDED
    // fm6353_regtype28: P? - FM6353 - 1/26
    // Scan membership: Scan_26
    {
        28, 5,
        {
            {
                0x0000, 0x1970, 0x7f67, 0x40f7, 0x0000
            },
            {
                0x0000, 0x1970, 0x678c, 0x40f7, 0x0000
            },
            {
                0x0000, 0x1970, 0x5f16, 0x40f7, 0x0000
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_28_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_36_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_36_INCLUDED
    // fm6353_regtype36: P? - FM6353 - 1/26
    // Scan membership: Scan_26
    {
        36, 5,
        {
            {
                0x0001, 0x19f0, 0x779c, 0x0007, 0x0040
            },
            {
                0x0001, 0x19f0, 0x5f9c, 0x0007, 0x0040
            },
            {
                0x0001, 0x19f0, 0x539c, 0x0007, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_36_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_38_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_38_INCLUDED
    // fm6353_regtype38: P? - FM6353 - 1/26
    // Scan membership: Scan_26
    {
        38, 5,
        {
            {
                0x0000, 0x1970, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1970, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1970, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_38_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_39_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_39_INCLUDED
    // fm6353_regtype39: P? - FM6353 - 1/26
    // Scan membership: Scan_26
    {
        39, 5,
        {
            {
                0x0001, 0x19f8, 0x4b9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x19f8, 0x439d, 0x40f7, 0x0040
            },
            {
                0x0001, 0x19f8, 0x3b9d, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_39_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_41_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_41_INCLUDED
    // fm6353_regtype41: P? - FM6353 - 1/26
    // Scan membership: Scan_26
    {
        41, 5,
        {
            {
                0x0000, 0x1970, 0x739d, 0x00f7, 0x0040
            },
            {
                0x0000, 0x1970, 0x779d, 0x00f7, 0x0040
            },
            {
                0x0000, 0x1970, 0x5f9d, 0x00f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_41_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_42_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_42_INCLUDED
    // fm6353_regtype42: P? - FM6353 - 1/26
    // Scan membership: Scan_26
    {
        42, 5,
        {
            {
                0x0001, 0x1970, 0x7f96, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1970, 0x6796, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1970, 0x5f96, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_42_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_44_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_44_INCLUDED
    // fm6353_regtype44: P? - FM6353 - 1/26
    // Scan membership: Scan_26
    {
        44, 5,
        {
            {
                0x0000, 0x19f0, 0x7f9a, 0x40f7, 0x0040
            },
            {
                0x0000, 0x19f0, 0x679a, 0x40f7, 0x0040
            },
            {
                0x0000, 0x19f0, 0x5f9a, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_44_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_48_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_48_INCLUDED
    // fm6353_regtype48: P? - FM6353 - 1/26
    // Scan membership: Scan_26
    {
        48, 5,
        {
            {
                0x0001, 0x19f0, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x19f0, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x19f0, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_48_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_49_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_49_INCLUDED
    // fm6353_regtype49: P? - FM6353 - 1/26
    // Scan membership: Scan_26
    {
        49, 5,
        {
            {
                0x0001, 0x19f0, 0x739c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x19f0, 0x5f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x19f0, 0x539c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_49_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_86_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_86_INCLUDED
    // fm6353_regtype86: P1.53 - FM6353 - 1/26
    // Scan membership: Scan_26
    {
        86, 5,
        {
            {
                0x0000, 0x19f8, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x19f8, 0x679c, 0x40f7, 0x4040
            },
            {
                0x0000, 0x19f8, 0x5f9c, 0x40f7, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_86_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_87_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_87_INCLUDED
    // fm6353_regtype87: P1.538 - FM6353 - 5958 - 1/26
    // Scan membership: Scan_26
    {
        87, 5,
        {
            {
                0x0000, 0x1970, 0x7f14, 0x40f7, 0x0050
            },
            {
                0x0000, 0x1970, 0x66d4, 0x40f7, 0x0050
            },
            {
                0x0000, 0x1970, 0x5ede, 0x40f7, 0x0050
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_87_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_104_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_104_INCLUDED
    // fm6353_regtype104: P3.076 - FM6353 - 1/26
    // Scan membership: Scan_26
    {
        104, 5,
        {
            {
                0x0001, 0x1970, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1970, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1970, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_104_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_136_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_136_INCLUDED
    // fm6353_regtype136: P? - FM6353 - 5958 - 1/26
    // Scan membership: Scan_26
    {
        136, 5,
        {
            {
                0x0001, 0x19f8, 0x6774, 0x00f7, 0x0040
            },
            {
                0x0001, 0x19f8, 0x5f38, 0x00f7, 0x0040
            },
            {
                0x0001, 0x19f8, 0x52d2, 0x00f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_136_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_26_H
