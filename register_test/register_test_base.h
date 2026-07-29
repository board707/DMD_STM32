#ifndef DMD_SPWM_REGISTER_TEST_BASE_H
#define DMD_SPWM_REGISTER_TEST_BASE_H

#include <stdint.h>

// Compile-time scene choices. The sketch defines
// DMD_SPWM_REGISTER_TEST_PATTERN before including this file so that only the
// selected renderer is instantiated in the firmware.
#define DMD_SPWM_REGISTER_TEST_PATTERN_GRADIENT 0
#define DMD_SPWM_REGISTER_TEST_PATTERN_ALIGN 1
#define DMD_SPWM_REGISTER_TEST_PATTERN_TEXTSCROLL 2

#ifndef DMD_SPWM_REGISTER_TEST_PATTERN
#define DMD_SPWM_REGISTER_TEST_PATTERN \
    DMD_SPWM_REGISTER_TEST_PATTERN_GRADIENT
#endif

#if DMD_SPWM_REGISTER_TEST_PATTERN != \
        DMD_SPWM_REGISTER_TEST_PATTERN_GRADIENT && \
    DMD_SPWM_REGISTER_TEST_PATTERN != DMD_SPWM_REGISTER_TEST_PATTERN_ALIGN && \
    DMD_SPWM_REGISTER_TEST_PATTERN != \
        DMD_SPWM_REGISTER_TEST_PATTERN_TEXTSCROLL
#error "Select the GRADIENT, ALIGN, or TEXTSCROLL SPWM register-test pattern"
#endif

// Let TEXTSCROLL tune its one-pixel frame interval without affecting the two
// existing patterns or compiling the option into their firmware.
#if DMD_SPWM_REGISTER_TEST_PATTERN == \
    DMD_SPWM_REGISTER_TEST_PATTERN_TEXTSCROLL
#ifndef DMD_SPWM_REGISTER_TEST_TEXT_SCROLL_INTERVAL_MS
#define DMD_SPWM_REGISTER_TEST_TEXT_SCROLL_INTERVAL_MS 30UL
#endif
#if DMD_SPWM_REGISTER_TEST_TEXT_SCROLL_INTERVAL_MS < 1
#error "DMD_SPWM_REGISTER_TEST_TEXT_SCROLL_INTERVAL_MS must be at least 1"
#endif
#endif

// Compact catalog entry containing the displayed REG number, payload length,
// and channel-major Red, Green, and Blue register words.
template <uint8_t MaxWords>
struct DMD_SPWM_RegisterTestProfile {
    enum { MAX_WORDS = MaxWords };
    uint16_t catalog_index;
    uint8_t word_count;
    uint16_t channel_words[3][MaxWords];
};

