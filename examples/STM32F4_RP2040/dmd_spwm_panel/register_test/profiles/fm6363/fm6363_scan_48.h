#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_48_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_48_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6363
#error "Register-test profile fragment is in the wrong chip array"
#endif

// Generated from lib/spwm/registertest/data/fm6363.profiles at
// Raspberry Pi revision f9dc4d0a8c25. Only Scan_48 profiles are present.

#ifndef DMD_SPWM_FM6363_REGTYPE_9_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_9_INCLUDED
    // fm6363_regtype9: P1.8 - FM6363 - 5958 - 1/48
    // Source scan membership: Scan_48
    {
        9, 5,
        {
            {
                0x2ff0, 0x4f9d, 0x4c46, 0x5a60, 0x7e08
            },
            {
                0x2ff0, 0x679d, 0x4a46, 0x5a70, 0x7e08
            },
            {
                0x2ff0, 0x579d, 0x6046, 0x5a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_9_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_15_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_15_INCLUDED
    // fm6363_regtype15: P? - FM6363 - TC7559C - 1/48
    // Source scan membership: Scan_48
    {
        15, 5,
        {
            {
                0x2fb0, 0x73c0, 0x60b6, 0x1a00, 0x7e08
            },
            {
                0x2fb0, 0x67a4, 0x60b6, 0x1a70, 0x7e08
            },
            {
                0x2fb0, 0x577c, 0x60b6, 0x1a70, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_15_INCLUDED

#ifndef DMD_SPWM_FM6363_REGTYPE_18_INCLUDED
#define DMD_SPWM_FM6363_REGTYPE_18_INCLUDED
    // fm6363_regtype18: P1.8 - FM6363 - 5958 - 1/48
    // Source scan membership: Scan_48
    {
        18, 5,
        {
            {
                0xaff0, 0x4b9d, 0x4426, 0x5a60, 0x7e08
            },
            {
                0xaff0, 0x5b9d, 0x4a26, 0x5a40, 0x7e08
            },
            {
                0xaff0, 0x579d, 0x6026, 0x5a40, 0x7e08
            }
        }
    },
#endif  // DMD_SPWM_FM6363_REGTYPE_18_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_FM6363_SCAN_48_H
