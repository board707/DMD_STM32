#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_15_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_15_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6363
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6363 register profiles. Only Scan_15 profiles are present.

#ifndef DMD_SPWM_FM6363_REGTYPE_60_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_60_INCLUDED
    // fm6363_regtype60: P4.8 - FM6363 - 1/15
    // Scan membership: Scan_15
    {
        60, 5,
        {
            {
                0x0eb8, 0xf39c, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x0eb8, 0xe79c, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x0eb8, 0xd79c, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_60_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_15_H
