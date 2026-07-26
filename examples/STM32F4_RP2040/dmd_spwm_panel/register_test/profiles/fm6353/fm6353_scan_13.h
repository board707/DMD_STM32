#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_13_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_13_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// Generated from lib/spwm/registertest/data/fm6353.profiles at
// Raspberry Pi revision f9dc4d0a8c25. Only Scan_13 profiles are present.

#ifndef DMD_SPWM_FM6353_REGTYPE_4_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_4_INCLUDED
    // fm6353_regtype4: P3.076 - FM6353 - 1/13
    // Source scan membership: Scan_2,Scan_4,Scan_5,Scan_6,Scan_7,Scan_8,Scan_10,Scan_12,Scan_13,Scan_15,Scan_16,Scan_18,Scan_20,Scan_21,Scan_23,Scan_24,Scan_26,Scan_27,Scan_28,Scan_30,Scan_31,Scan_32
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

#ifndef DMD_SPWM_FM6353_REGTYPE_11_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_11_INCLUDED
    // fm6353_regtype11: P4.81 - FM6353 - 1/13
    // Source scan membership: Scan_13
    {
        11, 5,
        {
            {
                0x0001, 0x0c70, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0c70, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0c70, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_11_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_69_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_69_INCLUDED
    // fm6353_regtype69: P? - FM6353 - 1/13
    // Source scan membership: Scan_13
    {
        69, 5,
        {
            {
                0x0001, 0x0c70, 0x7f0c, 0x00f7, 0x0040
            },
            {
                0x0001, 0x0c70, 0x66f8, 0x00f7, 0x0040
            },
            {
                0x0001, 0x0c70, 0x5ef2, 0x00f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_69_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_81_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_81_INCLUDED
    // fm6353_regtype81: P? - FM6353 - 1/13
    // Source scan membership: Scan_13
    {
        81, 5,
        {
            {
                0x0001, 0x0c70, 0x7fd2, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0c70, 0x67fe, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0c70, 0x5f8e, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_81_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_114_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_114_INCLUDED
    // fm6353_regtype114: P4.81 - FM6353 - 5166 - 1/13
    // Source scan membership: Scan_13
    {
        114, 5,
        {
            {
                0x0000, 0x0c70, 0x7ffe, 0x40f7, 0x0040
            },
            {
                0x0000, 0x0c70, 0x67fe, 0x40f7, 0x0040
            },
            {
                0x0000, 0x0c70, 0x5ffe, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_114_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_13_H
