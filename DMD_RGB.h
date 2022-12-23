#pragma once

#include "DMD_STM32a.h"
#if (defined(__STM32F1__))
#include <dma_private.h>
#endif
/*#if (defined(ARDUINO_ARCH_RP2040))
#include <hardware/irq.h>
#include <hardware/pwm.h>
#include <hardware/dma.h>
#include <hardware/gpio.h>
#include <pico/stdlib.h> 
#include "dmd_out.pio.h"
#endif*/

/*--------------------------------------------------------------------------------------
 DMD_RGB.h  - part of the library DMD_STM32

 DMD_STM32.h  - STM32 port of DMD.h library

 adapted by Dmitry Dmitriev (c) 2019-2022

 =======  based on =========

 * RGBmatrixPanel.h
 *
 * Adafruit's RGB LED Matrix Panel library
 * for the Arduino platform.
 *
 * Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon for
 * Adafruit Industries.
 */

 // == MATRIX TYPES ==
 // = matrices with plain pattern =
#define RGB64x64plainS32 1			// 64x64 1/32
#define RGB80x40plainS20 2			// 80x40 1/20
#define RGB64x32plainS16 3			// 64x32 1/16
#define RGB32x32plainS16 20			// 32x32 1/16
#define RGB32x32plainS8 21			// 32x32 1/8   near plain pattern
#define RGB32x16plainS8 4			// 32x16 1/8
#define RGB32x16plainS4 5			// 32x16 1/4
#define RGB32x16plainS2 6			// 32x16 1/2
#define RGB32x16plainS4_DIRECT 17	// 32x16 1/4 DIRECT mux
#define RGB128x64plainS32 16		// 128x64 1/32

// = complex pattern matrices =
#define RGB32x16_S4 7               // 32x16 1/4 ZIGGII pattern matrix, BINARY mux
#define RGB32x16_S4_bilalibrir 10   // 32x16 1/4 ZAGGIZ pattern, DIRECT mux
#define RGB32x16_S2 8               // 32x16 1/2 complex pattern, DIRECT mux
#define RGB32x16_S2_quangli 9       // 32x16 1/2 complex pattern, DIRECT mux

// COLOR DEPTH
#if (defined(__STM32F1__)|| defined(__STM32F4__)) 
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

	virtual void scan_dmd();
#if (defined(__STM32F1__) || defined(__STM32F4__))
	virtual void initialize_timers(voidFuncPtr handler) override;
#endif
	
	
	void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) override;
	void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) override;

	uint16_t
		Color333(uint8_t r, uint8_t g, uint8_t b),
		Color444(uint8_t r, uint8_t g, uint8_t b),
		Color888(uint8_t r, uint8_t g, uint8_t b);
	
	

#if defined(DEBUG2)
	//void dumpMatrix(void);
	void dumpMask(void);
#endif

	~DMD_RGB_BASE();

protected:

#if (defined(__STM32F1__) || defined(__STM32F4__))
	virtual void generate_rgbtable() { generate_rgbtable_default(CLK_WITH_DATA); }
	void generate_rgbtable_default(uint8_t options);
	void send_to_allRGB(uint16_t data, uint16_t latches);
	virtual void chip_init() {};	
