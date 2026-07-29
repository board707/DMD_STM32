#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_64_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_64_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_DP3264
#error "Register-test profile fragment is in the wrong chip array"
#endif

#ifndef DMD_SPWM_DP3264_REGTYPE_9_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_9_INCLUDED
    // dp3264_regtype9: P1.25 - DP3265 - 5368 - 1/64
    // Chip family aliases: DP3265
    // Scan membership: Scan_64; GrayDepth: 12 bits
    {
        9, 13,
        {
            {
                0x023f, 0x0310, 0x041f, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x023f, 0x0310, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x023f, 0x0310, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_9_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_10_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_10_INCLUDED
    // dp3264_regtype10: P1.25 - DP3265 - DP32020 - 1/64
    // Chip family aliases: DP3265
    // Scan membership: Scan_64; GrayDepth: 13 bits
    {
        10, 13,
        {
            {
                0x023f, 0x033f, 0x041d, 0x0504, 0x0642, 0x0708, 0x087f, 0x0960,
                0x0abe, 0x0b28, 0x0c9a, 0x0d08, 0x1100
            },
            {
                0x023f, 0x033f, 0x041d, 0x0504, 0x0642, 0x0709, 0x087f, 0x0960,
                0x0abe, 0x0b2b, 0x0c9a, 0x0d12, 0x1100
            },
            {
                0x023f, 0x033f, 0x041d, 0x0504, 0x0642, 0x0709, 0x087f, 0x0960,
                0x0abe, 0x0b31, 0x0c9a, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_10_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_11_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_11_INCLUDED
    // dp3264_regtype11: P1.25 - 3264 - 1/64
    // Chip family aliases: 3264
    // Scan membership: Scan_64; GrayDepth: 13 bits
    {
        11, 13,
        {
            {
                0x023f, 0x033f, 0x041f, 0x0504, 0x0642, 0x0708, 0x08b9, 0x0960,
                0x0abe, 0x0b28, 0x0c18, 0x0d08, 0x1100
            },
            {
                0x023f, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08b9, 0x0960,
                0x0abe, 0x0b2b, 0x0c18, 0x0d12, 0x1100
            },
            {
                0x023f, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08b9, 0x0960,
                0x0abe, 0x0b31, 0x0c18, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_11_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_76_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_76_INCLUDED
    // dp3264_regtype76: P? - 3264 - 32020 - 1/64
    // Chip family aliases: 3264
    // Scan membership: Scan_64; GrayDepth: 13 bits
    {
        76, 13,
        {
            {
                0x023f, 0x032c, 0x041f, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x023f, 0x032c, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x023f, 0x032c, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_76_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_77_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_77_INCLUDED
    // dp3264_regtype77: P? - 3264 - 5368 - 1/64
    // Chip family aliases: 3264
    // Scan membership: Scan_64; GrayDepth: 13 bits
    {
        77, 13,
        {
            {
                0x023f, 0x0337, 0x041f, 0x0504, 0x064a, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c08, 0x0d08, 0x1100
            },
            {
                0x023f, 0x0337, 0x041f, 0x0504, 0x064a, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c08, 0x0d12, 0x1100
            },
            {
                0x023f, 0x0337, 0x041f, 0x0504, 0x064a, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c08, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_77_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_78_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_78_INCLUDED
    // dp3264_regtype78: P? - 3264 - 32020 - 1/64
    // Chip family aliases: 3256, 3264
    // Scan membership: Scan_64; GrayDepth: 13 bits
    {
        78, 13,
        {
            {
                0x023f, 0x033f, 0x0415, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x023f, 0x033f, 0x0415, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x023f, 0x033f, 0x0415, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_78_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_79_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_79_INCLUDED
    // dp3264_regtype79: P? - 3264 - 32020 - 1/64
    // Chip family aliases: 3264
    // Scan membership: Scan_64; GrayDepth: 13 bits
    {
        79, 13,
        {
            {
                0x023f, 0x033f, 0x0414, 0x0506, 0x0642, 0x0700, 0x08ff, 0x0960,
                0x0abe, 0x0b28, 0x0c0a, 0x0d08, 0x1180
            },
            {
                0x023f, 0x033f, 0x0414, 0x0503, 0x0642, 0x0700, 0x08ff, 0x0960,
                0x0abe, 0x0b2b, 0x0c0a, 0x0d0e, 0x1180
            },
            {
                0x023f, 0x033f, 0x0414, 0x0505, 0x0642, 0x0700, 0x08ff, 0x0960,
                0x0abe, 0x0b38, 0x0c0a, 0x0d12, 0x1180
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_79_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_80_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_80_INCLUDED
    // dp3264_regtype80: P? - 3265B - 32020 - 1/64
    // Chip family aliases: 3265B
    // Scan membership: Scan_64; GrayDepth: 13 bits
    {
        80, 13,
        {
            {
                0x023f, 0x033f, 0x0417, 0x0504, 0x064a, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x023f, 0x033f, 0x0417, 0x0504, 0x064a, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x023f, 0x033f, 0x0417, 0x0504, 0x064a, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_80_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_81_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_81_INCLUDED
    // dp3264_regtype81: P? - 3264 - 32020 - 1/64
    // Chip family aliases: 3264, 3364, DP3364
    // Scan membership: Scan_64; GrayDepth: 13 bits
    {
        81, 13,
        {
            {
                0x023f, 0x033f, 0x0416, 0x0506, 0x0642, 0x0700, 0x08ff, 0x0960,
                0x0abe, 0x0b28, 0x0c0a, 0x0d08, 0x1180
            },
            {
                0x023f, 0x033f, 0x0416, 0x0503, 0x0642, 0x0700, 0x08ff, 0x0960,
                0x0abe, 0x0b2b, 0x0c0a, 0x0d0e, 0x1180
            },
            {
                0x023f, 0x033f, 0x0416, 0x0505, 0x0642, 0x0700, 0x08ff, 0x0960,
                0x0abe, 0x0b38, 0x0c0a, 0x0d12, 0x1180
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_81_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_98_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_98_INCLUDED
    // dp3264_regtype98: P2.5 - DP3264S - DP32020B - 1/64
    // Chip family aliases: DP3264S
    // Scan membership: Scan_64; GrayDepth: 13 bits
    {
        98, 13,
        {
            {
                0x023f, 0x033f, 0x0411, 0x0500, 0x0629, 0x0708, 0x08f4, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x023f, 0x033f, 0x0411, 0x0502, 0x0629, 0x0709, 0x08f3, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x023f, 0x033f, 0x0411, 0x0504, 0x0629, 0x0709, 0x08f6, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_98_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_110_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_110_INCLUDED
    // dp3264_regtype110: P? - 3264 - 5366 - 1/64
    // Chip family aliases: 3264
    // Scan membership: Scan_64; GrayDepth: 13 bits
    {
        110, 13,
        {
            {
                0x023f, 0x033f, 0x041f, 0x0504, 0x0639, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c08, 0x0d08, 0x1100
            },
            {
                0x023f, 0x033f, 0x041f, 0x0504, 0x0639, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c08, 0x0d12, 0x1100
            },
            {
                0x023f, 0x033f, 0x041f, 0x0504, 0x0639, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c08, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_110_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_64_H
