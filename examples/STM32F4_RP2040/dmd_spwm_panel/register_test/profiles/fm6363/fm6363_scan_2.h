#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_2_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_2_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6363
#error "Register-test profile fragment is in the wrong chip array"
#endif

// Generated from lib/spwm/registertest/data/fm6363.profiles at
// Raspberry Pi revision f9dc4d0a8c25. Only Scan_2 profiles are present.

#ifndef DMD_SPWM_FM6363_REGTYPE_39_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_39_INCLUDED
    // fm6363_regtype39: P10 - FM6363 - 5958 - 1/2
    // Source scan membership: Scan_2
    {
        39, 5,
        {
            {
                0x01b8, 0xf39c, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x01b8, 0xe79c, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x01b8, 0xd79c, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_39_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_73_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_73_INCLUDED
    // fm6363_regtype73: P10 - FM6363 - 1/2
    // Source scan membership: Scan_2
    {
        73, 5,
        {
            {
                0x01b0, 0xf2de, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x01b0, 0xe710, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x01b0, 0xd6e4, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_73_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_2_H
