#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_20_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_20_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_DP3264
#error "Register-test profile fragment is in the wrong chip array"
#endif

#ifndef DMD_SPWM_DP3264_REGTYPE_36_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_36_INCLUDED
    // dp3264_regtype36: P2 - 3269 - 32029 - 1/20
    // Chip family aliases: 3269
    // Scan membership: Scan_20; GrayDepth: 14 bits
    {
        36, 13,
        {
            {
                0x0213, 0x033f, 0x0423, 0x0505, 0x0609, 0x07c0, 0x087f, 0x0960,
                0x0abe, 0x0b28, 0x0c08, 0x0d08, 0x1100
            },
            {
                0x0213, 0x033f, 0x0423, 0x0504, 0x0609, 0x07c0, 0x087f, 0x0960,
                0x0abe, 0x0b33, 0x0c08, 0x0d11, 0x1100
            },
            {
                0x0213, 0x033f, 0x0423, 0x0504, 0x0609, 0x07c0, 0x087f, 0x0960,
                0x0abe, 0x0b34, 0x0c08, 0x0d19, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_36_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_37_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_37_INCLUDED
    // dp3264_regtype37: P2 - 3269 - 32029 - 1/20
    // Chip family aliases: 3269
    // Scan membership: Scan_20; GrayDepth: 14 bits
    {
        37, 13,
        {
            {
                0x0213, 0x033f, 0x0427, 0x0503, 0x0612, 0x07b0, 0x087f, 0x0960,
                0x0abe, 0x0b28, 0x0c08, 0x0d08, 0x1100
            },
            {
                0x0213, 0x033f, 0x0427, 0x0503, 0x0612, 0x0700, 0x087f, 0x0960,
                0x0abe, 0x0b36, 0x0c08, 0x0d16, 0x1100
            },
            {
                0x0213, 0x033f, 0x0427, 0x0503, 0x0612, 0x07b0, 0x087f, 0x0960,
                0x0abe, 0x0b34, 0x0c08, 0x0d1e, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_37_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_84_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_84_INCLUDED
    // dp3264_regtype84: P? - 3264 - 32020 - 1/20
    // Chip family aliases: 3264
    // Scan membership: Scan_20; GrayDepth: 13 bits
    {
        84, 13,
        {
            {
                0x0213, 0x033f, 0x041f, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0213, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0213, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_84_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_92_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_92_INCLUDED
    // dp3264_regtype92: P? - 3256 - 5158 - 1/20
    // Chip family aliases: 3256
    // Scan membership: Scan_20; GrayDepth: 13 bits
    {
        92, 13,
        {
            {
                0x0213, 0x033f, 0x041f, 0x0504, 0x0619, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0213, 0x033f, 0x041f, 0x0504, 0x0619, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0213, 0x033f, 0x041f, 0x0504, 0x0619, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_92_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_20_H