// Return one row of the shared 3x5 font used by the REG label and marquee.
static uint8_t dmdSpwmRegisterTestGlyphRow(char character, uint8_t row)
{
    static const uint8_t digits[10][5] = {
        {0x07, 0x05, 0x05, 0x05, 0x07},
        {0x02, 0x06, 0x02, 0x02, 0x07},
        {0x07, 0x01, 0x07, 0x04, 0x07},
        {0x07, 0x01, 0x07, 0x01, 0x07},
        {0x05, 0x05, 0x07, 0x01, 0x01},
        {0x07, 0x04, 0x07, 0x01, 0x07},
        {0x07, 0x04, 0x07, 0x05, 0x07},
        {0x07, 0x01, 0x02, 0x02, 0x02},
        {0x07, 0x05, 0x07, 0x05, 0x07},
        {0x07, 0x05, 0x07, 0x01, 0x07}
    };
    static const uint8_t letter_r[5] = {0x06, 0x05, 0x06, 0x05, 0x05};
    static const uint8_t letter_e[5] = {0x07, 0x04, 0x06, 0x04, 0x07};
    static const uint8_t letter_g[5] = {0x07, 0x04, 0x05, 0x05, 0x07};
#if DMD_SPWM_REGISTER_TEST_PATTERN == \
    DMD_SPWM_REGISTER_TEST_PATTERN_TEXTSCROLL
    static const uint8_t letter_c[5] = {0x07, 0x04, 0x04, 0x04, 0x07};
    static const uint8_t letter_f[5] = {0x07, 0x04, 0x06, 0x04, 0x04};
    static const uint8_t letter_i[5] = {0x07, 0x02, 0x02, 0x02, 0x07};
    static const uint8_t letter_n[5] = {0x05, 0x07, 0x07, 0x07, 0x05};
    static const uint8_t letter_o[5] = {0x07, 0x05, 0x05, 0x05, 0x07};
    static const uint8_t letter_s[5] = {0x07, 0x04, 0x07, 0x01, 0x07};
    static const uint8_t letter_t[5] = {0x07, 0x02, 0x02, 0x02, 0x02};
#endif

    if (row >= 5) return 0;
    if (character >= '0' && character <= '9')
    {
        return digits[character - '0'][row];
    }
    if (character == 'R' || character == 'r') return letter_r[row];
    if (character == 'E' || character == 'e') return letter_e[row];
    if (character == 'G' || character == 'g') return letter_g[row];
#if DMD_SPWM_REGISTER_TEST_PATTERN == \
    DMD_SPWM_REGISTER_TEST_PATTERN_TEXTSCROLL
    if (character == 'C' || character == 'c') return letter_c[row];
    if (character == 'F' || character == 'f') return letter_f[row];
    if (character == 'I' || character == 'i') return letter_i[row];
    if (character == 'N' || character == 'n') return letter_n[row];
    if (character == 'O' || character == 'o') return letter_o[row];
    if (character == 'S' || character == 's') return letter_s[row];
    if (character == 'T' || character == 't') return letter_t[row];
#endif
    return 0;
}

// Draw a white REG number overlay without relying on an external font.
template <typename DmdType>
static void dmdSpwmDrawRegisterTestLabel(DmdType &dmd,
                                         uint16_t catalog_index)
{
    char label[8] = {'R', 'E', 'G', ' ', 0, 0, 0, 0};
    uint8_t length = 4;

    if (catalog_index >= 100)
    {
        label[length++] = '0' + catalog_index / 100;
        label[length++] = '0' + (catalog_index / 10) % 10;
    }
    else if (catalog_index >= 10)
    {
        label[length++] = '0' + catalog_index / 10;
    }
    label[length++] = '0' + catalog_index % 10;
    label[length] = '\0';

    dmd.drawFilledBox(1, 1, 2 + length * 4, 7, 0);
    const uint16_t label_color = dmd.Color888(255, 255, 255);
    for (uint8_t character = 0; character < length; character++)
    {
        for (uint8_t row = 0; row < 5; row++)
        {
            const uint8_t pixels =
                dmdSpwmRegisterTestGlyphRow(label[character], row);
            for (uint8_t column = 0; column < 3; column++)
            {
                if (pixels & (1 << (2 - column)))
                {
                    dmd.drawPixel(2 + character * 4 + column,
                                  2 + row, label_color);
                }
            }
        }
    }
}

// Return the panel's normal logical width for test-pattern rendering.
template <typename DmdType>
static int16_t dmdSpwmRegisterTestVisibleWidth(const DmdType &dmd)
{
    return dmd.width();
}

// Exclude each shadowpho panel's four shifted but unconnected padding columns.
template <template <int...> class DmdType, int ColorDepth>
static int16_t dmdSpwmRegisterTestVisibleWidth(
    const DmdType<RGB172x86_s43_shadowpho, ColorDepth> &dmd)
{
    // This template shifts 176 positions per panel, but four positions are
    // unconnected padding rather than visible pixels.
    return (dmd.width() / 176) * 172;
}

