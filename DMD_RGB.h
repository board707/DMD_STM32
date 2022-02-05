#pragma once
#include <dma_private.h>
#include "DMD_STM32a.h"
// MATRIX TYPES
#define RGB64x64plainS32 1
#define RGB80x40plainS20 2
#define RGB64x32plainS16 3
#define RGB32x16plainS8 4
#define RGB32x16plainS4 5
#define RGB32x16plainS2 6

#define RGB128x64plainS32 16


//#define RGB32x16_S4 7
//#define RGB32x16_S2 8
//#define RGB32x16_S2_quangli 9

// COLOR DEPTH
#define COLOR_4BITS		4
#define COLOR_1BITS		1

// RGB TABLE OPTIONS
#define CLK_WITH_DATA   0x1
#define CLK_AFTER_DATA   0

//void inline __attribute__((always_inline)) scan_running_dmd_R();

class DMD_RGB_BASE :
	public DMD
{
public:

	DMD_RGB_BASE(byte mux_cnt, uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf, uint8_t col_depth, uint8_t n_Rows, byte dmd_pixel_x, byte dmd_pixel_y);

	void init(uint16_t scan_interval = 700) override ;
	virtual void drawPixel(int16_t x, int16_t y, uint16_t color) =0 ;
	
	virtual void scan_dmd();
	
	virtual void generate_muxmask();
	virtual void generate_rgbtable() { generate_rgbtable_default(CLK_WITH_DATA); }
	void generate_rgbtable_default(uint8_t options);
	virtual void initialize_timers(uint16_t scan_interval);
	virtual void setCycleLen();
	void send_to_allRGB(uint16_t data, uint16_t latches);
	
	virtual void chip_init() {};
	
	void clearScreen(byte bNormal) override;
	void shiftScreen(int8_t step) override;
	virtual void set_mux(uint8_t curr_row);
	
	void fillScreen(uint16_t color) override;
	void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) override;
	void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) override;
	
	virtual void drawHByte(int16_t x, int16_t y, uint8_t hbyte, uint8_t bsize, uint8_t* fg_col_bytes,
		uint8_t* bg_col_bytes) = 0;
	virtual void getColorBytes(uint8_t* cbytes, uint16_t color) = 0;
	uint16_t
		Color333(uint8_t r, uint8_t g, uint8_t b),
		Color444(uint8_t r, uint8_t g, uint8_t b),
		Color888(uint8_t r, uint8_t g, uint8_t b);

	void setBrightness(uint8_t level) override {
		this->brightness = level;
	};
	

#if defined(DEBUG2)
	//void dumpMatrix(void);
	void dumpMask(void);
#endif

	~DMD_RGB_BASE();
	
protected:
	byte pin_DMD_C;
	byte pin_DMD_D;
	byte pin_DMD_E;
	byte rgbpins[6];
	
	// Pin bitmasks
	PortType clk_clrmask, clkmask, addrcmask, addrdmask, addremask, mux_clrmask, rgbmask_all;
	
	// PORT register pointers 
	volatile PortType  *dataclrreg, *datasetreg, *dataport, *muxclrreg, *muxsetreg;
	volatile PortType *latsetreg, *latclrreg, * oesetreg, * oeclrreg;
	uint16_t           expand[256];           // 6-to-32 bit converter table
	uint16_t          *mux_ch_masks;
	uint16_t           *mux_mask;         // muxmask 
	uint32_t           *mux_mask2;         // muxmask fm6353

	
	// Counters/pointers for interrupt handler:
	volatile uint8_t row, plane;
	volatile uint8_t *buffptr;
	
	const uint8_t nRows = 0;
	const uint8_t nPlanes = 4;
	const uint8_t pol_displ = DMD_PIXELS_DOWN / 2;
	const uint8_t multiplex = pol_displ / nRows;
	const uint16_t x_len = WIDTH * multiplex * DisplaysHigh;

	uint16_t colors[2] = { 0, 0 };
	uint8_t col_cache[6] = { 0 };
	
	uint8_t last_color = 0;
	uint16_t scan_cycle_len = 0;
	
};
template<int COL_DEPTH>
class DMD_RGB_BASE2 : public DMD_RGB_BASE
{

public:
	DMD_RGB_BASE2() = 0;
	
};
template<>
class DMD_RGB_BASE2< COLOR_1BITS> : public DMD_RGB_BASE
{

public:
	DMD_RGB_BASE2(byte mux_cnt, uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf, uint8_t col_depth, uint8_t n_Rows, byte dmd_pixel_x, byte dmd_pixel_y) :
		DMD_RGB_BASE(mux_cnt, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COLOR_1BITS, n_Rows, dmd_pixel_x, dmd_pixel_y)
	{}
#if defined(__STM32F1__)
#define CALLOVERHEAD 100 
#define LOOPTIME     7200
#endif
	void setCycleLen() override {
		this->scan_cycle_len = LOOPTIME;
		if ((this->x_len) > 128) this->scan_cycle_len = ((this->x_len) / 128) * LOOPTIME;
	}
	
