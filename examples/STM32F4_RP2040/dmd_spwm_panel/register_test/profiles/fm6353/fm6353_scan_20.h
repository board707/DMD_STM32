#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_20_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_20_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6353 register profiles. Only Scan_20 profiles are present.

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

#ifndef DMD_SPWM_FM6353_REGTYPE_17_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_17_INCLUDED
    // fm6353_regtype17: P? - FM6353 - 1/20
    // Scan membership: Scan_20
    {
        17, 5,
        {
            {
                0x0000, 0x13f8, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x13f8, 0x4b9c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x13f8, 0x439c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_17_INCLUDED

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

#ifndef DMD_SPWM_FM6353_REGTYPE_51_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_51_INCLUDED
    // fm6353_regtype51: P? - FM6353 - 74HC138 - 1/20
    // Scan membership: Scan_20
    {
        51, 5,
        {
            {
                0x0000, 0x1370, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1370, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1370, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_51_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_122_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_122_INCLUDED
    // fm6353_regtype122: P4 - FM6353 - RUC7258D - 1/20
    // Scan membership: Scan_20
    {
        122, 5,
        {
            {
                0x0001, 0x13b0, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x13b0, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x13b0, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_122_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_144_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_144_INCLUDED
    // fm6353_regtype144: P? - FM6353 - 74HC138 - 1/20
    // Scan membership: Scan_20
    {
        144, 5,
        {
            {
                0x0000, 0x1370, 0xff9c, 0x40f3, 0x0040
            },
            {
                0x0000, 0x1370, 0xf39c, 0x40f3, 0x0050
            },
            {
                0x0000, 0x1370, 0xdf9c, 0x40f3, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_144_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_157_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_157_INCLUDED
    // fm6353_regtype157: P? - FM6353 - 1/20
    // Scan membership: Scan_20
    {
        157, 5,
        {
            {
                0x0000, 0x13f8, 0x7f9d, 0x40f7, 0x0000
            },
            {
                0x0000, 0x13f8, 0x679d, 0x40f7, 0x4000
            },
            {
                0x0000, 0x13f8, 0x5f9d, 0x40e7, 0x4000
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_157_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_181_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_181_INCLUDED
    // fm6353_regtype181: FM6353 register profile
    // Scan membership: Scan_20
    {
        181, 5,
        {
            {
                0x0001, 0x1370, 0x7ffe, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1370, 0x67fe, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1370, 0x5ffe, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_181_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_20_H
