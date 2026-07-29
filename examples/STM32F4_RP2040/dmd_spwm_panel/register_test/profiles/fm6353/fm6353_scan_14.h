#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_14_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_14_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6353 register profiles. Only Scan_14 profiles are present.

#ifndef DMD_SPWM_FM6353_REGTYPE_76_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_76_INCLUDED
    // fm6353_regtype76: P? - FM6353 - 1/14
    // Scan membership: Scan_14
    {
        76, 5,
        {
            {
                0x0001, 0x0d70, 0x7f9c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0d70, 0x679c, 0x40f7, 0x0040
            },
            {
                0x0001, 0x0d70, 0x5f9c, 0x40f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_76_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_14_H
