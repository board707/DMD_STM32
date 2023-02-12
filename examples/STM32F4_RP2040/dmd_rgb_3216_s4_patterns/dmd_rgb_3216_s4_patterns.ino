/*--------------------------------------------------------------------------------------
  Demo for RGB panels

  DMD_STM32a example code for STM32 and RP2040 boards
  ------------------------------------------------------------------------------------- */
#include "DMD_RGB.h"

/* Pattern types for 32x16 s4 panels.
  
  This example demonstrates the construction of a pattern based on three simple features.  
  See detailed explanation on the thread:
  https://community.pixelmatix.com/t/coordinate-transformations-for-4scan-panels/1236
  
  Pattern name contructed with 3 letters:
  U/L - ether the first oktet (8 pixs) is lighten Upper than second or vise versa
  P/N - ether the first octet goes to Positive X direction ( left to right) or Negative
  S/D - ether the second octet goes to the Same direction as first or not

  example Lower, Positive, Different  - select the PATTERN_LPD
*/

#define PATTERN_UPS   0b0111
#define PATTERN_UPD   0b0110
#define PATTERN_UNS   0b0101
#define PATTERN_UND   0b0100
#define PATTERN_LPS   0b0011
#define PATTERN_LPD   0b0010
#define PATTERN_LNS   0b0001
#define PATTERN_LND   0b0000

// Only 32x16 s4 panels are supported with this example
#define RGB32x16_S4_BIN   2,32,16,4,32  // 32x16 1/4 Binary mux variable pattern 
#define RGB32x16_S4_DIR   4,32,16,4,32  // 32x16 1/4 Direct mux variable pattern

//====Select panel type here====
#define PANEL_TYPE RGB32x16_S4_BIN

//====Select correct pattern to your panel here====
#define PANEL_PATTERN_TYPE PATTERN_LPD

// variable pattern template
template<int MUX_CNT, int COL_DEPTH >
class DMD_RGB<MUX_CNT, 32, 16, 4, 32, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
  public:
    DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
            byte panelsWide, byte panelsHigh, bool d_buf = false) :
      DMD_RGB_BASE2<COL_DEPTH>(2, mux_list, _pin_nOE, _pin_SCLK, pinlist,
                               panelsWide, panelsHigh, d_buf, COL_DEPTH, 4, 32, 16)
    {
      this->fast_Hbyte = false;
      this->use_shift = false;
    }
    // Fast text shift is disabled for complex patterns, so we don't need the method
    void disableFastTextShift(bool shift) override {}

  protected:
    uint16_t get_base_addr(int16_t x, int16_t y) override {
      this->transform_XY(x, y);
      uint8_t pol_y = y % this->pol_displ;
      x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;

      static const bool Upper = (PANEL_PATTERN_TYPE & 0xf) & 0b0100;
      static const bool Pos =   (PANEL_PATTERN_TYPE & 0xf) & 0b0010;
      static const bool Same =  (PANEL_PATTERN_TYPE & 0xf) & 0b0001;

      bool B = (((pol_y < this->nRows) ^ Upper));
      uint16_t base_addr = (pol_y % this->nRows) * this->x_len + (x / 8) * this->multiplex * 8;
      if (B) // B=1
      {
        if (!(Pos ^ Same)) base_addr += 8 + x % 8;
        else base_addr += (15 - x % 8);
      }
      else
      {
        if (Pos) base_addr += x % 8;
        else base_addr += (7 - x % 8);
      }

      return base_addr;
    }

};
// Fonts includes
#include "st_fonts/UkrRusArial14.h"
#pragma GCC diagnostic ignored "-Wnarrowing"
#pragma GCC diagnostic ignored "-Woverflow"
#include "gfx_fonts/GlametrixLight12pt7b.h"
#include "gfx_fonts/GlametrixBold12pt7b.h"
#pragma GCC diagnostic warning "-Wnarrowing"
#pragma GCC diagnostic warning "-Woverflow"

//Number of panels in x and y axis
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1

// Enable of output buffering
// if true, changes only outputs to matrix after
// swapBuffers(true) command
// If dual buffer not enabled, all output draw at matrix directly
// and swapBuffers(true) cimmand do nothing
#define ENABLE_DUAL_BUFFER false
/* =================== *
      STM32F4 pins
   =================== */
