#include "DMD_RGB.h"
static volatile DMD_RGB_BASE *running_dmd_R;
void inline __attribute__((always_inline)) scan_running_dmd_R()

{
	DMD_RGB_BASE *next = (DMD_RGB_BASE*)running_dmd_R;
	next->scan_dmd();
}

void inline __attribute__((always_inline)) oe_disable_R()

{
	DMD_RGB_BASE *next = (DMD_RGB_BASE*)running_dmd_R;
	next->oe_disable();
}


#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

DMD_RGB_BASE::DMD_RGB_BASE(byte mux_cnt, uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
	byte panelsWide, byte panelsHigh, bool d_buf, uint8_t col_depth, uint8_t n_Rows, byte dmd_pixel_x, byte dmd_pixel_y)
	: DMD(mux_list[0], mux_list[1], _pin_nOE, _pin_SCLK, panelsWide, panelsHigh, d_buf, dmd_pixel_x, dmd_pixel_y),  nRows(n_Rows), nPlanes(col_depth)
{
	muxsetreg = portSetRegister(pin_DMD_A);
	muxclrreg = portClearRegister(pin_DMD_A);
	
	fast_Hbyte = true;
	
	if (mux_cnt > 2) {
		pin_DMD_C = mux_list[2];
		digitalWrite(pin_DMD_C, LOW);
		pinMode(pin_DMD_C, OUTPUT);
		addrcmask = digitalPinToBitMask(pin_DMD_C);
	}

	if (mux_cnt > 3) {
		pin_DMD_D = mux_list[3];
		digitalWrite(pin_DMD_D, LOW);
		pinMode(pin_DMD_D, OUTPUT);
		addrdmask = digitalPinToBitMask(pin_DMD_D);
	}

	if (mux_cnt > 4) {
		pin_DMD_E = mux_list[4];
		digitalWrite(pin_DMD_E, LOW);
		pinMode(pin_DMD_E, OUTPUT);
		addremask = digitalPinToBitMask(pin_DMD_E);
	}
	
	
	latsetreg = portSetRegister(pin_DMD_SCLK);
	latclrreg = portClearRegister(pin_DMD_SCLK);
	oesetreg = portSetRegister(pin_DMD_nOE);
	oeclrreg = portClearRegister(pin_DMD_nOE);
	
	byte clk_pin = pinlist[0];
	datasetreg = portSetRegister(clk_pin);
	dataclrreg = portClearRegister(clk_pin);
	clk_clrmask = clkmask = digitalPinToBitMask(clk_pin);
	dataport = portOutputRegister(digitalPinToPort(clk_pin));
	pinMode(clk_pin, OUTPUT);
	pinMode(pin_DMD_nOE, OUTPUT);
	memcpy(rgbpins, pinlist + 1, sizeof rgbpins);
	running_dmd_R = this;

	// Allocate and initialize matrix buffer:

	// x3 = 3 bytes holds 4 planes "packed"
	if (nPlanes == 4) mem_Buffer_Size = panelsWide * panelsHigh * DMD_PIXELS_ACROSS * DMD_PIXELS_DOWN * 3 / 2; 
	else if (nPlanes == 1) mem_Buffer_Size = panelsWide * panelsHigh * DMD_PIXELS_ACROSS * DMD_PIXELS_DOWN / 2;
	uint16_t allocsize = (dbuf == true) ? (mem_Buffer_Size * 2) : mem_Buffer_Size;

	mux_mask = (uint16_t*)malloc(nRows * 2);
	matrixbuff[0] = (uint8_t*)malloc(allocsize);
	memset(matrixbuff[0], 0, allocsize);
	// If not double-buffered, both buffers then point to the same address:
	matrixbuff[1] = (dbuf == true) ? &matrixbuff[0][mem_Buffer_Size] : matrixbuff[0];

#if defined(DEBUG2)
	if (!dd_ptr) dd_ptr = (uint16_t*)malloc(200);
#endif	
}


