#ifndef DMD_SPWM_REGISTER_TEST_CONFIG_H
#define DMD_SPWM_REGISTER_TEST_CONFIG_H

#ifndef DMD_SPWM_REGISTER_TEST_ENABLED
#define DMD_SPWM_REGISTER_TEST_ENABLED 0
#endif

// Zero uses the driver's normal register configuration. A positive value
// selects that source catalog regtype for the chip named by the driver type.
#ifndef DMD_SPWM_REGISTER_OVERRIDE
#define DMD_SPWM_REGISTER_OVERRIDE 0
#endif

#if DMD_SPWM_REGISTER_OVERRIDE < 0 || DMD_SPWM_REGISTER_OVERRIDE > 65535
#error "DMD_SPWM_REGISTER_OVERRIDE must be 0 or a uint16_t regtype number"
#endif

#if DMD_SPWM_REGISTER_TEST_ENABLED && DMD_SPWM_REGISTER_OVERRIDE > 0
#error "Disable the register test before selecting a fixed register override"
#endif

#if DMD_SPWM_REGISTER_TEST_ENABLED || DMD_SPWM_REGISTER_OVERRIDE > 0

#if ((!defined(__STM32F4__) || defined(DMD_STM32DUINO)) && \
     !defined(ARDUINO_ARCH_RP2040))
#error "The SPWM register test/override requires libmaple STM32F4 or RP2040"
#endif

#include "register_test_driver.h"

// Select any number of scan-rate fragments in each chip section. The driver
// type chooses the matching catalog, so no separate chip macro is needed.
// Fixed-register override mode searches these same arrays: uncomment the scan
// fragment containing the requested REG number before enabling an override.
#define DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353 1
#define DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6363 2
#define DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6373 3
#define DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_ICND1065L 4
#define DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_SM16380SH 5
#define DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY 1

#define DMD_SPWM_REGISTER_TEST_PROFILE_CHIP \
    DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
static constexpr DMD_SPWM_FM6353_RegisterTestProfile
dmd_spwm_fm6353_register_test_profiles[] = {
// #include "profiles/fm6353/fm6353_scan_2.h"
// #include "profiles/fm6353/fm6353_scan_3.h"
// #include "profiles/fm6353/fm6353_scan_4.h"
// #include "profiles/fm6353/fm6353_scan_5.h"
// #include "profiles/fm6353/fm6353_scan_6.h"
// #include "profiles/fm6353/fm6353_scan_7.h"
// #include "profiles/fm6353/fm6353_scan_8.h"
// #include "profiles/fm6353/fm6353_scan_10.h"
// #include "profiles/fm6353/fm6353_scan_11.h"
// #include "profiles/fm6353/fm6353_scan_12.h"
// #include "profiles/fm6353/fm6353_scan_13.h"
// #include "profiles/fm6353/fm6353_scan_14.h"
// #include "profiles/fm6353/fm6353_scan_15.h"
// #include "profiles/fm6353/fm6353_scan_16.h"
// #include "profiles/fm6353/fm6353_scan_18.h"
// #include "profiles/fm6353/fm6353_scan_20.h"
// #include "profiles/fm6353/fm6353_scan_21.h"
// #include "profiles/fm6353/fm6353_scan_23.h"
// #include "profiles/fm6353/fm6353_scan_24.h"
// #include "profiles/fm6353/fm6353_scan_25.h"
// #include "profiles/fm6353/fm6353_scan_26.h"
// #include "profiles/fm6353/fm6353_scan_27.h"
// #include "profiles/fm6353/fm6353_scan_28.h"
// #include "profiles/fm6353/fm6353_scan_29.h"
// #include "profiles/fm6353/fm6353_scan_30.h"
// #include "profiles/fm6353/fm6353_scan_31.h"
// #include "profiles/fm6353/fm6353_scan_32.h"
};
#undef DMD_SPWM_REGISTER_TEST_PROFILE_CHIP

