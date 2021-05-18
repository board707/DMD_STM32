#pragma once

/*--------------------------------------------------------------------------------------
 DMD_STM32a.h  - advansed version of DMD_STM32.h

 ****** VERSION 0.5.0 ******

 DMD_STM32.h  - STM32 port of DMD.h library 
 
 adapted by Dmitry Dmitriev (c) 2019
 
 
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
#ifndef DMD_STM32a_H_
#define DMD_STM32a_H_
#include "stm_int.h"
//#define DEBUG2		1

//Arduino toolchain header, version dependent
 #if defined(ARDUINO) && ARDUINO >= 100
	 #include "Arduino.h"
 #else
	#include "WProgram.h"
 #endif



#include "Adafruit_GFX.h"
#include "DMD_Font.h"


#if defined(__AVR__)
typedef uint8_t  PortType;
#elif defined(__STM32F1__)
typedef uint32_t PortType; 
#endif

//Pixel/graphics writing modes (bGraphicsMode)
#define GRAPHICS_NORMAL    1
#define GRAPHICS_INVERSE   0
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
//#define DMD_PIXELS_ACROSS         32      //pixels across x axis 
//#define DMD_PIXELS_DOWN           16      //pixels down y axis
#define DMD_BITSPERPIXEL           1       // used for Monochrome panels only
#define DMD_MONO_SCAN              4

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
class DMD : public Adafruit_GFX
{
  public:
    //Instantiate the DMD
    
	DMD(byte _pin_A, byte _pin_B, byte _pin_nOE, byte _pin_SCLK, byte panelsWide, byte panelsHigh, 
		bool d_buf = false, byte dmd_pixel_x =32, byte dmd_pixel_y =16);
	
	virtual ~DMD();

	virtual void init(uint16_t scan_interval = 2000);

 //Set or clear a pixel at the x and y location (0,0 is the top left corner)
  //void writePixel(int16_t x, int16_t y, uint16_t color);
  virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;
  //Draw a string
  void drawString( int bX, int bY, const char* bChars, int length, uint16_t color,  byte orientation =0);
  void drawStringX( int bX, int bY, const char* bChars, uint16_t color,  byte orientation =0);

  //Select a text font
  void selectFont(DMD_Font * font);

  //Draw a single character
  int drawChar(const int bX, const int bY, const unsigned char letter, uint16_t color, byte orientation =0);
 
  //Draw a single character vertically 
  int drawCharV(const int bX, const int bY, const unsigned char letter, uint16_t color );

  //Find the width of a character
  int charWidth(const unsigned char letter,  byte orientation =0);

  //Draw a scrolling string
  void drawMarquee(const char* bChars, int length, int left, int top,  byte orientation =0);
  void drawMarqueeX(const char* bChars, int left, int top,  byte orientation =0);

  //Move the maquee accross by amount
  uint8_t  stepMarquee( int amountX, int amountY,  byte orientation =0);

  //Clear the screen in DMD RAM
  virtual void clearScreen( byte bNormal );
  virtual void fillScreen(uint16_t color);
  virtual void shiftScreen(int8_t step) =0;

 //Draw or clear a filled box(rectangle) with a single pixel border
  void drawFilledBox( int x1, int y1, int x2, int y2, uint16_t color );

  //ADD from DMD2 library, set brightness of panel
  inline void setBrightness(uint8_t level) { 
   this->brightness = map(level, 0, 255, 0, brightrange); };
  
  // Inverse all data on display - for p10 matrix inversed by design
  inline void inverseAll(uint8_t flag) { this->inverse_ALL_flag = flag; };
  
  
  // return string width in pixels
  uint16_t stringWidth(const char* bChars, uint8_t length = 0, byte orientation = 0);
  uint16_t stringWidthV(const char* bChars, uint8_t length = 0)
  {
	  return stringWidth(bChars, length, 1);
  } 
  void dumpDDbuf(void);
  void swapBuffers(boolean copy);
protected:
	// pins
	byte pin_DMD_nOE;   // active low Output Enable, setting this low lights all the LEDs in the selected rows. Can pwm it at very high frequency for brightness control.
	byte pin_DMD_A;
	byte pin_DMD_B;

	byte pin_DMD_SCLK;  // LATCH PORT
	
	// Pin bitmasks
	PortType latmask, oemask, addramask, addrbmask, addrcmask, addrdmask, addremask, mux_clrmask;
	// PORT register pointers 
	volatile PortType* latport, * oeport, * addraport, * addrbport;
	// * addrcport, * addrdport;

	uint16_t brightness = 100;
	uint16_t brightrange = 255;

	//Mirror of DMD pixels in RAM, ready to be clocked out by the main loop or high speed timer calls
	uint8_t *bDMDScreenRAM;
	bool  dbuf = false;
	uint8_t* matrixbuff[2];
	volatile uint8_t backindex = 0;
	volatile boolean swapflag;
	volatile uint8_t* front_buff;
	//DMD I/O pin macros
	virtual void switch_row();
	
	void OE_DMD_ROWS_OFF();
	void OE_DMD_ROWS_ON();


	//Marquee values
	char marqueeText[MAX_STRING_LEN];
	int marqueeLength;
	int marqueeWidth;
	int marqueeHeight;
	int marqueeOffsetX;
	int marqueeOffsetY;

	//Pointer to current font
	DMD_Font* Font;

	//Display information
	byte DisplaysWide;
	byte DisplaysHigh;
	byte DisplaysTotal;
	uint8_t DMD_PIXELS_ACROSS;
	uint8_t DMD_PIXELS_DOWN;
	uint16_t mem_Buffer_Size;

	//scanning pointer into bDMDScreenRAM, setup init @ 48 for the first valid scan
	volatile byte bDMDByte;

	
	uint8_t inverse_ALL_flag = PANEL_INVERSE;
	//uint16_t fg_color = 1;
	//uint16_t bg_color = 0;
	
	uint8_t graph_mode = GRAPHICS_NORMAL;
	void set_graph_mode(uint8_t gm = GRAPHICS_NORMAL) {
		graph_mode = gm;
	}
	uint16_t inverse_color(uint16_t col) {
		if (col == textcolor) return textbgcolor; else return textcolor;

	}
#if defined(DEBUG2)
	
	volatile uint16_t *dd_ptr;
	volatile uint8_t dd_cnt = 0;
#endif	
  private:
    
};



#endif /* DMD_H_ */
