#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_32_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_32_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6363
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6363 register profiles. Only Scan_32 profiles are present.

#ifndef DMD_SPWM_FM6363_REGTYPE_1_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_1_INCLUDED
    // fm6363_regtype1: built-in main FM6363 register config
    // Scan membership: Scan_32
    {
        1, 5,
        {
            {
                0x1fb0, 0xf39c, 0x20b6, 0x1a00, 0x7e08
            },
            {
                0x1fb0, 0xf39c, 0x20b6, 0x1a00, 0x7e08
            },
            {
                0x1fb0, 0xf39c, 0x20b6, 0x1a00, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_1_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_5_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_5_INCLUDED
    // fm6363_regtype5: P2.5 - FM6363 - 7559 - 1/32
    // Scan membership: Scan_32
    {
        5, 5,
        {
            {
                0x1fb0, 0xf39c, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x1fb0, 0xe79c, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x1fb0, 0xd79c, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_5_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_11_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_11_INCLUDED
    // fm6363_regtype11: P? - FM6363 - 1/32
    // Scan membership: Scan_32
    {
        11, 5,
        {
            {
                0x1fb8, 0xf3b8, 0x60b6, 0x5a30, 0x7e08
            },
            {
                0x1fb8, 0xe7b8, 0x60b6, 0x5a70, 0x7e08
            },
            {
                0x1fb8, 0xd7b8, 0x60b6, 0x5a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_11_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_23_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_23_INCLUDED
    // fm6363_regtype23: P3 - FM6363 - 7262 - 1/32
    // Scan membership: Scan_32
    {
        23, 5,
        {
            {
                0x1ff8, 0xff9d, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x1ff8, 0xf39d, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x1ff8, 0xe39d, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_23_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_42_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_42_INCLUDED
    // fm6363_regtype42: P2.5 - FM6363 - 7258 - 1/32
    // Scan membership: Scan_32
    {
        42, 5,
        {
            {
                0x1ff0, 0xf39c, 0x60b6, 0x1a30, 0x7e08
            },
            {
                0x1ff0, 0xe79c, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x1ff0, 0xd79c, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_42_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_43_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_43_INCLUDED
    // fm6363_regtype43: P2.5 - FM6363 - 7258 - 1/32
    // Scan membership: Scan_32
    {
        43, 5,
        {
            {
                0x1ff0, 0xf39c, 0x60b6, 0x1a20, 0x7e08
            },
            {
                0x1ff0, 0xe79c, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x1ff0, 0xd79c, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_43_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_46_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_46_INCLUDED
    // fm6363_regtype46: P2.5 - FM6363 - 1/32
    // Scan membership: Scan_32
    {
        46, 5,
        {
            {
                0x1ff0, 0xf39c, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x1ff0, 0xe79c, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x1ff0, 0xd79c, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_46_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_47_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_47_INCLUDED
    // fm6363_regtype47: P2.604 - FM6363 - 1/32
    // Scan membership: Scan_32
    {
        47, 5,
        {
            {
                0x1fb0, 0xf3fe, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x1fb0, 0xe7fe, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x1fb0, 0xd7fe, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_47_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_72_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_72_INCLUDED
    // fm6363_regtype72: P2.5 - FM6363 - RUC7258D - 1/32
    // Scan membership: Scan_32
    {
        72, 5,
        {
            {
                0x1ff8, 0xf39d, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x1ff8, 0xe79d, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x1ff8, 0xd79d, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_72_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_32_H
