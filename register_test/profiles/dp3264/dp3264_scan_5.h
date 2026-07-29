#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_5_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_5_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_DP3264
#error "Register-test profile fragment is in the wrong chip array"
#endif

#ifndef DMD_SPWM_DP3264_REGTYPE_63_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_63_INCLUDED
    // dp3264_regtype63: P8 - DP3264-family - 1/5
    // Chip family aliases: DP3264-family
    // Scan membership: Scan_5; GrayDepth: 14 bits
    {
        63, 13,
        {
            {
                0x0204, 0x033f, 0x043f, 0x0504, 0x0618, 0x0708, 0x08ad, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0204, 0x033f, 0x043f, 0x0504, 0x0618, 0x0709, 0x0876, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0204, 0x033f, 0x043f, 0x0504, 0x0618, 0x0709, 0x08ae, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_63_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_66_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_66_INCLUDED
    // dp3264_regtype66: P8 - 3269 - 32029 - 1/5
    // Chip family aliases: 3269
    // Scan membership: Scan_5; GrayDepth: 14 bits
    {
        66, 13,
        {
            {
                0x0204, 0x033f, 0x043f, 0x0502, 0x0600, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c08, 0x0d08, 0x1100
            },
            {
                0x0204, 0x033f, 0x043f, 0x0503, 0x0600, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c08, 0x0d12, 0x1100
            },
            {
                0x0204, 0x033f, 0x043f, 0x0503, 0x0600, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c08, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_66_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_67_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_67_INCLUDED
    // dp3264_regtype67: P8 - 3269 - 32029 - 1/5
    // Chip family aliases: 3269
    // Scan membership: Scan_5; GrayDepth: 14 bits
    {
        67, 13,
        {
            {
                0x0204, 0x033f, 0x043c, 0x0504, 0x0600, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0204, 0x033f, 0x043c, 0x0504, 0x0600, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0204, 0x033f, 0x043c, 0x0504, 0x0600, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_67_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_68_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_68_INCLUDED
    // dp3264_regtype68: P8 - 3269 - 32029 - 1/5
    // Chip family aliases: 3269
    // Scan membership: Scan_5; GrayDepth: 13 bits
    {
        68, 13,
        {
            {
                0x0204, 0x033f, 0x041f, 0x0504, 0x0608, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0204, 0x033f, 0x041f, 0x0504, 0x0608, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0204, 0x033f, 0x041f, 0x0504, 0x0608, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_68_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_97_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_97_INCLUDED
    // dp3264_regtype97: P? - 3256 - 32019 - 1/5
    // Chip family aliases: 3256, 3264
    // Scan membership: Scan_5; GrayDepth: 13 bits
    {
        97, 13,
        {
            {
                0x0204, 0x033f, 0x041f, 0x0504, 0x0600, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0204, 0x033f, 0x041f, 0x0504, 0x0600, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0204, 0x033f, 0x041f, 0x0504, 0x0600, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_97_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_5_H
