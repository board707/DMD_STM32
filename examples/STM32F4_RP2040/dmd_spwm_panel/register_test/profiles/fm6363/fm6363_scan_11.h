#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_11_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_11_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6363
#error "Register-test profile fragment is in the wrong chip array"
#endif

// Generated from lib/spwm/registertest/data/fm6363.profiles at
// Raspberry Pi revision f9dc4d0a8c25. Only Scan_11 profiles are present.

#ifndef DMD_SPWM_FM6363_REGTYPE_76_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_76_INCLUDED
    // fm6363_regtype76: P5 - FM6363 - 1/11
    // Source scan membership: Scan_11
    {
        76, 5,
        {
            {
                0x0a70, 0xf306, 0x60b6, 0x1a10, 0x7e08
            },
            {
                0x0a70, 0xe702, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x0a70, 0xd720, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_76_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_11_H
