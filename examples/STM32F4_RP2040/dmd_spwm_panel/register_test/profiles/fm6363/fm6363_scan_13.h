#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_13_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_13_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6363
#error "Register-test profile fragment is in the wrong chip array"
#endif

// Generated from lib/spwm/registertest/data/fm6363.profiles at
// Raspberry Pi revision f9dc4d0a8c25. Only Scan_13 profiles are present.

#ifndef DMD_SPWM_FM6363_REGTYPE_13_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_13_INCLUDED
    // fm6363_regtype13: P? - FM6363 - 1/13
    // Source scan membership: Scan_13
    {
        13, 5,
        {
            {
                0x0cb0, 0xf39c, 0x60b6, 0x5000, 0x7e08
            },
            {
                0x0cb0, 0xe79c, 0x60b6, 0x5070, 0x7e08
            },
            {
                0x0cb0, 0xd79c, 0x60b6, 0x5070, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_13_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_14_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_14_INCLUDED
    // fm6363_regtype14: P3.076 - FM6363 - 7262 - 1/13
    // Source scan membership: Scan_13
    {
        14, 5,
        {
            {
                0x0cb8, 0xf39c, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x0cb8, 0xe79c, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x0cb8, 0xd79c, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_14_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_51_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_51_INCLUDED
    // fm6363_regtype51: P3.076 - FM6363 - 1/13
    // Source scan membership: Scan_13
    {
        51, 5,
        {
            {
                0x0cb0, 0xf39c, 0x20b6, 0x1a00, 0x7e08
            },
            {
                0x0cb0, 0xe79c, 0x20b6, 0x1a70, 0x7e08
            },
            {
                0x0cb0, 0xd79c, 0x20b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_51_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_78_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_78_INCLUDED
    // fm6363_regtype78: P3 - FM6363 - 1/13
    // Source scan membership: Scan_13
    {
        78, 5,
        {
            {
                0x0cf8, 0xf317, 0x20a6, 0x0a00, 0x7c08
            },
            {
                0x0cf8, 0xe721, 0x20b6, 0x0a70, 0x7c08
            },
            {
                0x0cf8, 0xd6e7, 0x20b6, 0x0a70, 0x7c08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_78_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_13_H