#define DMD_SPWM_REGISTER_TEST_PROFILE_CHIP \
    DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6363
static constexpr DMD_SPWM_FM6363_RegisterTestProfile
dmd_spwm_fm6363_register_test_profiles[] = {
// #include "profiles/fm6363/fm6363_scan_2.h"
// #include "profiles/fm6363/fm6363_scan_5.h"
// #include "profiles/fm6363/fm6363_scan_6.h"
// #include "profiles/fm6363/fm6363_scan_8.h"
// #include "profiles/fm6363/fm6363_scan_10.h"
// #include "profiles/fm6363/fm6363_scan_11.h"
// #include "profiles/fm6363/fm6363_scan_13.h"
// #include "profiles/fm6363/fm6363_scan_15.h"
// #include "profiles/fm6363/fm6363_scan_16.h"
// #include "profiles/fm6363/fm6363_scan_19.h"
// #include "profiles/fm6363/fm6363_scan_21.h"
// #include "profiles/fm6363/fm6363_scan_26.h"
// #include "profiles/fm6363/fm6363_scan_32.h"
// #include "profiles/fm6363/fm6363_scan_40.h"
// #include "profiles/fm6363/fm6363_scan_43.h"
// #include "profiles/fm6363/fm6363_scan_45.h"
// #include "profiles/fm6363/fm6363_scan_48.h"
// #include "profiles/fm6363/fm6363_scan_52.h"
// #include "profiles/fm6363/fm6363_scan_58.h"
// #include "profiles/fm6363/fm6363_scan_64.h"
};
#undef DMD_SPWM_REGISTER_TEST_PROFILE_CHIP

#define DMD_SPWM_REGISTER_TEST_PROFILE_CHIP \
    DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6373
static constexpr DMD_SPWM_FM6373_RegisterTestProfile
dmd_spwm_fm6373_register_test_profiles[] = {
// #include "profiles/fm6373/fm6373_scan_5.h"
// #include "profiles/fm6373/fm6373_scan_8.h"
// #include "profiles/fm6373/fm6373_scan_10.h"
// #include "profiles/fm6373/fm6373_scan_13.h"
// #include "profiles/fm6373/fm6373_scan_16.h"
// #include "profiles/fm6373/fm6373_scan_20.h"
// #include "profiles/fm6373/fm6373_scan_21.h"
// #include "profiles/fm6373/fm6373_scan_32.h"
// #include "profiles/fm6373/fm6373_scan_40.h"
// #include "profiles/fm6373/fm6373_scan_43.h"
// #include "profiles/fm6373/fm6373_scan_52.h"
// #include "profiles/fm6373/fm6373_scan_64.h"
};
#undef DMD_SPWM_REGISTER_TEST_PROFILE_CHIP

#define DMD_SPWM_REGISTER_TEST_PROFILE_CHIP \
    DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_ICND1065L
static constexpr DMD_SPWM_ICND1065L_RegisterTestProfile
dmd_spwm_icnd1065l_register_test_profiles[] = {
// #include "profiles/icnd1065l/icnd1065l_scan_2.h"
// #include "profiles/icnd1065l/icnd1065l_scan_4.h"
// #include "profiles/icnd1065l/icnd1065l_scan_5.h"
// #include "profiles/icnd1065l/icnd1065l_scan_6.h"
// #include "profiles/icnd1065l/icnd1065l_scan_8.h"
// #include "profiles/icnd1065l/icnd1065l_scan_10.h"
// #include "profiles/icnd1065l/icnd1065l_scan_13.h"
// #include "profiles/icnd1065l/icnd1065l_scan_16.h"
// #include "profiles/icnd1065l/icnd1065l_scan_20.h"
// #include "profiles/icnd1065l/icnd1065l_scan_26.h"
// #include "profiles/icnd1065l/icnd1065l_scan_32.h"
// #include "profiles/icnd1065l/icnd1065l_scan_40.h"
// #include "profiles/icnd1065l/icnd1065l_scan_43.h"
// #include "profiles/icnd1065l/icnd1065l_scan_45.h"
// #include "profiles/icnd1065l/icnd1065l_scan_48.h"
// #include "profiles/icnd1065l/icnd1065l_scan_52.h"
// #include "profiles/icnd1065l/icnd1065l_scan_54.h"
// #include "profiles/icnd1065l/icnd1065l_scan_56.h"
// #include "profiles/icnd1065l/icnd1065l_scan_58.h"
// #include "profiles/icnd1065l/icnd1065l_scan_60.h"
// #include "profiles/icnd1065l/icnd1065l_scan_64.h"
};
#undef DMD_SPWM_REGISTER_TEST_PROFILE_CHIP

