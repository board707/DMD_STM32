#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_40_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_40_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6363
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6363 register profiles. Only Scan_40 profiles are present.

#ifndef DMD_SPWM_FM6363_REGTYPE_16_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_16_INCLUDED
    // fm6363_regtype16: P2 - FM6363 - HX6158H - 1/40
    // Scan membership: Scan_40
    {
        16, 5,
        {
            {
                0x27f0, 0xf301, 0x08b6, 0x5c70, 0x7e08
            },
            {
                0x27f0, 0xc701, 0x04b6, 0x5c70, 0x7e08
            },
            {
                0x27f0, 0xc701, 0x00b6, 0x5c70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_16_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_17_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_17_INCLUDED
    // fm6363_regtype17: P2 - FM6363 - HX6158H - 1/40
    // Scan membership: Scan_40
    {
        17, 5,
        {
            {
                0x27f0, 0xf307, 0x08b6, 0x5c70, 0x7e08
            },
            {
                0x27f0, 0xc707, 0x04b6, 0x5c70, 0x7e08
            },
            {
                0x27f0, 0xc707, 0x00b6, 0x5c70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_17_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_19_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_19_INCLUDED
    // fm6363_regtype19: P2 - FM6363 - HX6158H - 1/40
    // Scan membership: Scan_40
    {
        19, 5,
        {
            {
                0x27f0, 0xf30b, 0x08b6, 0x5c70, 0x7e08
            },
            {
                0x27f0, 0xc70b, 0x04b6, 0x5c70, 0x7e08
            },
            {
                0x27f0, 0xc70f, 0x00b6, 0x5c70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_19_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_20_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_20_INCLUDED
    // fm6363_regtype20: P2 - FM6363 - HX6158H - 1/40
    // Scan membership: Scan_40
    {
        20, 5,
        {
            {
                0x27f0, 0xf301, 0x08b6, 0x5c70, 0x7e08
            },
            {
                0x27f0, 0xc6fb, 0x04b6, 0x5c70, 0x7e08
            },
            {
                0x27f0, 0xc701, 0x00b6, 0x5c70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_20_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_21_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_21_INCLUDED
    // fm6363_regtype21: P2 - FM6363 - HX6158H - 1/40
    // Scan membership: Scan_40
    {
        21, 5,
        {
            {
                0x27f0, 0xf321, 0x08b6, 0x5c70, 0x7e08
            },
            {
                0x27f0, 0xc71b, 0x04b6, 0x5c70, 0x7e08
            },
            {
                0x27f0, 0xc717, 0x00b6, 0x5c70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_21_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_40_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_40_INCLUDED
    // fm6363_regtype40: P2 - FM6363 - 1/40
    // Scan membership: Scan_40
    {
        40, 5,
        {
            {
                0x27b0, 0x739c, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x27b0, 0x679c, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x27b0, 0x579c, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_40_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_41_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_41_INCLUDED
    // fm6363_regtype41: P2 - FM6363 - 1/40
    // Scan membership: Scan_40
    {
        41, 5,
        {
            {
                0x27b8, 0xf3ce, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x27b8, 0xe7ce, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x27b8, 0xd7ce, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_41_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_69_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_69_INCLUDED
    // fm6363_regtype69: P2 - FM6363 - HX6158H - 1/40
    // Scan membership: Scan_40
    {
        69, 5,
        {
            {
                0x27f8, 0xf3a8, 0x60b6, 0x1a00, 0x7a08
            },
            {
                0x27f8, 0xe7fe, 0x60b6, 0x1a70, 0x7a08
            },
            {
                0x27f8, 0xd7a8, 0x60b6, 0x1a70, 0x7a08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_69_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_70_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_70_INCLUDED
    // fm6363_regtype70: P2 - FM6363 - HX6158H - 1/40
    // Scan membership: Scan_40
    {
        70, 5,
        {
            {
                0x27f8, 0xf3b6, 0x60b6, 0x1a00, 0x7a08
            },
            {
                0x27f8, 0xe7fe, 0x60b6, 0x1a70, 0x7a08
            },
            {
                0x27f8, 0xd784, 0x60b6, 0x1a70, 0x7a08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_70_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_79_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_79_INCLUDED
    // fm6363_regtype79: FM6363 register profile
    // Scan membership: Scan_40
    {
        79, 5,
        {
            {
                0x27b0, 0x639d, 0x6496, 0x5a30, 0x7e08
            },
            {
                0x27b0, 0x4b9d, 0x6896, 0x5a70, 0x7e08
            },
            {
                0x27b0, 0x439d, 0x6c96, 0x5a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_79_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_40_H