// Draw hue and brightness ramps that expose color and register faults.
template <typename DmdType>
static void dmdSpwmDrawRegisterTestGradient(DmdType &dmd,
                                            uint16_t catalog_index)
{
    const int width = dmdSpwmRegisterTestVisibleWidth(dmd);
    const int height = dmd.height();
    dmd.clearScreen(true);

    for (int y = 0; y < height; y++)
    {
        // Keep the lowest row at the first visible COLOR_4BITS level. Fading
        // to zero made the bottom few rows quantize to black.
        const int minimum_brightness = 16;
        const int brightness =
            (height > 1) ? minimum_brightness +
                (255 - minimum_brightness) * (height - 1 - y) /
                (height - 1) : 255;
        for (int x = 0; x < width; x++)
        {
            const int hue = (width > 1) ? x * 1535 / (width - 1) : 0;
            const int segment = hue / 256;
            const int offset = hue % 256;
            int red = 0;
            int green = 0;
            int blue = 0;

            switch (segment)
            {
            case 0: red = 255; green = offset; break;
            case 1: red = 255 - offset; green = 255; break;
            case 2: green = 255; blue = offset; break;
            case 3: green = 255 - offset; blue = 255; break;
            case 4: red = offset; blue = 255; break;
            default: red = 255; blue = 255 - offset; break;
            }

            dmd.drawPixel(x, y,
                dmd.Color888(red * brightness / 255,
                             green * brightness / 255,
                             blue * brightness / 255));
        }
    }

    dmdSpwmDrawRegisterTestLabel(dmd, catalog_index);
}

// Draw the Pi Demo 3/15 borders and diagonals to expose scan alignment faults.
template <typename DmdType>
static void dmdSpwmDrawRegisterTestAlignment(DmdType &dmd,
                                             uint16_t catalog_index)
{
    const int16_t right = dmdSpwmRegisterTestVisibleWidth(dmd) - 1;
    const int16_t bottom = dmd.height() - 1;
    dmd.clearScreen(true);
    if (right < 0 || bottom < 0) return;

    // Raspberry Pi Demo 3 / Demo 15 Align: four panel edges followed by
    // both diagonals. Keep this order so the corner colors match the source.
    dmd.drawLine(0, 0, right, 0, dmd.Color888(255, 0, 0));
    dmd.drawLine(0, bottom, right, bottom, dmd.Color888(255, 255, 0));
    dmd.drawLine(0, 0, 0, bottom, dmd.Color888(0, 0, 255));
    dmd.drawLine(right, 0, right, bottom, dmd.Color888(0, 255, 0));
    dmd.drawLine(0, 0, right, bottom, dmd.Color888(255, 255, 255));
    dmd.drawLine(0, bottom, right, 0, dmd.Color888(255, 0, 255));

    dmdSpwmDrawRegisterTestLabel(dmd, catalog_index);
}

#if DMD_SPWM_REGISTER_TEST_PATTERN == \
    DMD_SPWM_REGISTER_TEST_PATTERN_TEXTSCROLL

// Return one row of the slimmer 5x7 marquee font. Small displays fall back to
// the shared 3x5 font when one-third of their height cannot hold seven rows.
static uint8_t dmdSpwmRegisterTestTextGlyphRow(char character, uint8_t row)
{
    static const uint8_t letter_r[7] = {
        0x1e, 0x11, 0x11, 0x1e, 0x14, 0x12, 0x11
    };
    static const uint8_t letter_e[7] = {
        0x1f, 0x10, 0x10, 0x1e, 0x10, 0x10, 0x1f
    };
    static const uint8_t letter_g[7] = {
        0x0e, 0x11, 0x10, 0x17, 0x11, 0x11, 0x0e
    };
    static const uint8_t letter_i[7] = {
        0x1f, 0x04, 0x04, 0x04, 0x04, 0x04, 0x1f
    };
    static const uint8_t letter_s[7] = {
        0x0f, 0x10, 0x10, 0x0e, 0x01, 0x01, 0x1e
    };
    static const uint8_t letter_t[7] = {
        0x1f, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04
    };
    static const uint8_t letter_c[7] = {
        0x0e, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0e
    };
    static const uint8_t letter_o[7] = {
        0x0e, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0e
    };
    static const uint8_t letter_n[7] = {
        0x11, 0x19, 0x19, 0x15, 0x13, 0x13, 0x11
    };
    static const uint8_t letter_f[7] = {
        0x1f, 0x10, 0x10, 0x1e, 0x10, 0x10, 0x10
    };

    if (row >= 7) return 0;
    if (character == 'R' || character == 'r') return letter_r[row];
    if (character == 'E' || character == 'e') return letter_e[row];
    if (character == 'G' || character == 'g') return letter_g[row];
    if (character == 'I' || character == 'i') return letter_i[row];
    if (character == 'S' || character == 's') return letter_s[row];
    if (character == 'T' || character == 't') return letter_t[row];
    if (character == 'C' || character == 'c') return letter_c[row];
    if (character == 'O' || character == 'o') return letter_o[row];
    if (character == 'N' || character == 'n') return letter_n[row];
    if (character == 'F' || character == 'f') return letter_f[row];
    return 0;
}

