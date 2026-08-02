#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_10_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_10_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_DP3264
#error "Register-test profile fragment is in the wrong chip array"
#endif

#ifndef DMD_SPWM_DP3264_REGTYPE_51_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_51_INCLUDED
    // dp3264_regtype51: P4 - 3269 - 32029 - 1/10
    // Chip family aliases: 3269
    // Scan membership: Scan_10; GrayDepth: 14 bits
    {
        51, 13,
        {
            {
                0x0209, 0x033f, 0x043f, 0x0503, 0x0609, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c08, 0x0d08, 0x1100
            },
            {
                0x0209, 0x033f, 0x043f, 0x0503, 0x0609, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c08, 0x0d12, 0x1100
            },
            {
                0x0209, 0x033f, 0x043f, 0x0503, 0x0609, 0x0700, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c08, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_51_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_52_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_52_INCLUDED
    // dp3264_regtype52: P4 - 3269 - 32029 - 1/10
    // Chip family aliases: 3269
    // Scan membership: Scan_10; GrayDepth: 14 bits
    {
        52, 13,
        {
            {
                0x0209, 0x033f, 0x043f, 0x0504, 0x0639, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0209, 0x033f, 0x043f, 0x0504, 0x0639, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0209, 0x033f, 0x043f, 0x0504, 0x0639, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_52_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_53_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_53_INCLUDED
    // dp3264_regtype53: P4 - 3265 - 1/10
    // Chip family aliases: 3265
    // Scan membership: Scan_10; GrayDepth: 14 bits
    {
        53, 13,
        {
            {
                0x0209, 0x033f, 0x043b, 0x0504, 0x0608, 0x0708, 0x08f1, 0x0960,
                0x0abe, 0x0b88, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0209, 0x033f, 0x043b, 0x0504, 0x0608, 0x0709, 0x08be, 0x0960,
                0x0abe, 0x0b8b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0209, 0x033f, 0x043b, 0x0504, 0x0608, 0x0709, 0x08b3, 0x0960,
                0x0abe, 0x0b91, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_53_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_91_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_91_INCLUDED
    // dp3264_regtype91: P? - 3256 - 32020 - 1/10
    // Chip family aliases: 3256
    // Scan membership: Scan_10; GrayDepth: 13 bits
    {
        91, 13,
        {
            {
                0x0209, 0x033f, 0x041f, 0x0504, 0x0642, 0x0708, 0x08bf, 0x0960,
                0x0abe, 0x0b28, 0x0c98, 0x0d08, 0x1100
            },
            {
                0x0209, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b2b, 0x0c98, 0x0d12, 0x1100
            },
            {
                0x0209, 0x033f, 0x041f, 0x0504, 0x0642, 0x0709, 0x08bf, 0x0960,
                0x0abe, 0x0b31, 0x0c98, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_91_INCLUDED

#ifndef DMD_SPWM_DP3264_REGTYPE_115_INCLUDED
#define DMD_SPWM_DP3264_REGTYPE_115_INCLUDED
    // dp3264_regtype115: P? - 3264 - 5266 - 1/10
    // Chip family aliases: 3264
    // Scan membership: Scan_10; GrayDepth: 14 bits
    {
        115, 13,
        {
            {
                0x0209, 0x033e, 0x0423, 0x0504, 0x0629, 0x0708, 0x08bf, 0x0960,
                0x0ab6, 0x0b28, 0x0c08, 0x0d08, 0x1100
            },
            {
                0x0209, 0x033e, 0x0423, 0x0504, 0x0629, 0x0709, 0x08bf, 0x0960,
                0x0ab6, 0x0b2b, 0x0c08, 0x0d12, 0x1100
            },
            {
                0x0209, 0x033e, 0x0423, 0x0504, 0x0629, 0x0709, 0x08bf, 0x0960,
                0x0ab6, 0x0b31, 0x0c08, 0x0d18, 0x1100
            }
        }
    },
#endif  // DMD_SPWM_DP3264_REGTYPE_115_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_DP3264_SCAN_10_H