	void scan_dmd() override {
		
		uint16_t duration;
		volatile uint8_t* ptr;
		
		// Calculate time to next interrupt BEFORE incrementing plane #.
		// This is because duration is the display time for the data loaded
		// on the PRIOR interrupt.  CALLOVERHEAD is subtracted from the
		// result because that time is implicit between the timer overflow
		// (interrupt triggered) and the initial LEDs-off line at the start
		// of this method.
		duration = this->scan_cycle_len;

#if defined(__STM32F1__)
		timer_pause(MAIN_TIMER);
		timer_set_reload(MAIN_TIMER, duration - CALLOVERHEAD);

		timer_pause(OE_TIMER);
		timer_set_reload(OE_TIMER, duration * 2);

		timer_set_compare(OE_TIMER, this->oe_channel, ((uint32_t)duration * this->brightness) / 255);




#endif
		// Borrowing a technique here from Ray's Logic:
	  // www.rayslogic.com/propeller/Programming/AdafruitRGB/AdafruitRGB.htm
	  // This code cycles through all four planes for each scanline before
	  // advancing to the next line.  While it might seem beneficial to
	  // advance lines every time and interleave the planes to reduce
	  // vertical scanning artifacts, in practice with this panel it causes
	  // a green 'ghosting' effect on black pixels, a much worse artifact.		
		
		//*oesetreg = oemask; // Disable LED output during row/plane switchover
		
		// For OneBitColor set mux BEFORE changing row
	    this->set_mux(row);
	
		
		
		    this->plane = 0;                   // Yes, reset to plane 0, and
			if (++row >= nRows) {        // advance row counter.  Maxed out?
				row = 0;              // Yes, reset row counter, then...
				if (swapflag == true) {    // Swap front/back buffers if requested
					backindex = 1 - backindex;
					swapflag = false;
				}
				buffptr = matrixbuff[1 - backindex]; // Reset into front buffer

			}
		//}
		
	
		// buffptr, being 'volatile' type, doesn't take well to optimization.
		// A local register copy can speed some things up:
		ptr = buffptr;

		*latsetreg = latmask; // Latch data loaded during *prior* interrupt
		*latclrreg = latmask; // Latch down
		
		//*oeclrreg = oemask;   // Re-enable output
	
		timer_set_count(MAIN_TIMER, 0);
		timer_set_count(OE_TIMER, 0);
		timer_generate_update(MAIN_TIMER);
		timer_generate_update(OE_TIMER);
		timer_resume(OE_TIMER);
		timer_resume(MAIN_TIMER);
		


#if defined(__STM32F1__)
#define pew                    \
      *dataclrreg = clk_clrmask;     \
      *datasetreg = expand[*ptr++];

#endif


			for (uint16_t uu = 0; uu < x_len; uu += 8)
			{
				// Loop is unrolled for speed:
				pew pew pew pew pew pew pew pew

			}


#if defined(__STM32F1__)
			*dataclrreg = clkmask; // Set clock low
#endif

			buffptr = ptr; //+= 32;

#if defined(DEBUG3)
		if (dd_cnt < 100) dd_ptr[dd_cnt++] = plane;
		if (dd_cnt < 100) dd_ptr[dd_cnt++] = timer_get_count(MAIN_TIMER);
#endif	

	}

#undef pew
#undef CALLOVERHEAD
#undef LOOPTIME