#if (defined(__STM32F1__) || defined(__STM32F4__))
// ==== DMD_RGB pins ====
// mux pins - A, B, C... all mux pins must be selected from same port!
#define DMD_PIN_A PB6
#define DMD_PIN_B PB5
#define DMD_PIN_C PB4
#define DMD_PIN_D PB3
#define DMD_PIN_E PB8
// put all mux pins at list
uint8_t mux_list[] = { DMD_PIN_A , DMD_PIN_B , DMD_PIN_C , DMD_PIN_D , DMD_PIN_E };

// pin OE must be one of PB0 PB1 PA6 PA7
#define DMD_PIN_nOE PB0
#define DMD_PIN_SCLK PB7

// Pins for R0, G0, B0, R1, G1, B1 channels and for clock.
// By default the library uses RGB color order.
// If you need to change this - reorder the R0, G0, B0, R1, G1, B1 pins.
// All this pins also must be selected from same port!
uint8_t custom_rgbpins[] = {PA6, PA0, PA1, PA2, PA3, PA4, PA5 }; // CLK, R0, G0, B0, R1, G1, B1

/* =================== *
      RP2040 pins
   =================== */
#elif (defined(ARDUINO_ARCH_RP2040))
// ==== DMD_RGB pins ====
// mux pins - A, B, C... mux pins must be consecutive in ascending order
#define DMD_PIN_A 6
#define DMD_PIN_B 7
#define DMD_PIN_C 8
#define DMD_PIN_D 9
#define DMD_PIN_E 10
// put all mux pins at list
uint8_t mux_list[] = { DMD_PIN_A , DMD_PIN_B , DMD_PIN_C , DMD_PIN_D , DMD_PIN_E };

// pin OE must be one of PB0 PB1 PA6 PA7
#define DMD_PIN_nOE 15
#define DMD_PIN_SCLK 12

// Pins for R0, G0, B0, R1, G1, B1 channels and for clock.
// By default the library uses RGB color order.2
// If you need to change this - reorder the R0, G0, B0, R1, G1, B1 pins.
// All this pins also must be consecutive in ascending order
uint8_t custom_rgbpins[] = { 11, 0, 1, 2, 3, 4, 5 }; // CLK, R0, G0, B0, R1, G1, B1
#endif
// Fire up the DMD object as dmd<MATRIX_TYPE, COLOR_DEPTH>
// We test 32x16 1/4 binary mux matrix :
DMD_RGB <PANEL_TYPE, COLOR_4BITS> dmd(mux_list, DMD_PIN_nOE, DMD_PIN_SCLK, custom_rgbpins, DISPLAYS_ACROSS, DISPLAYS_DOWN, ENABLE_DUAL_BUFFER);
// panel options are:
// <RGB32x16_S4_BIN> -  32x16 1/4 binary mux matrix
// <RGB32x16_S4_DIR> -  32x16 1/4 direct mux matrix
// Color depth - <COLOR_4BITS_Packed>(STM32 only), <COLOR_4BITS> or <COLOR_1BITS>


// --- Define fonts ----
// DMD.h old style font
DMD_Standard_Font UkrRusArial_F(UkrRusArial_14);
// GFX font with sepatate parts for Latin and Cyrillic chars
DMD_GFX_Font GlametrixL((uint8_t*)&GlametrixLight12pt7b, (uint8_t*)&GlametrixLight12pt8b_rus, 0x80, 13);


/*--------------------------------------------------------------------------------------
  UTF8 char recoding

  --------------------------------------------------------------------------------------*/
int utf8_rus(char* dest, const unsigned char* src) {

  uint16_t i, j;
  for (i = 0, j = 0; src[i]; i++) {
    if ((src[i] == 0xD0) && src[i + 1]) {
      dest[j++] = src[++i] - 0x10;
    }
    else if ((src[i] == 0xD1) && src[i + 1]) {
      dest[j++] = src[++i] + 0x30;
    }
    else dest[j++] = src[i];
  }
  dest[j] = '\0';
  return j;
}

/*--------------------------------------------------------------------------------------
  setup
  Called by the Arduino architecture before the main loop begins
  --------------------------------------------------------------------------------------*/
