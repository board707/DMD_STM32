#pragma once
/*--------------------------------------------------------------------------------------
 This file is a part of the library DMD_STM32

 DMD_STM32.h  - STM32 port of DMD.h library

 https://github.com/board707/DMD_STM32
 Dmitry Dmitriev (c) 2019-2023
 /--------------------------------------------------------------------------------------

 =======  based on =========

 * RGBmatrixPanel.h
 *
 * Adafruit's RGB LED Matrix Panel library
 * for the Arduino platform.
 *
 * Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon for
 * Adafruit Industries.
 */
#ifndef DMD_RGB_H
#define DMD_RGB_H

#include "DMD_STM32a.h"
#if (defined(__STM32F1__))
#include <dma_private.h>
#endif




// COLOR DEPTH
#if (defined(__STM32F1__)|| defined(__STM32F4__)) 

void inline __attribute__((always_inline)) scan_running_dmd_R();

#define COLOR_4BITS_Packed		3
#endif
#define COLOR_4BITS		4
#define COLOR_1BITS		1

// RGB TABLE OPTIONS
#define CLK_WITH_DATA   0x1
#define CLK_AFTER_DATA   0

class DMD_RGB_BASE :
	public DMD
{
public:

	DMD_RGB_BASE(byte mux_cnt, uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf, uint8_t col_depth, uint8_t n_Rows, byte dmd_pixel_x, byte dmd_pixel_y);

	// set desired FPS as init() parameter
	void init(uint16_t scan_interval = 200) override;
	virtual void drawPixel(int16_t x, int16_t y, uint16_t color) override;
	void clearScreen(byte bNormal) override;
	void shiftScreen(int8_t step) override;
	void fillScreen(uint16_t color) override;

 /**********************************************************************/
 /*!
   @brief   Set marquee text and background color

   @param   text_color		16-bit 5-6-5 Color to draw text with
   @param   bg_color		16-bit 5-6-5 Color to draw background/fill with
 */
 /**********************************************************************/
	void setMarqueeColor(uint16_t text_color, uint16_t bg_color);

/**********************************************************************/
 /*!
   @brief   Set marquee color for multicolor version

   @param   colors	pointer to list of colors,
					where 1st is for bacrground, and next colors loops over text chars
*/
 /**********************************************************************/
	void setMarqueeColor(DMD_Colorlist* colors);

	
	virtual void scan_dmd();
	void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) override;
	void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) override;
	
	uint16_t
		Color333(uint8_t r, uint8_t g, uint8_t b),
		Color444(uint8_t r, uint8_t g, uint8_t b),
		Color888(uint8_t r, uint8_t g, uint8_t b);
	
	~DMD_RGB_BASE();

	virtual void scan_dmd_p1();
#if (defined(__STM32F1__) || defined(__STM32F4__))
	virtual void scan_dmd_p2();
	virtual void scan_dmd_p3();
	virtual void initialize_timers(voidFuncPtr handler) override;
#endif
#if defined(DEBUG2)
	//void dumpMatrix(void);
	void dumpMask(void);
#endif
protected:

#if (defined(__STM32F1__) || defined(__STM32F4__))
	virtual void generate_rgbtable() { generate_rgbtable_default(CLK_WITH_DATA); }
	void generate_rgbtable_default(uint8_t options);
	void send_to_allRGB(uint16_t data, uint16_t latches);
	virtual void chip_init() {};	
#endif
	virtual void setCycleLen();
	virtual uint16_t get_base_addr(int16_t& x, int16_t& y);
	virtual void drawHByte(int16_t x, int16_t y, uint8_t hbyte, uint16_t bsize, uint8_t* fg_col_bytes,
		uint8_t* bg_col_bytes) override;
	virtual void getColorBytes(uint8_t* cbytes, uint16_t color) override;
	
	void  drawMarqueeString(int bX, int bY, const char* bChars, int length,
		int16_t miny, int16_t maxy, byte orientation = 0) override;

	byte* rgbpins;
