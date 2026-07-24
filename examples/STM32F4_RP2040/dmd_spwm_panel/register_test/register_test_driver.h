#ifndef DMD_SPWM_REGISTER_TEST_DRIVER_H
#define DMD_SPWM_REGISTER_TEST_DRIVER_H

#include "register_test_base.h"

enum DMD_SPWM_RegisterTestWordOrder : uint8_t {
    DMD_SPWM_REGISTER_TEST_WORDS_IN_ORDER,
    DMD_SPWM_REGISTER_TEST_LAST_WORD_FIRST
};

enum DMD_SPWM_RegisterTestLoadMode : uint8_t {
    DMD_SPWM_REGISTER_TEST_LOAD_ALL,
    DMD_SPWM_REGISTER_TEST_LOAD_INDEXED,
    DMD_SPWM_REGISTER_TEST_LOAD_ONE_WORD
};

// Example-local adapter shared by every supported SPWM chip. It only replaces
// the register data; the native driver remains responsible for its own
// LAT/VSYNC/PIO/DMA protocol.
template <typename DriverType, typename ProfileType,
          DMD_SPWM_RegisterTestWordOrder WordOrder =
              DMD_SPWM_REGISTER_TEST_WORDS_IN_ORDER,
          DMD_SPWM_RegisterTestLoadMode LoadMode =
              DMD_SPWM_REGISTER_TEST_LOAD_ONE_WORD,
          bool InsertSm16380shF003 = false>
class DMD_SPWM_RegisterTestDriver : public DriverType
{
public:
    DMD_SPWM_RegisterTestDriver(
        uint8_t *mux_list, byte pin_nOE, byte pin_SCLK, uint8_t *pinlist,
        byte panelsWide, byte panelsHigh, bool double_buffer = false) :
        DriverType(mux_list, pin_nOE, pin_SCLK, pinlist,
                   panelsWide, panelsHigh, double_buffer)
    {
    }

    bool selectRegisterTestProfile(const ProfileType &profile)
    {
        if (profile.word_count == 0 ||
            profile.word_count > ProfileType::MAX_WORDS)
        {
            return false;
        }

        active_profile = &profile;
        active_word = 0;

        if (LoadMode == DMD_SPWM_REGISTER_TEST_LOAD_ONE_WORD)
        {
            this->conf_reg_cnt = 1;
            native_words[0] = profile.channel_words[0][0];
        }
        else
        {
            this->conf_reg_cnt = profile.word_count;
            for (uint8_t target = 0; target < profile.word_count; target++)
            {
                uint8_t source = target;
                if (WordOrder == DMD_SPWM_REGISTER_TEST_LAST_WORD_FIRST)
                {
                    source = (target == 0) ?
                        profile.word_count - 1 : target - 1;
                }
                native_words[target] = profile.channel_words[0][source];
            }
        }

        return true;
    }

    uint8_t registerTestApplyCycles(const ProfileType &profile) const
    {
        return LoadMode == DMD_SPWM_REGISTER_TEST_LOAD_ALL ?
            1 : profile.word_count;
    }

    bool applyRegisterConfig(const ProfileType &profile,
                             uint8_t word_delay_ms)
    {
        if (!selectRegisterTestProfile(profile)) return false;

        const uint8_t cycles = registerTestApplyCycles(profile);
        for (uint8_t cycle = 0; cycle < cycles; cycle++)
        {
            this->swapBuffers(true);
            delay(word_delay_ms);
        }
        return true;
    }

protected:
    void load_config_regs(uint16_t *config_registers) override
    {
        if (active_profile == NULL)
        {
            DriverType::load_config_regs(config_registers);
            return;
        }

        if (LoadMode == DMD_SPWM_REGISTER_TEST_LOAD_ONE_WORD)
        {
            this->conf_reg_cnt = 1;
            native_words[0] =
                active_profile->channel_words[0][active_word];
        }

        native_frame_word = 0;
        DriverType::load_config_regs(native_words);

        if (LoadMode == DMD_SPWM_REGISTER_TEST_LOAD_ONE_WORD)
        {
            active_word++;
            if (active_word >= active_profile->word_count) active_word = 0;
        }
    }

    void send_to_allRGB(uint16_t data, uint16_t latches) override
    {
#if DMD_SPWM_REGISTER_TEST_USE_RGB_CHANNEL_DATA
        uint8_t source_word = 0;
        if (registerTestSourceWord(latches, source_word))
        {
            DriverType::send_to_RGB(
                active_profile->channel_words[0][source_word],
                active_profile->channel_words[1][source_word],
                active_profile->channel_words[2][source_word], latches);
        }
        else
        {
            DriverType::send_to_allRGB(data, latches);
        }
#else
        DriverType::send_to_allRGB(data, latches);
#endif

        // The Pi SM16380SH sequence places F003 immediately after the
        // selected register word. Native STM32/RP2040 loaders omit this one
        // command, so add it without duplicating the rest of their framing.
        if (InsertSm16380shF003 && active_profile != NULL &&
            native_frame_word == 2)
        {
            DriverType::send_to_allRGB(0xf003, latches);
        }
        native_frame_word++;
    }

private:
#if DMD_SPWM_REGISTER_TEST_USE_RGB_CHANNEL_DATA
    uint8_t sourceWordForNativeSlot(uint8_t target_word) const
    {
        if (WordOrder == DMD_SPWM_REGISTER_TEST_LAST_WORD_FIRST)
        {
            return target_word == 0 ? active_profile->word_count - 1 :
                                      target_word - 1;
        }
        return target_word;
    }

