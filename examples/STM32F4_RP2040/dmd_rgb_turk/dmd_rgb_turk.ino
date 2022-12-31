/*--------------------------------------------------------------------------------------
 Demo for RGB panels

 DMD_STM32a example code for STM32F4 and RP2040 boards
 
 Using Turkish fonts
 Turkish font and conversuin 
 by HakkanR https://github.com/HakkanR/DMD2TUR
 ------------------------------------------------------------------------------------- */
#include "DMD_RGB.h"

 // Fonts includes
#include "st_fonts/Arial_Black_16TR.h"
#pragma GCC diagnostic ignored "-Wnarrowing"
#pragma GCC diagnostic ignored "-Woverflow"
#include "gfx_fonts/GlametrixLight12pt7b.h"
#include "gfx_fonts/GlametrixBold12pt7b.h"
#pragma GCC diagnostic warning "-Wnarrowing"
#pragma GCC diagnostic warning "-Woverflow" 

//Number of panels in x and y axis
#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 1

// Enable of output buffering
// if true, changes only outputs to matrix after
// swapBuffers(true) command
// If dual buffer not enabled, all output draw at matrix directly
// and swapBuffers(true) cimmand do nothing
#define ENABLE_DUAL_BUFFER false

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
uint8_t custom_rgbpins[] = {PA6, PA0,PA1,PA2,PA3,PA4,PA5 }; // CLK, R0, G0, B0, R1, G1, B1

#elif (defined(ARDUINO_ARCH_RP2040))

// ==== DMD_RGB pins ====
// mux pins - A, B, C... all mux pins must be selected from same port!
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
// All this pins also must be selected from same port!
uint8_t custom_rgbpins[] = { 11, 0,1,2,3,4,5 }; // CLK, R0, G0, B0, R1, G1, B1
#endif
// Fire up the DMD object as dmd<MATRIX_TYPE, COLOR_DEPTH>
// We use 64x32 matrix with 16 scans and 4bit color:
DMD_RGB <RGB64x32plainS16, COLOR_4BITS> dmd(mux_list, DMD_PIN_nOE, DMD_PIN_SCLK, custom_rgbpins, DISPLAYS_ACROSS, DISPLAYS_DOWN, ENABLE_DUAL_BUFFER);
// other options are:
// <RGB32x16plainS8> -  32x16 matrix with 8scans
// <RGB80x40plainS20> - 80x40 matrix with 20scans
// <RGB64x64plainS32> - 64x64 matrix with 32scans
// Color depth - <COLOR_4BITS> or <COLOR_1BITS>


// --- Define fonts ----
// Turkish standard font
DMD_Standard_Font Turk_Arial_F(Arial_Black_16TR);
// GFX font with sepatate parts for Latin and Cyrillic chars
DMD_GFX_Font GlametrixL((uint8_t*)&GlametrixLight12pt7b, (uint8_t*)&GlametrixLight12pt8b_rus, 0x80, 13);


/*--------------------------------------------------------------------------------------
  UTF8 Turkish char recoding
  Conversion code by HakkanR https://github.com/HakkanR/DMD2TUR
--------------------------------------------------------------------------------------*/

#define RESET_FS    {f195 = f196 = f197 = 0;sent = 1;}


char recode(uint8_t character)
{
    static uint8_t f195 = 0;
    static uint8_t f196 = 0;
    static uint8_t f197 = 0;
    static bool sent = true;
    if (character == 195)
    {
        f195 = 1;
        sent = 0;
        return 1;
    }
    if (character == 196)
    {
        f196 = 1;
        sent = 0;
        return 1;
    }
    if (character == 197)
    {
        f197 = 1;
        sent = 0;
        return 1;
    }
    if (f196 == 1)
    {
        RESET_FS;
        if (character == 177) // ı
            character = 0x1F;
        else if (character == 176) // İ
            character = 0x1E;
        else if (character == 158) // Ğ
            character = 0x1D;
        else if (character == 159) // ğ
            character = 0x1C;
    }

    if (f195 == 1)
    {
        RESET_FS;
        if (character == 182) // ö
            character = 0x1b;
        else if (character == 150) // Ö
            character = 0x1a;
        else if (character == 156) // Ü
            character = 0x19;
        else if (character == 188) // ü
            character = 0x18;
        else if (character == 135) // Ç
            character = 0x17;
        else if (character == 167) // ç
            character = 0x16;
    }
    if (f197 == 1)
    {
        RESET_FS;
        if (character == 158) // Ş
            character = 0x15;
        else if (character == 159) // ş
            character = 0x14;
    }

    if (sent)
        return character;
    return 1;
}

int utf8_turk(char* dest, char* src) {
    int cnt = 0;
    while (*src != 0) {
        char new_char = recode(*src);
        if (new_char != 1) { *dest = new_char; dest++; cnt++; }
        src++;
    }
    *dest = 0;
    return cnt;
}
/*--------------------------------------------------------------------------------------
  UTF8 cyrillic char recoding

--------------------------------------------------------------------------------------*/
int utf8_rus(char* dest, const unsigned char* src) {

    uint16_t i, j;
    for (i = 0, j = 0; src[i]; i++) {
        if ((src[i] == 0xD0) && src[i + 1]) { dest[j++] = src[++i] - 0x10; }
        else if ((src[i] == 0xD1) && src[i + 1]) { dest[j++] = src[++i] + 0x30; }
        else dest[j++] = src[i];
    }
    dest[j] = '\0';
    return j;
}
/*--------------------------------------------------------------------------------------
  setup
  Called by the Arduino architecture before the main loop begins
--------------------------------------------------------------------------------------*/

void setup(void)
{

    // initialize DMD objects
	dmd.init(); 
    
}


/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
--------------------------------------------------------------------------------------*/

void loop(void)
{

    // create foreground colors
    uint16_t col[] = {
        dmd.Color888(255,0, 0), // red
        dmd.Color888(0, 255, 0), // green
        dmd.Color888(0, 0, 255)  // blue

    };
    uint16_t bg = 0;  // background - black
    int col_cnt = 3;   // color count

   // text
    char s[] = "Привет Ардуино!";

    // Turkish text 
    char t[] = "Küçük ördek ve büyük baykuş";  //"Small duck and big owl"
    // transcode message to UTF for use with GFX fonts
    char k[30];
    char kt[35];
    utf8_rus(k, (const unsigned char*)s);
    utf8_turk(kt, t);
    char* m = kt;
    // select standard font
    dmd.selectFont(&Turk_Arial_F);

    // set text foreground and background colors
    dmd.setTextColor(col[0], bg);

    // shift steps in pixels for running text (positive - shift right, negative - left)
    int8_t step[] = { 1,-1,-2,2 };
    // running text shift interval
    uint16_t interval = 20;

    long prev_step = millis();
    uint8_t col_ptr = 0;
    uint8_t i = 0, b = 0;
    uint8_t test = 255;
    uint8_t test_cnt = 4;
    dmd.setBrightness(100);

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
