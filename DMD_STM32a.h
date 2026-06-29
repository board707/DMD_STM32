#pragma once

/*--------------------------------------------------------------------------------------
 DMD_STM32a.h  - advansed version of DMD_STM32.h

 ****** VERSION 1.2.0 ******

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
#include "DMD_Defs.h"
#include "Adafruit_GFX.h"
#include "DMD_Config.h"
#include "DMD_Font.h"
#include "DMD_Multiplexer.h"

//typedef uint8_t(*FontCallback)(const uint8_t*);





/*--------------------------------------------------------------------------------------*/
//The main class of DMD library functions
class DMD : public Adafruit_GFX
{
public:
	//Instantiate the DMD

	DMD(byte _pin_nOE, byte _pin_SCLK, byte panelsWide, byte panelsHigh,
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
	
	
	
	// -- Char, string and marquee methods -- //
	
	/**********************************************************************/
	/*!
	@brief		Draw a text string with custom background color

	@param		bX, bY - start coordinates (top left point)
	@param		bChars - string data
	@param		length - string length
	@param		color -  color to draw text with, 16-bit single value or DMD_Colorlist for multicolor text
	@param		mixy, maxy - most upper and lower text point relative to bY - defines the area 
					will covered by backgroung color
	@param		orientation - gorizontal (0) or vertical (1) 

	@note		drawStringX variant expects a null-terminated string and don't need a length, 
				other two prints only first <length> chars of long text
    */
   /**********************************************************************/
   
	template <typename T>
	void drawString(int bX, int bY, const char* bChars, int length,
		T color, int16_t miny, int16_t maxy, byte orientation = 0 )
		{
		if ((bX >= _width) || (bY >= _height))
			return;
		uint8_t height = Font->get_height();
		if (bY + height < 0) return;

		int strWidth = 0;
		this->drawLine(bX - 1, bY + miny, bX - 1, bY + maxy, textbgcolor);

		for (int i = 0; i < length; i++) {

			uint16_t current_color = get_text_color(i, color);
			int charWide = this->drawChar(bX + strWidth, bY, bChars[i], current_color, miny, maxy, orientation);

			if (charWide > 0) {
				strWidth += charWide;
				if( Font->interCharSpace > 0 ) {
					this->drawFilledBox(bX + strWidth, bY + miny, bX + strWidth + Font->interCharSpace - 1, bY + maxy, textbgcolor);
					strWidth+=Font->interCharSpace;
				}
				}
			else if (charWide < 0) {
				return;
				}
			if ((bX + strWidth) >= _width || bY >= _height) return;
			}

		}
	/*--------------------------------------------------------------------------------------*/
	template <typename T>
	void drawString(int bX, int bY, const char* bChars, int length,
		T color, byte orientation = 0)
		{
		int16_t miny = 0, maxy = 0, w;
		stringBounds(bChars, length, &w, &miny, &maxy, orientation);
		drawString(bX, bY, bChars, length, color, miny, maxy, orientation);
		}
	/*--------------------------------------------------------------------------------------*/
	template <typename T>
	void drawStringX(int bX, int bY, const char* bChars, T color, byte orientation = 0)
		{
		int len = 0;
		while (bChars[len] && len < MAX_STRING_LEN) { len++; }
		this->drawString(bX, bY, bChars, len, color, orientation);
		}
	/*--------------------------------------------------------------------------------------*/
	


	/**********************************************************************/
	/*!
	@brief		Draw a single char with custom background color

	@param		bX, bY - start coordinates (top left point)
	@param		letter - char code
	@param		color -  16-bit color to draw
	@param		mixy, maxy - most upper and lower text point relative to bY (optional)
	@param		orientation - gorizontal (0) or vertical (1)

	*/
	/**********************************************************************/
	int drawChar(const int bX, const int bY, const unsigned char letter, uint16_t color, byte orientation = 0);
	int drawChar(const int bX, const int bY, const unsigned char letter, uint16_t color, int16_t miny, int16_t maxy, byte orientation = 0);
	
	/**********************************************************************/
	/*!
	@brief		Draw a string and prepare it to scroll

	@param		bChars - string data
	@param		length - string length
	@param		left, top - start coordinates
	@param		orientation - gorizontal (0) or vertical (1)
	
	@note		=== only one marquee can be used at the time ===

	@note		to set color of the text and background use in RGB panels
				use setMarqueeColor(text_color, bg_color) method
	*/
	/**********************************************************************/
	void drawMarquee(const char* bChars, int length, int left, int top, byte orientation = 0);
	void drawMarqueeX(const char* bChars, int left, int top, byte orientation = 0);
	
	//Scroll the marquee by amountX and amountY pixels
	uint8_t  stepMarquee(int amountX, int amountY, byte orientation = 0);

	/*--------------------------------------------------------------------------------------*/

	// -- Char and text attributes -- //

	//Select a font for drawing chars, strings and marquee text 
	void selectFont(DMD_Font* font, uint8_t interCharInterval);
	void selectFont(DMD_Font* font) {
		selectFont(font, 1);
	}

    //Find the width of a single character using defined text font
	int charWidth(const unsigned char letter, byte orientation = 0);

	//Return string width in pixels using defined text font
	uint16_t stringWidth(const char* bChars, uint16_t length = 0, byte orientation = 0);
	uint16_t stringWidthV(const char* bChars, uint16_t length = 0)
	{
		return stringWidth(bChars, length, 1);
	}

	//string bounds in pixels using defined text font
	void stringBounds(const char* bChars, uint16_t length,
		int16_t* w, int16_t* min_y, int16_t* max_y, byte orientation = 0);
	
	// Default method to scrolling the marquee is shifting of whole screen.
	// Set this flag (true) to avoid this if you need to display more than one string at time.
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

	//Set brightness of panel ( 0 - 255)
	virtual void setBrightness(uint8_t level) {
		this->brightness = level;
	};

	//Inverse all data on display - for p10 matrix inversed by design
	inline void inverseAll(uint8_t flag) { this->inverse_ALL_flag = flag; };
	
	//Exchange drawing and output buffers (in dual_buf mode)
	virtual void swapBuffers(bool copy);

#if defined(DEBUG2)
	void dumpDDbuf(void);
	void dumpMatrix(void);
#endif

	virtual void initialize_timers(voidFuncPtr handler);
	#if (defined(ARDUINO_ARCH_RP2040))
	virtual void pio_dma_init();
    #endif
	
	bool marqueeType_MultiColor = false;
	DMD_Colorlist* marqueeColors = NULL;


protected:
	virtual void set_pin_modes();
#if (defined(__STM32F1__) || defined(__STM32F4__))
		//virtual void generate_muxmask();
		virtual uint16_t setup_main_timer(uint32_t cycles, voidFuncPtr handler);
#endif
	//virtual void generate_muxmask();
	//virtual void set_mux(uint8_t curr_row);
	virtual void drawHByte(int16_t x, int16_t y, uint8_t hbyte, uint16_t bsize, uint8_t* fg_col_bytes, uint8_t* bg_col_bytes) {
		UNUSED3(x, y, hbyte); UNUSED3(bsize, fg_col_bytes, bg_col_bytes);
		} ;
	virtual void getColorBytes(uint8_t* cbytes, uint16_t color) {
		UNUSED2(cbytes,color);
	};
	virtual void  drawMarqueeString(int bX, int bY, const char* bChars, int length,
		int16_t miny, int16_t maxy, byte orientation = 0);
	// pins
	//const uint8_t mux_cnt = 2;
	uint8_t data_pins_cnt = 0;
	//uint8_t* mux_pins;
	uint8_t* data_pins;
	
	//DMD_Pinlist* mux_pinlist;
	const uint8_t nRows = 4;
	DMD_Pinlist* data_pinlist;
	//uint32_t* mux_mask2;

	DMD_Multiplexer* Mux = NULL;
	
	const byte pin_DMD_CLK;
	const byte pin_DMD_nOE;   // active low Output Enable, setting this low lights all the LEDs in the selected rows. Can pwm it at very high frequency for brightness control.
	const byte pin_DMD_SCLK;  // LATCH PORT
	PortType clk_clrmask = 0;
	PortType clkmask = 0;
#if (defined(__STM32F1__) || defined(__STM32F4__))
	// Pin bitmasks
	PortType latmask, oemask; 
	
	// PORT register pointers 
	//volatile PortType* muxsetreg;
	volatile PortType* oesetreg, * latsetreg;
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
	volatile bool swapflag = false;
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
	
	
	/*--------------------------------------------------------------------------------------*/
	// service routines for text and marquee modes, internal use
	uint16_t inverse_color(uint16_t col) {
		if (col == textbgcolor) return textcolor; else return textbgcolor;
	}
	

	uint16_t get_marquee_text_color(uint8_t num) {
		if (marqueeType_MultiColor)
			return get_text_color(num, marqueeColors);
		
		else return textcolor;
		}

	uint16_t get_text_color(uint8_t num, uint16_t color) {
		UNUSED1(num);
		return color;
		}
	
	uint16_t get_text_color(uint8_t num, DMD_Colorlist* colorlist) {
		uint16_t color = colorlist->list[(num % (colorlist->count - 1)) + 1];
		setTextColor(color, colorlist->list[0]);
		return color;
		}
	/*--------------------------------------------------------------------------------------*/
	
// --- specific variables for RP2030 boards ---
#if (defined(ARDUINO_ARCH_RP2040))
	uint8_t OE_slice_num;
	uint8_t MAIN_slice_num;
	uint8_t dma_chan;
	// PIO config
	PIO pio = pio0;
	uint8_t sm_data = 0;
	//uint8_t sm_mux = 1;
	uint8_t pwm_clk_div = 10;
	uint16_t data_prog_offs = 0;
	pio_sm_config pio_config;
	uint8_t pio_clkdiv = 3;
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
