#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_58_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_58_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6363
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6363 register profiles. Only Scan_58 profiles are present.

#ifndef DMD_SPWM_FM6363_REGTYPE_8_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_8_INCLUDED
    // fm6363_regtype8: P1.5 - FM6363 - 5958 - 1/58
    // Scan membership: Scan_58
    {
        8, 5,
        {
            {
                0xb9f0, 0x639d, 0x4af6, 0x5a70, 0x7e08
            },
            {
                0xb9f0, 0x5b9d, 0x4cf6, 0x5a70, 0x7e08
            },
            {
                0xb9f0, 0x5b9d, 0x60f6, 0x5a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_8_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_32_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_32_INCLUDED
    // fm6363_regtype32: P1.5 - FM6363 - RUL5158 - 1/58
    // Scan membership: Scan_58
    {
        32, 5,
        {
            {
                0xb9f0, 0x679d, 0x0426, 0x1a30, 0x7e08
            },
            {
                0xb9f0, 0x4b9d, 0x0826, 0x1a70, 0x7e08
            },
            {
                0xb9f0, 0x4b9d, 0x2026, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_32_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_58_H
