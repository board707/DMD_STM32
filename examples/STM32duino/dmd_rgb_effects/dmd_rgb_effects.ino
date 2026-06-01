/*--------------------------------------------------------------------------------------
  RGB effects demo for STM32duino (Arduino Core STM32)

  Panel: RGB40x20_S5_LNikon (pattern 102), 1x1, COLOR_4BITS, dual buffer.
  Fonts: GlametrixBold9pt / GlametrixLight12pt with Cyrillic (utf8_rus + drawMarqueeX).

  Tested: STM32F103CBT, STM32F401, STM32F411.
  Serial 115200 — scene names in loop.
 ------------------------------------------------------------------------------------- */
#include "DMD_RGB.h"
#pragma GCC diagnostic ignored "-Wnarrowing"
#pragma GCC diagnostic ignored "-Woverflow"
#include "gfx_fonts/GlametrixBold9pt7b.h"
#include "gfx_fonts/GlametrixLight12pt7b.h"
#pragma GCC diagnostic warning "-Wnarrowing"
#pragma GCC diagnostic warning "-Woverflow"

#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
#define ENABLE_DUAL_BUFFER true
#define SCROLL_SCENE_MS 12000

#define DMD_PIN_A PB6
#define DMD_PIN_B PB5
#define DMD_PIN_C PB4
#define DMD_PIN_D PB3
#define DMD_PIN_E PB8
uint8_t mux_list[] = { DMD_PIN_A, DMD_PIN_B, DMD_PIN_C, DMD_PIN_D, DMD_PIN_E };

#define DMD_PIN_nOE PB0
#define DMD_PIN_SCLK PB7
uint8_t custom_rgbpins[] = { PA6, PA0, PA1, PA2, PA3, PA4, PA5 };

DMD_RGB<RGB40x20_S5_LNikon, COLOR_4BITS> dmd(
  mux_list, DMD_PIN_nOE, DMD_PIN_SCLK, custom_rgbpins,
  DISPLAYS_ACROSS, DISPLAYS_DOWN, ENABLE_DUAL_BUFFER);

DMD_GFX_Font FontSmall((uint8_t*)&GlametrixBold9pt7b, (uint8_t*)&GlametrixBold9pt8b_rus, 0x80, 11);
DMD_GFX_Font FontBig((uint8_t*)&GlametrixLight12pt7b, (uint8_t*)&GlametrixLight12pt8b_rus, 0x80, 13);

#define BLUE_LED_PIN PC13
#define BRIGHTNESS 200
#define SCROLL_MS 50

static DMD_Font* activeFont = &FontSmall;

static const uint16_t COL_BLACK = 0;
static uint16_t colRed, colGreen, colBlue, colYellow, colCyan, colMagenta, colWhite;
static uint16_t palette[6];

static int textCenterY() {
  return (dmd.height() - activeFont->get_height()) / 2;
}

static int utf8_rus(char* dest, const unsigned char* src) {
  uint16_t i, j;
  for (i = 0, j = 0; src[i]; i++) {
    if ((src[i] == 0xD0) && src[i + 1]) { dest[j++] = src[++i] - 0x10; }
    else if ((src[i] == 0xD1) && src[i + 1]) { dest[j++] = src[++i] + 0x30; }
    else dest[j++] = src[i];
  }
  dest[j] = '\0';
  return j;
}

static void matrixPinsSafeBeforeInit() {
  pinMode(DMD_PIN_nOE, OUTPUT);
  digitalWrite(DMD_PIN_nOE, HIGH);
  pinMode(DMD_PIN_SCLK, OUTPUT);
  digitalWrite(DMD_PIN_SCLK, LOW);
}

static void initColors() {
  colRed     = dmd.Color888(255, 0, 0);
  colGreen   = dmd.Color888(0, 255, 0);
  colBlue    = dmd.Color888(0, 0, 255);
  colYellow  = dmd.Color888(255, 255, 0);
  colCyan    = dmd.Color888(0, 255, 255);
  colMagenta = dmd.Color888(255, 0, 255);
  colWhite   = dmd.Color888(255, 255, 255);
  palette[0] = colRed;
  palette[1] = colGreen;
  palette[2] = colBlue;
  palette[3] = colYellow;
  palette[4] = colCyan;
  palette[5] = colMagenta;
}

static uint32_t lastTick = 0;
static uint32_t sceneStart = 0;

static void selectFont(DMD_Font* font) {
  activeFont = font;
  dmd.selectFont(font);
}

static void finishFrame(bool copyFromFront = true) {
  dmd.swapBuffers(copyFromFront);
}

