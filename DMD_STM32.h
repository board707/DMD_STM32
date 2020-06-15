/*--------------------------------------------------------------------------------------

 DMD_STM32.h  - STM32 port of DMD.h library (see below)
 
 adapted by Dmitry Dmitriev (c) 2019
 
 ****** VERSION 0.4.2 ******
 
 DMD.h   - Function and support library for the Freetronics DMD, a 512 LED matrix display
           panel arranged in a 32 x 16 layout.

 Copyright (C) 2011 Marc Alexander (info <at> freetronics <dot> com)

 
 
 This program is free software: you can redistribute it and/or modify it under the terms
 of the version 3 GNU General Public License as published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with this program.
 If not, see <http://www.gnu.org/licenses/>.

--------------------------------------------------------------------------------------*/
#ifndef DMD_STM32_H_
#define DMD_STM32_H_

#define DMD_SPI_CLOCK_18MHZ     18000000
#define DMD_SPI_CLOCK_9MHZ      9000000
#define DMD_SPI_CLOCK_4_5MHZ    4500000
#define DMD_SPI_CLOCK_2_2MHZ    2300000
#define DMD_SPI_CLOCK_1MHZ      1000000


	

//Arduino toolchain header, version dependent
 #if defined(ARDUINO) && ARDUINO >= 100
	 #include "Arduino.h"
 #else
	#include "WProgram.h"
 #endif


#include <SPI.h>
#include "gfxfont.h"
#include "DMD_Font.h"

#if defined(__STM32F1__)
       #define DMD_SPI_CLOCK DMD_SPI_CLOCK_9MHZ
       #define DMD_USE_DMA	1
#elif defined(__AVR_ATmega328P__)
       #define DMD_SPI_CLOCK SPI_CLOCK_DIV4
#endif





//Pixel/graphics writing modes (bGraphicsMode)
#define GRAPHICS_NORMAL    0
#define GRAPHICS_INVERSE   1
#define GRAPHICS_TOGGLE    2
#define GRAPHICS_OR        3
#define GRAPHICS_NOR       4

//Panel inverse mode (for some panels)
#define PANEL_INVERSE 0
	
//Max length of scrolling text
#define MAX_STRING_LEN 300

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
#define DMD_DMA_BUF_SIZE 		 (DMD_RAM_SIZE_BYTES/4)
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
	
	void init(uint16_t scan_interval = 2000);

 //Set or clear a pixel at the x and y location (0,0 is the top left corner)
  void writePixel( unsigned int bX, unsigned int bY, byte bGraphicsMode, byte bPixel );

  //Draw a string
  void drawString( int bX, int bY, const char* bChars, int length, byte bGraphicsMode,  byte orientation =0);
  void drawStringX( int bX, int bY, const char* bChars, byte bGraphicsMode,  byte orientation =0);

  //Select a text font
  void selectFont(DMD_Font * font);

  //Draw a single character
  int drawChar(const int bX, const int bY, const unsigned char letter, byte bGraphicsMode,  byte orientation =0);
  
  //Draw a single character vertically 
  int drawCharV(const int bX, const int bY, const unsigned char letter, byte bGraphicsMode);

  //Find the width of a character
  int charWidth(const unsigned char letter,  byte orientation =0);

  //Draw a scrolling string
  void drawMarquee(const char* bChars, int length, int left, int top,  byte orientation =0);
  void drawMarqueeX(const char* bChars, int left, int top,  byte orientation =0);

  //Move the maquee accross by amount
  boolean stepMarquee( int amountX, int amountY,  byte orientation =0);

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
  
 #if defined(__STM32F1__)
  void scanDisplayByDMA();
  void latchDMA();
 #endif
  
  
  ///Next part is customly added by mozokevgen
  
  //ADD from DMD2 library, set brightness of panel
  inline void setBrightness(uint8_t level) { 
   this->brightness = map(level, 0, 255, 0, brightrange); };
  
  // Inverse all data on display - for p10 matrix inversed by design
  inline void inverseAll(uint8_t flag) { this->inverse_ALL_flag = flag; };
  
  //Draw the image (0,0 is the top left corner)
  void drawImg( const int bX, const int bY, const uint8_t *img, byte length);
  
  //Move the image accross by amount
  boolean stepImg( int amountX, int amountY);
  
  //2 sprites animation
  void animation(const int bX, const int bY, const uint8_t *img1, byte length1, const uint8_t *img2, byte length2, bool beginFlag);

  // return string width in pixels
  uint16_t stringWidth(const char *bChars, uint8_t length);
  
  uint8_t spi_num =0;
  
  
  private:
    // pins
	byte pin_DMD_nOE;   // active low Output Enable, setting this low lights all the LEDs in the selected rows. Can pwm it at very high frequency for brightness control.
    byte pin_DMD_A;   
    byte pin_DMD_B;       
    byte pin_DMD_CLK;    // is SPI Clock if SPI is used
    byte pin_DMD_SCLK;     
    byte pin_DMD_R_DATA ;   // is SPI Master Out if SPI is used
	
	SPIClass SPI_DMD;
    uint16_t brightness=100;
    uint16_t brightrange=255;
	
	void drawCircleSub( int cx, int cy, int x, int y, byte bGraphicsMode );

    //Mirror of DMD pixels in RAM, ready to be clocked out by the main loop or high speed timer calls
    byte *bDMDScreenRAM;
	
#if defined(__STM32F1__)
    dma_channel  spiTxDmaChannel;
	dma_dev* spiDmaDev;
    uint8_t *dmd_dma_buf;
    uint8_t *rx_dma_buf;
#endif
    

	//DMD I/O pin macros
  void LIGHT_DMD_ROW_01_05_09_13();
  void LIGHT_DMD_ROW_02_06_10_14();
  void LIGHT_DMD_ROW_03_07_11_15();
  void LIGHT_DMD_ROW_04_08_12_16() ;
  void LATCH_DMD_SHIFT_REG_TO_OUTPUT();
  void OE_DMD_ROWS_OFF() ;
  void OE_DMD_ROWS_ON() ;


  //Marquee values
    char marqueeText[MAX_STRING_LEN];
    int marqueeLength;
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
    uint8_t inverse_ALL_flag = PANEL_INVERSE;
};

#if defined(__STM32F1__)
    
    static void register_running_dmd(DMD *dmd);

    static void inline __attribute__((always_inline)) scan_running_dmds();

    static void SPI1_DMA_callback();

    static void SPI2_DMA_callback();
#endif



#endif /* DMD_H_ */
