/*--------------------------------------------------------------------------------------
  DMD calibration and showcase for STM32F1/F4 and RP2040

  One sketch for conventional HUB75 panels (DMD_RGB) and SPWM driver panels.
  Panel geometry is selected explicitly by PANEL_TYPE for every MCU. The user is
  responsible for matching it to the physical panel and available SRAM. The SPWM class
  can be changed to SM16380SH, ICND1065, ICND2055, FM6373, DP3264, and others.

  Supported targets:
    - STM32F1 with the Roger Clark Arduino_STM32 core (__STM32F1__)
    - STM32F4 with the Roger Clark Arduino_STM32 core (__STM32F4__)
    - RP2040 with the Earle Philhower Arduino core

  SPWM drivers are not currently supported by the STMicroelectronics STM32duino core.

  QUICK START
  -----------
  1. Select the backend:
       DISPLAY_BACKEND = BACKEND_DMD_SPWM  (default), or
       DISPLAY_BACKEND = BACKEND_DMD_RGB
     For SPWM, also select its class, for example:
       SPWM_DRIVER_CLASS = DMD_RGB_ICN1065
       SPWM_DRIVER_CLASS = DMD_RGB_SM16380SH
     Note: the physical chip is ICND1065, but its library class is DMD_RGB_ICN1065.
  2. Set DEMO_INDEX:
       0      automatically runs every scene
       1..19  continuously runs only that scene
  3. Adjust PANEL_TYPE, panel count, row multiplexer, color order and pins.

--------------------------------------------------------------------------------------*/

#define BACKEND_DMD_RGB  1
#define BACKEND_DMD_SPWM 2
#define ROW_MUX_PANEL_DEFAULT  0
#define ROW_MUX_BINARY         1
#define ROW_MUX_SHIFT_REGISTER 2
#define STRINGIFY_DETAIL(value) #value
#define STRINGIFY(value) STRINGIFY_DETAIL(value)

// ========================= USER SETTINGS =============================================

// ----- Display hardware: edit these first --------------------------------------------

// Library family: BACKEND_DMD_SPWM or BACKEND_DMD_RGB.
#ifndef DISPLAY_BACKEND
#define DISPLAY_BACKEND      BACKEND_DMD_RGB
#endif

// Physical LED driver chip; ignored when DISPLAY_BACKEND is BACKEND_DMD_RGB.
// Available classes: DMD_RGB_FM6353, DMD_RGB_FM6363, DMD_RGB_FM6373,
// DMD_RGB_DP3264, DMD_RGB_ICN2055, DMD_RGB_ICN1065 and DMD_RGB_SM16380SH.
#ifndef SPWM_DRIVER_CLASS
#define SPWM_DRIVER_CLASS    DMD_RGB_SM16380SH
#endif

// Fixed SPWM register profile found with the dmd_spwm_panel register test.
// Zero uses the driver's normal register configuration. For a positive REG number,
// uncomment the matching chip/scan profile in register_test_config.h first.
#ifndef DMD_SPWM_REGISTER_OVERRIDE
#define DMD_SPWM_REGISTER_OVERRIDE 0
#endif

// Match the register test by applying each profile's separate R/G/B words.
#ifndef DMD_SPWM_REGISTER_TEST_USE_RGB_CHANNEL_DATA
#define DMD_SPWM_REGISTER_TEST_USE_RGB_CHANNEL_DATA 1
#endif

// Panel width, height, scan rate and pixel mapping. A 20 KB STM32F1 defaults to
// 64x32 so its 4-bit framebuffer leaves enough RAM for globals, heap and stack.
#ifndef PANEL_TYPE
#if defined(__STM32F1__)
#define PANEL_TYPE           RGB64x32plainS16
#else
// STM32F4 and RP2040 configured here for a 64x32, 1/16-scan panel.
#define PANEL_TYPE           RGB64x32plainS16
#endif
#endif
#define DISPLAYS_ACROSS      1
#define DISPLAYS_DOWN        1

// ROW_MUX_PANEL_DEFAULT keeps the multiplexer selected by PANEL_TYPE.
// ROW_MUX_BINARY uses a 3-to-8 decoder; ROW_MUX_SHIFT_REGISTER uses CLK/LAT/DATA.
#ifndef ROW_MULTIPLEXER_MODE
#define ROW_MULTIPLEXER_MODE  ROW_MUX_PANEL_DEFAULT
#endif

// Available orders: RGB, RBG, BRG, BGR, GRB and GBR.
#ifndef PANEL_COLOR_ORDER
#define PANEL_COLOR_ORDER    DMD_Color_order::RGB
#endif

// ----- Showcase selection ------------------------------------------------------------

//  0 autoplay all                8 plasma nebula
//  1 register-test alignment     9 neon tunnel
//  2 register-test gradient      10 fireworks
//  3 RGBW solid colors           11 aurora ribbons
//  4 color bars / ramps          12 mirror prism calibration
//  5 pixel health / address      13 shop promo transitions
//  6 brightness / linearity      14 aligned multiline text
//  7 refresh / ghosting          15 horizontal text scroll
//                                16 vertical text scroll
//                                17 pixel text zoom
//                                18 font showcase
//                                19 full-screen digital clock
#define DEMO_INDEX           0     // 0 = autoplay, 1..19 = one fixed scene
#define AUTOPLAY_SCENE_MS    9000UL  // Default when sceneDurationOverrideMs is 0

// ----- Text demos --------------------------------------------------------------------

#define TEXT_ALIGN_LEFT      0
#define TEXT_ALIGN_CENTER    1
#define TEXT_ALIGN_RIGHT     2

// Demo 14 displays these lines in place; demo 16 scrolls the same block vertically.
// Set the count from 1 to 4. Each line keeps its own preferred alignment.
#define TEXT_DEMO_LINE_COUNT       3
#define TEXT_LINE_1                "LEFT EDGE"
#define TEXT_LINE_1_ALIGNMENT      TEXT_ALIGN_LEFT
#define TEXT_LINE_2                "CENTRE"
#define TEXT_LINE_2_ALIGNMENT      TEXT_ALIGN_CENTER
#define TEXT_LINE_3                "RIGHT EDGE"
#define TEXT_LINE_3_ALIGNMENT      TEXT_ALIGN_RIGHT
#define TEXT_LINE_4                "WELCOME"
#define TEXT_LINE_4_ALIGNMENT      TEXT_ALIGN_CENTER

// Shop copy and animation speeds used by demos 13 and 15-18.
// Keep the promo title/subtitle strings short enough for the smallest panel.
#define TEXT_PROMO_CARD_MS         2600UL
#define TEXT_SCROLL_STEP_MS        35UL
#define TEXT_VERTICAL_STEP_MS      55UL
#define TEXT_FONT_HOLD_MS          1500UL
#define TEXT_ZOOM_STEP_MS          420UL
#define TEXT_ZOOM_MAX_SCALE        4
#define TEXT_PROMO_1_TITLE         "OPEN NOW"
#define TEXT_PROMO_1_SUBTITLE      "COME IN"
#define TEXT_PROMO_2_TITLE         "BIG SALE"
#define TEXT_PROMO_2_SUBTITLE      "THIS WEEK"
#define TEXT_PROMO_3_TITLE         "NEW STOCK"
#define TEXT_PROMO_3_SUBTITLE      "JUST IN"
#define TEXT_SCROLL_LEFT_MESSAGE   "THIS WEEK ONLY"
#define TEXT_SCROLL_RIGHT_MESSAGE  "OPEN TODAY"
#define TEXT_ZOOM_MESSAGE          "50%"
#define TEXT_FONT_SAMPLE           "SALE"

// ----- Clock demos -------------------------------------------------------------------

// The portable showcase has no board-independent RTC. Leave CLOCK_START_HOUR at -1
// to choose a random time at boot, or set it to 0..23 to use all three start values.
// The scene uses a millis()-driven clock. CLOCK_TICK_MS = 1000 keeps real time; a
// smaller value can be useful when demonstrating the animations.
#define CLOCK_START_HOUR           -1
#define CLOCK_START_MINUTE         0
#define CLOCK_START_SECOND         0
#define CLOCK_USE_24_HOUR          1
// Set to 1 to show dim outlines for unlit digital-clock segments.
#define CLOCK_SHOW_INACTIVE_SEGMENTS 0
#define CLOCK_TICK_MS              1000UL
#define CLOCK_DEMO_DURATION_MS     15000UL

// Full mode showcases all 12 distinct Latin font faces. Set this to 0 for a compact
// six-font set if a small-flash STM32F1 sketch later grows beyond the available space.
#ifndef TEXT_SHOWCASE_ALL_FONTS
#define TEXT_SHOWCASE_ALL_FONTS    1
#endif

// ----- Brightness and buffering ------------------------------------------------------

// SPWM backend: 0 is brightest; each larger shift approximately halves brightness.
#define DMD_SPWM_BRIGHTNESS_SHIFT 0
// Conventional DMD_RGB backend: 0 is off and 255 is maximum brightness.
#define DMD_RGB_BRIGHTNESS        192

#ifndef DMD_RGB_DUAL_BUFFER
#if defined(__STM32F1__)
#define DMD_RGB_DUAL_BUFFER  0       // Set 1 only when the F1 board has enough SRAM
#else
#define DMD_RGB_DUAL_BUFFER  1
#endif
#endif
// =====================================================================================

#define LAST_DEMO_INDEX 19
#define PANEL_MAPPING_DETAIL(muxPins, panelWidth, panelHeight, scanRows, mapping, ...) mapping
#define PANEL_MAPPING_EXPAND(...) PANEL_MAPPING_DETAIL(__VA_ARGS__)
#define PANEL_MAPPING PANEL_MAPPING_EXPAND(PANEL_TYPE)

#if (DEMO_INDEX < 0) || (DEMO_INDEX > LAST_DEMO_INDEX)
#error "DEMO_INDEX must be from 0 to 19"
#endif

#if (CLOCK_START_HOUR < -1) || (CLOCK_START_HOUR > 23) || \
    (CLOCK_START_MINUTE < 0) || (CLOCK_START_MINUTE > 59) || \
    (CLOCK_START_SECOND < 0) || (CLOCK_START_SECOND > 59)
