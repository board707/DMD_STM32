#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_16_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_16_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6353 register profiles. Only Scan_16 profiles are present.

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

#ifndef DMD_SPWM_FM6353_REGTYPE_10_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_10_INCLUDED
    // fm6353_regtype10: P3.91 - FM6353 - 1/16
    // Scan membership: Scan_16
    {
        10, 5,
        {
            {
                0x0001, 0x0f70, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0f70, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0f70, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_10_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_14_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_14_INCLUDED
    // fm6353_regtype14: P3 - FM6353 - 1/16
    // Scan membership: Scan_16
    {
        14, 5,
        {
            {
                0x0001, 0x4f38, 0x7f9c, 0x4017, 0x4040
            },
            {
                0x0001, 0x4f38, 0x7f9c, 0x4017, 0x4040
            },
            {
                0x0001, 0x4f38, 0x5f9c, 0x4017, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_14_INCLUDED

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

#ifndef DMD_SPWM_FM6353_REGTYPE_65_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_65_INCLUDED
    // fm6353_regtype65: P? - FM6353 - 1/16
    // Scan membership: Scan_16
    {
        65, 5,
        {
            {
                0x0001, 0x0fb0, 0x7eaa, 0x00f7, 0x0040
            },
            {
                0x0001, 0x0fb0, 0x668e, 0x00f7, 0x0040
            },
            {
                0x0001, 0x0fb0, 0x5eea, 0x00f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_65_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_77_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_77_INCLUDED
    // fm6353_regtype77: P? - FM6353 - 1/16
    // Scan membership: Scan_16
    {
        77, 5,
        {
            {
                0x0001, 0x0f70, 0x7f6a, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0f70, 0x67b2, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0f70, 0x5f7a, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_77_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_78_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_78_INCLUDED
    // fm6353_regtype78: P? - FM6353 - 1/16
    // Scan membership: Scan_16
    {
        78, 5,
        {
            {
                0x0001, 0x0f70, 0x7f74, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0f70, 0x6722, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0f70, 0x5f40, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_78_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_94_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_94_INCLUDED
    // fm6353_regtype94: P2.5 - FM6353 - 1/16
    // Scan membership: Scan_16
    {
        94, 5,
        {
            {
                0x0001, 0x0fb0, 0x6fc6, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0fb0, 0x5fa2, 0x40b7, 0x4040
            },
            {
                0x0001, 0x0fb0, 0x4b8c, 0x4077, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_94_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_105_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_105_INCLUDED
    // fm6353_regtype105: P3.91 - FM6353 - 1/16
    // Scan membership: Scan_16
    {
        105, 5,
        {
            {
                0x0000, 0x0f78, 0x7ffe, 0x40f7, 0x0040
            },
            {
                0x0000, 0x0f78, 0x67fe, 0x40f7, 0x0040
            },
            {
                0x0000, 0x0f78, 0x5ffe, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_105_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_106_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_106_INCLUDED
    // fm6353_regtype106: P3.91 - FM6353 - 1/16
    // Scan membership: Scan_16
    {
        106, 5,
        {
            {
                0x0001, 0x0f70, 0x7ffe, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0f70, 0x67fe, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0f70, 0x5ffe, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_106_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_107_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_107_INCLUDED
    // fm6353_regtype107: P3.91 - FM6353 - 1/16
    // Scan membership: Scan_16
    {
        107, 5,
        {
            {
                0x0001, 0x4f78, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x4f78, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x4f78, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_107_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_108_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_108_INCLUDED
    // fm6353_regtype108: P3.91 - FM6353 - 1/16
    // Scan membership: Scan_16
    {
        108, 5,
        {
            {
                0x0001, 0x0f70, 0x7fba, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0f70, 0x67ba, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0f70, 0x5fc4, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_108_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_109_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_109_INCLUDED
    // fm6353_regtype109: P3.91 - FM6353 - 1/16
    // Scan membership: Scan_16
    {
        109, 5,
        {
            {
                0x0001, 0x0f70, 0x7f9c, 0x6c00, 0x0000
            },
            {
                0x0001, 0x0f70, 0x679c, 0x7c00, 0x0000
            },
            {
                0x0001, 0x0f70, 0x5f9c, 0x5c00, 0x0000
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_109_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_138_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_138_INCLUDED
    // fm6353_regtype138: P? - FM6353 - ICN2012 - 1/16
    // Scan membership: Scan_16
    {
        138, 5,
        {
            {
                0x0001, 0x4ff0, 0x5b9c, 0x40f7, 0x0000
            },
            {
                0x0001, 0x4ff0, 0x579d, 0x40f7, 0x0000
            },
            {
                0x0001, 0x4ff0, 0x679d, 0x40f7, 0x0070
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_138_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_139_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_139_INCLUDED
    // fm6353_regtype139: P? - FM6353 - ICN2012 - 1/16
    // Scan membership: Scan_16
    {
        139, 5,
        {
            {
                0x0000, 0x4f70, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x4f70, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0000, 0x4f70, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_139_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_159_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_159_INCLUDED
    // fm6353_regtype159: P? - FM6353 - 74HC138 - 1/16
    // Scan membership: Scan_16
    {
        159, 5,
        {
            {
                0x0000, 0x0f70, 0xff9d, 0x40f3, 0x0040
            },
            {
                0x0000, 0x0f70, 0xf39c, 0x40f3, 0x0040
            },
            {
                0x0000, 0x0f70, 0xdf9c, 0x40f3, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_159_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_160_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_160_INCLUDED
    // fm6353_regtype160: P? - FM6353 - 74HC138 - 1/16
    // Scan membership: Scan_16
    {
        160, 5,
        {
            {
                0x0000, 0x0f70, 0xff9c, 0x40f3, 0x0040
            },
            {
                0x0000, 0x0f70, 0xf39c, 0x40f3, 0x0040
            },
            {
                0x0000, 0x0f70, 0xdf9c, 0x40f3, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_160_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_170_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_170_INCLUDED
    // fm6353_regtype170: FM6353 register profile
    // Scan membership: Scan_16
    {
        170, 5,
        {
            {
                0x0001, 0x4ff8, 0x7f8a, 0x40b7, 0x4040
            },
            {
                0x0001, 0x4ff8, 0x67a8, 0x4007, 0x4070
            },
            {
                0x0001, 0x4ff8, 0x5ed0, 0x4007, 0x4070
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_170_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_179_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_179_INCLUDED
    // fm6353_regtype179: FM6353 register profile
    // Scan membership: Scan_16
    {
        179, 5,
        {
            {
                0x0001, 0x0f70, 0x7fb4, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0f70, 0x67b4, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0f70, 0x5fb4, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_179_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_180_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_180_INCLUDED
    // fm6353_regtype180: FM6353 register profile
    // Scan membership: Scan_16
    {
        180, 5,
        {
            {
                0x0001, 0x0f70, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0f70, 0x7b9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0f70, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_180_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_16_H
