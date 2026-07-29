#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_16_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_16_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6363
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6363 register profiles. Only Scan_16 profiles are present.

#ifndef DMD_SPWM_FM6363_REGTYPE_12_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_12_INCLUDED
    // fm6363_regtype12: P? - FM6363 - 1/16
    // Scan membership: Scan_16
    {
        12, 5,
        {
            {
                0x0fb8, 0xf39c, 0x60b6, 0x5000, 0x7e08
            },
            {
                0x0fb8, 0xe79c, 0x60b6, 0x5070, 0x7e08
            },
            {
                0x0fb8, 0xd79c, 0x60b6, 0x5070, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_12_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_44_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_44_INCLUDED
    // fm6363_regtype44: P2.5 - FM6363 - 7258 - 1/16
    // Scan membership: Scan_16
    {
        44, 5,
        {
            {
                0x0fb8, 0xf34d, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x0fb8, 0xe753, 0x60b6, 0x1f70, 0x7e08
            },
            {
                0x0fb8, 0xd74b, 0x60b6, 0x1b70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_44_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_45_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_45_INCLUDED
    // fm6363_regtype45: P2.5 - FM6363 - 7258 - 1/16
    // Scan membership: Scan_16
    {
        45, 5,
        {
            {
                0x0fb8, 0xf39c, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x0fb8, 0xe79c, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x0fb8, 0xd79c, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_45_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_50_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_50_INCLUDED
    // fm6363_regtype50: P3 - FM6363 - 1/16
    // Scan membership: Scan_16
    {
        50, 5,
        {
            {
                0x0fb0, 0xd79d, 0x60b6, 0x1030, 0x7e08
            },
            {
                0x0fb0, 0xc39d, 0x60b6, 0x1070, 0x7e08
            },
            {
                0x0fb0, 0xbb9d, 0x60b6, 0x1070, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_50_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_56_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_56_INCLUDED
    // fm6363_regtype56: P3.91 - FM6363 - 1/16
    // Scan membership: Scan_16
    {
        56, 5,
        {
            {
                0x0fb0, 0xf39c, 0x20b6, 0x1a00, 0x7e08
            },
            {
                0x0fb0, 0xe79c, 0x20b6, 0x1a70, 0x7e08
            },
            {
                0x0fb0, 0xd79c, 0x20b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_56_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_71_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_71_INCLUDED
    // fm6363_regtype71: P? - FM6363 - RUC7258D - 1/16
    // Scan membership: Scan_16
    {
        71, 5,
        {
            {
                0x0fb8, 0xf39d, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x0fb8, 0xe79d, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x0fb8, 0xd79d, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_71_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_75_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_75_INCLUDED
    // fm6363_regtype75: P2.5 - FM6363 - 1/16
    // Scan membership: Scan_16
    {
        75, 5,
        {
            {
                0x0ff8, 0xf2db, 0x60b2, 0x0a10, 0x7e08
            },
            {
                0x0ff8, 0xe6bf, 0x60b6, 0x0a70, 0x7e08
            },
            {
                0x0ff8, 0xd71f, 0x60b6, 0x0a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_75_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_16_H
