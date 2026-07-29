#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_32_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_32_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_DP3264
#error "Register-test profile fragment is in the wrong chip array"
#endif

#ifndef DMD_SPWM_DP3264_REGTYPE_5_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_5_INCLUDED
    // dp3264_regtype5: P? - 3264 - 32020 - 1/32
    // Chip family aliases: 3264
    // Scan membership: Scan_32; GrayDepth: 13 bits
    {
        5, 13,
        {
            {
                0x021f, 0x033f, 0x041e, 0x0504, 0x061a, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x021f, 0x033f, 0x041e, 0x0504, 0x061a, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x021f, 0x033f, 0x041e, 0x0504, 0x061a, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_5_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_24_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_24_INCLUDED
    // dp3264_regtype24: P1.875 - 3265 - 6158 - 1/32
    // Chip family aliases: 3265
    // Scan membership: Scan_32; GrayDepth: 13 bits
    {
        24, 13,
        {
            {
                0x021f, 0x033f, 0x041f, 0x0504, 0x0619, 0x0709, 0x0871, 0x0960,
                0x0abe, 0x0b0c, 0x0c98, 0x0d0c, 0x1100
            },
            {
                0x021f, 0x033f, 0x041f, 0x0504, 0x0619, 0x0709, 0x0869, 0x0960,
                0x0abe, 0x0b12, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x021f, 0x033f, 0x041f, 0x0504, 0x0619, 0x0709, 0x086c, 0x0960,
                0x0abe, 0x0b18, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_24_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_25_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_25_INCLUDED
    // dp3264_regtype25: P1.875 - 3265 - 6158 - 1/32
    // Chip family aliases: 3265
    // Scan membership: Scan_32; GrayDepth: 13 bits
    {
        25, 13,
        {
            {
                0x021f, 0x033f, 0x041f, 0x0504, 0x0642, 0x0708, 0x08bd, 0x0960,
                0x0afe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x021f, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08f3, 0x0960,
                0x0afe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x021f, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bc, 0x0960,
                0x0afe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_25_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_33_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_33_INCLUDED
    // dp3264_regtype33: P2 - 3264S - 32019 - 1/32
    // Chip family aliases: 3264S, 3265
    // Scan membership: Scan_32; GrayDepth: 13 bits
    {
        33, 13,
        {
            {
                0x021f, 0x033f, 0x041f, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x021f, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x021f, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_33_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_42_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_42_INCLUDED
    // dp3264_regtype42: P2.5 - 3265 - 7258 - 1/32
    // Chip family aliases: 3265
    // Scan membership: Scan_32; GrayDepth: 14 bits
    {
        42, 13,
        {
            {
                0x021f, 0x033f, 0x0428, 0x0503, 0x0629, 0x07b0, 0x08f9, 0x0960,
                0x0afe, 0x0b08, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x021f, 0x033f, 0x0428, 0x0507, 0x0629, 0x07c0, 0x08bb, 0x0960,
                0x0afe, 0x0b08, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x021f, 0x033f, 0x0428, 0x0509, 0x0629, 0x07e9, 0x08af, 0x0960,
                0x0afe, 0x0b0e, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_42_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_43_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_43_INCLUDED
    // dp3264_regtype43: P2.5 - 3265 - 7268 - 1/32
    // Chip family aliases: 3265
    // Scan membership: Scan_32; GrayDepth: 13 bits
    {
        43, 13,
        {
            {
                0x021f, 0x033f, 0x041f, 0x0504, 0x0629, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c18, 0x0d08, 0x1100
            },
            {
                0x021f, 0x033f, 0x041f, 0x0504, 0x0629, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c18, 0x0d12, 0x1100
            },
            {
                0x021f, 0x033f, 0x041f, 0x0504, 0x0629, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c18, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_43_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_73_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_73_INCLUDED
    // dp3264_regtype73: P? - 3256 - 32020 - 1/32
    // Chip family aliases: 3256, 3264
    // Scan membership: Scan_32; GrayDepth: 13 bits
    {
        73, 13,
        {
            {
                0x021f, 0x033f, 0x041f, 0x0504, 0x062a, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x021f, 0x033f, 0x041f, 0x0504, 0x062a, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x021f, 0x033f, 0x041f, 0x0504, 0x062a, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_73_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_74_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_74_INCLUDED
    // dp3264_regtype74: P? - 3256 - 32020 - 1/32
    // Chip family aliases: 3256
    // Scan membership: Scan_32; GrayDepth: 14 bits
    {
        74, 13,
        {
            {
                0x021f, 0x033f, 0x042f, 0x0526, 0x0633, 0x0700, 0x08b6, 0x0960,
                0x0ab6, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x021f, 0x033f, 0x042f, 0x0502, 0x0633, 0x0700, 0x08b6, 0x0960,
                0x0ab6, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x021f, 0x033f, 0x042f, 0x0506, 0x0633, 0x0700, 0x08b6, 0x0960,
                0x0ab6, 0x0b38, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_74_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_75_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_75_INCLUDED
    // dp3264_regtype75: P? - 3264 - 5158 - 1/32
    // Chip family aliases: 3264
    // Scan membership: Scan_32; GrayDepth: 14 bits
    {
        75, 13,
        {
            {
                0x021f, 0x033f, 0x042c, 0x0500, 0x0629, 0x0708, 0x08f4, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x021f, 0x033f, 0x042c, 0x0504, 0x0629, 0x0709, 0x08f4, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x021f, 0x033f, 0x042c, 0x0504, 0x0629, 0x0709, 0x08f4, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_75_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_82_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_82_INCLUDED
    // dp3264_regtype82: P? - 3256S - 32020 - 1/32
    // Chip family aliases: 3256S
    // Scan membership: Scan_32; GrayDepth: 14 bits
    {
        82, 13,
        {
            {
                0x021f, 0x033f, 0x0438, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c08, 0x0d08, 0x1100
            },
            {
                0x021f, 0x033f, 0x0438, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c08, 0x0d12, 0x1100
            },
            {
                0x021f, 0x033f, 0x0438, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c08, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_82_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_83_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_83_INCLUDED
    // dp3264_regtype83: P? - 3256 - 32020 - 1/32
    // Chip family aliases: 3256, 3364
    // Scan membership: Scan_32; GrayDepth: 14 bits
    {
        83, 13,
        {
            {
                0x021f, 0x033f, 0x043f, 0x0504, 0x064a, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x021f, 0x033f, 0x043f, 0x0504, 0x064a, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x021f, 0x033f, 0x043f, 0x0504, 0x064a, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_83_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_90_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_90_INCLUDED
    // dp3264_regtype90: P? - DP3264 - DP32019 - 1/32
    // Chip family aliases: DP3264
    // Scan membership: Scan_32; GrayDepth: 13 bits
    {
        90, 13,
        {
            {
                0x021f, 0x033f, 0x041f, 0x0504, 0x0621, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x021f, 0x033f, 0x041f, 0x0504, 0x0621, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x021f, 0x033f, 0x041f, 0x0504, 0x0621, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_90_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_109_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_109_INCLUDED
    // dp3264_regtype109: P? - 3264 - 32019 - 1/32
    // Chip family aliases: 3264
    // Scan membership: Scan_32; GrayDepth: 14 bits
    {
        109, 13,
        {
            {
                0x021f, 0x033f, 0x0436, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0910,
                0x0a3e, 0x0b8f, 0x0c98, 0x0d02, 0x1100
            },
            {
                0x021f, 0x033f, 0x0436, 0x0504, 0x0642, 0x07b0, 0x08bf, 0x0901,
                0x0a3e, 0x0b2b, 0x0c98, 0x0d0a, 0x1100
            },
            {
                0x021f, 0x033f, 0x0436, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0901,
                0x0a3e, 0x0b31, 0x0c98, 0x0d0f, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_109_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_32_H