#define DMD_SPWM_REGISTER_TEST_PROFILE_CHIP \
    DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_SM16380SH
static constexpr DMD_SPWM_SM16380SH_RegisterTestProfile
dmd_spwm_sm16380sh_register_test_profiles[] = {
// #include "profiles/sm16380sh/sm16380sh_scan_2.h"
// #include "profiles/sm16380sh/sm16380sh_scan_5.h"
// #include "profiles/sm16380sh/sm16380sh_scan_6.h"
// #include "profiles/sm16380sh/sm16380sh_scan_8.h"
// #include "profiles/sm16380sh/sm16380sh_scan_10.h"
// #include "profiles/sm16380sh/sm16380sh_scan_16.h"
// #include "profiles/sm16380sh/sm16380sh_scan_20.h"
// #include "profiles/sm16380sh/sm16380sh_scan_21.h"
// #include "profiles/sm16380sh/sm16380sh_scan_24.h"
// #include "profiles/sm16380sh/sm16380sh_scan_26.h"
#include "profiles/sm16380sh/sm16380sh_scan_32.h"
// #include "profiles/sm16380sh/sm16380sh_scan_40.h"
// #include "profiles/sm16380sh/sm16380sh_scan_43.h"
// #include "profiles/sm16380sh/sm16380sh_scan_52.h"
// #include "profiles/sm16380sh/sm16380sh_scan_64.h"
};
#undef DMD_SPWM_REGISTER_TEST_PROFILE_CHIP

#undef DMD_SPWM_REGISTER_TEST_BUILDING_PROFILE_ARRAY
#undef DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6353
#undef DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6363
#undef DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_FM6373
#undef DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_ICND1065L
#undef DMD_SPWM_REGISTER_TEST_PROFILE_CHIP_SM16380SH

template <typename DmdType>
struct DMD_SPWM_RegisterTestCatalog;

template <typename ProfileType>
static constexpr bool dmdSpwmRegisterTestCatalogContains(
    const ProfileType *profiles, uint16_t count, uint16_t catalog_index)
{
    return count == 0 ? false :
        profiles[0].catalog_index == catalog_index ? true :
        dmdSpwmRegisterTestCatalogContains(
            profiles + 1, count - 1, catalog_index);
}

template <int... Pars>
struct DMD_SPWM_RegisterTestCatalog<DMD_RGB_FM6353_RegisterTest<Pars...> > {
    typedef DMD_SPWM_FM6353_RegisterTestProfile ProfileType;
    enum {
        PROFILE_COUNT = sizeof(dmd_spwm_fm6353_register_test_profiles) /
                        sizeof(dmd_spwm_fm6353_register_test_profiles[0])
    };
    static const ProfileType *profiles()
    {
        return dmd_spwm_fm6353_register_test_profiles;
    }
    static uint16_t profileCount() { return PROFILE_COUNT; }
    static constexpr bool contains(uint16_t catalog_index)
    {
        return dmdSpwmRegisterTestCatalogContains(
            dmd_spwm_fm6353_register_test_profiles,
            PROFILE_COUNT, catalog_index);
    }
};

