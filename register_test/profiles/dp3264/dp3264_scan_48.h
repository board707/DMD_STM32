#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_48_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_48_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_DP3264
#error "Register-test profile fragment is in the wrong chip array"
#endif

#ifndef DMD_SPWM_DP3264_REGTYPE_104_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_104_INCLUDED
    // dp3264_regtype104: P1.66 - DP3264 - 5958 - 1/48
    // Chip family aliases: DP3264
    // Scan membership: Scan_48; GrayDepth: 13 bits
    {
        104, 13,
        {
            {
                0x022f, 0x032a, 0x041f, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x022f, 0x032a, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x022f, 0x032a, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_104_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_48_H