#endif
	virtual void setCycleLen();
	virtual uint16_t get_base_addr(int16_t x, int16_t y);
	virtual void drawHByte(int16_t x, int16_t y, uint8_t hbyte, uint8_t bsize, uint8_t* fg_col_bytes,
		uint8_t* bg_col_bytes) override;
	virtual void getColorBytes(uint8_t* cbytes, uint16_t color) override;

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
			panelsWide, panelsHigh, d_buf, COLOR_1BITS, n_Rows, dmd_pixel_x, dmd_pixel_y)
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
			panelsWide, panelsHigh, d_buf, COLOR_4BITS, n_Rows, dmd_pixel_x, dmd_pixel_y)
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
			panelsWide, panelsHigh, d_buf, COLOR_4BITS_Packed, n_Rows, dmd_pixel_x, dmd_pixel_y)
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
	void scan_dmd() {

		uint16_t duration;
		uint32_t oe_duration;
		volatile uint8_t* ptr;

		// Calculate time to next interrupt BEFORE incrementing plane #.
		// This is because duration is the display time for the data loaded
		// on the PRIOR interrupt.  CALLOVERHEAD is subtracted from the
		// result because that time is implicit between the timer overflow
		// (interrupt triggered) and the initial LEDs-off line at the start
		// of this method.
		if (this->plane > 0) duration = ((this->scan_cycle_len) << (this->plane - 1));
		else  duration = this->scan_cycle_len;

		if ((this->plane > 0) || (nPlanes == 1)) oe_duration = (duration * this->brightness) / 255;
		else oe_duration = ((duration * this->brightness) / 255) / 2;

#if (defined(__STM32F1__) || defined(__STM32F4__))
		timer_pause(MAIN_TIMER);
		timer_set_reload(MAIN_TIMER, (duration - this->callOverhead) );

		timer_pause(OE_TIMER);
		timer_set_reload(OE_TIMER, (duration + this->callOverhead *10) );
		

#endif
		// Borrowing a technique here from Ray's Logic:
	  // www.rayslogic.com/propeller/Programming/AdafruitRGB/AdafruitRGB.htm
	  // This code cycles through all four planes for each scanline before
	  // advancing to the next line.  While it might seem beneficial to
	  // advance lines every time and interleave the planes to reduce
	  // vertical scanning artifacts, in practice with this panel it causes
	  // a green 'ghosting' effect on black pixels, a much worse artifact.

		if (++plane >= nPlanes) {      // Advance plane counter.  Maxed out?
			plane = 0;                  // Yes, reset to plane 0, and
			if (++row >= nRows) {        // advance row counter.  Maxed out?
				row = 0;              // Yes, reset row counter, then...
				if (swapflag == true) {    // Swap front/back buffers if requested
					backindex = 1 - backindex;
					swapflag = false;
				}
			}
			buffptr = matrixbuff[1 - backindex]; // Reset into front buffer
			buffptr += row * x_len;
		}

		// For 4bit Color set mux at 1st Plane
		else if (plane == 1) {

			set_mux(row);
		}

		// buffptr, being 'volatile' type, doesn't take well to optimization.
		// A local register copy can speed some things up:
		ptr = buffptr;
#if (defined(__STM32F1__) || defined(__STM32F4__))
		* latsetreg = latmask; // Latch data loaded during *prior* interrupt
		*latsetreg = latmask << 16;// Latch down

		timer_set_compare(OE_TIMER, oe_channel, oe_duration);
		timer_set_count(MAIN_TIMER, 0);
		timer_set_count(OE_TIMER, 0);
		timer_generate_update(MAIN_TIMER);
		timer_generate_update(OE_TIMER);
		timer_resume(OE_TIMER);
		timer_resume(MAIN_TIMER);

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
#endif
#if defined(DEBUG3)
		if (dd_cnt < 100) dd_ptr[dd_cnt++] = plane;
		if (dd_cnt < 100) dd_ptr[dd_cnt++] = timer_get_count(MAIN_TIMER);
#endif	
	}

#undef pew


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
	void drawHByte(int16_t x, int16_t y, uint8_t hbyte, uint8_t bsize, uint8_t* fg_col_bytes,
		uint8_t* bg_col_bytes) override {

		static uint8_t ColorByteMask[] = { B00000111 , B01000111 , B11000111 ,
											  B11111000 , B10111000 , B00111000 };
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
		if ((x < 0) || (x >= WIDTH) || (y < 0) || (y >= HEIGHT)) return;

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
#endif
/*--------------------------------------------------------------------------------------*/
template <int MATRIX_TYPE, int COL_DEPTH>

class DMD_RGB : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB() = 0;
};
/*--------------------------------------------------------------------------------------*/
// Matrix types templates
template<int COL_DEPTH>
class DMD_RGB<RGB64x64plainS32, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(5, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 32, 64, 64)
	{}
};
/*--------------------------------------------------------------------------------------*/
template<int COL_DEPTH>
class DMD_RGB<RGB80x40plainS20, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(5, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 20, 80, 40)
	{}

};
/*--------------------------------------------------------------------------------------*/
template<int COL_DEPTH>
class DMD_RGB<RGB64x32plainS16, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(4, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 16, 64, 32)
	{}

};
/*--------------------------------------------------------------------------------------*/
template<int COL_DEPTH>
class DMD_RGB<RGB32x32plainS16, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(4, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 16, 32, 32)
	{}

};

