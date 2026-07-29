#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_59_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_59_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_DP3264
#error "Register-test profile fragment is in the wrong chip array"
#endif

#ifndef DMD_SPWM_DP3264_REGTYPE_14_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_14_INCLUDED
    // dp3264_regtype14: P1.538 - 3265 - 6158 - 1/59
    // Chip family aliases: 3265
    // Scan membership: Scan_59; GrayDepth: 13 bits
    {
        14, 13,
        {
            {
                0x023a, 0x033f, 0x041f, 0x0514, 0x065a, 0x0709, 0x087b, 0x0900,
                0x0afe, 0x0b0c, 0x0c18, 0x0d08, 0x1100
            },
            {
                0x023a, 0x033f, 0x041f, 0x0517, 0x065a, 0x0709, 0x087b, 0x0900,
                0x0afe, 0x0b0f, 0x0c18, 0x0d12, 0x1100
            },
            {
                0x023a, 0x033f, 0x041f, 0x0522, 0x065a, 0x0709, 0x087b, 0x0900,
                0x0afe, 0x0b11, 0x0c18, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_14_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_59_H
