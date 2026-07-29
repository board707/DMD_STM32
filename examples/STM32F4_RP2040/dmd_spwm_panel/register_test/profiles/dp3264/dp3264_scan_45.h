#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_45_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_45_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_DP3264
#error "Register-test profile fragment is in the wrong chip array"
#endif

#ifndef DMD_SPWM_DP3264_REGTYPE_103_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_103_INCLUDED
    // dp3264_regtype103: P? - DP3264 - 2018 - 1/45
    // Chip family aliases: DP3264
    // Scan membership: Scan_45; GrayDepth: 13 bits
    {
        103, 13,
        {
            {
                0x022c, 0x033f, 0x041f, 0x0506, 0x0642, 0x0700, 0x08ab, 0x0960,
                0x0abe, 0x0b28, 0x0c9c, 0x0d08, 0x1100
            },
            {
                0x022c, 0x033f, 0x041f, 0x0504, 0x0642, 0x0700, 0x08ab, 0x0960,
                0x0abe, 0x0b29, 0x0c9c, 0x0d0d, 0x1100
            },
            {
                0x022c, 0x033f, 0x041f, 0x0505, 0x0642, 0x0700, 0x08ab, 0x0960,
                0x0abe, 0x0b31, 0x0c9c, 0x0d16, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_103_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_45_H
