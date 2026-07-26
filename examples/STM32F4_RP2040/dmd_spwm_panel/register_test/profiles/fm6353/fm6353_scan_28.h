#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_28_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_28_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// Generated from lib/spwm/registertest/data/fm6353.profiles at
// Raspberry Pi revision f9dc4d0a8c25. Only Scan_28 profiles are present.

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

#ifndef DMD_SPWM_FM6353_REGTYPE_74_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_74_INCLUDED
    // fm6353_regtype74: P? - FM6353 - 1/28
    // Source scan membership: Scan_28
    {
        74, 5,
        {
            {
                0x0001, 0x5bf0, 0x7fa4, 0x40f7, 0x0040
            },
            {
                0x0001, 0x5bf0, 0x673e, 0x40f7, 0x0040
            },
            {
                0x0001, 0x5bf0, 0x5f0a, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_74_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_75_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_75_INCLUDED
    // fm6353_regtype75: P? - FM6353 - 1/28
    // Source scan membership: Scan_28
    {
        75, 5,
        {
            {
                0x0001, 0x1bf8, 0x6340, 0x40f7, 0x4040
            },
            {
                0x0001, 0x1bf8, 0x4b40, 0x40e7, 0x4040
            },
            {
                0x0001, 0x1bf8, 0x4380, 0x40c7, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_75_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_28_H
