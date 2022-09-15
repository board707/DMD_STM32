/*--------------------------------------------------------------------------------------
 Demo for RGB panels

 DMD_STM32a example code for STM32F103xxx board

 Draw bitmap example.
 ------------------------------------------------------------------------------------- */
#include "DMD_RGB.h"
#include "bitmaps.h"

//Number of panels in x and y axis
#define DISPLAYS_ACROSS 1
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
DMD_RGB <RGB64x32plainS16,COLOR_4BITS> dmd(mux_list, DMD_PIN_nOE, DMD_PIN_SCLK, custom_rgbpins, DISPLAYS_ACROSS, DISPLAYS_DOWN, ENABLE_DUAL_BUFFER);
// other options are:
// <RGB32x16plainS8> -  32x16 matrix with 8scans
// <RGB80x40plainS20> - 80x40 matrix with 20scans
// <RGB64x64plainS32> - 64x64 matrix with 32scans
// Color depth - <COLOR_4BITS> or <COLOR_1BITS>

#define BRIGHTNESS_DEFAULT 50  // (brightness 0-255, recomended 30-100)

// bitmap images to show
const uint16_t* bitmaps[] = {evening_64_32, vyshivka_64_32};
uint8_t ptr = 0;
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
  if (ptr == (sizeof(bitmaps)/ sizeof(bitmaps[0]))) ptr =0;
  
  // initial brightness
  uint8_t b=BRIGHTNESS_DEFAULT;      
  dmd.setBrightness(b);
  
  // draw image starting from 0,0, width 64 height 32
  dmd.drawRGBBitmap(dmd.width() - 64, 0, bitmaps[ptr], 64, 32);
  
  // show the image during 15sec
  delay(15000);
  
  // fading to dark
  while (b) {
    dmd.setBrightness(b);
    delay(100);
    b--;
  }

  // blank screen 2sec
  dmd.clearScreen(true);
  delay(2000);

  // increment image pointer
  ptr++;
}