#error "CLOCK_START_HOUR must be -1 or 0..23; minute and second must be 0..59"
#endif

#if (CLOCK_USE_24_HOUR != 0) && (CLOCK_USE_24_HOUR != 1)
#error "CLOCK_USE_24_HOUR must be 0 or 1"
#endif

#if (CLOCK_SHOW_INACTIVE_SEGMENTS != 0) && \
    (CLOCK_SHOW_INACTIVE_SEGMENTS != 1)
#error "CLOCK_SHOW_INACTIVE_SEGMENTS must be 0 or 1"
#endif

#if (CLOCK_TICK_MS == 0) || (CLOCK_TICK_MS > 60000UL)
#error "CLOCK_TICK_MS must be from 1 to 60000"
#endif

#if (CLOCK_DEMO_DURATION_MS < CLOCK_TICK_MS)
#error "CLOCK_DEMO_DURATION_MS must last for at least one clock tick"
#endif

#if (DMD_SPWM_BRIGHTNESS_SHIFT < 0) || (DMD_SPWM_BRIGHTNESS_SHIFT > 15)
#error "DMD_SPWM_BRIGHTNESS_SHIFT must be from 0 to 15"
#endif

#if (DMD_RGB_BRIGHTNESS < 0) || (DMD_RGB_BRIGHTNESS > 255)
#error "DMD_RGB_BRIGHTNESS must be from 0 to 255"
#endif

#if (TEXT_DEMO_LINE_COUNT < 1) || (TEXT_DEMO_LINE_COUNT > 4)
#error "TEXT_DEMO_LINE_COUNT must be from 1 to 4"
#endif

#if (TEXT_PROMO_CARD_MS < 1100UL)
#error "TEXT_PROMO_CARD_MS must be at least 1100"
#endif

#if (TEXT_SCROLL_STEP_MS == 0) || (TEXT_VERTICAL_STEP_MS == 0) || \
    (TEXT_FONT_HOLD_MS == 0) || (TEXT_ZOOM_STEP_MS == 0)
#error "Text animation timing values must be greater than zero"
#endif

#if (TEXT_SCROLL_STEP_MS > 60000UL) || (TEXT_VERTICAL_STEP_MS > 60000UL)
#error "Text scroll step values must be 60000 or less"
#endif

#if (TEXT_ZOOM_MAX_SCALE < 1)
#error "TEXT_ZOOM_MAX_SCALE must be at least 1"
#endif

#if (TEXT_LINE_1_ALIGNMENT < TEXT_ALIGN_LEFT) || \
    (TEXT_LINE_1_ALIGNMENT > TEXT_ALIGN_RIGHT) || \
    (TEXT_LINE_2_ALIGNMENT < TEXT_ALIGN_LEFT) || \
    (TEXT_LINE_2_ALIGNMENT > TEXT_ALIGN_RIGHT) || \
    (TEXT_LINE_3_ALIGNMENT < TEXT_ALIGN_LEFT) || \
    (TEXT_LINE_3_ALIGNMENT > TEXT_ALIGN_RIGHT) || \
    (TEXT_LINE_4_ALIGNMENT < TEXT_ALIGN_LEFT) || \
    (TEXT_LINE_4_ALIGNMENT > TEXT_ALIGN_RIGHT)
#error "Every TEXT_LINE_n_ALIGNMENT must be LEFT, CENTER or RIGHT"
#endif

#if (ROW_MULTIPLEXER_MODE < ROW_MUX_PANEL_DEFAULT) || \
    (ROW_MULTIPLEXER_MODE > ROW_MUX_SHIFT_REGISTER)
#error "Unknown ROW_MULTIPLEXER_MODE"
#endif

#if DISPLAY_BACKEND == BACKEND_DMD_RGB
#include "DMD_RGB.h"
#elif DISPLAY_BACKEND == BACKEND_DMD_SPWM
#if defined(__STM32F1__) || defined(__STM32F4__)
#include "DMD_SPWM_Driver.h"
#elif defined(ARDUINO_ARCH_RP2040)
#include "DMD_SPWM_Driver_RP.h"
#else
#error "SPWM mode requires Roger Clark STM32F1/F4 or the Earle Philhower RP2040 core"
#endif
#if DMD_SPWM_REGISTER_OVERRIDE > 0
#include "examples/STM32F4_RP2040/dmd_spwm_panel/register_test/register_test_config.h"
#endif
#else
#error "Unknown DISPLAY_BACKEND"
#endif

#include "st_fonts/SystemFont5x7.h"
#include "st_fonts/Arial14.h"
#include "st_fonts/Arial_black_16.h"

// Some generated GFX font tables contain intentional narrow integer constants.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnarrowing"
#pragma GCC diagnostic ignored "-Woverflow"
#include "gfx_fonts/GlametrixBold9pt7b.h"
#include "gfx_fonts/GlametrixLight12pt7b.h"
#include "gfx_fonts/comic9pt8b.h"
#if TEXT_SHOWCASE_ALL_FONTS
#include "gfx_fonts/FreeMono12pt7b.h"
#include "gfx_fonts/FreeSerifBold9pt7b.h"
#include "gfx_fonts/FreeSerifItalic9pt7b.h"
#include "gfx_fonts/FreeSerifBoldItalic9pt7b.h"
#include "gfx_fonts/Glametrix12pt7b.h"
#include "gfx_fonts/GlametrixBold12pt7b.h"
#endif
#pragma GCC diagnostic pop

/* =================== *
 *    STM32F1/F4 pins  *
 * =================== */
#if defined(__STM32F1__) || defined(__STM32F4__)
#define DMD_PIN_A PB6
#define DMD_PIN_B PB5
#define DMD_PIN_C PB4
#define DMD_PIN_D PB3
#define DMD_PIN_E PB8
uint8_t mux_list[] = {DMD_PIN_A, DMD_PIN_B, DMD_PIN_C, DMD_PIN_D, DMD_PIN_E};

#define DMD_PIN_nOE PB0
#define DMD_PIN_SCLK PB7
// CLK, R0, G0, B0, R1, G1, B1. All pins must be on the same GPIO port.
uint8_t custom_rgbpins[] = {PA6, PA0, PA1, PA2, PA3, PA4, PA5};

/* =================== *
 *      RP2040 pins    *
 * =================== */
#elif defined(ARDUINO_ARCH_RP2040)
#define DMD_PIN_A 6
#define DMD_PIN_B 7
#define DMD_PIN_C 8
#define DMD_PIN_D 9
#define DMD_PIN_E 10
uint8_t mux_list[] = {DMD_PIN_A, DMD_PIN_B, DMD_PIN_C, DMD_PIN_D, DMD_PIN_E};

#define DMD_PIN_nOE 15
#define DMD_PIN_SCLK 12
// CLK, R0, G0, B0, R1, G1, B1. RGB pins must be consecutive.
uint8_t custom_rgbpins[] = {11, 0, 1, 2, 3, 4, 5};
#else
#error "This example supports Roger Clark STM32F1/F4 and Earle Philhower RP2040"
#endif

#if DISPLAY_BACKEND == BACKEND_DMD_RGB
// F4/RP2040 default to two MCU buffers; memory-constrained F1 defaults to one.
#define ENABLE_DUAL_BUFFER DMD_RGB_DUAL_BUFFER
DMD_RGB<PANEL_TYPE, COLOR_4BITS> dmd(
  mux_list, DMD_PIN_nOE, DMD_PIN_SCLK, custom_rgbpins,
  DISPLAYS_ACROSS, DISPLAYS_DOWN, ENABLE_DUAL_BUFFER);
#else
// SPWM classes ignore the host dual-buffer flag by design; panel SRAM is the
// visible front buffer and the MCU framebuffer stages the next complete image.
#define ENABLE_DUAL_BUFFER false
SPWM_DRIVER_CLASS<PANEL_TYPE, COLOR_4BITS> dmd(
  mux_list, DMD_PIN_nOE, DMD_PIN_SCLK, custom_rgbpins,
  DISPLAYS_ACROSS, DISPLAYS_DOWN, ENABLE_DUAL_BUFFER);
#endif

DMD_Standard_Font SmallFont(SystemFont5x7);
DMD_Standard_Font ArialFont(Arial_14);
DMD_Standard_Font ArialBlackFont(Arial_Black_16);
DMD_GFX_Font GlametrixBold9Font((uint8_t *)&GlametrixBold9pt7b, 11);
DMD_GFX_Font GlametrixLight12Font((uint8_t *)&GlametrixLight12pt7b, 13);
DMD_GFX_Font Comic9Font((uint8_t *)&comic9pt8b, 13);
#if TEXT_SHOWCASE_ALL_FONTS
DMD_GFX_Font FreeMono12Font((uint8_t *)&FreeMono12pt7b, 18);
DMD_GFX_Font FreeSerifBold9Font((uint8_t *)&FreeSerifBold9pt7b, 15);
DMD_GFX_Font FreeSerifItalic9Font((uint8_t *)&FreeSerifItalic9pt7b, 15);
DMD_GFX_Font FreeSerifBoldItalic9Font((uint8_t *)&FreeSerifBoldItalic9pt7b, 15);
DMD_GFX_Font Glametrix12Font((uint8_t *)&Glametrix12pt7b, 13);
DMD_GFX_Font GlametrixBold12Font((uint8_t *)&GlametrixBold12pt7b, 13);
#endif

enum DemoScene : uint8_t {
  SCENE_AUTOPLAY = 0,
  TEST_ALIGNMENT = 1,
  TEST_GRADIENT,
  TEST_RGBW_SOLIDS,
  TEST_COLOR_RAMPS,
  TEST_PIXEL_HEALTH,
  TEST_BRIGHTNESS,
  TEST_GHOSTING,
  DEMO_PLASMA,
  DEMO_NEON_TUNNEL,
  DEMO_FIREWORKS,
  DEMO_AURORA,
  DEMO_MIRROR_PRISM_CALIBRATION,
  DEMO_SHOP_PROMO,
  DEMO_ALIGNED_MULTILINE_TEXT,
  DEMO_HORIZONTAL_TEXT_SCROLL,
  DEMO_VERTICAL_TEXT_SCROLL,
  DEMO_PIXEL_TEXT_ZOOM,
  DEMO_FONT_SHOWCASE,
  DEMO_DIGITAL_CLOCK
};