#if (defined(__STM32F1__) || defined(__STM32F4__))

	// Pin bitmasks
	PortType rgbmask_all;
	// PORT register pointers 

uint16_t           expand[256];           // 6-to-32 bit converter table

#if defined(RGB_DMA)

#if defined(__STM32F1__) 
	timer_dev* DMA_TIMER = TIMER2;
	timer_gen_reg_map* DMA_TIMER_BASE = TIMER2_BASE;
	dma_dev* rgbDmaDev = DMA1;
	dma_channel  DmaDataChannel = DMA_CH5;
	dma_channel  DmaClkChannel = DMA_CH1;
#elif defined(__STM32F4__) 
	const timer_dev* DMA_TIMER = TIMER1;
	timer_adv_reg_map* DMA_TIMER_BASE = TIMER1_BASE;
	const dma_dev* rgbDmaDev = DMA2;
	dma_channel  DmaDataChannel = DMA_CH6;
	dma_channel  DmaClkChannel = DMA_CH6;
	dma_stream  datTxDmaStream = DMA_STREAM1; // TIM1 CH1
	dma_stream  clkTxDmaStream = DMA_STREAM6; // TIM1 CH3 
#endif
#endif

#endif

	// Counters/pointers for interrupt handler:
	volatile uint8_t row, plane;
	volatile uint8_t* buffptr;
	uint8_t nPlanes = 4;
	const uint8_t pol_displ = DMD_PIXELS_DOWN / 2;
	const uint8_t multiplex = pol_displ / nRows;
	const uint16_t displ_len = WIDTH * pol_displ * DisplaysHigh;
    uint8_t col_bytes_cnt = nPlanes;
	uint16_t colors[2] = { 0, 0 };
	uint8_t col_cache[8] = { 0 };
	uint8_t last_color = 0;

	// interrupt cycles length (in clock tics)
	uint32_t callOverhead;
	uint16_t transfer64bits_time =10;   // in uS
	uint16_t transfer_duty = 3;
	uint16_t transfer_duty2 =1;
	uint16_t default_fps = 200;
#if (defined(ARDUINO_ARCH_RP2040))
	uint16_t min_scan_len = 15;        // in uS
#endif
#if defined (DIRECT_OUTPUT)
	uint8_t output_mask = 0b01000000;
#else
	uint8_t output_mask = 0;
#endif
};

