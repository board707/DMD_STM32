#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_30_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_30_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_DP3264
#error "Register-test profile fragment is in the wrong chip array"
#endif

#ifndef DMD_SPWM_DP3264_REGTYPE_32_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_32_INCLUDED
    // dp3264_regtype32: P2 - 3264S - 32020 - 1/30
    // Chip family aliases: 3264S
    // Scan membership: Scan_30; GrayDepth: 13 bits
    {
        32, 13,
        {
            {
                0x021d, 0x033f, 0x041f, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x021d, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x021d, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_32_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_38_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_38_INCLUDED
    // dp3264_regtype38: P2 - 3265 - 6158 - 1/30
    // Chip family aliases: 3265
    // Scan membership: Scan_30; GrayDepth: 13 bits
    {
        38, 13,
        {
            {
                0x021d, 0x033f, 0x041f, 0x0504, 0x0621, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b0c, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x021d, 0x033f, 0x041f, 0x0504, 0x0621, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b0f, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x021d, 0x033f, 0x041f, 0x0504, 0x0621, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b11, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_38_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_30_H