/*--------------------------------------------------------------------------------------*/
// p6 32x32 scan 8 matrix from @maxmurugan 
// plain pattern with consecutive bytes in horizontal lines
// lower row first
template<int COL_DEPTH>
class DMD_RGB<RGB32x32plainS8, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(3, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 8, 32, 32)
	{}
protected:
	uint16_t get_base_addr(int16_t x, int16_t y) override {
		this->transform_XY(x, y);
		uint8_t pol_y = y % this->pol_displ;
		x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
		uint16_t base_addr = (pol_y % this->nRows) * this->x_len + 
			(x / this->DMD_PIXELS_ACROSS) * this->multiplex * this->DMD_PIXELS_ACROSS;
		if (pol_y / this->nRows)  base_addr += x % this->DMD_PIXELS_ACROSS;
		else   base_addr += x % this->DMD_PIXELS_ACROSS + this->DMD_PIXELS_ACROSS;
		return base_addr;
	}

};
/*--------------------------------------------------------------------------------------*/
template<int COL_DEPTH>
class DMD_RGB<RGB32x16plainS8, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(3, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 8, 32, 16)
	{}

};
/*--------------------------------------------------------------------------------------*/
// "plain" type 1/4 scan matrix, BINARY mux
// with consecutive bytes in horizontal lines 
// left for testing
template<int COL_DEPTH>
class DMD_RGB<RGB32x16plainS4, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(2, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 4, 32, 16)
	{}

protected:
	uint16_t get_base_addr(int16_t x, int16_t y) override {
		this->transform_XY(x, y);
		uint8_t pol_y = y % this->pol_displ;
		x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
		uint16_t base_addr = (pol_y / this->multiplex) * this->x_len +
			(x / this->DMD_PIXELS_ACROSS) * this->multiplex * this->DMD_PIXELS_ACROSS +
			(pol_y % this->multiplex) *  this->DMD_PIXELS_ACROSS + x % this->DMD_PIXELS_ACROSS;
		return base_addr;
	}
};
/*--------------------------------------------------------------------------------------*/
// "plain" type 1/4 scan matrix, DIRECT mux
// with consecutive bytes in horizontal lines 
// left for testing
template<int COL_DEPTH>
class DMD_RGB<RGB32x16plainS4_DIRECT, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(4, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 4, 32, 16)
	{}

protected:
	uint16_t get_base_addr(int16_t x, int16_t y) override {
		this->transform_XY(x, y);
		uint8_t pol_y = y % this->pol_displ;
		x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
		uint16_t base_addr = (pol_y / this->multiplex) * this->x_len +
			(x / this->DMD_PIXELS_ACROSS) * this->multiplex * this->DMD_PIXELS_ACROSS +
			(pol_y % this->multiplex) * this->DMD_PIXELS_ACROSS + x % this->DMD_PIXELS_ACROSS;
		return base_addr;
	}
};
/*--------------------------------------------------------------------------------------*/
// 1/4 matrix I have
//
// with pattern   [1H|1L] [3H|3L] 
//                   |   *   |             
//                [0L|0H] [2L|2H]   
// and BINARY mux

template<int COL_DEPTH>
class DMD_RGB<RGB32x16_S4, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
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
		uint16_t base_addr = (pol_y % this->nRows) * this->x_len + (x / 8) * this->multiplex * 8;
		if (pol_y / this->nRows) base_addr += x % 8;
		else base_addr += (15 - x % 8);
		return base_addr;
	}
};
/*--------------------------------------------------------------------------------------*/
// 1/4 matrix from Bilal Ibrir
//
// with pattern   [0H|0L] [2H|2L] 
//                   |   /   |   /           
//                [1L|1H] [3L|3H]   
// and DIRECT mux

