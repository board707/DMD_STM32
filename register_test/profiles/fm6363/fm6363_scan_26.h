#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_26_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_26_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6363
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6363 register profiles. Only Scan_26 profiles are present.

#ifndef DMD_SPWM_FM6363_REGTYPE_52_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_52_INCLUDED
    // fm6363_regtype52: P3.076 - FM6363 - 1/26
    // Scan membership: Scan_26
    {
        52, 5,
        {
            {
                0x19b0, 0xf3fe, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x19b0, 0xe7fe, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x19b0, 0xd7fe, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_52_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_53_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_53_INCLUDED
    // fm6363_regtype53: P3.076 - FM6363 - 1/26
    // Scan membership: Scan_26
    {
        53, 5,
        {
            {
                0x19f8, 0xf39d, 0x60b6, 0x1000, 0x7e08
            },
            {
                0x19f8, 0xe79d, 0x60b6, 0x1070, 0x7e08
            },
            {
                0x19f8, 0xd79d, 0x60b6, 0x1070, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_53_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_54_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_54_INCLUDED
    // fm6363_regtype54: P3.076 - FM6363 - 1/26
    // Scan membership: Scan_26
    {
        54, 5,
        {
            {
                0x19f0, 0xf324, 0x60b6, 0x0a00, 0x7e08
            },
            {
                0x19f0, 0xe734, 0x60b6, 0x0a70, 0x7e08
            },
            {
                0x19f0, 0xd76e, 0x60b6, 0x0a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_54_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_26_H