// Convert one of the six distinct marquee colors through the active panel's
// native Color888 conversion. Values align with the four-bit color levels.
template <typename DmdType>
static uint16_t dmdSpwmRegisterTestTextColor(DmdType &dmd,
                                             uint8_t color_index)
{
    static const uint8_t palette[6][3] = {
        {255, 255, 255}, // White
        {255,   0,   0}, // Red
        {  0, 255,   0}, // Green
        {  0,   0, 255}, // Blue
        {255, 255,   0}, // Yellow
        {170,   0, 255}  // Purple
    };
    const uint8_t index = color_index % 6;
    return dmd.Color888(
        palette[index][0], palette[index][1], palette[index][2]);
}

// Track one continuous marquee across REG changes and the three vertical
// display bands. Preserving this state lets RP2040 reach every band even when
// its automatic profile interval is shorter than one complete text pass.
struct DMD_SPWM_RegisterTestTextScrollState {
    int32_t x;
    uint8_t band;
    bool initialized;
};

static DMD_SPWM_RegisterTestTextScrollState
dmd_spwm_register_test_text_scroll_state = {0, 0, false};

// Size the marquee bitmap to approximately one third of the panel height.
static int16_t dmdSpwmRegisterTestTextScrollHeight(int16_t panel_height)
{
    if (panel_height <= 0) return 0;
    const int16_t text_height = panel_height / 3;
    return text_height > 0 ? text_height : 1;
}

// Use the slimmer 5:7 proportions when the derived height can retain every
// source row, falling back to 3:5 for very short panels.
static int16_t dmdSpwmRegisterTestTextScrollGlyphWidth(int16_t text_height)
{
    const int16_t glyph_width = text_height >= 7 ?
        (text_height * 5 + 3) / 7 : (text_height * 3 + 2) / 5;
    return glyph_width > 0 ? glyph_width : 1;
}

// Match the inter-character gap to one source-font column at either font size.
static int16_t dmdSpwmRegisterTestTextScrollSpacing(int16_t text_height)
{
    const int16_t spacing = text_height >= 7 ?
        text_height / 7 : text_height / 5;
    return spacing > 0 ? spacing : 1;
}

// Return the full marquee width including one proportional inter-character
// space, but no extra space after the final character.
static int32_t dmdSpwmRegisterTestTextScrollWidth(int16_t text_height)
{
    static const uint8_t character_count =
        sizeof("Register Test") - 1;
    const int16_t glyph_width =
        dmdSpwmRegisterTestTextScrollGlyphWidth(text_height);
    const int16_t spacing =
        dmdSpwmRegisterTestTextScrollSpacing(text_height);
    return (int32_t)character_count * glyph_width +
        (int32_t)(character_count - 1) * spacing;
}

