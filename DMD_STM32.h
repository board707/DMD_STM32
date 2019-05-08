/*--------------------------------------------------------------------------------------

 DMD.h   - Function and support library for the Freetronics DMD, a 512 LED matrix display
           panel arranged in a 32 x 16 layout.

 Copyright (C) 2011 Marc Alexander (info <at> freetronics <dot> com)

 Note that the DMD library uses the SPI port for the fastest, low overhead writing to the
 display. Keep an eye on conflicts if there are any other devices running from the same
 SPI port, and that the chip select on those devices is correctly set to be inactive
 when the DMD is being written to.


LED Panel Layout in RAM
                            32 pixels (4 bytes)
        top left  ----------------------------------------
                  |                                      |
         Screen 1 |        512 pixels (64 bytes)         | 16 pixels
                  |                                      |
                  ---------------------------------------- bottom right

 ---
 
 This program is free software: you can redistribute it and/or modify it under the terms
 of the version 3 GNU General Public License as published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with this program.
 If not, see <http://www.gnu.org/licenses/>.

--------------------------------------------------------------------------------------*/
#ifndef DMD_H_
#define DMD_H_

//Arduino toolchain header, version dependent
// #if defined(ARDUINO) && ARDUINO >= 100
	// #include "Arduino.h"
// #else
	#include "WProgram.h"
// #endif


#include <SPI.h>
#include "gfxfont.h"
#include "DMD_Font.h"


#define DMD_SPI_CLOCK SPI_CLOCK_DIV8
//Pixel/graphics writing modes (bGraphicsMode)
#define GRAPHICS_NORMAL    0
#define GRAPHICS_INVERSE   1
#define GRAPHICS_TOGGLE    2
#define GRAPHICS_OR        3
#define GRAPHICS_NOR       4

//drawTestPattern Patterns
#define PATTERN_ALT_0     0
#define PATTERN_ALT_1     1
#define PATTERN_STRIPE_0  2
#define PATTERN_STRIPE_1  3

//display screen (and subscreen) sizing
#define DMD_PIXELS_ACROSS         32      //pixels across x axis (base 2 size expected)
#define DMD_PIXELS_DOWN           16      //pixels down y axis
#define DMD_BITSPERPIXEL           1      //1 bit per pixel, use more bits to allow for pwm screen brightness control
#define DMD_RAM_SIZE_BYTES        ((DMD_PIXELS_ACROSS*DMD_BITSPERPIXEL/8)*DMD_PIXELS_DOWN)
                                  // (32x * 1 / 8) = 4 bytes, * 16y = 64 bytes per screen here.
//lookup table for DMD::writePixel to make the pixel indexing routine faster
static byte bPixelLookupTable[8] =
{
   0x80,   //0, bit 7
   0x40,   //1, bit 6
   0x20,   //2. bit 5
   0x10,   //3, bit 4
   0x08,   //4, bit 3
   0x04,   //5, bit 2
   0x02,   //6, bit 1
   0x01    //7, bit 0
};


typedef uint8_t (*FontCallback)(const uint8_t*);


//The main class of DMD library functions
class DMD
{
  public:
    //Instantiate the DMD
    
	DMD(byte _pin_A, byte _pin_B, byte _pin_nOE, byte _pin_SCLK, byte panelsWide, byte panelsHigh, SPIClass _spi );


	//DMD I/O pin macros
void LIGHT_DMD_ROW_01_05_09_13();
void LIGHT_DMD_ROW_02_06_10_14();
void LIGHT_DMD_ROW_03_07_11_15();
void LIGHT_DMD_ROW_04_08_12_16() ;
void LATCH_DMD_SHIFT_REG_TO_OUTPUT();
void OE_DMD_ROWS_OFF() ;
void OE_DMD_ROWS_ON() ;
	
	
  //Set or clear a pixel at the x and y location (0,0 is the top left corner)
  void writePixel( unsigned int bX, unsigned int bY, byte bGraphicsMode, byte bPixel );

