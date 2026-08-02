#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_16_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_16_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6353 register profiles. Only Scan_16 profiles are present.

#ifndef DMD_SPWM_FM6353_REGTYPE_9_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_9_INCLUDED
    // fm6353_regtype9: P3.91 - FM6353 - ICN2053 schema - 5368 - 1/16
    // Scan membership: Scan_16
    {
        9, 5,
        {
            {
                0x0008, 0x0f70, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0008, 0x0f70, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0008, 0x0f70, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_9_INCLUDED

#ifndef DMD_SPWM_FM6353_REGTYPE_13_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_13_INCLUDED
    // fm6353_regtype13: P3 - FM6353 - ICN2053 schema - 1/16
    // Scan membership: Scan_16
    {
        13, 5,
        {
            {
                0x0008, 0x4f38, 0x7f9c, 0x4017, 0x4040
            },
            {
                0x0008, 0x4f38, 0x7f9c, 0x4017, 0x4040
            },
            {
                0x0008, 0x4f38, 0x5f9c, 0x4017, 0x4040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_13_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_16_H