static uint16_t BLACK;
static uint16_t RED;
static uint16_t GREEN;
static uint16_t BLUE;
static uint16_t CYAN;
static uint16_t MAGENTA;
static uint16_t YELLOW;
static uint16_t WHITE;
static uint16_t DIM_RED;
static uint16_t DIM_BLUE;
static uint16_t huePalette[256];

static uint8_t activeScene = (DEMO_INDEX == SCENE_AUTOPLAY) ? TEST_ALIGNMENT : DEMO_INDEX;
static uint32_t sceneStarted = 0;
static uint32_t lastFrameAt = 0;
static bool firstFrame = true;
static uint32_t clockLastUpdateAt = 0;
static uint32_t clockTickElapsedMs = 0;
static uint32_t clockSecondsOfDay = 0;
// A renderer can set this to override its autoplay length; 0 uses the default.
static uint32_t sceneDurationOverrideMs = 0;

struct ShowcaseClockTime {
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  uint32_t tickElapsedMs;
};

static const char *const configuredTextLines[] = {
  TEXT_LINE_1, TEXT_LINE_2, TEXT_LINE_3, TEXT_LINE_4
};
static const uint8_t configuredTextAlignments[] = {
  TEXT_LINE_1_ALIGNMENT, TEXT_LINE_2_ALIGNMENT,
  TEXT_LINE_3_ALIGNMENT, TEXT_LINE_4_ALIGNMENT
};

struct PromoCard {
  const char *title;
  const char *subtitle;
};

static const PromoCard promoCards[] = {
  {TEXT_PROMO_1_TITLE, TEXT_PROMO_1_SUBTITLE},
  {TEXT_PROMO_2_TITLE, TEXT_PROMO_2_SUBTITLE},
  {TEXT_PROMO_3_TITLE, TEXT_PROMO_3_SUBTITLE}
};

struct FontShowcaseEntry {
  DMD_Font *font;
  const char *label;
};

static const FontShowcaseEntry fontShowcase[] = {
  {&SmallFont, "System5x7"},
  {&ArialFont, "Arial 14"},
  {&ArialBlackFont, "ArialBlk16"},
  {&GlametrixBold9Font, "GlamBold9"},
  {&GlametrixLight12Font, "GlamLight"},
  {&Comic9Font, "Comic 9"},
#if TEXT_SHOWCASE_ALL_FONTS
  {&FreeMono12Font, "FreeMono12"},
  {&FreeSerifBold9Font, "SerifBold"},
  {&FreeSerifItalic9Font, "Serif It9"},
  {&FreeSerifBoldItalic9Font, "Serif BIt"},
  {&Glametrix12Font, "Glametrix"},
  {&GlametrixBold12Font, "GlamBold12"},
#endif
};

static const uint8_t FONT_SHOWCASE_COUNT =
    sizeof(fontShowcase) / sizeof(fontShowcase[0]);

// ---------- Shared driver wrappers ----------------------------------------------------

static void presentFrame() {
  // Match dmd_spwm_panel: present the frame, then preserve it in the draw buffer.
  // SPWM drivers ignore the copy flag and upload the staged frame into panel SRAM.
  dmd.swapBuffers(true);
}

// ---------- Small drawing/math helpers ------------------------------------------------

static int16_t abs16(int16_t value) {
  return (value < 0) ? -value : value;
}

// Fast, smooth, periodic approximation: -128..128 for a phase of 0..255.
static int16_t waveSigned(uint8_t phase) {
  int16_t x = phase;
  if (x >= 128) x -= 256;
  return (x * (128 - abs16(x))) >> 5;
}

static uint16_t wheelColor(uint8_t hue, uint8_t value) {
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
  uint8_t offset;

  if (hue < 85) {
    offset = hue * 3;
    r = 255 - offset;
    g = offset;
  } else if (hue < 170) {
    offset = (hue - 85) * 3;
    g = 255 - offset;
    b = offset;
  } else {
    offset = (hue - 170) * 3;
    b = 255 - offset;
    r = offset;
  }

  r = ((uint16_t)r * value) >> 8;
  g = ((uint16_t)g * value) >> 8;
  b = ((uint16_t)b * value) >> 8;
  return dmd.Color888(r, g, b);
}

static void initColors() {
  BLACK = dmd.Color444(0, 0, 0);
  RED = dmd.Color444(15, 0, 0);
  GREEN = dmd.Color444(0, 15, 0);
  BLUE = dmd.Color444(0, 0, 15);
  CYAN = dmd.Color444(0, 15, 15);
  MAGENTA = dmd.Color444(15, 0, 15);
  YELLOW = dmd.Color444(15, 15, 0);
  WHITE = dmd.Color444(15, 15, 15);
  DIM_RED = dmd.Color444(3, 0, 0);
  DIM_BLUE = dmd.Color444(0, 0, 3);

  for (uint16_t i = 0; i < 256; i++) {
    huePalette[i] = wheelColor((uint8_t)i, 255);
  }
}

static void drawPixelSafe(int16_t x, int16_t y, uint16_t color) {
  if (x >= 0 && x < dmd.width() && y >= 0 && y < dmd.height()) {
    dmd.drawPixel(x, y, color);
  }
}

static void drawGlowPixel(int16_t x, int16_t y, uint16_t core, uint16_t glow) {
  drawPixelSafe(x - 1, y, glow);
  drawPixelSafe(x + 1, y, glow);
  drawPixelSafe(x, y - 1, glow);
  drawPixelSafe(x, y + 1, glow);
  drawPixelSafe(x, y, core);
}

static void drawCenteredText(const char *text, int16_t y, uint16_t fg, uint16_t bg) {
  dmd.setTextColor(fg, bg);
  int16_t x = (dmd.width() - dmd.stringWidth(text)) / 2;
  dmd.drawStringX(x, y, text, fg);
}

static int16_t alignedTextX(const char *text, uint8_t alignment,
                            int16_t margin = 2) {
  const int16_t textWidth = dmd.stringWidth(text);
  if (alignment == TEXT_ALIGN_LEFT) return margin;
  if (alignment == TEXT_ALIGN_RIGHT) return dmd.width() - margin - textWidth;
  return (dmd.width() - textWidth) / 2;
}

static uint16_t alignmentColor(uint8_t alignment) {
  if (alignment == TEXT_ALIGN_LEFT) return CYAN;
  if (alignment == TEXT_ALIGN_RIGHT) return MAGENTA;
  return YELLOW;
}

static void drawAlignedText(const char *text, int16_t y, uint8_t alignment,
                            uint16_t color) {
  dmd.setTextColor(color, BLACK);
  dmd.drawStringX(alignedTextX(text, alignment), y, text, color);
}

static uint8_t adaptiveTextScale() {
  return (dmd.width() >= 96 && dmd.height() >= 48) ? 2 : 1;
}

static uint8_t configuredVisibleLineCount(uint8_t scale = 1,
                                          uint8_t gap = 1) {
  const uint8_t lineHeight = SmallFont.get_height() * scale;
  uint8_t panelCapacity = (dmd.height() + gap) / (lineHeight + gap);
  if (panelCapacity > 4) panelCapacity = 4;
  return (TEXT_DEMO_LINE_COUNT < panelCapacity) ?
      TEXT_DEMO_LINE_COUNT : panelCapacity;
}

static int16_t configuredTextBlockHeight(uint8_t count, uint8_t scale = 1,
                                         uint8_t gap = 1) {
  if (count == 0) return 0;
  return count * SmallFont.get_height() * scale + (count - 1) * gap;
}

// DMD fonts have fixed bitmap sizes. This app-level helper expands the one-byte-high
// SystemFont5x7 pixels by an integer amount so demo 17 can change size at runtime.
static int16_t scaled5x7TextWidth(const char *text, uint8_t scale) {
  int16_t width = 0;
  for (uint16_t i = 0; i < MAX_STRING_LEN && text[i] != '\0'; i++) {
    uint8_t charWidth = SmallFont.get_char_width((uint8_t)text[i]);
    if (charWidth == 0) continue;
    if (width != 0) width += scale;
    width += charWidth * scale;
  }
  return width;
}

static void drawScaled5x7Text(int16_t x, int16_t y, const char *text,
                              uint8_t scale, uint16_t color) {
  for (uint16_t i = 0; i < MAX_STRING_LEN && text[i] != '\0'; i++) {
    const uint8_t character = (uint8_t)text[i];
    const uint8_t charWidth = SmallFont.get_char_width(character);
    if (charWidth == 0) continue;
    const uint16_t bitmapIndex = SmallFont.get_bitmap_index(character);

    for (uint8_t column = 0; column < charWidth; column++) {
      const uint8_t pixels = pgm_read_byte(
          SmallFont.font_ptr + bitmapIndex + column);
      for (uint8_t row = 0; row < SmallFont.get_height(); row++) {
        if (pixels & (1 << row)) {
          dmd.fillRect(x + column * scale, y + row * scale,
                       scale, scale, color);
        }
      }
    }
    x += (charWidth + 1) * scale;
  }
}

static int16_t alignedScaled5x7TextX(const char *text, uint8_t alignment,
                                     uint8_t scale, int16_t margin = 2) {
  const int16_t textWidth = scaled5x7TextWidth(text, scale);
  if (alignment == TEXT_ALIGN_LEFT) return margin;
  if (alignment == TEXT_ALIGN_RIGHT) return dmd.width() - margin - textWidth;
  return (dmd.width() - textWidth) / 2;
}

static void drawAligned5x7Text(const char *text, int16_t y,
                               uint8_t alignment, uint8_t scale,
                               uint16_t color) {
  if (scale == 1) {
    drawAlignedText(text, y, alignment, color);
    return;
  }
  drawScaled5x7Text(alignedScaled5x7TextX(text, alignment, scale),
                    y, text, scale, color);
}