uint16_t bg = 0;  // background - black
uint16_t fg = 0;  // foreground 
void setup(void)
{
  // initialize DMD objects
  dmd.init();
  dmd.setBrightness(80);
  fg = dmd.Color888(0, 0, 255); 
  // fill the matrix with points row by row
  for (int i = 0; i < dmd.height(); i++) {
    for (int j = 0; j < dmd.width(); j++) {
      dmd.drawPixel(j, i, fg);
      delay(30);
    }
  }
  // clear the screen
  dmd.fillScreen(bg);
}


/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
  --------------------------------------------------------------------------------------*/

void loop(void)
{

  // create foreground colors
  uint16_t col[] = {
    dmd.Color888(255, 0, 0), // red
    dmd.Color888(0, 255, 0), // green
    dmd.Color888(0, 0, 255)  // blue

  };
  uint16_t bg = 0;  // background - black
  int col_cnt = 3;   // color count

  // text
  char s[] = "Привет Ардуино!";
  // transcode message to UTF for use with GFX fonts
  char k[30];

  utf8_rus(k, (const unsigned char*)s);
  char* m = s;
  // select standard font
  dmd.selectFont(&UkrRusArial_F);

  // set text foreground and background colors
  dmd.setTextColor(col[0], bg);

  // shift steps in pixels for running text (positive - shift right, negative - left)
  int8_t step[] = { 1, -1, -2, 2 };
  // running text shift interval
  uint16_t interval = 30;

  long prev_step = millis();
  uint8_t col_ptr = 0;
  uint8_t i = 0, b = 0;
  uint8_t test = 255;
  uint8_t test_cnt = 4;
  dmd.setBrightness(200);

  // Cycle for tests:
  // -- running texts moving at x and y axis with single and double speed
  // -- vertical scrolling message
  while (1) {
    if ((millis() - prev_step) > interval) {
      if (test >= test_cnt) {
        test = 0;
        // draw message
        dmd.drawMarqueeX(m, -1 * (dmd.stringWidth(m)), 0);

        dmd.swapBuffers(true);

      }
      switch (test) {
        // moving text at x axis
        case 0:
          if (dmd.stepMarquee(step[i], 0) & 1) { // if text is reached screen bounds

            dmd.clearScreen(true);
            // set next text color
            col_ptr++;
            if (col_ptr >= col_cnt) col_ptr = 0;
            dmd.setTextColor(col[col_ptr], bg);
            // set new text speed
            i++;
            // if all moving finished
            if (i > 3) {
              // go to next stage
              i = 0;
              test++;
              dmd.drawMarqueeX(m, 0, (dmd.height() > 16) ? 8 : 0);
            }
            else {
              if (step[i] < 0) dmd.drawMarqueeX(m, dmd.width() - 1, 0);
              else dmd.drawMarqueeX(m, -1 * dmd.stringWidth(m), 0);
            }
          }
          else {

            if (step[i] != 1) dmd.drawFilledBox(0, 0, 5, dmd.height() - 1, GRAPHICS_INVERSE);
          }
          // output mem buffer to matrix
          dmd.swapBuffers(true);
          break;
        case 1:
          b++;
          dmd.setBrightness(b);
          if (b > 250) {
            test++;
            b = 80;
            i = 0;
            dmd.setBrightness(b);
            dmd.drawMarqueeX(m, 0, 0);
          }
          dmd.swapBuffers(true);
          break;
        // moving text at y axis
        case 2:
          if (dmd.stepMarquee(0, step[i]) & 1) {  // if text is reached screen bounds

            // clear the screen
            dmd.clearScreen(true);
            // select new moving speed
            i++;
            // if all moving finished
            if (i > 3) {
              // go to next stage
              test++;
              // select GFX font for vertical scroll
              dmd.selectFont(&GlametrixL);
              dmd.drawMarquee(k, strlen(k), dmd.width() - 1,
                              (dmd.height() > 16) ? 8 : 0, 1);

            }
            else {
              if (step[i] < 0) dmd.drawMarqueeX(m, 0, dmd.height());
              else dmd.drawMarqueeX(m, 0, 0);
            }
          }
          // output mem buffer to matrix
          dmd.swapBuffers(true);
          break;

        // vertical scrolling
        case 3:

          dmd.stepMarquee(-1, 0, 1);
          dmd.swapBuffers(true);
          break;

      }

      prev_step = millis();

    }
  }
}

