#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_36_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_36_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_DP3264
#error "Register-test profile fragment is in the wrong chip array"
#endif

#ifndef DMD_SPWM_DP3264_REGTYPE_121_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_121_INCLUDED
    // dp3264_regtype121: P? - DP3264 - 2018 - 1/36
    // Chip family aliases: DP3264
    // Scan membership: Scan_36; GrayDepth: 13 bits
    {
        121, 13,
        {
            {
                0x0223, 0x033f, 0x041f, 0x0544, 0x063a, 0x0708, 0x08ac, 0x0960,
                0x0abe, 0x0b28, 0x0c9c, 0x0d08, 0x1100
            },
            {
                0x0223, 0x033f, 0x041f, 0x0506, 0x063a, 0x0709, 0x08ac, 0x0960,
                0x0abe, 0x0b2b, 0x0c9c, 0x0d12, 0x1100
            },
            {
                0x0223, 0x033f, 0x041f, 0x0506, 0x063a, 0x0709, 0x08ac, 0x0960,
                0x0abe, 0x0b31, 0x0c9c, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_121_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_36_H
