#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_5_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_5_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// Generated from lib/spwm/registertest/data/fm6353.profiles at
// Raspberry Pi revision f9dc4d0a8c25. Only Scan_5 profiles are present.

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

#ifndef DMD_SPWM_FM6353_REGTYPE_55_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_55_INCLUDED
    // fm6353_regtype55: P? - FM6353 - 74HC138 - 1/5
    // Source scan membership: Scan_5
    {
        55, 5,
        {
            {
                0x0000, 0x0470, 0x7f9c, 0x40f7, 0x0060
            },
            {
                0x0000, 0x0470, 0x679c, 0x40f7, 0x0060
            },
            {
                0x0000, 0x0470, 0x5f9c, 0x40f7, 0x0060
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_55_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_119_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_119_INCLUDED
    // fm6353_regtype119: P8 - FM6353 - 1/5
    // Source scan membership: Scan_5
    {
        119, 5,
        {
            {
                0x0000, 0x0470, 0x7fe8, 0x40f7, 0x0040
            },
            {
                0x0000, 0x0470, 0x67e8, 0x40f7, 0x0040
            },
            {
                0x0000, 0x0470, 0x5fe8, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_119_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_137_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_137_INCLUDED
    // fm6353_regtype137: P? - FM6353 - 1/5
    // Source scan membership: Scan_5
    {
        137, 5,
        {
            {
                0x0000, 0x0470, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x0470, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x0470, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_137_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_5_H
