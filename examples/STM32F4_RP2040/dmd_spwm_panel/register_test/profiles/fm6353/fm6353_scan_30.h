#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_30_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_30_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6353 register profiles. Only Scan_30 profiles are present.

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

#ifndef DMD_SPWM_FM6353_REGTYPE_29_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_29_INCLUDED
    // fm6353_regtype29: P? - FM6353 - 1/30
    // Scan membership: Scan_30
    {
        29, 5,
        {
            {
                0x0000, 0x5df8, 0x530e, 0x40f7, 0x0040
            },
            {
                0x0000, 0x5df8, 0x42f4, 0x4017, 0x4040
            },
            {
                0x0000, 0x5df8, 0x2b12, 0x4017, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_29_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_84_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_84_INCLUDED
    // fm6353_regtype84: P1.25 - FM6353 - 5958 - 1/30
    // Scan membership: Scan_30
    {
        84, 5,
        {
            {
                0x0000, 0x1df8, 0x4fb2, 0x40f7, 0x4040
            },
            {
                0x0000, 0x1df8, 0x3ba8, 0x4017, 0x4040
            },
            {
                0x0000, 0x1df8, 0x2fa0, 0x4017, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_84_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_85_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_85_INCLUDED
    // fm6353_regtype85: P1.25 - FM6353 - 1/30
    // Scan membership: Scan_30
    {
        85, 5,
        {
            {
                0x0000, 0x1d70, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1d70, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1d70, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_85_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_133_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_133_INCLUDED
    // fm6353_regtype133: P? - FM6353 - 74HC138 - 1/30
    // Scan membership: Scan_30
    {
        133, 5,
        {
            {
                0x0000, 0x5db8, 0x7f9d, 0x4007, 0x0060
            },
            {
                0x0000, 0x5db8, 0x739c, 0x4007, 0x0060
            },
            {
                0x0000, 0x5db8, 0x5f9c, 0x4007, 0x0060
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_133_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_134_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_134_INCLUDED
    // fm6353_regtype134: P? - FM6353 - 74HC138 - 1/30
    // Scan membership: Scan_30
    {
        134, 5,
        {
            {
                0x0000, 0x1d78, 0x7761, 0x40f3, 0x0000
            },
            {
                0x0000, 0x1d78, 0x6f16, 0x4063, 0x4050
            },
            {
                0x0000, 0x1d78, 0x5f70, 0x4063, 0x4050
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_134_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_148_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_148_INCLUDED
    // fm6353_regtype148: P? - FM6353 - 74HC138 - 1/30
    // Scan membership: Scan_30
    {
        148, 5,
        {
            {
                0x0000, 0x1df8, 0x7fac, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1df8, 0x67b0, 0x40f7, 0x0040
            },
            {
                0x0000, 0x1df8, 0x5fa8, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_148_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_149_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_149_INCLUDED
    // fm6353_regtype149: P? - FM6353 - 74HC138 - 1/30
    // Scan membership: Scan_30
    {
        149, 5,
        {
            {
                0x0100, 0x1df8, 0x531d, 0x40f7, 0x0040
            },
            {
                0x0100, 0x1df8, 0x3f38, 0x4007, 0x4040
            },
            {
                0x8100, 0x1df8, 0x372a, 0x4007, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_149_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_150_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_150_INCLUDED
    // fm6353_regtype150: P? - FM6353 - 74HC138 - 1/30
    // Scan membership: Scan_30
    {
        150, 5,
        {
            {
                0x0000, 0x1df8, 0x4f37, 0x40f7, 0x4040
            },
            {
                0x0000, 0x1df8, 0x377a, 0x4097, 0x4040
            },
            {
                0x0000, 0x1df8, 0x2f5e, 0x4017, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_150_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_156_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_156_INCLUDED
    // fm6353_regtype156: P1.667 - FM6353 - 5958 - 1/30
    // Scan membership: Scan_30
    {
        156, 5,
        {
            {
                0x0001, 0x1df8, 0x4f9e, 0x4017, 0x4040
            },
            {
                0x0001, 0x1df8, 0x43aa, 0x4017, 0x4040
            },
            {
                0x0001, 0x1df8, 0x2fa2, 0x4017, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_156_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_189_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_189_INCLUDED
    // fm6353_regtype189: FM6353 register profile
    // Scan membership: Scan_30
    {
        189, 5,
        {
            {
                0x0001, 0x1d78, 0x5af6, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1d78, 0x62f6, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1d78, 0x6af6, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_189_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_30_H
