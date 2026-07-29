#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_43_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_43_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_DP3264
#error "Register-test profile fragment is in the wrong chip array"
#endif

#ifndef DMD_SPWM_DP3264_REGTYPE_2_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_2_INCLUDED
    // dp3264_regtype2: P1.86 - DP3264 - DP32020 - 1/43
    // Chip family aliases: DP3264
    // Scan membership: Scan_43; GrayDepth: 13 bits
    {
        2, 13,
        {
            {
                0x022a, 0x033f, 0x041f, 0x0505, 0x0642, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b88, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x022a, 0x033f, 0x041f, 0x0504, 0x0642, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b8a, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x022a, 0x033f, 0x041f, 0x0504, 0x0642, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b91, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_2_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_4_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_4_INCLUDED
    // dp3264_regtype4: P1.86 - 3265 - 5158 - 1/43
    // Chip family aliases: 3265
    // Scan membership: Scan_43; GrayDepth: 13 bits
    {
        4, 13,
        {
            {
                0x022a, 0x033f, 0x041f, 0x0504, 0x063b, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x022a, 0x033f, 0x041f, 0x0504, 0x063b, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x022a, 0x033f, 0x041f, 0x0504, 0x063b, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_4_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_8_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_8_INCLUDED
    // dp3264_regtype8: P? - DP3264 - DP32020 - 1/43
    // Chip family aliases: DP3264
    // Scan membership: Scan_43; GrayDepth: 14 bits
    {
        8, 13,
        {
            {
                0x022a, 0x033f, 0x0421, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x022a, 0x033f, 0x0421, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x022a, 0x033f, 0x0421, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_8_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_16_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_16_INCLUDED
    // dp3264_regtype16: P1.86 - 3265 - 32020 - 1/43
    // Chip family aliases: DP3264, 3264S, 3265
    // Scan membership: Scan_43; GrayDepth: 13 bits
    {
        16, 13,
        {
            {
                0x022a, 0x033f, 0x041f, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x022a, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x022a, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_16_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_17_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_17_INCLUDED
    // dp3264_regtype17: P1.86 - 3264 - 32020 - 1/43
    // Chip family aliases: 3264
    // Scan membership: Scan_43; GrayDepth: 14 bits
    {
        17, 13,
        {
            {
                0x022a, 0x033f, 0x0429, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x022a, 0x033f, 0x0429, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x022a, 0x033f, 0x0429, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_17_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_18_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_18_INCLUDED
    // dp3264_regtype18: P1.86 - 3265 - 32020 - 1/43
    // Chip family aliases: 3265
    // Scan membership: Scan_43; GrayDepth: 11 bits
    {
        18, 13,
        {
            {
                0x022a, 0x0302, 0x041f, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x022a, 0x0302, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x022a, 0x0302, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_18_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_19_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_19_INCLUDED
    // dp3264_regtype19: P1.86 - 3265 - 5158 - 1/43
    // Chip family aliases: 3265
    // Scan membership: Scan_43; GrayDepth: 13 bits
    {
        19, 13,
        {
            {
                0x022a, 0x033f, 0x041f, 0x0506, 0x062a, 0x0709, 0x08be, 0x0900,
                0x0afe, 0x0b0b, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x022a, 0x033f, 0x041f, 0x0502, 0x062a, 0x0709, 0x08f4, 0x0900,
                0x0afe, 0x0b0f, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x022a, 0x033f, 0x041f, 0x0502, 0x062a, 0x0709, 0x08f5, 0x0900,
                0x0afe, 0x0b13, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_19_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_20_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_20_INCLUDED
    // dp3264_regtype20: P1.86 - 3265 - 6158 - 1/43
    // Chip family aliases: 3265
    // Scan membership: Scan_43; GrayDepth: 13 bits
    {
        20, 13,
        {
            {
                0x022a, 0x033f, 0x041f, 0x0506, 0x0629, 0x0709, 0x08be, 0x0900,
                0x0afe, 0x0b0b, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x022a, 0x033f, 0x041f, 0x0502, 0x0629, 0x0709, 0x08f4, 0x0900,
                0x0afe, 0x0b0f, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x022a, 0x033f, 0x041f, 0x0502, 0x0629, 0x0709, 0x08f5, 0x0900,
                0x0afe, 0x0b13, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_20_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_21_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_21_INCLUDED
    // dp3264_regtype21: P1.86 - DP3265 - 1/43
    // Chip family aliases: DP3265
    // Scan membership: Scan_43; GrayDepth: 13 bits
    {
        21, 13,
        {
            {
                0x022a, 0x033f, 0x041f, 0x0505, 0x0622, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b88, 0x0c98, 0x0d48, 0x1100
            },
            {
                0x022a, 0x033f, 0x041f, 0x0504, 0x0622, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b8b, 0x0c98, 0x0d52, 0x1100
            },
            {
                0x022a, 0x033f, 0x041f, 0x0504, 0x0622, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b91, 0x0c98, 0x0d58, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_21_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_22_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_22_INCLUDED
    // dp3264_regtype22: P1.86 - DP3265 - 1/43
    // Chip family aliases: DP3265
    // Scan membership: Scan_43; GrayDepth: 13 bits
    {
        22, 13,
        {
            {
                0x022a, 0x033f, 0x041f, 0x0504, 0x0622, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x022a, 0x033f, 0x041f, 0x0504, 0x0622, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x022a, 0x033f, 0x041f, 0x0504, 0x0622, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_22_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_23_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_23_INCLUDED
    // dp3264_regtype23: P1.86 - DP3265 - 1/43
    // Chip family aliases: DP3265
    // Scan membership: Scan_43; GrayDepth: 13 bits
    {
        23, 13,
        {
            {
                0x022a, 0x033f, 0x041f, 0x0504, 0x0622, 0x0700, 0x08bd, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x022a, 0x033f, 0x041f, 0x0504, 0x0622, 0x0700, 0x08bc, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x022a, 0x033f, 0x041f, 0x0504, 0x0622, 0x0700, 0x08ba, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_23_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_72_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_72_INCLUDED
    // dp3264_regtype72: P? - 3264 - 1/43
    // Chip family aliases: 3264, DP3264
    // Scan membership: Scan_43; GrayDepth: 14 bits
    {
        72, 13,
        {
            {
                0x022a, 0x033f, 0x0427, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x022a, 0x033f, 0x0427, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x022a, 0x033f, 0x0427, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_72_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_100_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_100_INCLUDED
    // dp3264_regtype100: P? - DP3264 - 2018 - 1/43
    // Chip family aliases: DP3264
    // Scan membership: Scan_43; GrayDepth: 13 bits
    {
        100, 13,
        {
            {
                0x022a, 0x033f, 0x041f, 0x0505, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d01, 0x1100
            },
            {
                0x022a, 0x033f, 0x041f, 0x0530, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2d, 0x0c98, 0x0d0c, 0x1100
            },
            {
                0x022a, 0x033f, 0x041f, 0x0505, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d0c, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_100_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_105_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_105_INCLUDED
    // dp3264_regtype105: P1.86 - 3264 - 2018 - 1/43
    // Chip family aliases: 3264
    // Scan membership: Scan_43; GrayDepth: 14 bits
    {
        105, 13,
        {
            {
                0x022a, 0x0339, 0x042b, 0x0504, 0x0631, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x022a, 0x0339, 0x042b, 0x0504, 0x0631, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x022a, 0x0339, 0x042b, 0x0504, 0x0631, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_105_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_43_H