    bool registerTestSourceWord(uint16_t latches, uint8_t &source_word) const
    {
        if (active_profile == NULL) return false;

        if (LoadMode == DMD_SPWM_REGISTER_TEST_LOAD_ONE_WORD)
        {
            if (native_frame_word != 2) return false;
            source_word = active_word;
            return source_word < active_profile->word_count;
        }

        uint8_t target_word = native_frame_word;
        if (LoadMode == DMD_SPWM_REGISTER_TEST_LOAD_INDEXED)
        {
            if (latches < 2 || ((latches - 2) & 1)) return false;
            target_word = (latches - 2) / 2;
        }

        if (target_word >= active_profile->word_count) return false;
        source_word = sourceWordForNativeSlot(target_word);
        return true;
    }

#endif

    enum {
        NATIVE_WORD_CAPACITY =
            LoadMode == DMD_SPWM_REGISTER_TEST_LOAD_ONE_WORD ?
                1 : ProfileType::MAX_WORDS
    };
    const ProfileType *active_profile = NULL;
    uint16_t native_words[NATIVE_WORD_CAPACITY] = {0};
    uint8_t active_word = 0;
    uint8_t native_frame_word = 0;
};

typedef DMD_SPWM_RegisterTestProfile<5>
    DMD_SPWM_FM6353_RegisterTestProfile;
typedef DMD_SPWM_RegisterTestProfile<5>
    DMD_SPWM_FM6363_RegisterTestProfile;
typedef DMD_SPWM_RegisterTestProfile<47>
    DMD_SPWM_FM6373_RegisterTestProfile;
typedef DMD_SPWM_RegisterTestProfile<22>
    DMD_SPWM_ICND1065L_RegisterTestProfile;
typedef DMD_SPWM_RegisterTestProfile<32>
    DMD_SPWM_SM16380SH_RegisterTestProfile;

template <int... Pars>
using DMD_RGB_FM6353_RegisterTest = DMD_SPWM_RegisterTestDriver<
    DMD_RGB_FM6353<Pars...>, DMD_SPWM_FM6353_RegisterTestProfile,
    DMD_SPWM_REGISTER_TEST_WORDS_IN_ORDER,
#if defined(ARDUINO_ARCH_RP2040)
    DMD_SPWM_REGISTER_TEST_LOAD_INDEXED>;
#else
    DMD_SPWM_REGISTER_TEST_LOAD_ALL>;
#endif

template <int... Pars>
using DMD_RGB_FM6363_RegisterTest = DMD_SPWM_RegisterTestDriver<
    DMD_RGB_FM6363<Pars...>, DMD_SPWM_FM6363_RegisterTestProfile,
    DMD_SPWM_REGISTER_TEST_LAST_WORD_FIRST,
    DMD_SPWM_REGISTER_TEST_LOAD_ALL>;

template <int... Pars>
using DMD_RGB_FM6373_RegisterTest = DMD_SPWM_RegisterTestDriver<
    DMD_RGB_FM6373<Pars...>, DMD_SPWM_FM6373_RegisterTestProfile,
    DMD_SPWM_REGISTER_TEST_WORDS_IN_ORDER,
    DMD_SPWM_REGISTER_TEST_LOAD_ONE_WORD>;

template <int... Pars>
using DMD_RGB_ICN1065_RegisterTest = DMD_SPWM_RegisterTestDriver<
    DMD_RGB_ICN1065<Pars...>, DMD_SPWM_ICND1065L_RegisterTestProfile,
    DMD_SPWM_REGISTER_TEST_WORDS_IN_ORDER,
    DMD_SPWM_REGISTER_TEST_LOAD_ONE_WORD>;

template <int... Pars>
using DMD_RGB_SM16380SH_RegisterTest = DMD_SPWM_RegisterTestDriver<
    DMD_RGB_SM16380SH<Pars...>, DMD_SPWM_SM16380SH_RegisterTestProfile,
    DMD_SPWM_REGISTER_TEST_WORDS_IN_ORDER,
    DMD_SPWM_REGISTER_TEST_LOAD_ONE_WORD, true>;

#endif // DMD_SPWM_REGISTER_TEST_DRIVER_H