void DMD_RGB_BASE::init(uint16_t scan_interval) {
	// mux mask
	if (nRows == 2) {
		
		mux_mask[0] = addramask;
		mux_mask[1] = addrbmask;
		mux_clrmask = addramask | addrbmask;
	}
	else {
		for (uint8_t i = 0; i < nRows; i++)
		{
			mux_mask[i] = 0;
			if (i & 0x1)   mux_mask[i] |= addramask;
			if (i & 0x2)   mux_mask[i] |= addrbmask;
			if (i & 0x4)   mux_mask[i] |= addrcmask;

			if (nRows > 8) {
				if (i & 0x8)   mux_mask[i] |= addrdmask;
			}
			if (nRows > 16) {
				if (i & 0x10)   mux_mask[i] |= addremask;
			}
		}
		mux_clrmask = addramask | addrbmask | addrcmask;
		if (nRows > 8) {
			mux_clrmask |= addrdmask;
		}
		if (nRows > 16) {
			mux_clrmask |= addremask;
		}
	}


	PortType rgbmask[6];
	
	for (uint8_t i = 0; i < 6; i++) {
		pinMode(rgbpins[i], OUTPUT);
		rgbmask[i] = digitalPinToBitMask(rgbpins[i]); // Pin bit mask
		clk_clrmask |= rgbmask[i];                      // Add to RGB+CLK bit mask
	}
	for (int i = 0; i < 256; i++) {
		expand[i] = 0;
		if (i & 0x04) expand[i] |= rgbmask[0];
		if (i & 0x08) expand[i] |= rgbmask[1];
		if (i & 0x10) expand[i] |= rgbmask[2];
		if (i & 0x20) expand[i] |= rgbmask[3];
		if (i & 0x40) expand[i] |= rgbmask[4];
		if (i & 0x80) expand[i] |= rgbmask[5];
		expand[i] |= clkmask;
	}

	plane = nPlanes - 1;
	row = nRows - 1;
	swapflag = false;
	backindex = 0;     // Array index of back buffer
	buffptr = matrixbuff[1 - backindex]; // -> front buffer
	
    Timer4.pause(); 
	Timer4.setPeriod(scan_interval); 
	Timer4.attachInterrupt(TIMER_UPDATE_INTERRUPT, scan_running_dmd_R); 
	Timer4.refresh(); 
	Timer4.resume(); 

	clearScreen(true);
	// default text colors - green on black
	textcolor = Color888(0,255,0); 
	textbgcolor = 0;
}


void DMD_RGB_BASE::oe_disable() {
	*oeport |= oemask;
	Timer4.detachInterrupt(TIMER_CC1_INTERRUPT);
}

