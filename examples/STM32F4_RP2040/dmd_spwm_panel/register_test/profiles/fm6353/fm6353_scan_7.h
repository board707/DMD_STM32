#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_7_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_7_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6353 register profiles. Only Scan_7 profiles are present.

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

#ifndef DMD_SPWM_FM6353_REGTYPE_35_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_35_INCLUDED
    // fm6353_regtype35: P? - FM6353 - 7258 - 1/7
    // Scan membership: Scan_7
    {
        35, 5,
        {
            {
                0x01ff, 0x0670, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x01ff, 0x0670, 0x679c, 0x40f7, 0x0040
            },
            {
                0x81ff, 0x0670, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_35_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_115_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_115_INCLUDED
    // fm6353_regtype115: P4.81 - FM6353 - 5958 - 1/7
    // Scan membership: Scan_7
    {
        115, 5,
        {
            {
                0x0001, 0x0670, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0670, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0670, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_115_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_191_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_191_INCLUDED
    // fm6353_regtype191: FM6353 register profile
    // Scan membership: Scan_7
    {
        191, 5,
        {
            {
                0x0001, 0x0670, 0x7fb4, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0670, 0x679a, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0670, 0x5f9a, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_191_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_7_H