template<int COL_DEPTH>
class DMD_RGB< RGB32x16_S4_bilalibrir, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(4, mux_list, _pin_nOE, _pin_SCLK, pinlist,
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
		uint16_t base_addr = (pol_y % this->nRows) * this->x_len + (x / 8) * this->multiplex * 8;
		if (pol_y / this->nRows) base_addr += 8 + x % 8;
		else base_addr += (7 - x % 8);
		return base_addr;
	}

};
/*--------------------------------------------------------------------------------------*/
// "plain" type 1/2 scan matrix  
// with consecutive bytes in horizontal lines and DIRECT  mux
// left for testing
template<int COL_DEPTH>
class DMD_RGB<RGB32x16plainS2, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(2, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 2, 32, 16)
	{}

protected:
	uint16_t get_base_addr(int16_t x, int16_t y) override {
		this->transform_XY(x, y);
		uint8_t pol_y = y % this->pol_displ;
		x += (y / this->DMD_PIXELS_DOWN) * this->WIDTH;
		uint16_t base_addr = (pol_y / this->multiplex) * this->x_len +
			(x / this->DMD_PIXELS_ACROSS) * this->multiplex * this->DMD_PIXELS_ACROSS +
			(pol_y % this->multiplex) * this->DMD_PIXELS_ACROSS + x % this->DMD_PIXELS_ACROSS;
		return base_addr;
	}
};
/*--------------------------------------------------------------------------------------*/
// 1/2 matrix I have
//
// with pattern   [0H|0L]     [4H|4L] 
//                   |       /   |              
//                [1L|1H]   / [5L|5H]   
//                   |     /     |
//                [2H|2L] /   [6H|6L] 
//                   |   /       |   /           
//                [3L|3H]     [7L|7H]   
// and DIRECT mux

template<int COL_DEPTH>
class DMD_RGB<RGB32x16_S2, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(2, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 2, 32, 16)
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
		uint16_t base_addr = (pol_y % this->nRows) * this->x_len + (x / 8) * this->multiplex * 8 + (pol_y / this->nRows) * 8;
		if (((pol_y / this->nRows) % 2) == 0) { base_addr += (7 - x % 8); }
		else base_addr += x % 8;
		return base_addr;
	}

};
/*--------------------------------------------------------------------------------------*/
// 1/2 matrix from quangli with two-byte pattern
// DIRECT mux
template<int COL_DEPTH>
class DMD_RGB<RGB32x16_S2_quangli, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(2, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 2, 32, 16)
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
		uint16_t base_addr = (pol_y % this->nRows) * this->x_len + (x / 16) * this->multiplex * 16;
		switch (pol_y / this->nRows) {
		case 0: base_addr += 32; break;
		case 1: base_addr += 40; break;
		case 2:  break;
		case 3: base_addr += 8; break;
		}

		if (x % 16 > 7) base_addr += 16 + x % 8;
		else base_addr += x % 8;
		return base_addr;
	}

};
/*--------------------------------------------------------------------------------------*/
template<int COL_DEPTH>
class DMD_RGB<RGB128x64plainS32, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(5, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, false, COL_DEPTH, 32, 128, 64)
	{}

};
/*--------------------------------------------------------------------------------------*/
template <int MATRIX_TYPE, int COL_DEPTH>
class DMD_RGB_SHIFTREG_ABC : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB_SHIFTREG_ABC() = 0;
};
/*--------------------------------------------------------------------------------------*/
template<int COL_DEPTH>
class DMD_RGB_SHIFTREG_ABC<RGB128x64plainS32, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB_SHIFTREG_ABC(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(3, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, false, COL_DEPTH, 32, 128, 64)
	{}

protected:
	void set_mux(uint8_t curr_row) override {
		// Just shift the row mux by one for incremental access
		digitalWrite(this->pin_DMD_B, HIGH);
		digitalWrite(this->pin_DMD_C, (curr_row == 0)); // Shift out 1 for line 0, 0 otherwise
		digitalWrite(this->pin_DMD_A, HIGH); // Clock out this bit
		digitalWrite(this->pin_DMD_A, LOW);
		digitalWrite(this->pin_DMD_B, LOW);
	}

};



