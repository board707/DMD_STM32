#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_4_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_4_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6353 register profiles. Only Scan_4 profiles are present.

#ifndef DMD_SPWM_FM6353_REGTYPE_4_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_4_INCLUDED
    // fm6353_regtype4: P3.076 - FM6353 - 1/13
    // Scan membership: Scan_2,Scan_4,Scan_5,Scan_6,Scan_7,Scan_8,Scan_10,Scan_12,Scan_13,Scan_15,Scan_16,Scan_18,Scan_20,Scan_21,Scan_23,Scan_24,Scan_25,Scan_26,Scan_27,Scan_28,Scan_30,Scan_31,Scan_32
    {
        4, 5,
        {
            {
                0x0000, 0x0000, 0xff9c, 0x0000, 0x0000
            },
            {
                0x0000, 0x0000, 0xf39c, 0x0000, 0x0000
            },
            {
                0x0000, 0x0000, 0xdf9c, 0x0000, 0x0000
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_4_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_26_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_26_INCLUDED
    // fm6353_regtype26: P? - FM6353 - 1/32
    // Scan membership: Scan_2,Scan_4,Scan_8,Scan_10,Scan_13,Scan_16,Scan_20,Scan_32
    {
        26, 5,
        {
            {
                0x0000, 0x0000, 0x0000, 0x0000, 0x0000
            },
            {
                0x0000, 0x0000, 0x0000, 0x0000, 0x0000
            },
            {
                0x0000, 0x0000, 0x0000, 0x0000, 0x0000
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_26_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_30_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_30_INCLUDED
    // fm6353_regtype30: P? - FM6353 - 1/4
    // Scan membership: Scan_4
    {
        30, 5,
        {
            {
                0x0001, 0x0370, 0x7f0e, 0x00f7, 0x0040
            },
            {
                0x0001, 0x0370, 0x66f0, 0x00f7, 0x0040
            },
            {
                0x0001, 0x0370, 0x5f54, 0x00f7, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_30_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_40_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_40_INCLUDED
    // fm6353_regtype40: P? - FM6353 - 1/4
    // Scan membership: Scan_4
    {
        40, 5,
        {
            {
                0x0000, 0x0350, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x0350, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x0350, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_40_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_64_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_64_INCLUDED
    // fm6353_regtype64: P? - FM6353 - 1/4
    // Scan membership: Scan_4
    {
        64, 5,
        {
            {
                0x0001, 0x0370, 0x7f10, 0x00f7, 0x0040
            },
            {
                0x0001, 0x0370, 0x673a, 0x00f7, 0x0040
            },
            {
                0x0001, 0x0370, 0x5eba, 0x00f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_64_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_70_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_70_INCLUDED
    // fm6353_regtype70: P? - FM6353 - 74HC138 - 1/4
    // Scan membership: Scan_4
    {
        70, 5,
        {
            {
                0x0001, 0x0370, 0x7fd2, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0370, 0x67ee, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0370, 0x5fb4, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_70_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_117_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_117_INCLUDED
    // fm6353_regtype117: P8 - FM6353 - 1/4
    // Scan membership: Scan_4
    {
        117, 5,
        {
            {
                0x0100, 0x0370, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0102, 0x0370, 0x679c, 0x40f7, 0x0040
            },
            {
                0x8100, 0x0370, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_117_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_118_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_118_INCLUDED
    // fm6353_regtype118: P8 - FM6353 - 1/4
    // Scan membership: Scan_4
    {
        118, 5,
        {
            {
                0xffff, 0x03f0, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0xffff, 0x03f0, 0x679c, 0x40f7, 0x0040
            },
            {
                0xffff, 0x03f0, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_118_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_129_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_129_INCLUDED
    // fm6353_regtype129: P10 - FM6353 - 1/4
    // Scan membership: Scan_4
    {
        129, 5,
        {
            {
                0x0001, 0x0350, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0350, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0350, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_129_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_183_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_183_INCLUDED
    // fm6353_regtype183: FM6353 register profile
    // Scan membership: Scan_4
    {
        183, 5,
        {
            {
                0x0001, 0x03f0, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x03f0, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x03f0, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_183_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_185_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_185_INCLUDED
    // fm6353_regtype185: FM6353 register profile
    // Scan membership: Scan_4
    {
        185, 5,
        {
            {
                0x0100, 0x03f0, 0x7fac, 0x40f7, 0x0040
            },
            {
                0x0100, 0x03f0, 0x67ac, 0x40f7, 0x0040
            },
            {
                0x8100, 0x03f0, 0x5fac, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_185_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_192_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_192_INCLUDED
    // fm6353_regtype192: FM6353 register profile
    // Scan membership: Scan_4
    {
        192, 5,
        {
            {
                0x0001, 0x0360, 0x7fc4, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0360, 0x679e, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0360, 0x5f8a, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_192_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_4_H