static void showFrame(bool copyFromFront = true) {
  finishFrame(copyFromFront);
}

static int scrollTextY() {
  return (dmd.height() > 16) ? 2 : 0;
}

static const char rusPrivet[] = "Привет!";

static void drawRusMarquee(const char* rusText, int x, int y, uint16_t fg) {
  dmd.setTextColor(fg, COL_BLACK);
  dmd.drawMarqueeX(rusText, x, y);
}

enum Scene : uint8_t {
  SCENE_TITLE = 0,
  SCENE_FONT_SHOW,
  SCENE_SCROLL_H,
  SCENE_BRIGHTNESS,
  SCENE_SCROLL_V,
  SCENE_VSCROLL_GLYPH,
  SCENE_MULTICOLOR,
  SCENE_COLOR_WIPE,
  SCENE_PIXELS,
  SCENE_COUNT
};

static uint8_t scene = SCENE_TITLE;
static uint8_t phase = 0;
static uint8_t colorIdx = 0;
static uint8_t stepIdx = 0;
static uint8_t brightnessVal = 80;

static const int8_t hSteps[] = { 1, -1, -2, 2 };
static const int8_t vSteps[] = { 1, -1, -2, 2 };

static void showSceneName(const char* name) {
  Serial.print(F("scene: "));
  Serial.println(name);
}

static void prepMarquee(uint16_t fg) {
  dmd.setMarqueeColor(fg, COL_BLACK);
}

static void beginScene(uint8_t next) {
  scene = next;
  phase = 0;
  colorIdx = 0;
  stepIdx = 0;
  sceneStart = millis();
  prepMarquee(COL_BLACK);
  dmd.fillScreen(COL_BLACK);
  dmd.setBrightness(BRIGHTNESS);
  selectFont(&FontSmall);
  showFrame();
}

static void nextScene() {
  beginScene((scene + 1) % SCENE_COUNT);
}

static void runTitle() {
  const char* msg = "RGB";

  if (phase == 0) {
    showSceneName("title (GlametrixLight12)");
    selectFont(&FontBig);
    dmd.setTextColor(palette[0], COL_BLACK);
    phase = 1;
    lastTick = millis();
  }

  if (millis() - lastTick >= 450) {
    lastTick = millis();
    colorIdx = (colorIdx + 1) % 6;
    dmd.fillScreen(COL_BLACK);
    dmd.setTextColor(palette[colorIdx], COL_BLACK);
    int x = (dmd.width() - dmd.stringWidth(msg)) / 2;
    dmd.drawStringX(x, textCenterY(), msg, palette[colorIdx]);
    showFrame();
    if (colorIdx == 0 && millis() - sceneStart > 3000) {
      nextScene();
    }
  }
}

static void runFontShow() {
  static const char* smallMsg = "Bold 9pt";
  static const char* bigMsg = "BIG";
  static char rusBuf[32];

  if (phase == 0) {
    showSceneName("fonts compare");
    utf8_rus(rusBuf, (const unsigned char*)rusPrivet);
    phase = 1;
    lastTick = millis();
    colorIdx = 0;
  }

  if (millis() - lastTick < 900) return;
  lastTick = millis();

  dmd.fillScreen(COL_BLACK);
  if (colorIdx == 6) {
    selectFont(&FontSmall);
    int x = (dmd.width() - dmd.stringWidth(rusBuf)) / 2;
    drawRusMarquee(rusBuf, x, textCenterY(), colYellow);
  } else if (colorIdx % 2 == 0) {
    selectFont(&FontSmall);
    dmd.drawStringX(2, 2, smallMsg, palette[colorIdx % 6]);
  } else {
    selectFont(&FontBig);
    int x = (dmd.width() - dmd.stringWidth(bigMsg)) / 2;
    dmd.drawStringX(x, textCenterY(), bigMsg, palette[colorIdx % 6]);
  }
  showFrame();
  colorIdx++;
  if (colorIdx >= 7) {
    nextScene();
  }
}

static int16_t scrollHStartX(const char* msg, int8_t step) {
  int16_t w = dmd.stringWidth(msg);
  if (step < 0) {
    return dmd.width() - w;
  }
  return -w;
}

