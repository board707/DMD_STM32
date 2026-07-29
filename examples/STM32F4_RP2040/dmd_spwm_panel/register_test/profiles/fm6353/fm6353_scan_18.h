#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_18_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_18_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6353 register profiles. Only Scan_18 profiles are present.

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

#ifndef DMD_SPWM_FM6353_REGTYPE_57_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_57_INCLUDED
    // fm6353_regtype57: P? - FM6353 - 1/18
    // Scan membership: Scan_18
    {
        57, 5,
        {
            {
                0x0001, 0x11f0, 0x7f16, 0x40f7, 0x0040
            },
            {
                0x0001, 0x11f0, 0x66b2, 0x40f7, 0x0040
            },
            {
                0x0001, 0x11f0, 0x5e98, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_57_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_162_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_162_INCLUDED
    // fm6353_regtype162: FM6353 register profile
    // Scan membership: Scan_18
    {
        162, 5,
        {
            {
                0x0001, 0x11f8, 0x7f9d, 0x40f7, 0x0070
            },
            {
                0x0001, 0x11f8, 0x679d, 0x4087, 0x0070
            },
            {
                0x0001, 0x11f8, 0x5f9d, 0x4087, 0x0070
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_162_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_18_H
