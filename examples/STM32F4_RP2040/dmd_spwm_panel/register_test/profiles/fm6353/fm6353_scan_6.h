#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_6_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_6_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6353 register profiles. Only Scan_6 profiles are present.

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

#ifndef DMD_SPWM_FM6353_REGTYPE_67_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_67_INCLUDED
    // fm6353_regtype67: P? - FM6353 - 1/6
    // Scan membership: Scan_6
    {
        67, 5,
        {
            {
                0x0001, 0x0570, 0x7efa, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0570, 0x66c2, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0570, 0x5eda, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_67_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_116_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_116_INCLUDED
    // fm6353_regtype116: P6.67 - FM6353 - 1/6
    // Scan membership: Scan_6
    {
        116, 5,
        {
            {
                0x0001, 0x0570, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0570, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0570, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_116_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_126_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_126_INCLUDED
    // fm6353_regtype126: P6.67 - FM6353 - RUC7258D - 1/6
    // Scan membership: Scan_6
    {
        126, 5,
        {
            {
                0x0001, 0x05f0, 0x7ff0, 0x4017, 0x4040
            },
            {
                0x0001, 0x05f0, 0x67f4, 0x4087, 0x4040
            },
            {
                0x0001, 0x05f0, 0x5ff0, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_126_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_127_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_127_INCLUDED
    // fm6353_regtype127: P? - FM6353 - RUC7258D - 1/6
    // Scan membership: Scan_6
    {
        127, 5,
        {
            {
                0x0001, 0x05f0, 0x7f9c, 0x4017, 0x4040
            },
            {
                0x0001, 0x05f0, 0x679c, 0x4087, 0x4040
            },
            {
                0x0001, 0x05f0, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_127_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_184_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_184_INCLUDED
    // fm6353_regtype184: FM6353 register profile
    // Scan membership: Scan_6
    {
        184, 5,
        {
            {
                0x0001, 0x0578, 0x7f9c, 0x40f7, 0x0060
            },
            {
                0x0001, 0x0578, 0x679c, 0x40f7, 0x4060
            },
            {
                0x0001, 0x0578, 0x5f9c, 0x40f7, 0x4060
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_184_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_6_H