	void getColorBytes(uint8_t* cbytes, uint16_t color) override {
		uint8_t r, g, b, bit; // limit;
		uint8_t* ptr;

		// special case color = 0
		if (color == 0) {
			cbytes[0] = 0; //cbytes[1] = 0; cbytes[2] = 0;
			return;
		}

		if ((colors[last_color] == color) || (colors[last_color = !last_color] == color)) {
			ptr = col_cache + last_color;
			cbytes[0] = *ptr;
			return;
		}

		ptr = col_cache + last_color;
		colors[last_color] = color;
		ptr[0] = 0; 

		// Adafruit_GFX uses 16-bit color in 5/6/5 format, while matrix needs
			// 4/4/4.  Pluck out relevant bits while separating into R,G,B:

		uint16_t c = color;
		r = c >> 12;        // RRRRrggggggbbbbb
		g = (c >> 7) & 0xF; // rrrrrGGGGggbbbbb
		b = (c >> 1) & 0xF; // rrrrrggggggBBBBb

		
		//if (nPlanes == 1) {
		
			bit = 8;
			if (r & bit) *ptr |= B00100100; // Plane N R: bit 2
			if (g & bit) *ptr |= B01001000; // Plane N G: bit 3
			if (b & bit) *ptr |= B10010000; // Plane N B: bit 4
		

	    cbytes[0] = *ptr;
		return;


	}

	void drawHByte(int16_t x, int16_t y, uint8_t hbyte, uint8_t bsize, uint8_t* fg_col_bytes,
		uint8_t* bg_col_bytes) override {

		static uint8_t ColorByteMask[] = { B00011100 , B00011101 , B00011111 ,
											  B11100011 , B11100010 , B11100000 };
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
		transform_XY(x, y);
		DEBUG_TIME_MARK;

		uint8_t pol_y = y % pol_displ;

		uint16_t base_addr = 0;

		
		//else if (nPlanes == 1) {
		
			base_addr = (pol_y / multiplex) * x_len +
				(pol_y % multiplex) * WIDTH * DisplaysHigh + (y / DMD_PIXELS_DOWN) * WIDTH * multiplex + x;
			uint8_t* ptr_base = &matrixbuff[backindex][base_addr]; // Base addr


			uint8_t* mask_ptr;
			uint8_t* col_bytes;
			uint8_t* ptr = ptr_base;
			if (y % DMD_PIXELS_DOWN < pol_displ) {
				mask_ptr = ColorByteMask;
			}
			else {

				mask_ptr = ColorByteMask + 5;
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
				ptr = ptr_base + j;
				*ptr &= ~(*mask_ptr);
				*ptr |= col_bytes[0] & *mask_ptr;

			}
		
	}
	void drawPixel(int16_t x, int16_t y, uint16_t c) override {
		uint8_t r, g, b; // bit, limit;
		uint8_t* ptr;

		DEBUG_TIME_MARK_333;
		DEBUG_TIME_MARK;
		if (graph_mode == GRAPHICS_NOR) {
			if (c == textcolor) c = textbgcolor;
			else return;
		}
		if ((x < 0) || (x >= WIDTH) || (y < 0) || (y >= HEIGHT)) return;

		// transform X & Y for Rotate and connect scheme
		transform_XY(x, y);
		DEBUG_TIME_MARK;

		//uint8_t pol_y = y % pol_displ;

		uint16_t base_addr = 0;


		
		//else if (nPlanes == 1) {
		
			// Adafruit_GFX uses 16-bit color in 5/6/5 format, convert to single bits
			// Pluck out relevant bits while separating into R,G,B:
			r = c >> 15;        // RRRRrggggggbbbbb
			g = (c >> 10) & 0x1; // rrrrrGGGGggbbbbb
			b = (c >> 4) & 0x1; // rrrrrggggggBBBBb

			base_addr = (y % nRows) * x_len + (y / DMD_PIXELS_DOWN) * WIDTH + x;
			ptr = &matrixbuff[backindex][base_addr]; // Base addr

			if (y % DMD_PIXELS_DOWN < nRows) {

				*ptr &= ~B00011100;            // Mask out R,G,B in one op
				if (r & 1) *ptr |= B00000100; // Plane N R: bit 2
				if (g & 1) *ptr |= B00001000; // Plane N G: bit 3
				if (b & 1) *ptr |= B00010000; // Plane N B: bit 4

			}
			else {

				*ptr &= ~B11100000;            // Mask out R,G,B in one op
				if (r & 1) *ptr |= B00100000; // Plane N R: bit 5
				if (g & 1) *ptr |= B01000000; // Plane N G: bit 6
				if (b & 1) *ptr |= B10000000; // Plane N B: bit 7

			}
		
	}
};

