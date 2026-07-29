#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_40_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_40_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_DP3264
#error "Register-test profile fragment is in the wrong chip array"
#endif

#ifndef DMD_SPWM_DP3264_REGTYPE_34_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_34_INCLUDED
    // dp3264_regtype34: P2 - 3264 - 32020 - 1/40
    // Chip family aliases: 3264
    // Scan membership: Scan_40; GrayDepth: 13 bits
    {
        34, 13,
        {
            {
                0x0227, 0x033f, 0x0418, 0x0504, 0x061a, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0227, 0x033f, 0x0418, 0x0504, 0x061a, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0227, 0x033f, 0x0418, 0x0504, 0x061a, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_34_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_35_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_35_INCLUDED
    // dp3264_regtype35: P2 - 3264S - 32020 - 1/40
    // Chip family aliases: DP3264, 3264S
    // Scan membership: Scan_40; GrayDepth: 13 bits
    {
        35, 13,
        {
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_35_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_39_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_39_INCLUDED
    // dp3264_regtype39: P2 - 3264 - 32020 - 1/40
    // Chip family aliases: 3264
    // Scan membership: Scan_40; GrayDepth: 13 bits
    {
        39, 13,
        {
            {
                0x0227, 0x033f, 0x041f, 0x0506, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c9a, 0x0d08, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c9a, 0x0d12, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c9a, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_39_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_40_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_40_INCLUDED
    // dp3264_regtype40: P2 - DP3264 - 1/40
    // Chip family aliases: DP3264
    // Scan membership: Scan_40; GrayDepth: 13 bits
    {
        40, 13,
        {
            {
                0x0227, 0x033f, 0x0416, 0x0548, 0x0622, 0x0708, 0x086d, 0x0960,
                0x0abe, 0x0b2d, 0x0c0a, 0x0d0c, 0x1100
            },
            {
                0x0227, 0x033f, 0x0416, 0x0528, 0x0622, 0x0709, 0x086d, 0x0960,
                0x0abe, 0x0b32, 0x0c0a, 0x0d0f, 0x1100
            },
            {
                0x0227, 0x033f, 0x0416, 0x0528, 0x0622, 0x0709, 0x086d, 0x0960,
                0x0abe, 0x0b33, 0x0c0a, 0x0d0f, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_40_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_85_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_85_INCLUDED
    // dp3264_regtype85: P? - 3264 - 32020 - 1/40
    // Chip family aliases: 3264, DP3264
    // Scan membership: Scan_40; GrayDepth: 12 bits
    {
        85, 13,
        {
            {
                0x0227, 0x033f, 0x040e, 0x050b, 0x0608, 0x0708, 0x08bf, 0x0960,
                0x0afe, 0x0b28, 0x0c08, 0x0d0a, 0x1100
            },
            {
                0x0227, 0x033f, 0x040e, 0x050a, 0x0608, 0x0709, 0x08bf, 0x0960,
                0x0afe, 0x0b2b, 0x0c08, 0x0d12, 0x1100
            },
            {
                0x0227, 0x033f, 0x040e, 0x0509, 0x0608, 0x0709, 0x08bf, 0x0960,
                0x0afe, 0x0b31, 0x0c08, 0x0d58, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_85_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_86_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_86_INCLUDED
    // dp3264_regtype86: P? - 3264 - 32020 - 1/40
    // Chip family aliases: 3264
    // Scan membership: Scan_40; GrayDepth: 14 bits
    {
        86, 13,
        {
            {
                0x0227, 0x033f, 0x0429, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0227, 0x033f, 0x0429, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0227, 0x033f, 0x0429, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_86_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_87_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_87_INCLUDED
    // dp3264_regtype87: P? - 3264 - 5368 - 1/40
    // Chip family aliases: 3264
    // Scan membership: Scan_40; GrayDepth: 14 bits
    {
        87, 13,
        {
            {
                0x0227, 0x033f, 0x0428, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0227, 0x033f, 0x0428, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0227, 0x033f, 0x0428, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_87_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_88_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_88_INCLUDED
    // dp3264_regtype88: P? - DP3264 - 5368 - 1/40
    // Chip family aliases: DP3264
    // Scan membership: Scan_40; GrayDepth: 13 bits
    {
        88, 13,
        {
            {
                0x0227, 0x033f, 0x041d, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c18, 0x0d08, 0x1100
            },
            {
                0x0227, 0x033f, 0x041d, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c18, 0x0d12, 0x1100
            },
            {
                0x0227, 0x033f, 0x041d, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c18, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_88_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_99_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_99_INCLUDED
    // dp3264_regtype99: P2 - DP3264 - DP32020 - 1/40
    // Chip family aliases: DP3264
    // Scan membership: Scan_40; GrayDepth: 13 bits
    {
        99, 13,
        {
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0642, 0x07d0, 0x08bf, 0x0960,
                0x0abe, 0x0b88, 0x0c9a, 0x0d04, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0642, 0x07d0, 0x08bf, 0x0960,
                0x0abe, 0x0b8a, 0x0c9a, 0x0d0c, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0642, 0x07d0, 0x08bf, 0x0960,
                0x0abe, 0x0b8a, 0x0c9a, 0x0d0e, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_99_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_101_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_101_INCLUDED
    // dp3264_regtype101: P? - DP3264 - 2018 - 1/40
    // Chip family aliases: DP3264
    // Scan membership: Scan_40; GrayDepth: 13 bits
    {
        101, 13,
        {
            {
                0x0227, 0x033f, 0x041f, 0x0506, 0x0642, 0x0708, 0x08ac, 0x0960,
                0x0abe, 0x0b28, 0x0c9c, 0x0d08, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08ac, 0x0960,
                0x0abe, 0x0b2b, 0x0c9c, 0x0d12, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08ac, 0x0960,
                0x0abe, 0x0b31, 0x0c9c, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_101_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_102_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_102_INCLUDED
    // dp3264_regtype102: P? - DP3264 - 5566 - 1/40
    // Chip family aliases: DP3264
    // Scan membership: Scan_40; GrayDepth: 13 bits
    {
        102, 13,
        {
            {
                0x0227, 0x033f, 0x041f, 0x0502, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d01, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0536, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2d, 0x0c98, 0x0d0c, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0536, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d0c, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_102_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_107_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_107_INCLUDED
    // dp3264_regtype107: P2 - DP3264 - 2018 - 1/40
    // Chip family aliases: DP3264
    // Scan membership: Scan_40; GrayDepth: 12 bits
    {
        107, 13,
        {
            {
                0x0227, 0x0335, 0x0409, 0x0504, 0x0608, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0227, 0x0335, 0x0409, 0x0504, 0x0608, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0227, 0x0335, 0x0409, 0x0504, 0x0608, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_107_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_108_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_108_INCLUDED
    // dp3264_regtype108: P2.0 - DP3264 - DP32020 - 1/40
    // Chip family aliases: DP3264
    // Scan membership: Scan_40; GrayDepth: 13 bits
    {
        108, 13,
        {
            {
                0x0227, 0x033b, 0x041f, 0x0524, 0x0641, 0x07b0, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0227, 0x033b, 0x041f, 0x0504, 0x0631, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0227, 0x033b, 0x041f, 0x0504, 0x0631, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_108_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_111_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_111_INCLUDED
    // dp3264_regtype111: P? - DP3264 - 5366 - 1/40
    // Chip family aliases: DP3264
    // Scan membership: Scan_40; GrayDepth: 13 bits
    {
        111, 13,
        {
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0632, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c18, 0x0d08, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0632, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c18, 0x0d12, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0632, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c18, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_111_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_112_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_112_INCLUDED
    // dp3264_regtype112: P? - DP3264 - 5368 - 1/40
    // Chip family aliases: DP3264
    // Scan membership: Scan_40; GrayDepth: 13 bits
    {
        112, 13,
        {
            {
                0x0227, 0x0337, 0x041f, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0227, 0x0337, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0227, 0x0337, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_112_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_116_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_116_INCLUDED
    // dp3264_regtype116: P? - DP3264-family - 1/40
    // Chip family aliases: DP3264-family
    // Scan membership: Scan_40; GrayDepth: 13 bits
    {
        116, 13,
        {
            {
                0x0227, 0x033f, 0x041f, 0x0500, 0x0639, 0x0708, 0x08bf, 0x0960,
                0x0aa6, 0x0b3f, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0639, 0x0709, 0x08bf, 0x0960,
                0x0aa6, 0x0b3f, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0639, 0x0709, 0x08bf, 0x0960,
                0x0aa6, 0x0b3f, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_116_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_117_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_117_INCLUDED
    // dp3264_regtype117: P2 - DP3264 - 5566P - 1/40
    // Chip family aliases: DP3264
    // Scan membership: Scan_40; GrayDepth: 13 bits
    {
        117, 13,
        {
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0669, 0x07c8, 0x08bf, 0x0960,
                0x0abe, 0x0b81, 0x0c98, 0x0d0f, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0669, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b81, 0x0c98, 0x0d0f, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0669, 0x07a8, 0x08bf, 0x0960,
                0x0abe, 0x0b81, 0x0c98, 0x0d0f, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_117_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_118_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_118_INCLUDED
    // dp3264_regtype118: P2 - DP3264 - 1/40
    // Chip family aliases: DP3264
    // Scan membership: Scan_40; GrayDepth: 13 bits
    {
        118, 13,
        {
            {
                0x0227, 0x033f, 0x041f, 0x0505, 0x0669, 0x07c9, 0x08bf, 0x0960,
                0x0abe, 0x0b85, 0x0c98, 0x0d0f, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0501, 0x0669, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b8a, 0x0c98, 0x0d0f, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0501, 0x0669, 0x07a8, 0x08bf, 0x0960,
                0x0abe, 0x0b8a, 0x0c98, 0x0d0f, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_118_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_119_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_119_INCLUDED
    // dp3264_regtype119: P2 - DP3264 - 5566P - 1/40
    // Chip family aliases: DP3264
    // Scan membership: Scan_40; GrayDepth: 13 bits
    {
        119, 13,
        {
            {
                0x0227, 0x033f, 0x041f, 0x05c4, 0x0669, 0x07c8, 0x08bf, 0x0960,
                0x0abe, 0x0b81, 0x0c98, 0x0d0f, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0584, 0x0669, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b81, 0x0c98, 0x0d0f, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0554, 0x0669, 0x07a8, 0x08bf, 0x0960,
                0x0abe, 0x0b81, 0x0c98, 0x0d0f, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_119_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_120_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_120_INCLUDED
    // dp3264_regtype120: P? - DP3264 - 2018 - 1/40
    // Chip family aliases: DP3264
    // Scan membership: Scan_40; GrayDepth: 13 bits
    {
        120, 13,
        {
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0642, 0x0708, 0x087f, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x087f, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0227, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x087f, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d0f, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_120_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_40_H
