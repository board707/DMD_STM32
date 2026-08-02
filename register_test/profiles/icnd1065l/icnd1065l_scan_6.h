#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_ICND1065L_SCAN_6_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_ICND1065L_SCAN_6_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_ICND1065L
#error "Register-test profile fragment is in the wrong chip array"
#endif

// Only Scan_6 profiles are present.

#ifndef DMD_SPWM_ICND1065L_REGTYPE_36_INCLUDED
#define DMD_SPWM_ICND1065L_REGTYPE_36_INCLUDED
    // icnd1065l_regtype36: P6 - ICND1065L - 1/6
    // Scan membership: Scan_6
    {
        36, 22,
        {
            {
                0x0000, 0x0245, 0x031f, 0x040b, 0x0500, 0x0601, 0x0740, 0x0c18,
                0x0d01, 0x0e84, 0x0f01, 0x1040, 0x1127, 0x1800, 0x1906, 0x1c7f,
                0x1dea, 0x1e71, 0x2040, 0x2101, 0x2340, 0x74a0
            },
            {
                0x0000, 0x0245, 0x031f, 0x040b, 0x0500, 0x0601, 0x0740, 0x0c1e,
                0x0d01, 0x0e84, 0x0f01, 0x1040, 0x1127, 0x1800, 0x1908, 0x1c7f,
                0x1dea, 0x1e55, 0x2060, 0x2101, 0x2340, 0x74a0
            },
            {
                0x0000, 0x0245, 0x031f, 0x040b, 0x0500, 0x0601, 0x0740, 0x0c1e,
                0x0d01, 0x0e84, 0x0f01, 0x1040, 0x1127, 0x1800, 0x190d, 0x1c7f,
                0x1dea, 0x1e85, 0x2060, 0x2101, 0x2340, 0x74a0
            }
        }
    },
#endif  // DMD_SPWM_ICND1065L_REGTYPE_36_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_ICND1065L_SCAN_6_H