// Initialize the marquee once so profile changes do not restart its band
// sequence before a complete pass has finished.
template <typename DmdType>
static void dmdSpwmInitializeRegisterTestTextScroll(const DmdType &dmd)
{
    if (dmd_spwm_register_test_text_scroll_state.initialized) return;
    dmd_spwm_register_test_text_scroll_state.x =
        dmdSpwmRegisterTestVisibleWidth(dmd);
    dmd_spwm_register_test_text_scroll_state.band = 0;
    dmd_spwm_register_test_text_scroll_state.initialized = true;
}

// Draw the fixed message at its current horizontal position in the active
// top, middle, or bottom third, scaling bitmap pixels to the band height.
template <typename DmdType>
static void dmdSpwmDrawRegisterTestTextScroll(DmdType &dmd,
                                              uint16_t catalog_index)
{
    static const char message[] = "Register Test";
    const int16_t visible_width = dmdSpwmRegisterTestVisibleWidth(dmd);
    const int16_t panel_height = dmd.height();
    const int16_t text_height =
        dmdSpwmRegisterTestTextScrollHeight(panel_height);
    dmd.clearScreen(true);
    if (visible_width <= 0 || text_height <= 0) return;

    dmdSpwmInitializeRegisterTestTextScroll(dmd);
    const bool use_slim_font = text_height >= 7;
    const uint8_t source_rows = use_slim_font ? 7 : 5;
    const uint8_t source_columns = use_slim_font ? 5 : 3;
    const int16_t glyph_width =
        dmdSpwmRegisterTestTextScrollGlyphWidth(text_height);
    const int16_t spacing =
        dmdSpwmRegisterTestTextScrollSpacing(text_height);
    const int16_t band_top =
        dmd_spwm_register_test_text_scroll_state.band * panel_height / 3;
    const int16_t band_bottom =
        (dmd_spwm_register_test_text_scroll_state.band + 1) *
        panel_height / 3;
    const int16_t text_y = band_top +
        (band_bottom - band_top - text_height) / 2;
    int32_t cursor_x = dmd_spwm_register_test_text_scroll_state.x;
    uint8_t letter_index = 0;

    for (uint8_t character = 0; message[character] != '\0'; character++)
    {
        if (message[character] != ' ')
        {
            if (cursor_x < visible_width && cursor_x + glyph_width > 0)
            {
                const uint16_t text_color =
                    dmdSpwmRegisterTestTextColor(dmd, letter_index);
                for (int16_t output_y = 0;
                     output_y < text_height; output_y++)
                {
                    const uint8_t source_row =
                        output_y * source_rows / text_height;
                    const uint8_t row_bits = use_slim_font ?
                        dmdSpwmRegisterTestTextGlyphRow(
                            message[character], source_row) :
                        dmdSpwmRegisterTestGlyphRow(
                            message[character], source_row);
                    for (int16_t output_x = 0;
                         output_x < glyph_width; output_x++)
                    {
                        const uint8_t source_column =
                            output_x * source_columns / glyph_width;
                        const int32_t pixel_x = cursor_x + output_x;
                        if (pixel_x >= 0 && pixel_x < visible_width &&
                            (row_bits &
                             (1 << (source_columns - 1 - source_column))))
                        {
                            dmd.drawPixel(pixel_x, text_y + output_y,
                                          text_color);
                        }
                    }
                }
            }
            letter_index = (letter_index + 1) % 6;
        }
        cursor_x += glyph_width + spacing;
    }

    dmdSpwmDrawRegisterTestLabel(dmd, catalog_index);
}