static void runScrollH() {
  static const char* msgs[] = {
    ">>> RIGHT >>>",
    "<<< LEFT  <<<",
    "== FAST ==",
    "DMD_STM32"
  };
  static int16_t scrollX = 0;
  static const uint32_t MSG_MS = 3000;

  if (phase == 0) {
    showSceneName("scroll H (GlametrixBold9)");
    selectFont(&FontSmall);
    stepIdx = 0;
    colorIdx = 0;
    scrollX = scrollHStartX(msgs[0], hSteps[0]);
    phase = 1;
    lastTick = millis() - SCROLL_MS;
    sceneStart = millis();
    dmd.clearScreen(true);
    prepMarquee(palette[colorIdx]);
    dmd.drawMarqueeX(msgs[0], scrollX, scrollTextY());
    showFrame(false);
    return;
  }

  uint8_t msgIdx = (uint8_t)(((millis() - sceneStart) / MSG_MS) % 4);
  if (msgIdx != stepIdx) {
    stepIdx = msgIdx;
    colorIdx = stepIdx % 6;
    scrollX = scrollHStartX(msgs[stepIdx], hSteps[stepIdx]);
    lastTick = millis() - SCROLL_MS;
  }

  if (millis() - lastTick < SCROLL_MS) return;
  lastTick = millis();

  const char* msg = msgs[stepIdx];
  int8_t step = hSteps[stepIdx];
  int16_t msgW = dmd.stringWidth(msg);

  scrollX += step;

  if (step > 0 && scrollX > dmd.width()) {
    scrollX = -msgW;
  } else if (step < 0 && scrollX + msgW <= 0) {
    scrollX = dmd.width() - msgW;
  }

  dmd.clearScreen(true);
  prepMarquee(palette[colorIdx]);
  dmd.drawMarqueeX(msg, scrollX, scrollTextY());
  showFrame(false);

  if (millis() - sceneStart >= SCROLL_SCENE_MS) {
    nextScene();
  }
}

static void runBrightness() {
  const char* msg = "BRIGHT";

  if (phase == 0) {
    showSceneName("brightness");
    selectFont(&FontSmall);
    dmd.setTextColor(colWhite, COL_BLACK);
    int x = (dmd.width() - dmd.stringWidth(msg)) / 2;
    dmd.drawStringX(x, textCenterY(), msg, colWhite);
    showFrame();
    brightnessVal = 40;
    phase = 1;
    lastTick = millis();
  }

  if (millis() - lastTick < 30) return;
  lastTick = millis();

  if (phase == 1) {
    brightnessVal += 4;
    dmd.setBrightness(brightnessVal);
    if (brightnessVal >= 250) phase = 2;
  } else {
    brightnessVal -= 4;
    dmd.setBrightness(brightnessVal);
    if (brightnessVal <= 40) nextScene();
  }
}

static void runScrollV() {
  static const char* msg = "UP/DOWN";

  if (phase == 0) {
    showSceneName("scroll V (GlametrixBold9)");
    selectFont(&FontSmall);
    stepIdx = 0;
    colorIdx = 0;
    prepMarquee(colCyan);
    dmd.fillScreen(COL_BLACK);
    dmd.drawMarqueeX(msg, 2, 0);
    showFrame();
    phase = 1;
    lastTick = millis();
    sceneStart = millis();
    return;
  }

  if (millis() - lastTick < SCROLL_MS) return;
  lastTick = millis();

  if (dmd.stepMarquee(0, vSteps[stepIdx]) & 1) {
    colorIdx = (colorIdx + 1) % 6;
    prepMarquee(palette[colorIdx]);
    stepIdx = (stepIdx + 1) % 4;
    if (vSteps[stepIdx] < 0) {
      dmd.drawMarqueeX(msg, 2, dmd.height());
    } else {
      dmd.drawMarqueeX(msg, 2, 0);
    }
  }
  showFrame();

  if (millis() - sceneStart >= SCROLL_SCENE_MS) {
    nextScene();
  }
}

static void runVScrollGlyph() {
  static char rusBuf[32];

  if (phase == 0) {
    showSceneName("scroll RU (GlametrixBold9)");
    selectFont(&FontSmall);
    utf8_rus(rusBuf, (const unsigned char*)rusPrivet);
    dmd.fillScreen(COL_BLACK);
    int x = (dmd.width() - dmd.stringWidth(rusBuf)) / 2;
    drawRusMarquee(rusBuf, x, textCenterY(), colYellow);
    showFrame();
    phase = 1;
    lastTick = millis();
    sceneStart = millis();
    return;
  }

  if (phase == 1) {
    if (millis() - sceneStart < 2500) return;
    prepMarquee(colGreen);
    dmd.fillScreen(COL_BLACK);
    dmd.setTextColor(colGreen, COL_BLACK);
    dmd.drawMarqueeX(rusBuf, -dmd.stringWidth(rusBuf), scrollTextY());
    showFrame();
    phase = 2;
    lastTick = millis();
    sceneStart = millis();
    return;
  }

  if (millis() - lastTick < SCROLL_MS) return;
  lastTick = millis();

  dmd.stepMarquee(1, 0);
  showFrame();

  if (millis() - sceneStart >= SCROLL_SCENE_MS) {
    nextScene();
  }
}