static void formatByte(uint8_t value, char *text) {
  uint8_t index = 0;
  if (value >= 100) {
    text[index++] = '0' + value / 100;
    value %= 100;
    text[index++] = '0' + value / 10;
  } else if (value >= 10) {
    text[index++] = '0' + value / 10;
  }
  text[index++] = '0' + value % 10;
  text[index] = '\0';
}

// ---------- Clock drawing helpers ----------------------------------------------------

static void beginShowcaseClock(uint32_t now) {
#if CLOCK_START_HOUR < 0
  clockSecondsOfDay = (uint32_t)random(86400L);
#else
  clockSecondsOfDay =
      (uint32_t)CLOCK_START_HOUR * 3600UL +
      (uint32_t)CLOCK_START_MINUTE * 60UL + CLOCK_START_SECOND;
#endif
  clockTickElapsedMs = 0;
  clockLastUpdateAt = now;
}

static void updateShowcaseClock(uint32_t now) {
  const uint32_t deltaMs = now - clockLastUpdateAt;
  clockLastUpdateAt = now;

  uint32_t ticks = deltaMs / CLOCK_TICK_MS;
  const uint32_t partialMs = deltaMs % CLOCK_TICK_MS;
  if (clockTickElapsedMs >= CLOCK_TICK_MS - partialMs) {
    clockTickElapsedMs -= CLOCK_TICK_MS - partialMs;
    ticks++;
  } else {
    clockTickElapsedMs += partialMs;
  }
  clockSecondsOfDay =
      (clockSecondsOfDay + ticks % 86400UL) % 86400UL;
}

static ShowcaseClockTime readShowcaseClock() {
  uint32_t secondsOfDay = clockSecondsOfDay;

  ShowcaseClockTime clock;
  clock.hour = secondsOfDay / 3600UL;
  secondsOfDay %= 3600UL;
  clock.minute = secondsOfDay / 60UL;
  clock.second = secondsOfDay % 60UL;
  clock.tickElapsedMs = clockTickElapsedMs;
  return clock;
}

static uint8_t clockDisplayHour(uint8_t hour24) {
#if CLOCK_USE_24_HOUR
  return hour24;
#else
  uint8_t hour12 = hour24 % 12;
  return (hour12 == 0) ? 12 : hour12;
#endif
}

static void drawSevenSegmentBar(int16_t x, int16_t y,
                                int16_t width, int16_t height,
                                bool lit, uint16_t activeColor,
                                uint16_t inactiveColor) {
  const uint16_t color = lit ? activeColor : inactiveColor;
  dmd.fillRect(x, y, width, height, color);

  // Removing the square corners gives each enlarged segment a crisp neon shape.
  if (width > 1 && height > 1) {
    dmd.drawPixel(x, y, BLACK);
    dmd.drawPixel(x + width - 1, y, BLACK);
    dmd.drawPixel(x, y + height - 1, BLACK);
    dmd.drawPixel(x + width - 1, y + height - 1, BLACK);
  }

  if (!lit) return;
  if (width > height && width > 3) {
    dmd.drawFastHLine(x + 1, y + height / 2, width - 2, WHITE);
  } else if (height > width && height > 3) {
    dmd.drawFastVLine(x + width / 2, y + 1, height - 2, WHITE);
  }
}

static void drawSevenSegmentDigit(int16_t x, int16_t y, uint8_t digit,
                                  uint8_t scale, uint16_t activeColor,
                                  uint16_t inactiveColor) {
  static const uint8_t digitSegments[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66,
    0x6d, 0x7d, 0x07, 0x7f, 0x6f
  };
  const uint8_t segments = digitSegments[digit % 10];
  const int16_t thickness = scale;
  const int16_t horizontalLength = scale * 2;
  const int16_t verticalLength = scale * 3;

  drawSevenSegmentBar(x + scale, y,
                      horizontalLength, thickness,
                      segments & 0x01, activeColor, inactiveColor);
  drawSevenSegmentBar(x + scale * 3, y + scale,
                      thickness, verticalLength,
                      segments & 0x02, activeColor, inactiveColor);
  drawSevenSegmentBar(x + scale * 3, y + scale * 5,
                      thickness, verticalLength,
                      segments & 0x04, activeColor, inactiveColor);
  drawSevenSegmentBar(x + scale, y + scale * 8,
                      horizontalLength, thickness,
                      segments & 0x08, activeColor, inactiveColor);
  drawSevenSegmentBar(x, y + scale * 5,
                      thickness, verticalLength,
                      segments & 0x10, activeColor, inactiveColor);
  drawSevenSegmentBar(x, y + scale,
                      thickness, verticalLength,
                      segments & 0x20, activeColor, inactiveColor);
  drawSevenSegmentBar(x + scale, y + scale * 4,
                      horizontalLength, thickness,
                      segments & 0x40, activeColor, inactiveColor);
}

// ---------- Shared calibration helpers ------------------------------------------------

static int16_t registerTestPatternVisibleWidth() {
#if PANEL_MAPPING == 65
  // Shadowpho panels shift 176 positions, but four columns are padding.
  return (dmd.width() / 176) * 172;
#else
  return dmd.width();
#endif
}

static void drawOrientationCornerLs(int16_t w, int16_t h) {
  if (w <= 0 || h <= 0) return;

  dmd.drawPixel(0, 0, RED);
  dmd.drawPixel(w - 1, 0, GREEN);
  dmd.drawPixel(0, h - 1, BLUE);
  dmd.drawPixel(w - 1, h - 1, YELLOW);
  if (w > 1) {
    dmd.drawPixel(1, 0, RED);
    dmd.drawPixel(w - 2, 0, GREEN);
    dmd.drawPixel(1, h - 1, BLUE);
    dmd.drawPixel(w - 2, h - 1, YELLOW);
  }
  if (h > 1) {
    dmd.drawPixel(0, 1, RED);
    dmd.drawPixel(w - 1, 1, GREEN);
    dmd.drawPixel(0, h - 2, BLUE);
    dmd.drawPixel(w - 1, h - 2, YELLOW);
  }
}

// ---------- 1 register-test alignment -------------------------------------------------

// Matches DMD_SPWM_REGISTER_TEST_PATTERN_ALIGN without its REG-number overlay.
static void renderAlignment(uint32_t elapsed) {
  sceneDurationOverrideMs = 3000UL;
  (void)elapsed;
  const int16_t right = registerTestPatternVisibleWidth() - 1;
  const int16_t bottom = dmd.height() - 1;
  dmd.fillScreen(BLACK);
  if (right < 0 || bottom < 0) return;

  dmd.drawLine(0, 0, right, 0, RED);
  dmd.drawLine(0, bottom, right, bottom, YELLOW);
  dmd.drawLine(0, 0, 0, bottom, BLUE);
  dmd.drawLine(right, 0, right, bottom, GREEN);
  dmd.drawLine(0, 0, right, bottom, WHITE);
  dmd.drawLine(0, bottom, right, 0, MAGENTA);
}

// ---------- 2 register-test gradient --------------------------------------------------