// Advance by the elapsed number of marquee pixels. Carry excess movement into
// later bands so slow SPWM uploads do not cap the configured scroll speed.
template <typename DmdType>
static void dmdSpwmAdvanceRegisterTestTextScroll(const DmdType &dmd,
                                                 uint32_t steps = 1)
{
    dmdSpwmInitializeRegisterTestTextScroll(dmd);
    if (steps == 0) return;

    const int32_t visible_width = dmdSpwmRegisterTestVisibleWidth(dmd);
    const int16_t text_height =
        dmdSpwmRegisterTestTextScrollHeight(dmd.height());
    const int32_t text_width =
        dmdSpwmRegisterTestTextScrollWidth(text_height);
    if (visible_width <= 0 || text_width <= 0) return;

    const uint32_t distance_to_wrap =
        (uint32_t)(dmd_spwm_register_test_text_scroll_state.x + text_width);
    if (steps < distance_to_wrap)
    {
        dmd_spwm_register_test_text_scroll_state.x -= (int32_t)steps;
    }
    else
    {
        const uint32_t travel = (uint32_t)(visible_width + text_width);
        steps -= distance_to_wrap;
        const uint32_t completed_passes = 1 + steps / travel;
        const uint32_t remaining_steps = steps % travel;
        dmd_spwm_register_test_text_scroll_state.band = (uint8_t)(
            (dmd_spwm_register_test_text_scroll_state.band +
             completed_passes % 3) % 3);
        dmd_spwm_register_test_text_scroll_state.x =
            visible_width - (int32_t)remaining_steps;
    }
}

#endif

// Dispatch to the display pattern selected at compile time.
template <typename DmdType>
static void dmdSpwmDrawRegisterTestScene(DmdType &dmd,
                                         uint16_t catalog_index)
{
#if DMD_SPWM_REGISTER_TEST_PATTERN == \
    DMD_SPWM_REGISTER_TEST_PATTERN_TEXTSCROLL
    dmdSpwmDrawRegisterTestTextScroll(dmd, catalog_index);
#elif DMD_SPWM_REGISTER_TEST_PATTERN == DMD_SPWM_REGISTER_TEST_PATTERN_ALIGN
    dmdSpwmDrawRegisterTestAlignment(dmd, catalog_index);
#else
    dmdSpwmDrawRegisterTestGradient(dmd, catalog_index);
#endif
}

// Update the selected pattern when its frame interval has elapsed. Keeping the
// presentation separate lets mandatory register-load swaps carry a fresh frame
// without adding any extra protocol cycles.
template <typename DmdType>
static bool dmdSpwmPrepareRegisterTestFrame(
    DmdType &dmd, uint16_t catalog_index, uint32_t &last_frame_at)
{
    const uint32_t now = millis();
    const uint32_t elapsed = (uint32_t)(now - last_frame_at);
#if DMD_SPWM_REGISTER_TEST_PATTERN == \
    DMD_SPWM_REGISTER_TEST_PATTERN_TEXTSCROLL
    const uint32_t interval =
        DMD_SPWM_REGISTER_TEST_TEXT_SCROLL_INTERVAL_MS;
#else
    const uint32_t interval = 30;
#endif
    if (elapsed < interval) return false;

#if DMD_SPWM_REGISTER_TEST_PATTERN == \
    DMD_SPWM_REGISTER_TEST_PATTERN_TEXTSCROLL
    const uint32_t steps = elapsed / interval;
    last_frame_at += steps * interval;
    dmdSpwmAdvanceRegisterTestTextScroll(dmd, steps);
#else
    last_frame_at = now;
#endif
    dmdSpwmDrawRegisterTestScene(dmd, catalog_index);
    return true;
}

// Redraw and present the selected pattern at the calibration showcase cadence,
// keeping the register test representative of a running animation display.
template <typename DmdType>
static void dmdSpwmRefreshRegisterTestFrame(
    DmdType &dmd, uint16_t catalog_index, uint32_t &last_frame_at)
{
    if (!dmdSpwmPrepareRegisterTestFrame(
            dmd, catalog_index, last_frame_at)) return;
    dmd.swapBuffers(true);
}

// Poll at a practical maximum of 100 Hz. TEXTSCROLL carries elapsed pixel steps
// forward, so this limits upload traffic without reducing its target speed.
static uint8_t dmdSpwmRegisterTestPollDelayMs()
{
    return 10;
}