template <int... Pars>
struct DMD_SPWM_RegisterTestCatalog<DMD_RGB_FM6363_RegisterTest<Pars...> > {
    typedef DMD_SPWM_FM6363_RegisterTestProfile ProfileType;
    enum {
        PROFILE_COUNT = sizeof(dmd_spwm_fm6363_register_test_profiles) /
                        sizeof(dmd_spwm_fm6363_register_test_profiles[0])
    };
    static const ProfileType *profiles()
    {
        return dmd_spwm_fm6363_register_test_profiles;
    }
    static uint16_t profileCount() { return PROFILE_COUNT; }
    static constexpr bool contains(uint16_t catalog_index)
    {
        return dmdSpwmRegisterTestCatalogContains(
            dmd_spwm_fm6363_register_test_profiles,
            PROFILE_COUNT, catalog_index);
    }
};

template <int... Pars>
struct DMD_SPWM_RegisterTestCatalog<DMD_RGB_FM6373_RegisterTest<Pars...> > {
    typedef DMD_SPWM_FM6373_RegisterTestProfile ProfileType;
    enum {
        PROFILE_COUNT = sizeof(dmd_spwm_fm6373_register_test_profiles) /
                        sizeof(dmd_spwm_fm6373_register_test_profiles[0])
    };
    static const ProfileType *profiles()
    {
        return dmd_spwm_fm6373_register_test_profiles;
    }
    static uint16_t profileCount() { return PROFILE_COUNT; }
    static constexpr bool contains(uint16_t catalog_index)
    {
        return dmdSpwmRegisterTestCatalogContains(
            dmd_spwm_fm6373_register_test_profiles,
            PROFILE_COUNT, catalog_index);
    }
};

template <int... Pars>
struct DMD_SPWM_RegisterTestCatalog<DMD_RGB_ICN1065_RegisterTest<Pars...> > {
    typedef DMD_SPWM_ICND1065L_RegisterTestProfile ProfileType;
    enum {
        PROFILE_COUNT = sizeof(dmd_spwm_icnd1065l_register_test_profiles) /
                        sizeof(dmd_spwm_icnd1065l_register_test_profiles[0])
    };
    static const ProfileType *profiles()
    {
        return dmd_spwm_icnd1065l_register_test_profiles;
    }
    static uint16_t profileCount() { return PROFILE_COUNT; }
    static constexpr bool contains(uint16_t catalog_index)
    {
        return dmdSpwmRegisterTestCatalogContains(
            dmd_spwm_icnd1065l_register_test_profiles,
            PROFILE_COUNT, catalog_index);
    }
};

template <int... Pars>
struct DMD_SPWM_RegisterTestCatalog<
    DMD_RGB_SM16380SH_RegisterTest<Pars...> > {
    typedef DMD_SPWM_SM16380SH_RegisterTestProfile ProfileType;
    enum {
        PROFILE_COUNT = sizeof(dmd_spwm_sm16380sh_register_test_profiles) /
                        sizeof(dmd_spwm_sm16380sh_register_test_profiles[0])
    };
    static const ProfileType *profiles()
    {
        return dmd_spwm_sm16380sh_register_test_profiles;
    }
    static uint16_t profileCount() { return PROFILE_COUNT; }
    static constexpr bool contains(uint16_t catalog_index)
    {
        return dmdSpwmRegisterTestCatalogContains(
            dmd_spwm_sm16380sh_register_test_profiles,
            PROFILE_COUNT, catalog_index);
    }
};

#ifndef DMD_SPWM_REGISTER_TEST_WORD_DELAY_MS
#define DMD_SPWM_REGISTER_TEST_WORD_DELAY_MS 30
#endif

#if DMD_SPWM_REGISTER_TEST_ENABLED

