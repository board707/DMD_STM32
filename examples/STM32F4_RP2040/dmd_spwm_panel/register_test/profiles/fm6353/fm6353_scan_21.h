#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_21_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_21_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6353 register profiles. Only Scan_21 profiles are present.

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

#ifndef DMD_SPWM_FM6353_REGTYPE_101_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_101_INCLUDED
    // fm6353_regtype101: P2.976 - FM6353 - 1/21
    // Scan membership: Scan_21
    {
        101, 5,
        {
            {
                0x0001, 0x5478, 0x7f9c, 0x40f7, 0x4040
            },
            {
                0x0001, 0x5478, 0x679c, 0x40f7, 0x4040
            },
            {
                0x0001, 0x5478, 0x5f9c, 0x40f7, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_101_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_172_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_172_INCLUDED
    // fm6353_regtype172: FM6353 register profile
    // Scan membership: Scan_21
    {
        172, 5,
        {
            {
                0x0001, 0x1470, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1470, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1470, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_172_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_173_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_173_INCLUDED
    // fm6353_regtype173: FM6353 register profile
    // Scan membership: Scan_21
    {
        173, 5,
        {
            {
                0x0000, 0x1470, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1470, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1470, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_173_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_174_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_174_INCLUDED
    // fm6353_regtype174: FM6353 register profile
    // Scan membership: Scan_21
    {
        174, 5,
        {
            {
                0x0001, 0x14f8, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x14f8, 0x679c, 0x40f7, 0x0070
            },
            {
                0x0001, 0x14f8, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_174_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_175_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_175_INCLUDED
    // fm6353_regtype175: FM6353 register profile
    // Scan membership: Scan_21
    {
        175, 5,
        {
            {
                0x0001, 0x1470, 0x7ffe, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1470, 0x67fe, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1470, 0x5ffe, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_175_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_21_H