// Draw the scene, stage one profile, and clock all required load cycles. Return
// the last presented frame time so animation cadence survives the transition.
template <typename DmdType, typename ProfileType>
static uint32_t dmdSpwmShowRegisterTestProfile(
    DmdType &dmd, const ProfileType &profile, uint8_t word_delay_ms)
{
    dmdSpwmDrawRegisterTestScene(dmd, profile.catalog_index);
    uint32_t last_frame_at = millis();
    if (!dmd.selectRegisterTestProfile(profile)) return last_frame_at;

    const uint8_t cycles = dmd.registerTestApplyCycles(profile);
    for (uint8_t cycle = 0; cycle < cycles; cycle++)
    {
        // Reuse each required register-load swap as the presentation step for
        // any frame that became due; this never changes the protocol count.
        dmdSpwmPrepareRegisterTestFrame(
            dmd, profile.catalog_index, last_frame_at);
        dmd.swapBuffers(true);
        delay(word_delay_ms);
    }
    return last_frame_at;
}

// Advance on a short button press; return the held profile's REG number so the
// STM32 sketch can continue into its normal demo using that active setting.
template <typename DmdType, typename ProfileType>
static uint16_t dmdSpwmRunRegisterTest(
    DmdType &dmd, const ProfileType *profiles, uint16_t profile_count,
    uint8_t button_pin, uint8_t button_active_level,
    uint16_t hold_time_ms, uint8_t word_delay_ms)
{
    if (profiles == NULL || profile_count == 0) return 0;

    pinMode(button_pin,
            button_active_level == LOW ? INPUT_PULLUP : INPUT_PULLDOWN);
    uint16_t profile_index = 0;

    while (true)
    {
        const ProfileType &profile = profiles[profile_index];
        uint32_t last_frame_at = dmdSpwmShowRegisterTestProfile(
            dmd, profile, word_delay_ms);

        // Require a stable press. A contact bounce must not reload the whole
        // profile before the user has had a chance to compare it.
        while (true)
        {
            while (digitalRead(button_pin) != button_active_level)
            {
                dmdSpwmRefreshRegisterTestFrame(
                    dmd, profile.catalog_index, last_frame_at);
                delay(dmdSpwmRegisterTestPollDelayMs());
            }
            delay(25);
            if (digitalRead(button_pin) == button_active_level) break;
        }

        const uint32_t pressed_at = millis();
        while (digitalRead(button_pin) == button_active_level)
        {
            dmdSpwmRefreshRegisterTestFrame(
                dmd, profile.catalog_index, last_frame_at);
            if ((uint32_t)(millis() - pressed_at) >= hold_time_ms)
            {
                while (digitalRead(button_pin) == button_active_level)
                {
                    dmdSpwmRefreshRegisterTestFrame(
                        dmd, profile.catalog_index, last_frame_at);
                    delay(dmdSpwmRegisterTestPollDelayMs());
                }
                return profile.catalog_index;
            }
            delay(dmdSpwmRegisterTestPollDelayMs());
        }

        profile_index++;
        if (profile_index >= profile_count) profile_index = 0;
    }
}

// Cycle profiles forever at a fixed interval on boards without a test button.
template <typename DmdType, typename ProfileType>
static uint16_t dmdSpwmRunRegisterTestAuto(
    DmdType &dmd, const ProfileType *profiles, uint16_t profile_count,
    uint32_t advance_time_ms, uint8_t word_delay_ms)
{
    if (profiles == NULL || profile_count == 0) return 0;

    uint16_t profile_index = 0;
    while (true)
    {
        const ProfileType &profile = profiles[profile_index];
        uint32_t last_frame_at = dmdSpwmShowRegisterTestProfile(
            dmd, profile, word_delay_ms);

        const uint32_t shown_at = millis();
        while ((uint32_t)(millis() - shown_at) < advance_time_ms)
        {
            dmdSpwmRefreshRegisterTestFrame(
                dmd, profile.catalog_index, last_frame_at);
            delay(dmdSpwmRegisterTestPollDelayMs());
        }

        profile_index++;
        if (profile_index >= profile_count) profile_index = 0;
    }
}

#endif // DMD_SPWM_REGISTER_TEST_BASE_H
