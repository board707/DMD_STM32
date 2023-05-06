#pragma once

/*--------------------------------------------------------------------------------------
 DMD_STM32a.h  - advansed version of DMD_STM32.h

 ****** VERSION 1.0.5 ******

 DMD_STM32.h  - STM32 port of DMD.h library

 adapted by Dmitry Dmitriev (c) 2019-2023

 =======  based on =========

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
#define DEBUG_PRINT( x )   Serial1.print( #x );Serial1.print(" = ");Serial1.println( x )

//Arduino toolchain header, version dependent
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Adafruit_GFX.h"
#include "DMD_Config.h"
#include "DMD_Font.h"
#if (defined(ARDUINO_ARCH_RP2040))
#include <hardware/irq.h>
#include <hardware/pwm.h>
#include <hardware/dma.h>
#include <hardware/gpio.h>
#include <pico/stdlib.h> 
#include "dmd_out.pio.h"
#endif
//#define TICS_IN_uS (F_CPU / 1000000ul)
#ifndef CYCLES_PER_MICROSECOND
#define CYCLES_PER_MICROSECOND (F_CPU / 1000000ul)
#endif

#if (defined(__STM32F1__) || defined(__STM32F4__))
typedef uint32 PortType;
#define TIM_MAX_RELOAD ((1 << 16) - 1)
enum OE_PWM_Polarity{ OE_PWM_POSITIVE = TIMER_OC_MODE_PWM_1, OE_PWM_NEGATIVE = TIMER_OC_MODE_PWM_2 };
#elif (defined(ARDUINO_ARCH_RP2040))
enum OE_PWM_Polarity { OE_PWM_POSITIVE = false, OE_PWM_NEGATIVE = true };
typedef uint16_t PortType;
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
#define DMD_BITSPERPIXEL           1       // used for Monochrome panels only
#define DMD_MONO_SCAN              4

// Panel connections variants
#define CONNECT_NORMAL 0
#define CONNECT_ROTATE90 1
#define CONNECT_ZIGZAG 2

// Shift marquee result codes
#define MARQUEE_OUT_OF_SCREEN 1					// text has left the screen
#define MARQUEE_JUSTIFY_ON_LEFT 2				// text justify on the left border
#define MARQUEE_JUSTIFY_ON_RIGHT 4				// ...on the right border

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

//typedef uint8_t(*FontCallback)(const uint8_t*);

/*--------------------------------------------------------------------------------------*/
// container list class for DMD GPIOs
class DMD_Pinlist
{
public:
	DMD_Pinlist(uint8_t pinA, uint8_t pinB) :count(2)
	{
		list = new uint8_t[2]{ pinA, pinB };
	}
	DMD_Pinlist(uint8_t pin_count, uint8_t* pinlist):count(pin_count)
	{
		list = new uint8_t[pin_count];
		memcpy(list, pinlist, count);
	}

	uint8_t count = 0;
	uint8_t* list = nullptr;

	~DMD_Pinlist() { delete[] list; }

};

/*--------------------------------------------------------------------------------------*/
//The main class of DMD library functions
class DMD : public Adafruit_GFX
{
public:
	//Instantiate the DMD

	DMD(DMD_Pinlist* _mux_pinlist, byte _pin_nOE, byte _pin_SCLK, byte panelsWide, byte panelsHigh,
		uint8_t n_Rows, DMD_Pinlist* _data_pinlist, bool d_buf, byte dmd_pixel_x, byte dmd_pixel_y);
	

	virtual ~DMD();

	virtual void init(uint16_t scan_interval = 1000);
	
	//Set or clear a pixel at the x and y location (0,0 is the top left corner)
	virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;

	//Clear the screen in DMD RAM
	virtual void clearScreen(byte bNormal);
	virtual void fillScreen(uint16_t color);
	virtual void shiftScreen(int8_t step) = 0;
	virtual void transform_XY(int16_t& x, int16_t& y);
	
	// -- Char, string and marquee methods --
	// Draw a string
	void drawString(int bX, int bY, const char* bChars, int length, uint16_t color, int16_t miny, int16_t maxy, byte orientation = 0);
	void drawString(int bX, int bY, const char* bChars, int length, uint16_t color, byte orientation = 0);
	void drawStringX(int bX, int bY, const char* bChars, uint16_t color, byte orientation = 0);

