#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_ICND1065L_SCAN_4_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_ICND1065L_SCAN_4_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_ICND1065L
#error "Register-test profile fragment is in the wrong chip array"
#endif

// Generated from lib/spwm/registertest/data/icnd1065l.profiles at
// Raspberry Pi revision f9dc4d0a8c25. Only Scan_4 profiles are present.

#ifndef DMD_SPWM_ICND1065L_REGTYPE_358_INCLUDED
#define DMD_SPWM_ICND1065L_REGTYPE_358_INCLUDED
    // icnd1065l_regtype358: P? - ICND1065L - 1/4
    // Source scan membership: Scan_4
    {
        358, 22,
        {
            {
                0x0000, 0x0243, 0x037f, 0x040b, 0x0500, 0x0601, 0x0710, 0x0c10,
                0x0d01, 0x0e88, 0x0f01, 0x1040, 0x1127, 0x1800, 0x1906, 0x1c60,
                0x1dca, 0x1e71, 0x2040, 0x2101, 0x2300, 0x74a0
            },
            {
                0x0000, 0x0243, 0x037f, 0x040b, 0x0500, 0x0601, 0x0710, 0x0c10,
                0x0d01, 0x0e88, 0x0f01, 0x1040, 0x1127, 0x1800, 0x1908, 0x1c60,
                0x1dca, 0x1e75, 0x2060, 0x2101, 0x2300, 0x74a0
            },
            {
                0x0000, 0x0243, 0x037f, 0x040b, 0x0500, 0x0601, 0x0710, 0x0c10,
                0x0d01, 0x0e88, 0x0f01, 0x1040, 0x1127, 0x1800, 0x190a, 0x1c60,
                0x1dca, 0x1eb5, 0x2060, 0x2101, 0x2300, 0x74a0
            }
        }
    },
#endif  // DMD_SPWM_ICND1065L_REGTYPE_358_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_ICND1065L_SCAN_4_H
