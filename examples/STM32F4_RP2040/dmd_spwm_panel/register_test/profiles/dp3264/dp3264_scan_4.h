#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_4_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_4_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_DP3264
#error "Register-test profile fragment is in the wrong chip array"
#endif

#ifndef DMD_SPWM_DP3264_REGTYPE_64_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_64_INCLUDED
    // dp3264_regtype64: P8 - 3269 - 32029 - 1/4
    // Chip family aliases: 3269
    // Scan membership: Scan_4; GrayDepth: 14 bits
    {
        64, 13,
        {
            {
                0x0203, 0x033f, 0x043f, 0x0504, 0x0602, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0203, 0x033f, 0x043f, 0x0504, 0x0602, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0203, 0x033f, 0x043f, 0x0504, 0x0602, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_64_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_65_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_65_INCLUDED
    // dp3264_regtype65: P8 - 3269 - 32029 - 1/4
    // Chip family aliases: 3269
    // Scan membership: Scan_4; GrayDepth: 14 bits
    {
        65, 13,
        {
            {
                0x0203, 0x033f, 0x043f, 0x0504, 0x0600, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0203, 0x033f, 0x043f, 0x0504, 0x0600, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0203, 0x033f, 0x043f, 0x0504, 0x0600, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_65_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_4_H
