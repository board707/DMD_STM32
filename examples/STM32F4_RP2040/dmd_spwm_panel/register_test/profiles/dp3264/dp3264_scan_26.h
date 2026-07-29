#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_26_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_26_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_DP3264
#error "Register-test profile fragment is in the wrong chip array"
#endif

#ifndef DMD_SPWM_DP3264_REGTYPE_46_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_46_INCLUDED
    // dp3264_regtype46: P3.076 - 3264S - 32019 - 1/26
    // Chip family aliases: 3264, 3264S
    // Scan membership: Scan_26; GrayDepth: 13 bits
    {
        46, 13,
        {
            {
                0x0219, 0x033f, 0x041f, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0219, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0219, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_46_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_47_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_47_INCLUDED
    // dp3264_regtype47: P3.076 - DP3264 - 7258 - 1/26
    // Chip family aliases: DP3264
    // Scan membership: Scan_26; GrayDepth: 14 bits
    {
        47, 13,
        {
            {
                0x0219, 0x033f, 0x042c, 0x0506, 0x0629, 0x0708, 0x08ac, 0x0960,
                0x0abe, 0x0b28, 0x0c18, 0x0d08, 0x1100
            },
            {
                0x0219, 0x033f, 0x042c, 0x0504, 0x0629, 0x07e8, 0x0872, 0x0960,
                0x0abe, 0x0b2b, 0x0c18, 0x0d12, 0x1100
            },
            {
                0x0219, 0x033f, 0x042c, 0x0504, 0x0629, 0x0709, 0x08ab, 0x0960,
                0x0abe, 0x0b31, 0x0c18, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_47_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_48_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_48_INCLUDED
    // dp3264_regtype48: P3.076 - 3264 - 7262 - 1/26
    // Chip family aliases: 3264
    // Scan membership: Scan_26; GrayDepth: 13 bits
    {
        48, 13,
        {
            {
                0x0219, 0x033f, 0x041f, 0x0504, 0x0611, 0x07a8, 0x08bf, 0x0960,
                0x0afe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0219, 0x033f, 0x041f, 0x0504, 0x0611, 0x07a8, 0x08bf, 0x0960,
                0x0afe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0219, 0x033f, 0x041f, 0x0504, 0x0611, 0x07a8, 0x08bf, 0x0960,
                0x0afe, 0x0b2c, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_48_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_26_H
