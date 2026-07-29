#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_8_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_8_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_DP3264
#error "Register-test profile fragment is in the wrong chip array"
#endif

#ifndef DMD_SPWM_DP3264_REGTYPE_54_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_54_INCLUDED
    // dp3264_regtype54: P5 - DP3264S - 7258D - 1/8
    // Chip family aliases: DP3264S
    // Scan membership: Scan_8; GrayDepth: 13 bits
    {
        54, 13,
        {
            {
                0x0207, 0x033f, 0x041f, 0x0504, 0x0688, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0207, 0x033f, 0x041f, 0x0504, 0x0688, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0207, 0x033f, 0x041f, 0x0504, 0x0688, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_54_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_55_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_55_INCLUDED
    // dp3264_regtype55: P5 - 3265 - 2012 - 1/8
    // Chip family aliases: 3265
    // Scan membership: Scan_8; GrayDepth: 13 bits
    {
        55, 13,
        {
            {
                0x0207, 0x033f, 0x041f, 0x0504, 0x0609, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c18, 0x0d08, 0x1100
            },
            {
                0x0207, 0x033f, 0x041f, 0x0504, 0x0609, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c18, 0x0d12, 0x1100
            },
            {
                0x0207, 0x033f, 0x041f, 0x0504, 0x0609, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c18, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_55_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_56_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_56_INCLUDED
    // dp3264_regtype56: P5 - 3269 - 32029 - 1/8
    // Chip family aliases: 3269
    // Scan membership: Scan_8; GrayDepth: 14 bits
    {
        56, 13,
        {
            {
                0x0207, 0x033e, 0x043f, 0x0503, 0x0619, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0207, 0x033e, 0x043f, 0x0503, 0x0619, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0207, 0x033e, 0x043f, 0x0503, 0x0619, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_56_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_57_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_57_INCLUDED
    // dp3264_regtype57: P5 - 3269 - 32029 - 1/8
    // Chip family aliases: 3269
    // Scan membership: Scan_8; GrayDepth: 14 bits
    {
        57, 13,
        {
            {
                0x0207, 0x033f, 0x043f, 0x0504, 0x0618, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0207, 0x033f, 0x043f, 0x0503, 0x0618, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0207, 0x033f, 0x043f, 0x0503, 0x0618, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_57_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_93_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_93_INCLUDED
    // dp3264_regtype93: P? - 3256 - 32020 - 1/8
    // Chip family aliases: 3256, 3356
    // Scan membership: Scan_8; GrayDepth: 13 bits
    {
        93, 13,
        {
            {
                0x0207, 0x033f, 0x041c, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0207, 0x033f, 0x041c, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0207, 0x033f, 0x041c, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_93_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_94_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_94_INCLUDED
    // dp3264_regtype94: P? - 3256 - 5158 - 1/8
    // Chip family aliases: 3256, 3356
    // Scan membership: Scan_8; GrayDepth: 13 bits
    {
        94, 13,
        {
            {
                0x0207, 0x033f, 0x041f, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0207, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0207, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_94_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_96_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_96_INCLUDED
    // dp3264_regtype96: P? - 3256 - 32020 - 1/8
    // Chip family aliases: 3256
    // Scan membership: Scan_8; GrayDepth: 13 bits
    {
        96, 13,
        {
            {
                0x0207, 0x033f, 0x041f, 0x0504, 0x063a, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0207, 0x033f, 0x041f, 0x0504, 0x063a, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0207, 0x033f, 0x041f, 0x0504, 0x063a, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_96_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_8_H
