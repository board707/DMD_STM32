#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_11_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_11_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#error "Register-test profile fragment is in the wrong chip array"
#endif

// FM6353 register profiles. Only Scan_11 profiles are present.

#ifndef DMD_SPWM_FM6353_REGTYPE_68_INCLUDED
#define DMD_SPWM_FM6353_REGTYPE_68_INCLUDED
    // fm6353_regtype68: P? - FM6353 - 1/11
    // Scan membership: Scan_11
    {
        68, 5,
        {
            {
                0x0001, 0x0a70, 0x7efe, 0x00f7, 0x0040
            },
            {
                0x0001, 0x0a70, 0x66dc, 0x00f7, 0x0040
            },
            {
                0x0001, 0x0a70, 0x5ef6, 0x00f7, 0x0040
            }
        }
    },
#endif  // DMD_SPWM_FM6353_REGTYPE_68_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6353_SCAN_11_H
