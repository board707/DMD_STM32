/*--------------------------------------------------------------------------------------
 Demo for RGB panels

 DMD_STM32a example code for STM32 and RP2040 boards

 Pattern test for 32x16 1/2 1/4 RGB panels
 ------------------------------------------------------------------------------------- */
 #include "DMD_RGB.h"

//Number of panels in x and y axis
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1

// Output buffering - false
#define ENABLE_DUAL_BUFFER false

/* =================== *
*     STM32F4 pins     *
*  =================== */
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

/* =================== *
*     RP2040 pins     *
*  =================== */
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
uint8_t custom_rgbpins[] = { 11, 0,1,2,3,4,5 }; // CLK, R0, G0, B0, R1, G1, B1
#endif

// Fire up the DMD object as dmd<MATRIX_TYPE, COLOR_DEPTH>

// For pattern testing use one of matrix below:
// RGB32x16plainS4         - 32x16 1/4 Binary mux
// RGB32x16plainS4_DIRECT  - 32x16 1/4 Direct mux
// RGB32x16plainS2         - 32x16 1/2 Binary mux
// RGB32x16plainS2_DIRECT  - 32x16 1/2 Direct mux

DMD_RGB <RGB32x16plainS4, COLOR_4BITS> dmd(mux_list, DMD_PIN_nOE, DMD_PIN_SCLK, custom_rgbpins, DISPLAYS_ACROSS, DISPLAYS_DOWN, ENABLE_DUAL_BUFFER);

uint16_t bg = 0;  // background - black
uint16_t fg = 0;  // foreground

void setup(void)
{
    dmd.init();
    fg = dmd.Color888(0, 0, 255);
    dmd.setBrightness(50);
}

void loop(void) {
    // fill the matrix with points row by row
    for (int i = 0; i < dmd.height(); i++) {
        for (int j = 0; j < dmd.width(); j++) {
            dmd.drawPixel(j,i, fg);
            delay(30);
        }
    }
    // clear the screen
    dmd.fillScreen(bg);
}
