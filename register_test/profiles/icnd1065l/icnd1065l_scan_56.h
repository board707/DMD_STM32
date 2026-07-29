#ifndef DMD_SPWM_REGISTER_TEST_PROFILES_ICND1065L_SCAN_56_H
#define DMD_SPWM_REGISTER_TEST_PROFILES_ICND1065L_SCAN_56_H

#ifndef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#error "Register-test profile fragments must be included inside the profile array"
#endif

#if DMD_SPWM_REGISTER_TEST_PROFILE_CHIP != DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_ICND1065L
#error "Register-test profile fragment is in the wrong chip array"
#endif

// Only Scan_56 profiles are present.

#ifndef DMD_SPWM_ICND1065L_REGTYPE_370_INCLUDED
#define DMD_SPWM_ICND1065L_REGTYPE_370_INCLUDED
    // icnd1065l_regtype370: P? - ICND1065L - 6158 - 1/56
    // Scan membership: Scan_56
    {
        370, 22,
        {
            {
                0x0000, 0x0277, 0x032a, 0x0412, 0x0500, 0x0601, 0x0720, 0x0c18,
                0x0d01, 0x0e88, 0x0f01, 0x1040, 0x1127, 0x1800, 0x1906, 0x1c65,
                0x1dea, 0x1e71, 0x2040, 0x2100, 0x2340, 0x74a0
            },
            {
                0x0000, 0x0277, 0x032a, 0x0412, 0x0500, 0x0601, 0x0720, 0x0c1e,
                0x0d01, 0x0e88, 0x0f01, 0x1040, 0x1127, 0x1800, 0x1908, 0x1c61,
                0x1dea, 0x1e75, 0x2060, 0x2100, 0x2340, 0x74a0
            },
            {
                0x0000, 0x0277, 0x032a, 0x0412, 0x0500, 0x0601, 0x0720, 0x0c1e,
                0x0d01, 0x0e88, 0x0f01, 0x1040, 0x1127, 0x1800, 0x190a, 0x1c64,
                0x1dea, 0x1eb5, 0x2060, 0x2100, 0x2340, 0x74a0
            }
        }
    },
#endif  // DMD_SPWM_ICND1065L_REGTYPE_370_INCLUDED

#endif  // DMD_SPWM_REGISTER_TEST_PROFILES_ICND1065L_SCAN_56_H