/*--------------------------------------------------------------------------------------*/
template<int COL_DEPTH>
class DMD_RGB_BASE2 : public DMD_RGB_BASE
{
public:
	DMD_RGB_BASE2() = 0;
};
/*--------------------------------------------------------------------------------------*/
template<>
class DMD_RGB_BASE2< COLOR_1BITS> : public DMD_RGB_BASE
{
public:
	DMD_RGB_BASE2(byte mux_cnt, uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf, uint8_t col_depth, uint8_t n_Rows, byte dmd_pixel_x, byte dmd_pixel_y) :
		DMD_RGB_BASE(mux_cnt, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, col_depth, n_Rows, dmd_pixel_x, dmd_pixel_y)
	{
	
#if (defined(__STM32F1__)) 
		this->callOverhead = 150;
		this->transfer64bits_time = 11;
		this->transfer_duty = 2;
		this->transfer_duty2 = 1;
#elif ( defined(__STM32F4__))
		this->callOverhead = 150;
#ifdef RGB_DMA
		this->transfer64bits_time =10;
		this->transfer_duty =2;
		this->transfer_duty2 =1;
#else
		this->transfer64bits_time = 5;
		this->transfer_duty = 3;
		this->transfer_duty2 = 1;
#endif

#elif (defined(ARDUINO_ARCH_RP2040))
		this->callOverhead = 100;
		this->transfer64bits_time = 6;
		this->transfer_duty = 2;
		this->transfer_duty2 = 1;
	
#endif
	
	}


};
/*--------------------------------------------------------------------------------------*/
template<>
class DMD_RGB_BASE2< COLOR_4BITS> : public DMD_RGB_BASE
{
public:
	DMD_RGB_BASE2(byte mux_cnt, uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf, uint8_t col_depth, uint8_t n_Rows, byte dmd_pixel_x, byte dmd_pixel_y) :
		DMD_RGB_BASE(mux_cnt, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, col_depth, n_Rows, dmd_pixel_x, dmd_pixel_y)
	{

#if (defined(__STM32F1__)) 
		this->callOverhead = 150;
		this->transfer64bits_time = 10;
		this->transfer_duty = 2;
		this->transfer_duty2 = 1;
#elif ( defined(__STM32F4__))
		this->callOverhead = 150;
#ifdef RGB_DMA
		this->transfer64bits_time = 10;
		this->transfer_duty = 6;
		this->transfer_duty2 = 5;
#else
		this->transfer64bits_time = 5;
		this->transfer_duty = 2;
		this->transfer_duty2 = 1;
#endif

#elif (defined(ARDUINO_ARCH_RP2040))
		this->callOverhead = 100;
		this->transfer64bits_time = 6;
		this->transfer_duty = 6;
		this->transfer_duty2 = 5;

#endif

	}

protected:
	
};
/*--------------------------------------------------------------------------------------*/
#if (defined(__STM32F1__)|| defined(__STM32F4__)) 
template<>
class DMD_RGB_BASE2< COLOR_4BITS_Packed> : public DMD_RGB_BASE
{

public:
	DMD_RGB_BASE2(byte mux_cnt, uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf, uint8_t col_depth, uint8_t n_Rows, byte dmd_pixel_x, byte dmd_pixel_y) :
		DMD_RGB_BASE(mux_cnt, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, col_depth, n_Rows, dmd_pixel_x, dmd_pixel_y)
	{
		output_mask = 0;

#if (defined(__STM32F1__)) 
		this->callOverhead = 150;
		this->transfer64bits_time = 12;
		this->transfer_duty = 2;
		this->transfer_duty2 = 1;
#elif ( defined(__STM32F4__))
		this->callOverhead = 150;
		this->transfer64bits_time = 6;
		this->transfer_duty = 2;
		this->transfer_duty2 = 1;
#endif
#if (defined(ARDUINO_ARCH_RP2040))
#error Cant use COLOR_4BITS_Packed mode with Rasberry Pico RP2040
#endif

	}

/*--------------------------------------------------------------------------------------*/
virtual void scan_dmd_p3() override {

	// buffptr, being 'volatile' type, doesn't take well to optimization.
	// A local register copy can speed some things up:
	volatile uint8_t* ptr = buffptr;

	if (plane > 0) {

#define pew                    \
		*datasetreg = clk_clrmask;     \
		*datasetreg = expand[*ptr++];

		for (uint16_t uu = 0; uu < x_len; uu += 8)
			{
				// Loop is unrolled for speed:
				pew pew pew pew pew pew pew pew
			}
		*datasetreg = clkmask << 16; // Set clock low

			buffptr += displ_len;
	}
	else { // 920 ticks from TCNT1=0 (above) to end of function

		for (int i = 0; i < x_len; i++) {
			byte b =
				((ptr[i] >> 2) & 0x30) |
				((ptr[i + displ_len] >> 4) & 0x0C) |
				((ptr[i + displ_len * 2] >> 6) & 0x03);

			*datasetreg = clk_clrmask; // Clear all data and clock bits together
			*datasetreg = expand[b];  // Set new data bits
			}
		*datasetreg = clkmask << 16;      // Set clock low
	}

#undef pew	
}

/*--------------------------------------------------------------------------------------*/
void getColorBytes(uint8_t* cbytes, uint16_t color) override {
	uint8_t r, g, b, bit, limit;
	uint8_t* ptr;

	// special case color = 0
	if (color == 0) {
		cbytes[0] = 0; cbytes[1] = 0; cbytes[2] = 0;
		return;
		}

	if ((colors[last_color] == color) || (colors[last_color = !last_color] == color)) {
		ptr = col_cache + last_color * 3;
		memcpy(cbytes, ptr, 3); return;
		}

	ptr = col_cache + last_color * 3;
	colors[last_color] = color;
	ptr[0] = 0; ptr[1] = 0; ptr[2] = 0;

	// Adafruit_GFX uses 16-bit color in 5/6/5 format, while matrix needs
		// 4/4/4.  Pluck out relevant bits while separating into R,G,B:

	uint16_t c = color;
	r = c >> 12;        // RRRRrggggggbbbbb
	g = (c >> 7) & 0xF; // rrrrrGGGGggbbbbb
	b = (c >> 1) & 0xF; // rrrrrggggggBBBBb

	//if (nPlanes == 4) {

	if (r & 1) { ptr[1] |= B10000000; ptr[2] |= B01000000; }
	if (g & 1) { *ptr |= B01000000; ptr[2] |= B10000000; }// Plane 0 G: bit 0
	if (b & 1) { *ptr |= B10000000; ptr[1] |= B01000000; }// Plane 0 B: bit 0


	limit = 1 << nPlanes;
	bit = 2;
	for (; bit < limit; bit <<= 1) {
		// Mask out R,G,B in one op
		if (r & bit) *ptr |= B001001; // Plane N R: bit 2
		if (g & bit) *ptr |= B010010; // Plane N G: bit 3
		if (b & bit) *ptr |= B100100; // Plane N B: bit 4

		ptr++;                 // Advance to next bit plane
		}
	ptr -= 3;
	memcpy(cbytes, ptr, 3); return;
	}
/*--------------------------------------------------------------------------------------*/
void drawHByte(int16_t x, int16_t y, uint8_t hbyte, uint16_t bsize, uint8_t* fg_col_bytes,
	uint8_t* bg_col_bytes) override {

	static uint8_t ColorByteMask[] = { B00000111 , B01000111 , B11000111 ,
										  B11111000 , B10111000 , B00111000 };

	if ((hbyte != 0xff) && (bsize > 8)) bsize = 8;

	//if whole line is outside - go out
	if (((x + bsize) <= 0) || (x >= WIDTH) || (y < 0) || (y >= HEIGHT)) return;

	//if start of line before 0 - draw portion of line from x=0
	if (x < 0) {
		bsize = bsize + x;
		if (hbyte != 0xff) hbyte <<= (x * -1);
		x = 0;
		}

	//if end of line after right edge of screen - draw until WIDTH-1
	if ((x + bsize) > WIDTH) bsize = WIDTH - x;

	// transform X & Y for Rotate and connect scheme

	uint16_t base_addr = get_base_addr(x, y);
	uint8_t* ptr_base = &matrixbuff[backindex][base_addr]; // Base addr

	DEBUG_TIME_MARK;
	uint8_t* mask_ptr, * mask;
	uint8_t* col_bytes;
	uint8_t* ptr = ptr_base;
	if (y % DMD_PIXELS_DOWN < pol_displ) {
		mask = ColorByteMask;
		}
	else {

		mask = ColorByteMask + 3;
		}
	col_bytes = fg_col_bytes;
	for (uint8_t j = 0; j < bsize; j++) {
		if (hbyte != 0xff) {
			if (hbyte & 0x80) {
				col_bytes = fg_col_bytes;
				}
			else {
				col_bytes = bg_col_bytes;
				}
			hbyte <<= 1;
			}
		mask_ptr = mask;
		ptr = ptr_base + j;
		*ptr &= ~(*mask_ptr);
		*ptr |= (col_bytes[0] & *mask_ptr++);
		ptr += displ_len;
		*ptr &= ~(*mask_ptr);
		*ptr |= (col_bytes[1] & *mask_ptr++);
		ptr += displ_len;
		*ptr &= ~(*mask_ptr);
		*ptr |= (col_bytes[2] & *mask_ptr);

		}
	DEBUG_TIME_MARK;

	}
/*--------------------------------------------------------------------------------------*/
void drawPixel(int16_t x, int16_t y, uint16_t c) override {
	uint8_t r, g, b, bit, limit, * ptr;


	DEBUG_TIME_MARK_333;
	DEBUG_TIME_MARK;
	if (graph_mode == GRAPHICS_NOR) {
		if (c == textcolor) c = textbgcolor;
		else return;
		}
	if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height)) return;

	// transform X & Y for Rotate and connect scheme

		// Adafruit_GFX uses 16-bit color in 5/6/5 format, while matrix needs
		// 4/4/4.  Pluck out relevant bits while separating into R,G,B:
	r = c >> 12;        // RRRRrggggggbbbbb
	g = (c >> 7) & 0xF; // rrrrrGGGGggbbbbb
	b = (c >> 1) & 0xF; // rrrrrggggggBBBBb

	uint16_t base_addr = get_base_addr(x, y);
	ptr = &matrixbuff[backindex][base_addr]; // Base addr
	DEBUG_TIME_MARK;
	bit = 2;
	limit = 1 << nPlanes;
	if (y % DMD_PIXELS_DOWN < pol_displ) {
		// Data for the upper half of the display is stored in the lower
		// bits of each byte.

		// Plane 0 is a tricky case -- its data is spread about,
		// stored in least two bits not used by the other planes.
		ptr[displ_len * 2] &= ~B11000000;           // Plane 0 R,G mask out in one op
		if (r & 1) ptr[displ_len * 2] |= B01000000; // Plane 0 R: 64 bytes ahead, bit 0
		if (g & 1) ptr[displ_len * 2] |= B10000000; // Plane 0 G: 64 bytes ahead, bit 1
		if (b & 1) ptr[displ_len] |= B01000000; // Plane 0 B: 32 bytes ahead, bit 0
		else      ptr[displ_len] &= ~B01000000; // Plane 0 B unset; mask out
		// The remaining three image planes are more normal-ish.
		// Data is stored in the high 6 bits so it can be quickly
		// copied to the DATAPORT register w/6 output lines.
		for (; bit < limit; bit <<= 1) {
			*ptr &= ~B000111;            // Mask out R,G,B in one op
			if (r & bit) *ptr |= B000001; // Plane N R: bit 2
			if (g & bit) *ptr |= B000010; // Plane N G: bit 3
			if (b & bit) *ptr |= B000100; // Plane N B: bit 4
			ptr += displ_len;                 // Advance to next bit plane
			}
		}
	else {
		// Data for the lower half of the display is stored in the upper
		// bits, except for the plane 0 stuff, using 2 least bits.

		*ptr &= ~B11000000;                  // Plane 0 G,B mask out in one op
		if (r & 1)  ptr[displ_len] |= B10000000; // Plane 0 R: 32 bytes ahead, bit 1
		else       ptr[displ_len] &= ~B10000000; // Plane 0 R unset; mask out
		if (g & 1) *ptr |= B01000000; // Plane 0 G: bit 0
		if (b & 1) *ptr |= B10000000; // Plane 0 B: bit 0
		for (; bit < limit; bit <<= 1) {
			*ptr &= ~B111000;            // Mask out R,G,B in one op
			if (r & bit) *ptr |= B001000; // Plane N R: bit 5
			if (g & bit) *ptr |= B010000; // Plane N G: bit 6
			if (b & bit) *ptr |= B100000; // Plane N B: bit 7
			ptr += displ_len;                 // Advance to next bit plane
			}
		}
	DEBUG_TIME_MARK;

	}
};
#endif  // if (defined(__STM32F1__)|| defined(__STM32F4__))

#endif  // DMD_RGB_H

// == MATRIX TYPES ==
// templates were moved to separate file

#ifndef DMD_PANEL_TEMPLATES_H
#include "DMD_Panel_Templates.h"
#endif