void DMD_RGB_BASE::scan_dmd() {
	//uint8_t  i, tick, tock;
	uint16_t t, duration;
	volatile uint8_t* ptr;
	// Calculate time to next interrupt BEFORE incrementing plane #.
	// This is because duration is the display time for the data loaded
	// on the PRIOR interrupt.  CALLOVERHEAD is subtracted from the
	// result because that time is implicit between the timer overflow
	// (interrupt triggered) and the initial LEDs-off line at the start
	// of this method.
#if defined(__STM32F1__)
#define CALLOVERHEAD 150  
#define LOOPTIME     2400
#endif
	t = (nRows > 8) ?   LOOPTIME : (LOOPTIME * 2);

	if (plane > 0) duration = ((t + CALLOVERHEAD * 2) << (plane -1)) ;
	else  duration = (t + CALLOVERHEAD * 2);
	

#if defined(__STM32F1__)
	Timer4.pause();
	Timer4.setOverflow(duration);
	if ((plane == 0) && (nPlanes > 1)) {
		Timer4.setCompare1(duration / 2);
		Timer4.attachInterrupt(TIMER_CC1_INTERRUPT, oe_disable_R);
	}
	Timer4.refresh();
	Timer4.resume();
	
#endif
	// Borrowing a technique here from Ray's Logic:
  // www.rayslogic.com/propeller/Programming/AdafruitRGB/AdafruitRGB.htm
  // This code cycles through all four planes for each scanline before
  // advancing to the next line.  While it might seem beneficial to
  // advance lines every time and interleave the planes to reduce
  // vertical scanning artifacts, in practice with this panel it causes
  // a green 'ghosting' effect on black pixels, a much worse artifact.


	
	*oesetreg = oemask; // Disable LED output during row/plane switchover
	
	// For OneBitColor set mux BEFORE changing row
	if (nPlanes == 1) {
		// Plane 0 was loaded on prior interrupt invocation and is about to
		// latch now, so update the row address lines before we do that:

		*muxclrreg = mux_clrmask; // Clear all mux channels
		*muxsetreg = mux_mask[row];
	
	}




	
	if (++plane >= nPlanes) {      // Advance plane counter.  Maxed out?
		plane = 0;                  // Yes, reset to plane 0, and
		if (++row >= nRows) {        // advance row counter.  Maxed out?
			row = 0;              // Yes, reset row counter, then...
			if (swapflag == true) {    // Swap front/back buffers if requested
				backindex = 1 - backindex;
				swapflag = false;
			}
			buffptr = matrixbuff[1 - backindex] ; // Reset into front buffer
			
		}
	}
	

	// For 4bit Color set mux at 1st Plane
	else if (plane == 1) {
		// Plane 0 was loaded on prior interrupt invocation and is about to
		// latch now, so update the row address lines before we do that:

		*muxclrreg = mux_clrmask; // Clear all mux channels
		*muxsetreg = mux_mask[row];
	
	}

	// buffptr, being 'volatile' type, doesn't take well to optimization.
	// A local register copy can speed some things up:
	ptr = buffptr;
	
	*latsetreg = latmask; // Latch data loaded during *prior* interrupt
    *latclrreg = latmask; // Latch down
	*oeclrreg = oemask;   // Re-enable output

	if ((plane > 0) || (nPlanes == 1)) {
		
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
		
	}
	else { // 920 ticks from TCNT1=0 (above) to end of function
		
		for (int i = 0; i < x_len; i++) {
			byte b =
				(ptr[i] << 6) |
				((ptr[i + x_len] << 4) & 0x30) |
				((ptr[i + x_len * 2] << 2) & 0x0C);
#if defined(__STM32F1__)
			*dataclrreg = clk_clrmask; // Clear all data and clock bits together
			*datasetreg = expand[b];  // Set new data bits
			
		}
		*dataclrreg = clkmask;      // Set clock low
		
#endif
		
	}

#if defined(DEBUG3)
	if (dd_cnt < 100) dd_ptr[dd_cnt++] = plane;
	if (dd_cnt < 100) dd_ptr[dd_cnt++] = Timer4.getCount();
#endif	
	
}



void DMD_RGB_BASE::fillScreen(uint16_t c) {
	if ((c == 0x0000) || (c == 0xffff)) {
		// For black or white, all bits in frame buffer will be identically
		// set or unset (regardless of weird bit packing), so it's OK to just
		// quickly memset the whole thing:
		memset(matrixbuff[backindex], c, WIDTH * nRows * 3);
	}
	else {
		// Otherwise, need to handle it the long way:
		Adafruit_GFX::fillScreen(c);
	}
}

void DMD_RGB_BASE::clearScreen(byte bNormal) {
	fillScreen(0x0000);
}
void DMD_RGB_BASE::shiftScreen(int8_t step) {
	uint8_t* ptr = matrixbuff[backindex];
	uint8_t mm = 0;
	
	if (step < 0) {

		for (uint16_t i = 0; i < mem_Buffer_Size;i++) {
			if ((i % WIDTH) == (WIDTH - 1)) {
				ptr[i] = mm;
			}
			else {
				ptr[i] = ptr[i+1];
			}
		}
		drawFastVLine(WIDTH - 1, 0, HEIGHT, textbgcolor);
	}
	else if (step > 0) {
		for (uint16_t i = (mem_Buffer_Size)-1; i > 0;i--) {
			if ((i % WIDTH) == 0) {
				ptr[i] = mm;
			}
			else {
				ptr[i] = ptr[i - 1];
			}
		}
		ptr[0] = mm;
		drawFastVLine(0, 0, HEIGHT, textbgcolor);
	}

} 