// Matches DMD_SPWM_REGISTER_TEST_PATTERN_GRADIENT without its REG-number overlay.
static void renderGradient(uint32_t elapsed) {
  sceneDurationOverrideMs = 2000UL;
  (void)elapsed;
  const int width = registerTestPatternVisibleWidth();
  const int height = dmd.height();
  dmd.fillScreen(BLACK);

  for (int y = 0; y < height; y++) {
    // Keep the lowest row at the first visible COLOR_4BITS level.
    const int minimumBrightness = 16;
    const int brightness = (height > 1)
        ? minimumBrightness +
            (255 - minimumBrightness) * (height - 1 - y) / (height - 1)
        : 255;

    for (int x = 0; x < width; x++) {
      const int hue = (width > 1) ? x * 1535 / (width - 1) : 0;
      const int segment = hue / 256;
      const int offset = hue % 256;
      int red = 0;
      int green = 0;
      int blue = 0;

      switch (segment) {
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
}

// ---------- 3 RGBW solid colors -------------------------------------------------------

static void renderRGBWSolids(uint32_t elapsed) {
  static const uint16_t PHASE_MS = 900;
  static const uint8_t PHASE_COUNT = 8;
  static const char *names[] = {
    "RED", "GREEN", "BLUE", "WHITE", "CYAN", "MAGENTA", "YELLOW", "BLACK"
  };
  sceneDurationOverrideMs = (uint32_t)PHASE_MS * PHASE_COUNT;
  const uint32_t phaseIndex = elapsed / PHASE_MS;
  const uint8_t phase = (phaseIndex < PHASE_COUNT) ?
      phaseIndex : PHASE_COUNT - 1;
  uint16_t color;
  switch (phase) {
    case 0: color = RED; break;
    case 1: color = GREEN; break;
    case 2: color = BLUE; break;
    case 3: color = WHITE; break;
    case 4: color = CYAN; break;
    case 5: color = MAGENTA; break;
    case 6: color = YELLOW; break;
    default: color = BLACK; break;
  }

#if DISPLAY_BACKEND == BACKEND_DMD_RGB
  dmd.setBrightness(DMD_RGB_BRIGHTNESS);
#else
  dmd.shiftColorBrightnessDown(DMD_SPWM_BRIGHTNESS_SHIFT);
#endif
  dmd.fillScreen(color);
  uint16_t labelColor = (phase == 1 || phase == 3 || phase == 4 || phase == 6) ? BLACK : WHITE;
  drawCenteredText(names[phase], dmd.height() / 2 - 3, labelColor, color);
}

// ---------- 4 color bars / 16-step ramps ----------------------------------------------

static void renderColorRamps(uint32_t elapsed) {
  static const uint32_t SCENE_MS = 3000UL;
  static const uint32_t PHASE_MS = SCENE_MS / 2;
  static const uint8_t PHASE_COUNT = 2;
  const int16_t w = dmd.width();
  const int16_t h = dmd.height();
  sceneDurationOverrideMs = SCENE_MS;
  const uint32_t phaseIndex = elapsed / PHASE_MS;
  // In fixed-scene mode, hold the final ramps instead of starting over.
  const uint8_t phase = (phaseIndex < PHASE_COUNT) ?
      phaseIndex : PHASE_COUNT - 1;
  dmd.fillScreen(BLACK);

  if (phase == 0) {
    uint16_t bars[] = {WHITE, YELLOW, CYAN, GREEN, MAGENTA, RED, BLUE, BLACK};
    int16_t barWidth = w / 8;
    for (uint8_t i = 0; i < 8; i++) {
      dmd.fillRect(i * barWidth, 0, (i == 7) ? w - i * barWidth : barWidth, h, bars[i]);
    }
    dmd.drawRect(0, 0, w, h, WHITE);
  } else {
    int16_t stepWidth = w / 16;
    int16_t bandHeight = h / 4;
    for (uint8_t level = 0; level < 16; level++) {
      int16_t x = level * stepWidth;
      int16_t sw = (level == 15) ? w - x : stepWidth;
      dmd.fillRect(x, 0, sw, bandHeight, dmd.Color444(level, level, level));
      dmd.fillRect(x, bandHeight, sw, bandHeight, dmd.Color444(level, 0, 0));
      dmd.fillRect(x, bandHeight * 2, sw, bandHeight, dmd.Color444(0, level, 0));
      dmd.fillRect(x, bandHeight * 3, sw, h - bandHeight * 3, dmd.Color444(0, 0, level));
    }
    dmd.drawFastHLine(0, bandHeight, w, WHITE);
    dmd.drawFastHLine(0, bandHeight * 2, w, WHITE);
    dmd.drawFastHLine(0, bandHeight * 3, w, WHITE);
  }
}

// ---------- 5 pixel health / address walk ---------------------------------------------

static const uint32_t PIXEL_HEALTH_PHASE_MS = 2200UL;

static void renderPixelHealth(uint32_t elapsed) {
  const int16_t w = dmd.width();
  const int16_t h = dmd.height();
  const bool verticalWalk = ((elapsed / PIXEL_HEALTH_PHASE_MS) & 1) == 0;
  dmd.fillScreen(BLACK);

  if (verticalWalk) {
    uint16_t x = (elapsed / 18UL) % w;
    for (int16_t y = 0; y < h; y++) {
      uint16_t px = (x + y * 3) % w;
      dmd.drawPixel(px, y, huePalette[(uint8_t)(y * 4)]);
    }
    dmd.drawFastVLine(x, 0, h, DIM_BLUE);
  } else {
    uint16_t y = (elapsed / 28UL) % h;
    for (int16_t x = 0; x < w; x++) {
      uint16_t py = (y + x) % h;
      dmd.drawPixel(x, py, huePalette[(uint8_t)(x * 2)]);
    }
    dmd.drawFastHLine(0, y, w, DIM_RED);
  }
}

// ---------- 6 brightness / linearity --------------------------------------------------

static void renderBrightness(uint32_t elapsed) {
  static const uint8_t dimmingSteps[] = {4, 3, 2, 1, 0, 1, 2, 3};
  const int16_t w = dmd.width();
  const int16_t h = dmd.height();
  uint8_t phase =
      (elapsed / 700UL) % (sizeof(dimmingSteps) / sizeof(dimmingSteps[0]));
  uint8_t actualLevel;
#if DISPLAY_BACKEND == BACKEND_DMD_RGB
  actualLevel = DMD_RGB_BRIGHTNESS >> dimmingSteps[phase];
  dmd.setBrightness(actualLevel);
#else
  actualLevel = dmd.shiftColorBrightnessDown(
      DMD_SPWM_BRIGHTNESS_SHIFT + dimmingSteps[phase]);
#endif
  dmd.fillScreen(BLACK);

  int16_t swatchWidth = w / 16;
  for (uint8_t level = 0; level < 16; level++) {
    int16_t x = level * swatchWidth;
    dmd.fillRect(x, 4, (level == 15) ? w - x : swatchWidth,
                 h - 16, dmd.Color444(level, level, level));
  }
  dmd.drawRect(0, 3, w, h - 14, WHITE);

  char valueText[6];
#if DISPLAY_BACKEND == BACKEND_DMD_RGB
  formatByte(actualLevel, valueText);
#else
  valueText[0] = 'S';
  formatByte(actualLevel, valueText + 1);
#endif
  drawCenteredText(valueText, h - 9, YELLOW, BLACK);
}

// ---------- 7 refresh / ghosting ------------------------------------------------------

static void renderGhosting(uint32_t elapsed) {
  const int16_t w = dmd.width();
  const int16_t h = dmd.height();
  uint8_t phase = (elapsed / 2800UL) % 2;
  int16_t x = (int16_t)((elapsed / 8UL) % (uint32_t)(w + 16)) - 8;
  int16_t y = (int16_t)((elapsed / 11UL) % (uint32_t)(h + 12)) - 6;

  if (phase == 0) {
    dmd.fillScreen(BLACK);
    dmd.fillRect(x, 0, 2, h, WHITE);
    dmd.fillRect(0, y, w, 2, RED);
    drawGlowPixel(x, y, WHITE, BLUE);
  } else {
    dmd.fillScreen(dmd.Color444(3, 3, 3));
    dmd.fillRect(x, 0, 3, h, BLACK);
    dmd.fillRect(0, y, w, 3, BLACK);
    dmd.drawRect(x - 2, y - 2, 7, 7, CYAN);
  }
}

// ---------- 8 plasma nebula -----------------------------------------------------------

static void renderPlasma(uint32_t elapsed) {
  const int16_t w = dmd.width();
  const int16_t h = dmd.height();
  uint8_t t = elapsed >> 4;

  for (int16_t y = 0; y < h; y++) {
    for (int16_t x = 0; x < w; x++) {
      int16_t sum = waveSigned((uint8_t)(x * 3 + t));
      sum += waveSigned((uint8_t)(y * 5 - t * 2));
      sum += waveSigned((uint8_t)((x + y) * 2 + t * 3));
      uint8_t hue = (uint16_t)(sum + 384) / 3;
      dmd.drawPixel(x, y, huePalette[hue]);
    }
  }
}

// ---------- 9 neon tunnel -------------------------------------------------------------

static void renderNeonTunnel(uint32_t elapsed) {
  const int16_t w = dmd.width();
  const int16_t h = dmd.height();
  uint8_t t = elapsed >> 3;
  int16_t cx = w / 2 + waveSigned(t) / 10;
  int16_t cy = h / 2 + waveSigned(t + 64) / 18;

  for (int16_t y = 0; y < h; y++) {
    int16_t dy = y - cy;
    for (int16_t x = 0; x < w; x++) {
      int16_t dx = x - cx;
      uint32_t radius2 = (int32_t)dx * dx + (int32_t)dy * dy;
      uint8_t ringPhase = (uint8_t)(radius2 / 7 - t * 4);
      int16_t ring = waveSigned(ringPhase);
      int16_t spoke = waveSigned((uint8_t)(dx * 5 + dy * 7 + t));
      uint8_t value = 8;
      if (ring > 92) value = 255;
      else if (ring > 55) value = 90;
      if (spoke > 118) value = 200;
      uint8_t hue = (uint8_t)(radius2 / 9 + t * 2);
      dmd.drawPixel(x, y, wheelColor(hue, value));
    }
  }
}

// ---------- 10 fireworks --------------------------------------------------------------

#define SPARK_COUNT 72
struct Spark {
  int32_t x;
  int32_t y;
  int16_t vx;
  int16_t vy;
  uint8_t life;
  uint8_t hue;
};
static Spark sparks[SPARK_COUNT];
static uint32_t lastFireworkAt = 0;
static bool fireworkStarted = false;

static void resetFireworks() {
  for (uint8_t i = 0; i < SPARK_COUNT; i++) sparks[i].life = 0;
  lastFireworkAt = 0;
  fireworkStarted = false;
}

static void spawnFirework(uint32_t elapsed) {
  int16_t originX = random(dmd.width() / 5, dmd.width() * 4 / 5);
  int16_t originY = random(dmd.height() / 5, dmd.height() * 3 / 5);
  uint8_t baseHue = random(0, 256);
  uint8_t made = 0;

  for (uint8_t i = 0; i < SPARK_COUNT && made < 28; i++) {
    if (sparks[i].life != 0) continue;
    uint8_t angle = made * (256 / 28) + random(-4, 5);
    int16_t speed = random(45, 115);
    sparks[i].x = (int32_t)originX * 64;
    sparks[i].y = (int32_t)originY * 64;
    sparks[i].vx = (waveSigned(angle + 64) * speed) >> 7;
    sparks[i].vy = (waveSigned(angle) * speed) >> 7;
    sparks[i].life = random(125, 220);
    sparks[i].hue = baseHue + made * 2;
    made++;
  }
  lastFireworkAt = elapsed;
  fireworkStarted = true;
}

static void renderFireworks(uint32_t elapsed, uint16_t deltaMs) {
  dmd.fillScreen(BLACK);
  if (!fireworkStarted || elapsed - lastFireworkAt >= 1500UL) {
    spawnFirework(elapsed);
  }

  uint8_t physicsSteps = (deltaMs + 16) / 32;
  if (physicsSteps == 0) physicsSteps = 1;
  if (physicsSteps > 6) physicsSteps = 6;

  for (uint8_t i = 0; i < SPARK_COUNT; i++) {
    Spark &spark = sparks[i];
    if (spark.life == 0) continue;
    int16_t oldX = spark.x >> 6;
    int16_t oldY = spark.y >> 6;
    for (uint8_t step = 0; step < physicsSteps && spark.life != 0; step++) {
      spark.x += spark.vx;
      spark.y += spark.vy;
      spark.vy += 3;
      spark.vx = (spark.vx * 63) >> 6;
      spark.life = (spark.life > 3) ? spark.life - 3 : 0;
    }
    int16_t x = spark.x >> 6;
    int16_t y = spark.y >> 6;

    if (x < -2 || x > dmd.width() + 2 || y < -2 || y > dmd.height() + 2) {
      spark.life = 0;
      continue;
    }
    uint16_t color = wheelColor(spark.hue, spark.life + (spark.life < 55 ? 55 : 0));
    dmd.drawLine(oldX, oldY, x, y, color);
    drawPixelSafe(x, y, WHITE);
  }
}

// ---------- 11 aurora ribbons ---------------------------------------------------------

static void renderAurora(uint32_t elapsed) {
  const int16_t w = dmd.width();
  const int16_t h = dmd.height();
  uint8_t t = elapsed >> 4;
  dmd.fillScreen(BLACK);

  for (uint8_t ribbon = 0; ribbon < 5; ribbon++) {
    int16_t previousY = h / 2;
    uint8_t hue = 75 + ribbon * 22 + t;
    uint16_t core = wheelColor(hue, 255);
    uint16_t glow = wheelColor(hue, 65);
    for (int16_t x = 0; x < w; x++) {
      int16_t y = h / 2;
      y += (waveSigned((uint8_t)(x * (2 + ribbon) + t * (ribbon + 1))) *
            (5 + ribbon * 2)) >> 7;
      y += waveSigned((uint8_t)(x + t * 2 + ribbon * 43)) >> 5;
      if (x > 0) {
        dmd.drawLine(x - 1, previousY - 2, x, y - 2, glow);
        dmd.drawLine(x - 1, previousY + 2, x, y + 2, glow);
        dmd.drawLine(x - 1, previousY, x, y, core);
      }
      previousY = y;
    }
  }
}


// ---------- 12 mirror prism calibration -----------------------------------------------

static void renderMirrorPrismCalibration(uint32_t elapsed) {
  const int16_t w = registerTestPatternVisibleWidth();
  const int16_t h = dmd.height();
  if (w <= 0 || h <= 0) return;

  const uint8_t t = elapsed >> 3;
  dmd.fillScreen(BLACK);

  // Doubled center coordinates make the field exactly symmetric on odd/even panels.
  for (int16_t y = 0; y < h; y++) {
    const int16_t dy = abs16(y * 2 - (h - 1));
    for (int16_t x = 0; x < w; x++) {
      const int16_t dx = abs16(x * 2 - (w - 1));
      const int16_t ring = (dx > dy) ? dx : dy;
      int16_t prism = waveSigned((uint8_t)(dx * 5 + t));
      prism += waveSigned((uint8_t)(dy * 7 - t));
      prism += waveSigned((uint8_t)((dx + dy) * 3 + t * 2));
      const uint8_t hue = (uint8_t)(ring * 7 + t * 3 + (prism >> 2));
      dmd.drawPixel(x, y, huePalette[hue]);
    }
  }

  const int16_t centerLeft = (w - 1) / 2;
  const int16_t centerRight = w / 2;
  const int16_t centerTop = (h - 1) / 2;
  const int16_t centerBottom = h / 2;

  dmd.drawFastHLine(0, 0, w, RED);
  dmd.drawFastHLine(0, h - 1, w, YELLOW);
  dmd.drawFastVLine(0, 0, h, BLUE);
  dmd.drawFastVLine(w - 1, 0, h, GREEN);

  // Both sampled diagonals verify mirroring, aspect ratio, and corner registration.
  if (w > 1 && h > 1) {
    for (int16_t x = 0; x < w; x++) {
      const int16_t y = (int32_t)x * (h - 1) / (w - 1);
      const bool invert = (x >> 1) & 1;
      dmd.drawPixel(x, y, invert ? WHITE : BLACK);
      dmd.drawPixel(x, h - 1 - y, invert ? BLACK : WHITE);
    }
  }

  // Draw axes after diagonals so the exact center reference remains unbroken.
  for (int16_t y = 0; y < h; y++) {
    const bool invert = (y >> 1) & 1;
    dmd.drawPixel(centerLeft, y, invert ? WHITE : BLACK);
    if (centerRight != centerLeft) {
      dmd.drawPixel(centerRight, y, invert ? BLACK : WHITE);
    }
  }
  for (int16_t x = 0; x < w; x++) {
    const bool invert = (x >> 1) & 1;
    dmd.drawPixel(x, centerTop, invert ? WHITE : BLACK);
    if (centerBottom != centerTop) {
      dmd.drawPixel(x, centerBottom, invert ? BLACK : WHITE);
    }
  }

  // Robust orientation Ls stay visible after all other calibration overlays.
  drawOrientationCornerLs(w, h);
}


/*
  TEXT FONT QUICK REFERENCE
  -------------------------
  Standard DMD fonts (construct with DMD_Standard_Font Name(bitmap)):
    st_fonts/SystemFont5x7.h                  -> SystemFont5x7
    st_fonts/Arial14.h                        -> Arial_14
    st_fonts/Arial_black_16.h                 -> Arial_Black_16
    st_fonts/SystemFont5x7TR.h                -> SystemFont5x7TR (Turkish)
    st_fonts/Arial_Black_16TR.h               -> Arial_Black_16TR (Turkish)
    st_fonts/Arial_Black_16_ISO_8859_1.h      -> Arial_Black_16_ISO_8859_1
    st_fonts/UkrRusSystemFont5x7.h            -> UkrRusSystemFont5x7
    st_fonts/UkrRusArial14.h                  -> UkrRusArial_14

  GFX fonts (construct with DMD_GFX_Font Name((uint8_t *)&fontDescriptor, baseline)):
    gfx_fonts/FreeMono12pt7b.h                -> FreeMono12pt7b
    gfx_fonts/FreeSerifBold9pt7b.h            -> FreeSerifBold9pt7b
    gfx_fonts/FreeSerifItalic9pt7b.h          -> FreeSerifItalic9pt7b
    gfx_fonts/FreeSerifBoldItalic9pt7b.h      -> FreeSerifBoldItalic9pt7b
    gfx_fonts/Glametrix12pt7b.h               -> Glametrix12pt7b + Glametrix12pt8b_rus
    gfx_fonts/GlametrixBold12pt7b.h           -> GlametrixBold12pt7b + GlametrixBold12pt8b_rus
    gfx_fonts/GlametrixBold9pt7b.h            -> GlametrixBold9pt7b + GlametrixBold9pt8b_rus
    gfx_fonts/GlametrixLight12pt7b.h          -> GlametrixLight12pt7b + GlametrixLight12pt8b_rus
    gfx_fonts/comic9pt8b.h                    -> comic9pt8b + comic9pt8brus

  The Ukr/Rus System and Arial headers replace, rather than accompany, their Latin
  versions because those pairs share symbols/include guards. Raw UTF-8 also needs the
  conversion helpers shown in the language examples. selectFont(font, value) changes
  character spacing, not size. The inherited Adafruit_GFX setTextSize() belongs to its
  separate Print-font path; demo 17 keeps the DMD font path and shows integer runtime
  scaling for SystemFont5x7.
*/

// ---------- 13 shop promo transitions -------------------------------------------------

static void renderShopPromo(uint32_t elapsed) {
  const int16_t w = dmd.width();
  const int16_t h = dmd.height();
  const uint8_t cardCount = sizeof(promoCards) / sizeof(promoCards[0]);
  sceneDurationOverrideMs = (uint32_t)cardCount * TEXT_PROMO_CARD_MS;
  dmd.selectFont(&SmallFont, 1);
  dmd.fillScreen(BLACK);

  const uint8_t cardIndex = (elapsed / TEXT_PROMO_CARD_MS) % cardCount;
  const uint32_t local = elapsed % TEXT_PROMO_CARD_MS;
  const PromoCard &card = promoCards[cardIndex];
  const uint16_t borderColor = huePalette[(uint8_t)(elapsed >> 3)];
  dmd.drawRect(0, 0, w, h, borderColor);

  for (int16_t x = 2; x < w - 1; x += 8) {
    dmd.drawPixel(x, 1, huePalette[(uint8_t)(x * 4 + (elapsed >> 3))]);
    dmd.drawPixel(w - 1 - x, h - 2,
                  huePalette[(uint8_t)(x * 4 - (elapsed >> 3))]);
  }

  uint8_t titleScale = 1;
  if (w >= 96 && h >= 48 &&
      scaled5x7TextWidth(card.title, 2) <= w - 4) {
    titleScale = 2;
  }
  const int16_t titleWidth = scaled5x7TextWidth(card.title, titleScale);
  const int16_t subtitleWidth = dmd.stringWidth(card.subtitle);
  const int16_t targetTitleX = (w - titleWidth) / 2;
  const int16_t targetSubtitleX = (w - subtitleWidth) / 2;
  const int16_t blockHeight = SmallFont.get_height() * titleScale + 3 +
                              SmallFont.get_height();
  const int16_t titleY = (h - blockHeight) / 2;
  const int16_t subtitleY = titleY + SmallFont.get_height() * titleScale + 3;
  const uint32_t entryMs = 550;
  int16_t titleX = targetTitleX;
  int16_t subtitleX = targetSubtitleX;

  if (local < entryMs) {
    titleX = -titleWidth +
        (int32_t)(targetTitleX + titleWidth) * local / entryMs;
    subtitleX = w -
        (int32_t)(w - targetSubtitleX) * local / entryMs;
  }

  drawScaled5x7Text(titleX + 1, titleY + 1, card.title,
                    titleScale, DIM_BLUE);
  drawScaled5x7Text(titleX, titleY, card.title, titleScale, WHITE);
  dmd.setTextColor(YELLOW, BLACK);
  dmd.drawStringX(subtitleX, subtitleY, card.subtitle, YELLOW);

  const uint32_t wipeStart = TEXT_PROMO_CARD_MS - 500UL;
  if (local > wipeStart) {
    const int16_t wipeHalf =
        (int32_t)(w / 2 + 1) * (local - wipeStart) /
        (TEXT_PROMO_CARD_MS - wipeStart);
    dmd.fillRect(w / 2 - wipeHalf, 0, wipeHalf * 2, h, BLACK);
    dmd.drawFastVLine(w / 2 - wipeHalf, 0, h, borderColor);
    dmd.drawFastVLine(w / 2 + wipeHalf - 1, 0, h, borderColor);
  }
}

// ---------- 14 aligned multiline text -------------------------------------------------

static void renderAlignedMultilineText(uint32_t elapsed) {
  sceneDurationOverrideMs = 6500UL;
  dmd.selectFont(&SmallFont, 1);
  dmd.fillScreen(BLACK);

  const uint8_t scale = adaptiveTextScale();
  const uint8_t gap = scale;
  const uint8_t lineCount = configuredVisibleLineCount(scale, gap);
  const int16_t blockHeight =
      configuredTextBlockHeight(lineCount, scale, gap);
  const int16_t top = (dmd.height() - blockHeight) / 2;
  const uint16_t guideColor = dmd.Color444(0, 2, 2);
  dmd.drawFastVLine(1, 0, dmd.height(), guideColor);
  dmd.drawFastVLine(dmd.width() / 2, 0, dmd.height(), guideColor);
  dmd.drawFastVLine(dmd.width() - 2, 0, dmd.height(), guideColor);

  for (uint8_t line = 0; line < lineCount; line++) {
    const int16_t y = top +
        line * (SmallFont.get_height() * scale + gap);
    const uint8_t alignment = configuredTextAlignments[line];
    const uint16_t color = alignmentColor(alignment);
    drawAligned5x7Text(configuredTextLines[line], y, alignment, scale, color);

    int16_t anchorX = dmd.width() / 2;
    if (alignment == TEXT_ALIGN_LEFT) anchorX = 1;
    if (alignment == TEXT_ALIGN_RIGHT) anchorX = dmd.width() - 2;
    drawPixelSafe(anchorX, y + SmallFont.get_height() * scale / 2,
                  huePalette[(uint8_t)(elapsed >> 2)]);
  }
}

// ---------- 15 horizontal text scroll -------------------------------------------------

static void renderHorizontalTextScroll(uint32_t elapsed) {
  sceneDurationOverrideMs = 10000UL;
  dmd.selectFont(&SmallFont, 1);
  dmd.fillScreen(BLACK);

  const int16_t w = dmd.width();
  const int16_t h = dmd.height();
  const uint8_t scale = adaptiveTextScale();
  const int16_t upperWidth =
      scaled5x7TextWidth(TEXT_SCROLL_LEFT_MESSAGE, scale);
  const int16_t lowerWidth =
      scaled5x7TextWidth(TEXT_SCROLL_RIGHT_MESSAGE, scale);
  const uint32_t pixelStep = elapsed / TEXT_SCROLL_STEP_MS;
  const int16_t upperX = w -
      pixelStep % (uint16_t)(w + upperWidth);
  const int16_t lowerX = -lowerWidth +
      pixelStep % (uint16_t)(w + lowerWidth);
  const int16_t lineHeight = SmallFont.get_height() * scale;
  const int16_t blockHeight = lineHeight * 2 + 5;
  const int16_t upperY = (h - blockHeight) / 2;
  const int16_t lowerY = upperY + lineHeight + 5;

  dmd.drawFastHLine(0, h / 2, w, dmd.Color444(1, 1, 3));
  if (scale == 1) {
    dmd.setTextColor(CYAN, BLACK);
    dmd.drawStringX(upperX, upperY, TEXT_SCROLL_LEFT_MESSAGE, CYAN);
    dmd.setTextColor(MAGENTA, BLACK);
    dmd.drawStringX(lowerX, lowerY, TEXT_SCROLL_RIGHT_MESSAGE, MAGENTA);
  } else {
    drawScaled5x7Text(upperX, upperY, TEXT_SCROLL_LEFT_MESSAGE, scale, CYAN);
    drawScaled5x7Text(lowerX, lowerY, TEXT_SCROLL_RIGHT_MESSAGE,
                      scale, MAGENTA);
  }
}

// ---------- 16 vertical text scroll ---------------------------------------------------

static void renderVerticalTextScroll(uint32_t elapsed) {
  dmd.selectFont(&SmallFont, 1);
  dmd.fillScreen(BLACK);

  const uint8_t scale = adaptiveTextScale();
  const uint8_t gap = scale * 2;
  const uint8_t lineCount = TEXT_DEMO_LINE_COUNT;
  const int16_t blockHeight =
      configuredTextBlockHeight(lineCount, scale, gap);
  const int16_t travel = dmd.height() + blockHeight + 1;
  sceneDurationOverrideMs = (uint32_t)travel * TEXT_VERTICAL_STEP_MS;
  const int16_t top = dmd.height() -
      (elapsed / TEXT_VERTICAL_STEP_MS) % (uint16_t)travel;

  for (uint8_t line = 0; line < lineCount; line++) {
    const int16_t y = top +
        line * (SmallFont.get_height() * scale + gap);
    drawAligned5x7Text(configuredTextLines[line], y,
                       configuredTextAlignments[line], scale,
                       alignmentColor(configuredTextAlignments[line]));
  }
}

// ---------- 17 pixel text zoom --------------------------------------------------------

static void renderPixelTextZoom(uint32_t elapsed) {
  const int16_t w = dmd.width();
  const int16_t h = dmd.height();
  const int16_t baseWidth = scaled5x7TextWidth(TEXT_ZOOM_MESSAGE, 1);
  uint8_t maxScaleX = (baseWidth > 0) ? (w - 6) / baseWidth : 1;
  uint8_t maxScaleY = (h - 6) / SmallFont.get_height();
  uint8_t maxScale = (maxScaleX < maxScaleY) ? maxScaleX : maxScaleY;
  if (maxScale > TEXT_ZOOM_MAX_SCALE) maxScale = TEXT_ZOOM_MAX_SCALE;
  if (maxScale < 1) maxScale = 1;

  const uint16_t cycleSteps = (maxScale > 1) ? maxScale * 2 - 2 : 1;
  const uint32_t cycleMs = (uint32_t)cycleSteps * TEXT_ZOOM_STEP_MS;
  const uint16_t cycleCount = (6500UL + cycleMs - 1) / cycleMs;
  // Hold scale 1 once more after the final complete out-and-back cycle.
  sceneDurationOverrideMs = cycleMs * cycleCount + TEXT_ZOOM_STEP_MS;

  uint8_t scale = 1;
  if (maxScale > 1) {
    const uint16_t zoomStep = (elapsed / TEXT_ZOOM_STEP_MS) % cycleSteps;
    scale = (zoomStep < maxScale) ?
        zoomStep + 1 : maxScale * 2 - 1 - zoomStep;
  }

  dmd.fillScreen(BLACK);
  const int16_t centerX = w / 2;
  const int16_t centerY = h / 2;
  const uint8_t motion = elapsed >> 3;
  for (int16_t x = 0; x < w; x += 8) {
    dmd.drawLine(centerX, centerY, x, 0,
                 wheelColor((uint8_t)(x * 3 + motion), 70));
    dmd.drawLine(centerX, centerY, w - 1 - x, h - 1,
                 wheelColor((uint8_t)(x * 3 - motion), 70));
  }

  const int16_t textWidth = scaled5x7TextWidth(TEXT_ZOOM_MESSAGE, scale);
  const int16_t textHeight = SmallFont.get_height() * scale;
  const int16_t x = (w - textWidth) / 2;
  const int16_t y = (h - textHeight) / 2;
  dmd.fillRect(x - 2, y - 2, textWidth + 4, textHeight + 4, BLACK);
  dmd.drawRect(x - 2, y - 2, textWidth + 4, textHeight + 4,
               huePalette[(uint8_t)(motion * 2)]);
  drawScaled5x7Text(x + 1, y + 1, TEXT_ZOOM_MESSAGE,
                    scale, dmd.Color444(0, 2, 5));
  drawScaled5x7Text(x, y, TEXT_ZOOM_MESSAGE, scale, WHITE);
}

// ---------- 18 font showcase ----------------------------------------------------------

static void renderFontShowcase(uint32_t elapsed) {
  sceneDurationOverrideMs = (uint32_t)FONT_SHOWCASE_COUNT * TEXT_FONT_HOLD_MS;
  const uint8_t fontIndex =
      (elapsed / TEXT_FONT_HOLD_MS) % FONT_SHOWCASE_COUNT;
  const FontShowcaseEntry &entry = fontShowcase[fontIndex];
  const char *sample = TEXT_FONT_SAMPLE;
  dmd.fillScreen(BLACK);

  dmd.selectFont(&SmallFont, 1);
  dmd.setTextColor(CYAN, BLACK);
  const int16_t labelX = (dmd.width() - dmd.stringWidth(entry.label)) / 2;
  dmd.drawStringX(labelX, 0, entry.label, CYAN);
  dmd.drawFastHLine(0, 8, dmd.width(),
                    huePalette[(uint8_t)(elapsed >> 3)]);

  dmd.selectFont(entry.font, 1);
  int16_t sampleWidth;
  int16_t minY;
  int16_t maxY;
  dmd.stringBounds(sample, 0, &sampleWidth, &minY, &maxY);
  const int16_t sampleHeight = maxY - minY + 1;
  const int16_t contentTop = 9;
  const int16_t availableHeight = dmd.height() - contentTop;
  const int16_t sampleX = (dmd.width() - sampleWidth) / 2;
  const int16_t sampleY = contentTop +
      (availableHeight - sampleHeight) / 2 - minY;
  const uint16_t color =
      huePalette[(uint8_t)(fontIndex * 31 + (elapsed >> 4))];
  dmd.setTextColor(color, BLACK);
  dmd.drawStringX(sampleX, sampleY, sample, color);
}

// ---------- 19 full-screen digital clock ---------------------------------------------

static void renderDigitalClock(uint32_t elapsed) {
  sceneDurationOverrideMs = CLOCK_DEMO_DURATION_MS;
  const ShowcaseClockTime clock = readShowcaseClock();
  const uint8_t displayHour = clockDisplayHour(clock.hour);
  const int16_t w = dmd.width();
  const int16_t h = dmd.height();
  const int16_t widthScale = w / 21;
  const int16_t heightScale = (h - 2) / 9;
  int16_t scaleValue =
      (widthScale < heightScale) ? widthScale : heightScale;
  if (scaleValue < 1) scaleValue = 1;
  const uint8_t scale = scaleValue;

  const int16_t digitWidth = scale * 4;
  const int16_t digitHeight = scale * 9;
  const int16_t gap = (scale > 1) ? scale - 1 : 1;
  const int16_t totalWidth = scale * 17 + gap * 4;
  int16_t x = (w - totalWidth) / 2;
  const int16_t y = (h - 1 - digitHeight) / 2;
  const uint8_t mood = elapsed >> 6;
  const uint16_t hourColor = wheelColor(mood, 255);
  const uint16_t minuteColor = wheelColor((uint8_t)(mood + 92), 255);
  const uint16_t hourInactive = CLOCK_SHOW_INACTIVE_SEGMENTS ?
      dmd.Color444(0, 0, 1) : BLACK;
  const uint16_t minuteInactive = CLOCK_SHOW_INACTIVE_SEGMENTS ?
      dmd.Color444(1, 0, 0) : BLACK;
  const uint8_t digits[] = {
    (uint8_t)(displayHour / 10), (uint8_t)(displayHour % 10),
    (uint8_t)(clock.minute / 10), (uint8_t)(clock.minute % 10)
  };

  dmd.fillScreen(BLACK);
  drawSevenSegmentDigit(x, y, digits[0], scale,
                        hourColor, hourInactive);
  x += digitWidth + gap;
  drawSevenSegmentDigit(x, y, digits[1], scale,
                        hourColor, hourInactive);
  x += digitWidth + gap;

  const uint32_t colonOnMs = (CLOCK_TICK_MS * 2UL + 2UL) / 3UL;
  const bool colonLit = clock.tickElapsedMs < colonOnMs;
  const uint16_t colonDim = dmd.Color444(2, 1, 0);
  drawSevenSegmentBar(x, y + scale * 2, scale, scale,
                      colonLit, YELLOW, colonDim);
  drawSevenSegmentBar(x, y + scale * 6, scale, scale,
                      colonLit, YELLOW, colonDim);
  if (colonLit && scale >= 3) {
    const uint8_t highlightSize = (scale & 1) ? 1 : 2;
    const int16_t highlightX = x + (scale - highlightSize) / 2;
    const int16_t highlightOffset = (scale - highlightSize) / 2;
    dmd.fillRect(highlightX, y + scale * 2 + highlightOffset,
                 highlightSize, highlightSize, WHITE);
    dmd.fillRect(highlightX, y + scale * 6 + highlightOffset,
                 highlightSize, highlightSize, WHITE);
  }
  x += scale + gap;

  drawSevenSegmentDigit(x, y, digits[2], scale,
                        minuteColor, minuteInactive);
  x += digitWidth + gap;
  drawSevenSegmentDigit(x, y, digits[3], scale,
                        minuteColor, minuteInactive);

  // The bottom edge is a continuous seconds track, including the current sub-second.
  const uint32_t minuteElapsedMs =
      (uint32_t)clock.second * CLOCK_TICK_MS + clock.tickElapsedMs;
  int16_t progress =
      (uint32_t)w * minuteElapsedMs / (60UL * CLOCK_TICK_MS);
  if (progress > w) progress = w;
  dmd.drawFastHLine(0, h - 1, w, dmd.Color444(0, 1, 2));
  if (progress > 0) {
    dmd.drawFastHLine(0, h - 1, progress,
                      wheelColor((uint8_t)(mood + 46), 220));
  }
  if (progress < w) dmd.drawPixel(progress, h - 1, WHITE);
}

// ---------- Scene control -------------------------------------------------------------

static const char *sceneName(uint8_t scene) {
  switch (scene) {
    case TEST_ALIGNMENT: return "1 register-test alignment";
    case TEST_GRADIENT: return "2 register-test gradient";
    case TEST_RGBW_SOLIDS: return "3 RGBW solid colors";
    case TEST_COLOR_RAMPS: return "4 color bars / 16-step ramps";
    case TEST_PIXEL_HEALTH: return "5 pixel health / address walk";
    case TEST_BRIGHTNESS: return "6 brightness / linearity";
    case TEST_GHOSTING: return "7 refresh / ghosting";
    case DEMO_PLASMA: return "8 plasma nebula";
    case DEMO_NEON_TUNNEL: return "9 neon tunnel";
    case DEMO_FIREWORKS: return "10 fireworks";
    case DEMO_AURORA: return "11 aurora ribbons";
    case DEMO_MIRROR_PRISM_CALIBRATION: return "12 mirror prism calibration";
    case DEMO_SHOP_PROMO: return "13 shop promo transitions";
    case DEMO_ALIGNED_MULTILINE_TEXT: return "14 aligned multiline text";
    case DEMO_HORIZONTAL_TEXT_SCROLL: return "15 horizontal text scroll";
    case DEMO_VERTICAL_TEXT_SCROLL: return "16 vertical text scroll";
    case DEMO_PIXEL_TEXT_ZOOM: return "17 pixel text zoom";
    case DEMO_FONT_SHOWCASE: return "18 font showcase";
    case DEMO_DIGITAL_CLOCK: return "19 full-screen digital clock";
    default: return "unknown";
  }
}

static uint32_t sceneAutoplayDuration() {
  return sceneDurationOverrideMs != 0 ?
      sceneDurationOverrideMs : AUTOPLAY_SCENE_MS;
}

static void resetSceneState(uint8_t scene) {
  sceneDurationOverrideMs = 0;
#if DISPLAY_BACKEND == BACKEND_DMD_RGB
  dmd.setBrightness(DMD_RGB_BRIGHTNESS);
#else
  dmd.shiftColorBrightnessDown(DMD_SPWM_BRIGHTNESS_SHIFT);
#endif
  dmd.selectFont(&SmallFont, 1);
  if (scene == DEMO_FIREWORKS) resetFireworks();
}

static void enterScene(uint8_t scene, uint32_t now) {
  activeScene = scene;
  sceneStarted = now;
  lastFrameAt = now;
  firstFrame = true;
  resetSceneState(scene);
  Serial.print(F("Scene: "));
  Serial.println(sceneName(scene));
}

static void renderScene(uint8_t scene, uint32_t elapsed, uint16_t deltaMs) {
  switch (scene) {
    case TEST_ALIGNMENT: renderAlignment(elapsed); break;
    case TEST_GRADIENT: renderGradient(elapsed); break;
    case TEST_RGBW_SOLIDS: renderRGBWSolids(elapsed); break;
    case TEST_COLOR_RAMPS: renderColorRamps(elapsed); break;
    case TEST_PIXEL_HEALTH: renderPixelHealth(elapsed); break;
    case TEST_BRIGHTNESS: renderBrightness(elapsed); break;
    case TEST_GHOSTING: renderGhosting(elapsed); break;
    case DEMO_PLASMA: renderPlasma(elapsed); break;
    case DEMO_NEON_TUNNEL: renderNeonTunnel(elapsed); break;
    case DEMO_FIREWORKS: renderFireworks(elapsed, deltaMs); break;
    case DEMO_AURORA: renderAurora(elapsed); break;
    case DEMO_MIRROR_PRISM_CALIBRATION: renderMirrorPrismCalibration(elapsed); break;
    case DEMO_SHOP_PROMO: renderShopPromo(elapsed); break;
    case DEMO_ALIGNED_MULTILINE_TEXT: renderAlignedMultilineText(elapsed); break;
    case DEMO_HORIZONTAL_TEXT_SCROLL: renderHorizontalTextScroll(elapsed); break;
    case DEMO_VERTICAL_TEXT_SCROLL: renderVerticalTextScroll(elapsed); break;
    case DEMO_PIXEL_TEXT_ZOOM: renderPixelTextZoom(elapsed); break;
    case DEMO_FONT_SHOWCASE: renderFontShowcase(elapsed); break;
    case DEMO_DIGITAL_CLOCK: renderDigitalClock(elapsed); break;
  }
}

void setup() {
  Serial.begin(115200);
  dmd.init();

#if DISPLAY_BACKEND == BACKEND_DMD_SPWM && DMD_SPWM_REGISTER_OVERRIDE > 0
  dmdSpwmApplySelectedRegisterOverride(dmd);
#endif

  // Both preferences are selected in USER SETTINGS near the top of this file.
#if ROW_MULTIPLEXER_MODE == ROW_MUX_BINARY
  dmd.configure_multiplexer(DMD_MUX_TYPE138);
#elif ROW_MULTIPLEXER_MODE == ROW_MUX_SHIFT_REGISTER
  dmd.configure_multiplexer(DMD_MUX_TYPE_SHIFTREG);
#endif
  dmd.setColorOrder(PANEL_COLOR_ORDER);

  dmd.selectFont(&SmallFont, 1);
  initColors();
  randomSeed(micros());
  const uint32_t now = millis();
  beginShowcaseClock(now);
  dmd.fillScreen(BLACK);
  presentFrame();

  Serial.println(F("DMD calibration and showcase"));
#if DISPLAY_BACKEND == BACKEND_DMD_RGB
#if DMD_RGB_DUAL_BUFFER
  Serial.println(F("Backend: DMD_RGB with two MCU framebuffers"));
#else
  Serial.println(F("Backend: DMD_RGB with one MCU framebuffer"));
#endif
#else
  Serial.print(F("Backend: SPWM "));
  Serial.print(F(STRINGIFY(SPWM_DRIVER_CLASS)));
  Serial.println(F(" with MCU staging buffer + panel SRAM"));
#endif
  enterScene(activeScene, now);
}

void loop() {
  uint32_t now = millis();
  updateShowcaseClock(now);
  uint32_t elapsed = now - sceneStarted;

  if (DEMO_INDEX == SCENE_AUTOPLAY &&
      elapsed >= sceneAutoplayDuration()) {
    uint8_t next = activeScene + 1;
    if (next > LAST_DEMO_INDEX) next = TEST_ALIGNMENT;
    enterScene(next, now);
    elapsed = 0;
  }

  // Match dmd_spwm_panel's normal frame-update interval.
  uint32_t interval = 30;
  if (!firstFrame && (uint32_t)(now - lastFrameAt) <= interval) return;
  uint32_t frameDelta = now - lastFrameAt;
  if (frameDelta > 200) frameDelta = 200;
  lastFrameAt = now;

  renderScene(activeScene, elapsed, frameDelta);
  presentFrame();
  firstFrame = false;
}
