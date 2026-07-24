#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_10_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_10_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6363
#error "Register-test profile fragment is in the wrong chip array"
#endif

// Generated from lib/spwm/registertest/data/fm6363.profiles at
// Raspberry Pi revision f9dc4d0a8c25. Only Scan_10 profiles are present.

#ifndef DMD_SPWM_FM6363_REGTYPE_57_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_57_INCLUDED
    // fm6363_regtype57: P4 - FM6363 - 5368 - 1/10
    // Source scan membership: Scan_10
    {
        57, 5,
        {
            {
                0x09b0, 0xf39c, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x09b0, 0xe79c, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x09b0, 0xd79c, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_57_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_58_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_58_INCLUDED
    // fm6363_regtype58: P4 - FM6363 - 5368 - 1/10
    // Source scan membership: Scan_10
    {
        58, 5,
        {
            {
                0x09b0, 0xf39c, 0x20b6, 0x1a00, 0x7e08
            },
            {
                0x09b0, 0xe79c, 0x20b6, 0x1a70, 0x7e08
            },
            {
                0x09b0, 0xd79c, 0x20b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_58_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_59_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_59_INCLUDED
    // fm6363_regtype59: P4.8 - FM6363 - 7559 - 1/10
    // Source scan membership: Scan_10
    {
        59, 5,
        {
            {
                0x09b8, 0xf39c, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x09b8, 0xe79c, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x09b8, 0xd79c, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_59_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_74_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_74_INCLUDED
    // fm6363_regtype74: P4 - FM6363 - 1/10
    // Source scan membership: Scan_10
    {
        74, 5,
        {
            {
                0x0978, 0xf33a, 0x20b6, 0x1a00, 0x7c08
            },
            {
                0x0978, 0xd362, 0x20b2, 0x1a70, 0x7c08
            },
            {
                0x0978, 0xb35a, 0x20b2, 0x1a70, 0x7c08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_74_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_10_H