template<>
class DMD_RGB_BASE2< COLOR_4BITS> : public DMD_RGB_BASE
{

public:
	DMD_RGB_BASE2(byte mux_cnt, uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf, uint8_t col_depth, uint8_t n_Rows, byte dmd_pixel_x, byte dmd_pixel_y) :
		DMD_RGB_BASE(mux_cnt, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COLOR_4BITS, n_Rows, dmd_pixel_x, dmd_pixel_y)
	{}
	
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
		
			if (r & 1) { ptr[1] |= B00000010; ptr[2] |= B00000001; }
			if (g & 1) { *ptr |= B00000001; ptr[2] |= B00000010; }// Plane 0 G: bit 0
			if (b & 1) { *ptr |= B00000010; ptr[1] |= B00000001; }// Plane 0 B: bit 0


			limit = 1 << nPlanes;
			bit = 2;
			for (; bit < limit; bit <<= 1) {
				// Mask out R,G,B in one op
				if (r & bit) *ptr |= B00100100; // Plane N R: bit 2
				if (g & bit) *ptr |= B01001000; // Plane N G: bit 3
				if (b & bit) *ptr |= B10010000; // Plane N B: bit 4

				ptr++;                 // Advance to next bit plane
			}
			ptr -= 3;

		
		memcpy(cbytes, ptr, 3); return;


	}

	void drawHByte(int16_t x, int16_t y, uint8_t hbyte, uint8_t bsize, uint8_t* fg_col_bytes,
		uint8_t* bg_col_bytes) override {

		static uint8_t ColorByteMask[] = { B00011100 , B00011101 , B00011111 ,
											  B11100011 , B11100010 , B11100000 };
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
		transform_XY(x, y);
		DEBUG_TIME_MARK;

		uint8_t pol_y = y % pol_displ;

		uint16_t base_addr = 0;

		//if (nPlanes == 4) {
		//if constexpr (COL_DEPTH == 4) {

			base_addr = (pol_y / multiplex) * x_len * (nPlanes - 1) +
				(pol_y % multiplex) * WIDTH * DisplaysHigh + (y / DMD_PIXELS_DOWN) * WIDTH * multiplex + x;
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
				ptr += x_len;
				*ptr &= ~(*mask_ptr);
				*ptr |= (col_bytes[1] & *mask_ptr++);
				ptr += x_len;
				*ptr &= ~(*mask_ptr);
				*ptr |= (col_bytes[2] & *mask_ptr);



			}
			DEBUG_TIME_MARK;

		
		
		
	}

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
		transform_XY(x, y);
		DEBUG_TIME_MARK;

		uint8_t pol_y = y % pol_displ;

		uint16_t base_addr = 0;


		//if (nPlanes == 4) {
		//if constexpr (COL_DEPTH == 4) {

			// Adafruit_GFX uses 16-bit color in 5/6/5 format, while matrix needs
			// 4/4/4.  Pluck out relevant bits while separating into R,G,B:
			r = c >> 12;        // RRRRrggggggbbbbb
			g = (c >> 7) & 0xF; // rrrrrGGGGggbbbbb
			b = (c >> 1) & 0xF; // rrrrrggggggBBBBb

			base_addr = (pol_y / multiplex) * x_len * (nPlanes - 1) +
				(pol_y % multiplex) * WIDTH * DisplaysHigh + (y / DMD_PIXELS_DOWN) * WIDTH * multiplex + x;
			ptr = &matrixbuff[backindex][base_addr]; // Base addr
			DEBUG_TIME_MARK;
			bit = 2;
			limit = 1 << nPlanes;
			if (y % DMD_PIXELS_DOWN < pol_displ) {
				// Data for the upper half of the display is stored in the lower
				// bits of each byte.

				// Plane 0 is a tricky case -- its data is spread about,
				// stored in least two bits not used by the other planes.
				ptr[x_len * 2] &= ~B00000011;           // Plane 0 R,G mask out in one op
				if (r & 1) ptr[x_len * 2] |= B00000001; // Plane 0 R: 64 bytes ahead, bit 0
				if (g & 1) ptr[x_len * 2] |= B00000010; // Plane 0 G: 64 bytes ahead, bit 1
				if (b & 1) ptr[x_len] |= B00000001; // Plane 0 B: 32 bytes ahead, bit 0
				else      ptr[x_len] &= ~B00000001; // Plane 0 B unset; mask out
				// The remaining three image planes are more normal-ish.
				// Data is stored in the high 6 bits so it can be quickly
				// copied to the DATAPORT register w/6 output lines.
				for (; bit < limit; bit <<= 1) {
					*ptr &= ~B00011100;            // Mask out R,G,B in one op
					if (r & bit) *ptr |= B00000100; // Plane N R: bit 2
					if (g & bit) *ptr |= B00001000; // Plane N G: bit 3
					if (b & bit) *ptr |= B00010000; // Plane N B: bit 4
					ptr += x_len;                 // Advance to next bit plane
				}
			}
			else {
				// Data for the lower half of the display is stored in the upper
				// bits, except for the plane 0 stuff, using 2 least bits.

				*ptr &= ~B00000011;                  // Plane 0 G,B mask out in one op
				if (r & 1)  ptr[x_len] |= B00000010; // Plane 0 R: 32 bytes ahead, bit 1
				else       ptr[x_len] &= ~B00000010; // Plane 0 R unset; mask out
				if (g & 1) *ptr |= B00000001; // Plane 0 G: bit 0
				if (b & 1) *ptr |= B00000010; // Plane 0 B: bit 0
				for (; bit < limit; bit <<= 1) {
					*ptr &= ~B11100000;            // Mask out R,G,B in one op
					if (r & bit) *ptr |= B00100000; // Plane N R: bit 5
					if (g & bit) *ptr |= B01000000; // Plane N G: bit 6
					if (b & bit) *ptr |= B10000000; // Plane N B: bit 7
					ptr += x_len;                 // Advance to next bit plane
				}
			}
			DEBUG_TIME_MARK;
		
		
		
	}
};
template <int MATRIX_TYPE, int COL_DEPTH>

