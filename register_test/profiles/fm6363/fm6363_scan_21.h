#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_21_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_21_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6363
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6363 register profiles. Only Scan_21 profiles are present.

#ifndef DMD_SPWM_FM6363_REGTYPE_48_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_48_INCLUDED
    // fm6363_regtype48: P2.976 - FM6363 - 5166 - 1/21
    // Scan membership: Scan_21
    {
        48, 5,
        {
            {
                0x14b0, 0xf39c, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x14b0, 0xe79c, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x14b0, 0xd79c, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_48_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_49_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_49_INCLUDED
    // fm6363_regtype49: P2.976 - FM6363 - 1/21
    // Scan membership: Scan_21
    {
        49, 5,
        {
            {
                0x14b0, 0xf3fe, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x14b0, 0xe7fe, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x14b0, 0xd7fe, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_49_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_21_H
