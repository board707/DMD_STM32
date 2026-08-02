#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_6_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_6_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6363
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6363 register profiles. Only Scan_6 profiles are present.

#ifndef DMD_SPWM_FM6363_REGTYPE_77_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_77_INCLUDED
    // fm6363_regtype77: P6 - FM6363 - 1/6
    // Scan membership: Scan_6
    {
        77, 5,
        {
            {
                0x0578, 0xf313, 0x20b2, 0x0a10, 0x7e08
            },
            {
                0x0578, 0xe6f5, 0x20b2, 0x0a70, 0x7e08
            },
            {
                0x0578, 0xd6ef, 0x20b2, 0x0a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_77_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_6_H