	//Select a text font
	void selectFont(DMD_Font* font);

	//Draw a single character
	int drawChar(const int bX, const int bY, const unsigned char letter, uint16_t color, byte orientation = 0);
	int drawChar(const int bX, const int bY, const unsigned char letter, uint16_t color, int16_t miny, int16_t maxy, byte orientation = 0);
	//Draw a single character vertically  - method moved to drawChar()
	//int drawCharV(const int bX, const int bY, const unsigned char letter, uint16_t color);

	//Find the width of a character
	int charWidth(const unsigned char letter, byte orientation = 0);

	//Draw a scrolling string
	void drawMarquee(const char* bChars, int length, int left, int top, byte orientation = 0);
	void drawMarqueeX(const char* bChars, int left, int top, byte orientation = 0);

	//Move the maquee accross by amount
	uint8_t  stepMarquee(int amountX, int amountY, byte orientation = 0);

	// return string width in pixels
	uint16_t stringWidth(const char* bChars, uint16_t length = 0, byte orientation = 0);
	uint16_t stringWidthV(const char* bChars, uint16_t length = 0)
	{
		return stringWidth(bChars, length, 1);
	}

	void stringBounds(const char* bChars, uint16_t length,
		int16_t* w, int16_t* min_y, int16_t* max_y, byte orientation = 0);
	
	// Disable moving of marquee by pixel shift of whole screen.
	// Set this flag if you need to display more than one string at time.
	virtual void disableFastTextShift(bool shift) {
		if ((!shift) && (this->connectScheme == CONNECT_NORMAL)) this->use_shift = true;
		else this->use_shift = false;
	}

	// set panel connection scheme
	virtual void setConnectScheme(uint8_t sch) {
		this->connectScheme = sch;
		if (sch != CONNECT_NORMAL) {
			this->use_shift = false;
			this->fast_Hbyte = false;
		}
	};
	// rotate the screen
	virtual void setRotation(uint8_t x) {
		uint8_t rot = (x & 3);
		if (rot) {
			this->use_shift = false;
			this->fast_Hbyte = false;
		}
		Adafruit_GFX::setRotation(rot);
	};


	
	//Draw or clear a filled box(rectangle) with a single pixel border
	void drawFilledBox(int x1, int y1, int x2, int y2, uint16_t color);

	//set brightness of panel
	virtual void setBrightness(uint8_t level) {
		this->brightness = level;
	};

	// Inverse all data on display - for p10 matrix inversed by design
	inline void inverseAll(uint8_t flag) { this->inverse_ALL_flag = flag; };
	
	virtual void swapBuffers(boolean copy);

#if defined(DEBUG2)
	void dumpDDbuf(void);
	void dumpMatrix(void);
#endif

	virtual void initialize_timers(voidFuncPtr handler);

protected:
	virtual void set_pin_modes();
#if (defined(__STM32F1__) || defined(__STM32F4__))
		//virtual void generate_muxmask();
		virtual uint16_t setup_main_timer(uint32_t cycles, voidFuncPtr handler);
#endif
	virtual void generate_muxmask();
	virtual void set_mux(uint8_t curr_row);
	virtual void drawHByte(int16_t x, int16_t y, uint8_t hbyte, uint16_t bsize, uint8_t* fg_col_bytes,
		uint8_t* bg_col_bytes) {} ;
	virtual void getColorBytes(uint8_t* cbytes, uint16_t color) {};
	
	// pins
	const uint8_t mux_cnt = 2;
	uint8_t data_pins_cnt = 0;
	uint8_t* mux_pins;
	uint8_t* data_pins;
	
	DMD_Pinlist* mux_pinlist;
	const uint8_t nRows = 4;
	DMD_Pinlist* data_pinlist;
	uint32_t* mux_mask2;
	

	const byte pin_DMD_CLK;
	const byte pin_DMD_nOE;   // active low Output Enable, setting this low lights all the LEDs in the selected rows. Can pwm it at very high frequency for brightness control.
	const byte pin_DMD_SCLK;  // LATCH PORT
	PortType clk_clrmask = 0;
	PortType clkmask = 0;
#if (defined(__STM32F1__) || defined(__STM32F4__))
	// Pin bitmasks
	PortType latmask, oemask; 
	