/**************************************************************************/
/*!
   @brief    Draw a perfectly vertical line (this is often optimized in a subclass!)
	@param    x   Top-most x coordinate
	@param    y   Top-most y coordinate
	@param    h   Height in pixels
   @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void DMD_RGB_BASE::drawFastVLine(int16_t x, int16_t y,
	int16_t h, uint16_t color) {
	for (uint16_t yy = 0; yy < h; yy++) {
		drawPixel(x, y + yy, color);
	}
}

/**************************************************************************/
/*!
   @brief    Draw a perfectly horizontal line (this is often optimized in a subclass!)
	@param    x   Left-most x coordinate
	@param    y   Left-most y coordinate
	@param    w   Width in pixels
   @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/

void DMD_RGB_BASE::drawFastHLine(int16_t x, int16_t y,
	int16_t w, uint16_t color) {
	
	if (w <= 0) return;

	if (fast_Hbyte) {
		uint8_t fg_col_bytes[3];
		getColorBytes(fg_col_bytes, color);
		drawHByte(x, y, 255, w, fg_col_bytes, fg_col_bytes);

	}
	else {
		for (uint16_t xx = 0; xx < w; xx++) {
			drawPixel(x + xx, y, color);
		}
	}
}

// Promote 3/3/3 RGB to Adafruit_GFX 5/6/5
uint16_t DMD_RGB_BASE::Color333(uint8_t r, uint8_t g, uint8_t b) {
	// RRRrrGGGgggBBBbb
	return ((r & 0x7) << 13) | ((r & 0x6) << 10) |
		((g & 0x7) << 8) | ((g & 0x7) << 5) |
		((b & 0x7) << 2) | ((b & 0x6) >> 1);
}

// Promote 4/4/4 RGB to Adafruit_GFX 5/6/5
uint16_t DMD_RGB_BASE::Color444(uint8_t r, uint8_t g, uint8_t b) {
	// RRRRrGGGGggBBBBb
	return ((r & 0xF) << 12) | ((r & 0x8) << 8) |
		((g & 0xF) << 7) | ((g & 0xC) << 3) |
		((b & 0xF) << 1) | ((b & 0x8) >> 3);
}

// Demote 8/8/8 to Adafruit_GFX 5/6/5
// If no gamma flag passed, assume linear color
uint16_t DMD_RGB_BASE::Color888(uint8_t r, uint8_t g, uint8_t b) {
	return ((uint16_t)(r & 0xF8) << 8) | ((uint16_t)(g & 0xFC) << 3) | (b >> 3);
}

void DMD_RGB_BASE::dumpMatrix(void) {

	int i, buffsize = WIDTH * nRows * 3;

	Serial.print(F("\n\n"
		"#include <avr/pgmspace.h>\n\n"
		"static const uint8_t PROGMEM img[] = {\n  "));

	for (i = 0; i < buffsize; i++) {
		Serial.print(F("0x"));
		if (matrixbuff[backindex][i] < 0x10) Serial.write('0');
		Serial.print(matrixbuff[backindex][i], HEX);
		if (i < (buffsize - 1)) {
			if ((i & 7) == 7) Serial.print(F(",\n  "));
			else             Serial.write(',');
		}
	}
	Serial.println(F("\n};"));
	
}

void DMD_RGB_BASE::dumpMask(void) {

	for (uint8_t i = 0; i < 6; i++) {
		Serial.print(F("i: "));Serial.print(i);
		Serial.print(F(" Pin: "));Serial.print(rgbpins[i]);
		PortType mask = digitalPinToBitMask(rgbpins[i]);
		Serial.print(F(" Mask 0x"));Serial.println(mask, HEX);

	}
	for (uint8_t i = 0; i < nRows; i++)
	{
		Serial.print(F("mux: "));Serial.print(i);

		Serial.print(F(" Mask 0x"));Serial.println(mux_mask[i], HEX);
	}


	Serial.print(F(" CLK Mask 0x"));Serial.println(clkmask, HEX);


}

DMD_RGB_BASE::~DMD_RGB_BASE()
{
	free(matrixbuff[0]);
	free(mux_mask);
#if defined(DEBUG2)
	free((uint16_t*)dd_ptr);
#endif	

}
