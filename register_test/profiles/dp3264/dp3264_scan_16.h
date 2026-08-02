#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_16_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_16_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_DP3264
#error "Register-test profile fragment is in the wrong chip array"
#endif

#ifndef DMD_SPWM_DP3264_REGTYPE_1_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_1_INCLUDED
    // dp3264_regtype1: DP3264 - main register profile - 1/16
    // Chip family aliases: DP3264
    // Scan membership: Scan_16; GrayDepth: 13 bits
    {
        1, 13,
        {
            {
                0x020f, 0x033f, 0x043f, 0x0504, 0x0642, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b8b, 0x0c88, 0x0d12, 0x1100
            },
            {
                0x020f, 0x033f, 0x043f, 0x0504, 0x0642, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b8b, 0x0c88, 0x0d12, 0x1100
            },
            {
                0x020f, 0x033f, 0x043f, 0x0504, 0x0642, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b8b, 0x0c88, 0x0d12, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_1_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_41_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_41_INCLUDED
    // dp3264_regtype41: P2.5 - 3264S - 32019 - 1/16
    // Chip family aliases: 3256, 3264, 3264S
    // Scan membership: Scan_16; GrayDepth: 13 bits
    {
        41, 13,
        {
            {
                0x020f, 0x033f, 0x041f, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x020f, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x020f, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_41_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_45_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_45_INCLUDED
    // dp3264_regtype45: P3 - 3264 - 2012 - 1/16
    // Chip family aliases: 3264
    // Scan membership: Scan_16; GrayDepth: 13 bits
    {
        45, 13,
        {
            {
                0x020f, 0x033f, 0x041f, 0x0504, 0x0609, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x020f, 0x033f, 0x041f, 0x0504, 0x0609, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x020f, 0x033f, 0x041f, 0x0504, 0x0609, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_45_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_49_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_49_INCLUDED
    // dp3264_regtype49: P3.91 - 3264 - 32020 - 1/16
    // Chip family aliases: 3264
    // Scan membership: Scan_16; GrayDepth: 14 bits
    {
        49, 13,
        {
            {
                0x020f, 0x033f, 0x042f, 0x0500, 0x0609, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x020f, 0x033f, 0x042f, 0x0500, 0x0609, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x020f, 0x033f, 0x042f, 0x0500, 0x0609, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_49_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_50_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_50_INCLUDED
    // dp3264_regtype50: P3.91 - 3269 - 32029 - 1/16
    // Chip family aliases: 3269
    // Scan membership: Scan_16; GrayDepth: 11 bits
    {
        50, 13,
        {
            {
                0x020f, 0x0300, 0x041f, 0x0503, 0x0600, 0x0708, 0x08bf, 0x0960,
                0x0afe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x020f, 0x0300, 0x041f, 0x0503, 0x0600, 0x0709, 0x08bf, 0x0960,
                0x0afe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x020f, 0x0300, 0x041f, 0x0503, 0x0600, 0x0709, 0x08bf, 0x0960,
                0x0afe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_50_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_16_H