#if defined(ARDUINO_ARCH_RP2040)
#ifndef DMD_SPWM_REGISTER_TEST_AUTO_ADVANCE_MS
#define DMD_SPWM_REGISTER_TEST_AUTO_ADVANCE_MS 3000UL
#endif
#if DMD_SPWM_REGISTER_TEST_AUTO_ADVANCE_MS < 1
#error "DMD_SPWM_REGISTER_TEST_AUTO_ADVANCE_MS must be at least 1"
#endif
#else
// Choose an application button exposed by the selected board variant.
#ifndef DMD_SPWM_REGISTER_TEST_BUTTON_PIN
#if defined(BOARD_BUTTON2_PIN)
#define DMD_SPWM_REGISTER_TEST_BUTTON_PIN BOARD_BUTTON2_PIN
#elif defined(BTN_K0)
#define DMD_SPWM_REGISTER_TEST_BUTTON_PIN BTN_K0
#elif defined(MCU_STM32F401CC) || defined(MCU_STM32F411CE)
#define DMD_SPWM_REGISTER_TEST_BUTTON_PIN PA0
#else
#error "Set DMD_SPWM_REGISTER_TEST_BUTTON_PIN to an unused active-low button pin"
#endif
#endif

#define DMD_SPWM_REGISTER_TEST_BUTTON_ACTIVE_LEVEL LOW
#define DMD_SPWM_REGISTER_TEST_HOLD_MS 1200
#endif

template <typename DmdType>
static uint16_t dmdSpwmRunSelectedRegisterTest(DmdType &dmd)
{
    typedef DMD_SPWM_RegisterTestCatalog<DmdType> Catalog;
    static_assert(Catalog::PROFILE_COUNT > 0,
                  "Uncomment at least one scan profile for this SPWM driver");
#if defined(ARDUINO_ARCH_RP2040)
    return dmdSpwmRunRegisterTestAuto(
        dmd, Catalog::profiles(), Catalog::profileCount(),
        DMD_SPWM_REGISTER_TEST_AUTO_ADVANCE_MS,
        DMD_SPWM_REGISTER_TEST_WORD_DELAY_MS);
#else
    return dmdSpwmRunRegisterTest(
        dmd, Catalog::profiles(), Catalog::profileCount(),
        DMD_SPWM_REGISTER_TEST_BUTTON_PIN,
        DMD_SPWM_REGISTER_TEST_BUTTON_ACTIVE_LEVEL,
        DMD_SPWM_REGISTER_TEST_HOLD_MS,
        DMD_SPWM_REGISTER_TEST_WORD_DELAY_MS);
#endif
}

#else // DMD_SPWM_REGISTER_OVERRIDE > 0

template <typename DmdType>
static bool dmdSpwmApplySelectedRegisterOverride(DmdType &dmd)
{
    typedef DMD_SPWM_RegisterTestCatalog<DmdType> Catalog;
    static_assert(
        Catalog::contains(DMD_SPWM_REGISTER_OVERRIDE),
        "DMD_SPWM_REGISTER_OVERRIDE REG is not in the uncommented scan profiles");

    for (uint16_t profile = 0; profile < Catalog::PROFILE_COUNT; profile++)
    {
        if (Catalog::profiles()[profile].catalog_index ==
            DMD_SPWM_REGISTER_OVERRIDE)
        {
            return dmd.applyRegisterConfig(
                Catalog::profiles()[profile],
                DMD_SPWM_REGISTER_TEST_WORD_DELAY_MS);
        }
    }
    return false;
}

#endif // DMD_SPWM_REGISTER_TEST_ENABLED

// Keep the sketch's original driver declarations. These example-local macros
// select the matching register-test adapter only while the feature is active.
#define DMD_RGB_FM6353 DMD_RGB_FM6353_RegisterTest
#define DMD_RGB_FM6363 DMD_RGB_FM6363_RegisterTest
#define DMD_RGB_FM6373 DMD_RGB_FM6373_RegisterTest
#define DMD_RGB_ICN1065 DMD_RGB_ICN1065_RegisterTest
#define DMD_RGB_SM16380SH DMD_RGB_SM16380SH_RegisterTest

#endif
#endif // DMD_SPWM_REGISTER_TEST_CONFIG_H
