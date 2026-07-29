#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_19_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_19_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6353 register profiles. Only Scan_19 profiles are present.

#ifndef DMD_SPWM_FM6353_REGTYPE_177_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_177_INCLUDED
    // fm6353_regtype177: FM6353 register profile
    // Scan membership: Scan_19
    {
        177, 5,
        {
            {
                0x0001, 0x1270, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1270, 0x7b9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x1270, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_177_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_19_H