  //Draw a string
  void drawString( int bX, int bY, const char* bChars, byte length, byte bGraphicsMode);

  //Select a text font
  void selectFont(DMD_Font * font);

  //Draw a single character
  int drawChar(const int bX, const int bY, const unsigned char letter, byte bGraphicsMode);

  //Find the width of a character
  int charWidth(const unsigned char letter);

  //Draw a scrolling string
  void drawMarquee(const char* bChars, byte length, int left, int top);

  //Move the maquee accross by amount
  boolean stepMarquee( int amountX, int amountY);

  //Clear the screen in DMD RAM
  void clearScreen( byte bNormal );

  //Draw or clear a line from x1,y1 to x2,y2
  void drawLine( int x1, int y1, int x2, int y2, byte bGraphicsMode );

  //Draw or clear a circle of radius r at x,y centre
  void drawCircle( int xCenter, int yCenter, int radius, byte bGraphicsMode );

  //Draw or clear a box(rectangle) with a single pixel border
  void drawBox( int x1, int y1, int x2, int y2, byte bGraphicsMode );

  //Draw or clear a filled box(rectangle) with a single pixel border
  void drawFilledBox( int x1, int y1, int x2, int y2, byte bGraphicsMode );

  //Draw the selected test pattern
  void drawTestPattern( byte bPattern );

  //Scan the dot matrix LED panel display, from the RAM mirror out to the display hardware.
  //Call 4 times to scan the whole display which is made up of 4 interleaved rows within the 16 total rows.
  //Insert the calls to this function into the main loop for the highest call rate, or from a timer interrupt
  void scanDisplayBySPI();
  
  
  ///Next part is customly added by mozokevgen
  
  //ADD from DMD2 library, set brightness of panel
  inline void setBrightness(uint16_t level) { this->brightness = level; };
  
  //Draw the image (0,0 is the top left corner)
  void drawImg( const int bX, const int bY, const uint8_t *img, byte length);
  
  //Move the image accross by amount
  boolean stepImg( int amountX, int amountY);
  
  //2 sprites animation
  void animation(const int bX, const int bY, const uint8_t *img1, byte length1, const uint8_t *img2, byte length2, bool beginFlag);

  // return string width in pixels
  uint16_t stringWidth(const char *bChars, uint8_t length);
  
  uint16_t brightness=20000;
  
  private:
    // pins
	byte pin_DMD_nOE;   // active low Output Enable, setting this low lights all the LEDs in the selected rows. Can pwm it at very high frequency for brightness control.
    byte pin_DMD_A;   
    byte pin_DMD_B;       
    byte pin_DMD_CLK;    // is SPI Clock if SPI is used
    byte pin_DMD_SCLK;     
    byte pin_DMD_R_DATA ;   // is SPI Master Out if SPI is used
	
	SPIClass SPI_DMD;
	
	void drawCircleSub( int cx, int cy, int x, int y, byte bGraphicsMode );

    //Mirror of DMD pixels in RAM, ready to be clocked out by the main loop or high speed timer calls
    byte *bDMDScreenRAM;

    //Marquee values
    char marqueeText[256];
    byte marqueeLength;
    int marqueeWidth;
    int marqueeHeight;
    int marqueeOffsetX;
    int marqueeOffsetY;

    //Pointer to current font
    //const uint8_t* Font;
    //bool is_gfx_font = false;
	//GFXfont * gfxFont;
    DMD_Font* Font;
	
	
	//Display information
    byte DisplaysWide;
    byte DisplaysHigh;
    byte DisplaysTotal;
    int row1, row2, row3;

    //scanning pointer into bDMDScreenRAM, setup init @ 48 for the first valid scan
    volatile byte bDMDByte;
	
	///Next part is customly added by mozokevgen
	
	
	
	bool spriteFlag = true;
	//uint8_t marqueeImg[64];

};

#endif /* DMD_H_ */
