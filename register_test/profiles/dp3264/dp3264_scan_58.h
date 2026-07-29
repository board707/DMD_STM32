#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_58_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_58_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_DP3264
#error "Register-test profile fragment is in the wrong chip array"
#endif

#ifndef DMD_SPWM_DP3264_REGTYPE_6_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_6_INCLUDED
    // dp3264_regtype6: P? - 3265 - 5158 - 1/58
    // Chip family aliases: 3265, 3265S
    // Scan membership: Scan_58; GrayDepth: 12 bits
    {
        6, 13,
        {
            {
                0x0239, 0x033f, 0x040f, 0x0507, 0x0642, 0x07c0, 0x08f0, 0x0960,
                0x0abe, 0x0b83, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0239, 0x033f, 0x040f, 0x0504, 0x0642, 0x07d0, 0x08be, 0x0960,
                0x0abe, 0x0b8a, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0239, 0x033f, 0x040f, 0x0504, 0x0642, 0x07f0, 0x08be, 0x0960,
                0x0abe, 0x0b8a, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_6_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_7_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_7_INCLUDED
    // dp3264_regtype7: P? - 3265 - 5158 - 1/58
    // Chip family aliases: 3265, 3265S
    // Scan membership: Scan_58; GrayDepth: 12 bits
    {
        7, 13,
        {
            {
                0x0239, 0x033f, 0x040f, 0x0507, 0x0621, 0x07c0, 0x08f0, 0x0960,
                0x0abe, 0x0b88, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0239, 0x033f, 0x040f, 0x0504, 0x0621, 0x07d0, 0x08be, 0x0960,
                0x0abe, 0x0b8b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0239, 0x033f, 0x040f, 0x0504, 0x0621, 0x07f0, 0x08be, 0x0960,
                0x0abe, 0x0b91, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_7_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_106_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_106_INCLUDED
    // dp3264_regtype106: P1.86 - 3264 - 5566 - 1/58
    // Chip family aliases: 3264
    // Scan membership: Scan_58; GrayDepth: 12 bits
    {
        106, 13,
        {
            {
                0x0239, 0x0313, 0x0420, 0x0504, 0x0638, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0239, 0x0313, 0x0420, 0x0504, 0x0638, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0239, 0x0313, 0x0420, 0x0504, 0x0638, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_106_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_58_H