class DMD_RGB : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB() = 0;

	
};

// Matrix types templates
template<int COL_DEPTH>
class DMD_RGB<RGB64x64plainS32, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false):
		DMD_RGB_BASE2<COL_DEPTH>(5, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 32, 64, 64)
	{}
};
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

template<int COL_DEPTH>
class DMD_RGB<RGB32x16plainS4, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(2, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 4, 32, 16)
	{}

};

template<int COL_DEPTH>
class DMD_RGB<RGB32x16plainS2, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(2, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, d_buf, COL_DEPTH, 2, 32, 16)
	{}

};

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





template <int MATRIX_TYPE, int COL_DEPTH>
class DMD_RGB_SHIFTREG_ABC : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB_SHIFTREG_ABC() = 0;

	
};
template<int COL_DEPTH>
class DMD_RGB_SHIFTREG_ABC<RGB128x64plainS32, COL_DEPTH> : public DMD_RGB_BASE2<COL_DEPTH>
{
public:
	DMD_RGB_SHIFTREG_ABC(uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
		byte panelsWide, byte panelsHigh, bool d_buf = false) :
		DMD_RGB_BASE2<COL_DEPTH>(3, mux_list, _pin_nOE, _pin_SCLK, pinlist,
			panelsWide, panelsHigh, false, COL_DEPTH, 32, 128, 64)
	{}

	void set_mux(uint8_t curr_row) override {
		// Just shift the row mux by one for incremental access
		digitalWrite(this->pin_DMD_B, HIGH);
		digitalWrite(this->pin_DMD_C, (curr_row == 0)); // Shift out 1 for line 0, 0 otherwise
		digitalWrite(this->pin_DMD_A, HIGH); // Clock out this bit
		digitalWrite(this->pin_DMD_A, LOW);
		digitalWrite(this->pin_DMD_B, LOW);
	}

};