	// PORT register pointers 
	volatile PortType* muxsetreg, * oesetreg, * latsetreg;
	volatile PortType* datasetreg;
	uint8_t oe_channel;
#endif
	OE_PWM_Polarity OE_polarity = OE_PWM_POSITIVE;
	uint16_t brightness = 100;
	
	//DMD I/O pin macros
	virtual void switch_row();



	//Mirror of DMD pixels in RAM, ready to be clocked out by the main loop or high speed timer calls
	uint8_t* bDMDScreenRAM;

	uint8_t* matrixbuff[2];
	volatile uint8_t backindex = 0;
	volatile boolean swapflag = false;
	volatile uint8_t* front_buff;
	uint16_t mem_Buffer_Size;
	uint16_t x_len;
	uint32_t scan_cycle_len = 0;
	

	//Marquee values
	char marqueeText[MAX_STRING_LEN];
	uint16_t marqueeLength;
	int16_t marqueeWidth,
		marqueeHeight,
		marqueeOffsetX,
		marqueeOffsetY,
		marqueeMarginH,
		marqueeMarginL;

	bool use_shift = true;
	bool fast_Hbyte = false;

	//Pointer to current font
	DMD_Font* Font;

	//Display information
	const byte DisplaysWide;
	const byte DisplaysHigh;
	byte DisplaysTotal;
	bool  dbuf = false;
	const uint8_t DMD_PIXELS_ACROSS;
	const uint8_t DMD_PIXELS_DOWN;
	
	
	//scanning pointer into bDMDScreenRAM
	volatile byte bDMDByte = 0;
	uint8_t inverse_ALL_flag = PANEL_INVERSE;
	byte connectScheme = CONNECT_NORMAL;
	uint8_t graph_mode = GRAPHICS_NORMAL;
	void set_graph_mode(uint8_t gm = GRAPHICS_NORMAL) {
		graph_mode = gm;
	}
	
	uint16_t inverse_color(uint16_t col) {
		if (col == textbgcolor) return textcolor; else return textbgcolor;

	}

// --- specific variables for RP2030 boards ---
#if (defined(ARDUINO_ARCH_RP2040))
	uint8_t OE_slice_num;
	uint8_t MAIN_slice_num;
	uint8_t dma_chan;
	// PIO config
	PIO pio = pio0;
	uint8_t sm_data = 0;
	uint8_t sm_mux = 1;
	const uint8_t pwm_clk_div = 10;
	uint16_t data_prog_offs = 0;
	pio_sm_config pio_config;
	const uint8_t pio_clkdiv = 3;
#endif
	
	
// --- Timer defines ---
#if defined(__STM32F1__)
#if defined(MCU_STM32F103C6)
	timer_dev* MAIN_TIMER = TIMER2;
	timer_dev* OE_TIMER = TIMER3;
#elif defined( ALTERNATIVE_DMD_TIMERS )
	timer_dev* MAIN_TIMER = TIMER3;
	timer_dev* OE_TIMER = TIMER4;
#else
	timer_dev* MAIN_TIMER = TIMER4;
	timer_dev* OE_TIMER = TIMER3;
#endif
#elif defined(__STM32F4__) 
#if defined( ALTERNATIVE_DMD_TIMERS )
	const timer_dev* MAIN_TIMER = TIMER3;
	const timer_dev* OE_TIMER = TIMER4;
#else
	const timer_dev* MAIN_TIMER = TIMER4;
	const timer_dev* OE_TIMER = TIMER3;
#endif
#endif


#if defined(DEBUG2)
#define DEBUG_TIME_MARK if (dd_cnt < 100) dd_ptr[dd_cnt++] = timer_get_count(MAIN_TIMER)
#define DEBUG_TIME_MARK_333 if (dd_cnt < 100) dd_ptr[dd_cnt++] = 333
	volatile uint16_t* dd_ptr = 0;
	volatile uint8_t dd_cnt = 0;
#else
#define DEBUG_TIME_MARK 
#define DEBUG_TIME_MARK_333 
#endif	
private:

};



#endif /* DMD_H_ */
