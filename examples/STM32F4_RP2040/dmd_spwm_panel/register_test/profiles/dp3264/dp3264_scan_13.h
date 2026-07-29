#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_13_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_13_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_DP3264
#error "Register-test profile fragment is in the wrong chip array"
#endif

#ifndef DMD_SPWM_DP3264_REGTYPE_3_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_3_INCLUDED
    // dp3264_regtype3: P? - 3256 - 32020 - 1/13
    // Chip family aliases: 3256
    // Scan membership: Scan_13; GrayDepth: 13 bits
    {
        3, 13,
        {
            {
                0x020c, 0x033f, 0x041f, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x020c, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x020c, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_3_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_13_H