static void runMulticolor() {
  static const char scrollMsg[] = "RGB TEST";
  static const char fixedMsg[] = "2026";
  static uint16_t mcColors[4];
  static DMD_Colorlist multi(4, mcColors);

  if (phase == 0) {
    showSceneName("multicolor");
    selectFont(&FontSmall);
    mcColors[0] = COL_BLACK;
    mcColors[1] = colRed;
    mcColors[2] = colGreen;
    mcColors[3] = colBlue;
    dmd.setMarqueeColor(&multi);
    dmd.fillScreen(COL_BLACK);
    dmd.drawMarqueeX(scrollMsg, -dmd.stringWidth(scrollMsg), 0);
    showFrame();
    phase = 1;
    lastTick = millis();
    sceneStart = millis();
    return;
  }

  if (millis() - lastTick < SCROLL_MS) return;
  lastTick = millis();

  dmd.stepMarquee(1, 0);
  int fx = (dmd.width() - dmd.stringWidth(fixedMsg)) / 2;
  dmd.drawStringX(fx, dmd.height() - activeFont->get_height(), fixedMsg, colYellow);
  showFrame();

  if (millis() - sceneStart > 6000) {
    prepMarquee(colWhite);
    nextScene();
  }
}

static void runColorWipe() {
  if (phase == 0) {
    showSceneName("color wipe");
    colorIdx = 0;
    phase = 1;
    lastTick = millis();
  }

  if (millis() - lastTick < 350) return;
  lastTick = millis();

  dmd.fillScreen(palette[colorIdx]);
  showFrame();
  colorIdx++;
  if (colorIdx >= 6) {
    dmd.fillScreen(COL_BLACK);
    showFrame();
    nextScene();
  }
}

static void runPixels() {
  static char rusBuf[24];
  static bool rusReady = false;
  static int px = 0;
  static int py = 0;

  if (phase == 0) {
    showSceneName("pixels + cyr");
    if (!rusReady) {
      utf8_rus(rusBuf, (const unsigned char*)rusPrivet);
      rusReady = true;
    }
    dmd.fillScreen(COL_BLACK);
    px = 0;
    py = 0;
    phase = 1;
    lastTick = millis();
  }

  if (phase == 1) {
    if (millis() - lastTick < 6) return;
    lastTick = millis();

    dmd.drawPixel(px, py, palette[(px + py) % 6]);
    if ((px & 7) == 7) {
      showFrame();
    }
    px++;
    if (px >= dmd.width()) {
      px = 0;
      py++;
    }
    if (py >= dmd.height()) {
      phase = 2;
      dmd.fillScreen(COL_BLACK);
      selectFont(&FontSmall);
      int x = (dmd.width() - dmd.stringWidth(rusBuf)) / 2;
      drawRusMarquee(rusBuf, x, textCenterY(), colGreen);
      showFrame();
      sceneStart = millis();
    }
    return;
  }

  if (millis() - sceneStart > 2500) {
    rusReady = false;
    nextScene();
  }
}

void setup() {
  pinMode(BLUE_LED_PIN, OUTPUT);
  digitalWrite(BLUE_LED_PIN, HIGH);

  Serial.begin(115200);
  Serial.println(F("DMD RGB effects demo"));

  matrixPinsSafeBeforeInit();
  dmd.init();
  initColors();
  dmd.setBrightness(BRIGHTNESS);
  beginScene(SCENE_TITLE);
  Serial.println(F("ready"));
}

void loop() {
  switch (scene) {
    case SCENE_TITLE:        runTitle();        break;
    case SCENE_FONT_SHOW:    runFontShow();     break;
    case SCENE_SCROLL_H:     runScrollH();      break;
    case SCENE_BRIGHTNESS:   runBrightness();   break;
    case SCENE_SCROLL_V:     runScrollV();      break;
    case SCENE_VSCROLL_GLYPH: runVScrollGlyph(); break;
    case SCENE_MULTICOLOR:   runMulticolor();   break;
    case SCENE_COLOR_WIPE:   runColorWipe();    break;
    case SCENE_PIXELS:       runPixels();       break;
    default:                 beginScene(0);     break;
  }

  static uint32_t ledTick = 0;
  if (millis() - ledTick >= 500) {
    ledTick = millis();
    digitalWrite(BLUE_LED_PIN, !digitalRead(BLUE_LED_PIN));
  }
}
