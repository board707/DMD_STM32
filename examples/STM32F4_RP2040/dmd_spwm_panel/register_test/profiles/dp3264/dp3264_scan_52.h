#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_52_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_52_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_DP3264
#error "Register-test profile fragment is in the wrong chip array"
#endif

#ifndef DMD_SPWM_DP3264_REGTYPE_12_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_12_INCLUDED
    // dp3264_regtype12: P1.538 - 3264 - 32020 - 1/52
    // Chip family aliases: 3264
    // Scan membership: Scan_52; GrayDepth: 13 bits
    {
        12, 13,
        {
            {
                0x0233, 0x033f, 0x0413, 0x05a0, 0x06a9, 0x07e0, 0x08bf, 0x0960,
                0x0afe, 0x0b46, 0x0c08, 0x0d00, 0x1100
            },
            {
                0x0233, 0x033f, 0x0413, 0x0581, 0x0629, 0x0709, 0x08bf, 0x0960,
                0x0afe, 0x0b4d, 0x0c08, 0x0d14, 0x1100
            },
            {
                0x0233, 0x033f, 0x0413, 0x0580, 0x0629, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b4f, 0x0c08, 0x0d16, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_12_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_13_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_13_INCLUDED
    // dp3264_regtype13: P1.538 - 3264 - 32020 - 1/52
    // Chip family aliases: 3264
    // Scan membership: Scan_52; GrayDepth: 14 bits
    {
        13, 13,
        {
            {
                0x0233, 0x033f, 0x0420, 0x0504, 0x063a, 0x07d0, 0x08be, 0x0960,
                0x0ab6, 0x0b00, 0x0c18, 0x0d10, 0x1100
            },
            {
                0x0233, 0x033f, 0x0420, 0x0508, 0x063a, 0x07a8, 0x08bf, 0x0960,
                0x0ab6, 0x0b07, 0x0c18, 0x0d17, 0x1100
            },
            {
                0x0233, 0x033f, 0x0420, 0x050a, 0x063a, 0x07e9, 0x08bf, 0x0960,
                0x0ab6, 0x0b0a, 0x0c18, 0x0d1f, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_13_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_69_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_69_INCLUDED
    // dp3264_regtype69: P? - 3264 - DP32020 - 1/52
    // Chip family aliases: 3264
    // Scan membership: Scan_52; GrayDepth: 12 bits
    {
        69, 13,
        {
            {
                0x0233, 0x032a, 0x040f, 0x0504, 0x062a, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c18, 0x0d08, 0x1100
            },
            {
                0x0233, 0x032a, 0x040f, 0x0504, 0x062a, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c18, 0x0d12, 0x1100
            },
            {
                0x0233, 0x032a, 0x040f, 0x0504, 0x062a, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c18, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_69_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_70_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_70_INCLUDED
    // dp3264_regtype70: P? - DP3264 - 5158 - 1/52
    // Chip family aliases: DP3264
    // Scan membership: Scan_52; GrayDepth: 12 bits
    {
        70, 13,
        {
            {
                0x0233, 0x033f, 0x040f, 0x0504, 0x0629, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c18, 0x0d08, 0x1100
            },
            {
                0x0233, 0x033f, 0x040f, 0x0504, 0x0629, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c18, 0x0d12, 0x1100
            },
            {
                0x0233, 0x033f, 0x040f, 0x0504, 0x0629, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c18, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_70_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_71_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_71_INCLUDED
    // dp3264_regtype71: P? - 3264 - 32020 - 1/52
    // Chip family aliases: 3264
    // Scan membership: Scan_52; GrayDepth: 13 bits
    {
        71, 13,
        {
            {
                0x0233, 0x033f, 0x041d, 0x0504, 0x064a, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0233, 0x033f, 0x041d, 0x0504, 0x064a, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0233, 0x033f, 0x041d, 0x0504, 0x064a, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_71_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_89_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_89_INCLUDED
    // dp3264_regtype89: P? - 3264 - 5158 - 1/52
    // Chip family aliases: 3264
    // Scan membership: Scan_52; GrayDepth: 13 bits
    {
        89, 13,
        {
            {
                0x0233, 0x033f, 0x041f, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0233, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0233, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_89_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_113_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_113_INCLUDED
    // dp3264_regtype113: P? - 3264 - 32020 - 1/52
    // Chip family aliases: 3264
    // Scan membership: Scan_52; GrayDepth: 13 bits
    {
        113, 13,
        {
            {
                0x0233, 0x0336, 0x041f, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0233, 0x0336, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0233, 0x0336, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_113_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_114_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_114_INCLUDED
    // dp3264_regtype114: P? - 3264 - 32020 - 1/52
    // Chip family aliases: 3264
    // Scan membership: Scan_52; GrayDepth: 13 bits
    {
        114, 13,
        {
            {
                0x0233, 0x0332, 0x041f, 0x0504, 0x0631, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0233, 0x0332, 0x041f, 0x0504, 0x0631, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0233, 0x0332, 0x041f, 0x0504, 0x0631, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_114_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_52_H
