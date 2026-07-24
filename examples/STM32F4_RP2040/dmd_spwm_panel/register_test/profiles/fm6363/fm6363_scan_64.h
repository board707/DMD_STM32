#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_64_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_64_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6363
#error "Register-test profile fragment is in the wrong chip array"
#endif

// Generated from lib/spwm/registertest/data/fm6363.profiles at
// Raspberry Pi revision f9dc4d0a8c25. Only Scan_64 profiles are present.

#ifndef DMD_SPWM_FM6363_REGTYPE_2_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_2_INCLUDED
    // fm6363_regtype2: P1.25 - FM6363 - 7559 - 1/64
    // Source scan membership: Scan_64
    {
        2, 5,
        {
            {
                0x3fb0, 0x6375, 0x64c6, 0x5a70, 0x7e08
            },
            {
                0x3fb0, 0x5375, 0x68c6, 0x5a70, 0x7e08
            },
            {
                0x3fb0, 0x4b75, 0x6cc6, 0x5a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_2_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_65_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_65_INCLUDED
    // fm6363_regtype65: P? - FM6363 - 1/64
    // Source scan membership: Scan_64
    {
        65, 5,
        {
            {
                0x3fb0, 0x739c, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x3fb0, 0x679c, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x3fb0, 0x579c, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_65_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_66_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_66_INCLUDED
    // fm6363_regtype66: P? - FM6363 - 1/64
    // Source scan membership: Scan_64
    {
        66, 5,
        {
            {
                0x3fb0, 0x73e4, 0x43f7, 0x304f, 0x7e08
            },
            {
                0x3fb0, 0x5be5, 0x48f7, 0x506f, 0x7e08
            },
            {
                0x3fb0, 0x57e5, 0x4cf7, 0x5070, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_66_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_64_H
