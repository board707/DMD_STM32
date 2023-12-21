/*--------------------------------------------------------------------------------------
 This file is a part of the library DMD_STM32

 DMD_STM32.h  - STM32 port of DMD.h library

 https://github.com/board707/DMD_STM32
 Dmitry Dmitriev (c) 2019-2023
 /--------------------------------------------------------------------------------------*/
#include "DMD_RGB.h"

static volatile DMD_RGB_BASE* running_dmd_R;
void inline __attribute__((always_inline)) scan_running_dmd_R()

{
	DMD_RGB_BASE* next = (DMD_RGB_BASE*)running_dmd_R;
	next->scan_dmd();
}

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

DMD_RGB_BASE::DMD_RGB_BASE(byte mux_cnt, uint8_t* mux_list, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
	byte panelsWide, byte panelsHigh, bool d_buf, uint8_t col_depth, uint8_t n_Rows, byte dmd_pixel_x, byte dmd_pixel_y)
	: DMD(new DMD_Pinlist(mux_cnt, mux_list), _pin_nOE, _pin_SCLK, panelsWide, panelsHigh, n_Rows, 
		new DMD_Pinlist(7, pinlist), d_buf, dmd_pixel_x, dmd_pixel_y), nPlanes(col_depth)
{

	fast_Hbyte = true;
	rgbpins = data_pins;
	running_dmd_R = this;
	OE_polarity = OE_PWM_NEGATIVE;

	// Allocate and initialize matrix buffer:
	mem_Buffer_Size = panelsWide * panelsHigh * DMD_PIXELS_ACROSS * DMD_PIXELS_DOWN * nPlanes / 2;
	col_bytes_cnt = nPlanes;
	// x3 = 3 bytes holds 4 planes "packed"
	if (nPlanes == 3) nPlanes = 4;
	
	uint32_t allocsize = (dbuf == true) ? (mem_Buffer_Size * 2ul) : mem_Buffer_Size;
	matrixbuff[0] = (uint8_t*)malloc(allocsize);
	memset(matrixbuff[0], 0, allocsize);
	// If not double-buffered, both buffers then point to the same address:
	matrixbuff[1] = (dbuf == true) ? &matrixbuff[0][mem_Buffer_Size] : matrixbuff[0];
	plane = nPlanes - 1;
	row = nRows - 1;
	swapflag = false;
	backindex = 0;     // Array index of back buffer
	buffptr = matrixbuff[1 - backindex]; // -> front buffer
	x_len = WIDTH * multiplex * DisplaysHigh;
	// default text colors - green on black
	textcolor = Color888(0, 255, 0);
	textbgcolor = 0;

}
/*--------------------------------------------------------------------------------------*/
#if (defined(__STM32F1__) || defined(__STM32F4__))
void DMD_RGB_BASE::generate_rgbtable_default(uint8_t options) {

	PortType rgbmask[6];
	rgbmask_all = 0;

	for (uint8_t i = 0; i < 6; i++) {
		pinMode(rgbpins[i], OUTPUT);
		rgbmask[i] = digitalPinToBitMask(rgbpins[i]); // Pin bit mask
		clk_clrmask |= rgbmask[i];   // Add to RGB+CLK bit mask
		rgbmask_all |= rgbmask[i];
	}
	clk_clrmask = clk_clrmask << 16;
//#ifndef DIRECT_OUTPUT
	for (int i = 0; i < 256; i++) {
		expand[i] = 0;
		if (i & 0x01) expand[i] |= rgbmask[0];
		if (i & 0x02) expand[i] |= rgbmask[1];
		if (i & 0x04) expand[i] |= rgbmask[2];
		if (i & 0x08) expand[i] |= rgbmask[3];
		if (i & 0x10) expand[i] |= rgbmask[4];
		if (i & 0x20) expand[i] |= rgbmask[5];
		if (options & CLK_WITH_DATA) expand[i] |= clkmask;
	}
}
#endif	


/*--------------------------------------------------------------------------------------*/
void DMD_RGB_BASE::setCycleLen()  {
	this->scan_cycle_len = ((1000000ul / this->default_fps) / (this->nRows * (1 << (this->nPlanes - 1)))) * CYCLES_PER_MICROSECOND;
	
	uint32_t write_time = ((this->x_len) / 64) * this->transfer64bits_time * CYCLES_PER_MICROSECOND;
	write_time = (write_time * this->transfer_duty) / this->transfer_duty2;
#if (defined(ARDUINO_ARCH_RP2040))
	if (write_time < (min_scan_len * CYCLES_PER_MICROSECOND)) write_time = min_scan_len * CYCLES_PER_MICROSECOND;
#endif
	if (this->scan_cycle_len < write_time) this->scan_cycle_len = write_time;

}

/*--------------------------------------------------------------------------------------*/
#if (defined(__STM32F1__) || defined(__STM32F4__))
void DMD_RGB_BASE::initialize_timers(voidFuncPtr handler) {


		uint32_t max_cycle_len = this->scan_cycle_len;
		if (nPlanes == 4)  max_cycle_len = 4 * this->scan_cycle_len;
		setup_main_timer(max_cycle_len, handler);
		DMD::initialize_timers(NULL);
		

#if defined(RGB_DMA)
		// DMA timer setup
#define TIM_PERIOD 14
		timer_init(DMA_TIMER);
		timer_pause(DMA_TIMER);
		DMA_TIMER_BASE->DIER |= (1 << 11) | (1 << 9);  //CH1 & CH3 DMA request enable
		DMA_TIMER_BASE->PSC = 0;
		DMA_TIMER_BASE->ARR = TIM_PERIOD - 1; //  9 MHz 
		DMA_TIMER_BASE->CCR3 = TIM_PERIOD / 4;    // 1 dma request 
		DMA_TIMER_BASE->CCR1 = TIM_PERIOD * 3 / 4;   // 2 dma request

		// dma setup
		dma_init(rgbDmaDev);
#if defined(__STM32F4__)
		uint8_t* ptr_t = matrixbuff[1 - backindex];
		dma_disable(rgbDmaDev, clkTxDmaStream);
		dma_disable(rgbDmaDev, datTxDmaStream);
		dma_clear_isr_bits(rgbDmaDev, datTxDmaStream);
		dma_clear_isr_bits(rgbDmaDev, clkTxDmaStream);
		dma_setup_transfer(rgbDmaDev, datTxDmaStream, DmaDataChannel, DMA_SIZE_8BITS, (uint8_t*)datasetreg, (uint8_t*)ptr_t, NULL, (DMA_MINC_MODE | DMA_FROM_MEM));
		dma_set_num_transfers(rgbDmaDev, datTxDmaStream, x_len);

		// 2 nd dma stream

		dma_setup_transfer(rgbDmaDev, clkTxDmaStream, DmaClkChannel, DMA_SIZE_32BITS, (uint32_t*)datasetreg, (uint32_t*)&clk_clrmask, NULL, (DMA_CIRC_MODE | DMA_FROM_MEM));
		dma_set_num_transfers(rgbDmaDev, clkTxDmaStream, 1);

		dma_enable(rgbDmaDev, datTxDmaStream);
		dma_enable(rgbDmaDev, clkTxDmaStream);
#endif
#endif

}
#endif

/*--------------------------------------------------------------------------------------*/
void DMD_RGB_BASE::init(uint16_t scan_interval) {

	if (scan_interval) this->default_fps = scan_interval;
	this->setCycleLen();
#if (defined(__STM32F1__) || defined(__STM32F4__))
	set_pin_modes();
	generate_muxmask();
	generate_rgbtable();
	chip_init();
#elif (defined(ARDUINO_ARCH_RP2040))
	generate_muxmask();
#endif
	initialize_timers(scan_running_dmd_R);
	setBrightness(200);
	clearScreen(true);

}
/*--------------------------------------------------------------------------------------*/
#if (defined(__STM32F1__) || defined(__STM32F4__))
void DMD_RGB_BASE::send_to_allRGB(uint16_t data, uint16_t latches) {

	uint8_t reg_bit = 0;
	const uint16_t b_mask = 0b1000000000000000;

	for (uint16_t i = 0; i < x_len; i++) {
		reg_bit = i % 16;

		if (i == (x_len - latches)) { *latsetreg = latmask; }  // switch LE ON
		if ((data << reg_bit) & b_mask)
		{
			*datasetreg = rgbmask_all;
		}
		else
		{
			*datasetreg = rgbmask_all << 16;
		}
		*datasetreg = clkmask;
		*datasetreg = clkmask << 16;
	}

	*latsetreg = latmask << 16;// Latch down
	*datasetreg = rgbmask_all << 16; // off all rgb channels

}
#endif
/*--------------------------------------------------------------------------------------*/
uint16_t DMD_RGB_BASE::get_base_addr(int16_t& x, int16_t& y) {
	this->transform_XY(x, y);
	uint16_t base_addr = 0;
	if (multiplex == 1) {
		base_addr = (y % pol_displ) * WIDTH * DisplaysHigh + (y / DMD_PIXELS_DOWN) * WIDTH + x;
	}
	else {
		uint8_t pol_y = y % pol_displ;
		x += (y / DMD_PIXELS_DOWN) * WIDTH;
		base_addr = (pol_y % nRows) * x_len + (x / 8) * multiplex * 8 + (pol_y / nRows) * 8 + x % 8;
	}
	return base_addr;
}
/*--------------------------------------------------------------------------------------*/
void DMD_RGB_BASE::scan_dmd() {
	
	scan_dmd_p1();
#if (defined(__STM32F1__) || defined(__STM32F4__))
	scan_dmd_p2();
	scan_dmd_p3();
#endif
}
/*--------------------------------------------------------------------------------------*/
void DMD_RGB_BASE::scan_dmd_p1() {

	uint32_t duration;
	uint32_t oe_duration;
	//volatile static uint8_t* ptr;

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

#if (defined(ARDUINO_ARCH_RP2040))
	pwm_clear_irq(MAIN_slice_num);             // clear PWM irq
	pwm_set_enabled(MAIN_slice_num, false);    // stop MAIN timer
	pwm_set_enabled(OE_slice_num, false);    // stop OE timer

	pwm_set_wrap(MAIN_slice_num, duration);     // set new TOP value
	pwm_set_gpio_level(pin_DMD_nOE, oe_duration);  // setup CC value for OE 

#endif

#if (defined(__STM32F1__) || defined(__STM32F4__))

	timer_pause(MAIN_TIMER);
	timer_set_reload(MAIN_TIMER, (duration - this->callOverhead));

	timer_pause(OE_TIMER);
	timer_oc_set_mode(OE_TIMER, oe_channel, TIMER_OC_MODE_FROZEN, 0);
	timer_set_reload(OE_TIMER, (duration + this->callOverhead * 10));
	timer_set_compare(OE_TIMER, oe_channel, oe_duration);

#endif
	// Borrowing a technique here from Ray's Logic:
  // www.rayslogic.com/propeller/Programming/AdafruitRGB/AdafruitRGB.htm
  // This code cycles through all four planes for each scanline before
  // advancing to the next line.  While it might seem beneficial to
  // advance lines every time and interleave the planes to reduce
  // vertical scanning artifacts, in practice with this panel it causes
  // a green 'ghosting' effect on black pixels, a much worse artifact.

	// For OneBitColor set mux BEFORE changing row
	if (nPlanes == 1) {
		this->set_mux(row);
		}


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
		this->set_mux(row);
		}



#if (defined(ARDUINO_ARCH_RP2040))

	dmd_out_program_reinit(pio, sm_data, data_prog_offs, &pio_config);
	dma_channel_set_read_addr(dma_chan, buffptr, true);
	pwm_set_counter(MAIN_slice_num, 0);
	pwm_set_counter(OE_slice_num, 0);
	pwm_set_enabled(MAIN_slice_num, true);
	pwm_set_enabled(OE_slice_num, true);
	buffptr += displ_len;
#endif
}
#if (defined(__STM32F1__) || defined(__STM32F4__))

void DMD_RGB_BASE::scan_dmd_p2() {
	*latsetreg = latmask; // Latch data loaded during *prior* interrupt
	*latsetreg = latmask << 16;// Latch down

	timer_set_count(MAIN_TIMER, 0);
	timer_set_count(OE_TIMER, 0);
	timer_oc_set_mode(OE_TIMER, oe_channel, (timer_oc_mode)this->OE_polarity, 0);
	timer_generate_update(MAIN_TIMER);
	timer_generate_update(OE_TIMER);
	timer_resume(OE_TIMER);
	timer_resume(MAIN_TIMER);
}
#endif

/*--------------------------------------------------------------------------------------*/
#if (defined(__STM32F1__) || defined(__STM32F4__))
void DMD_RGB_BASE::scan_dmd_p3() {

	// buffptr, being 'volatile' type, doesn't take well to optimization.
	// A local register copy can speed some things up:
	volatile static uint8_t* ptr;
	
	ptr = buffptr;
#if defined(RGB_DMA)
	timer_pause(DMA_TIMER);
#if defined(__STM32F1__) 

	dma_disable(rgbDmaDev, DmaDataChannel);
	dma_setup_transfer(rgbDmaDev, DmaDataChannel, (uint8_t*)datasetreg, DMA_SIZE_8BITS, (uint8_t*)ptr, DMA_SIZE_8BITS, (DMA_MINC_MODE | DMA_FROM_MEM | DMA_CCR_PL_HIGH));
	dma_set_num_transfers(rgbDmaDev, DmaDataChannel, x_len);


	dma_disable(rgbDmaDev, DmaClkChannel);
	dma_setup_transfer(rgbDmaDev, DmaClkChannel, (uint32_t*)datasetreg, DMA_SIZE_32BITS, (uint32_t*)&clk_clrmask, DMA_SIZE_32BITS, (DMA_CIRC_MODE | DMA_FROM_MEM | DMA_CCR_PL_VERY_HIGH));
	dma_set_num_transfers(rgbDmaDev, DmaClkChannel, x_len);

	dma_enable(rgbDmaDev, DmaDataChannel);
	dma_enable(rgbDmaDev, DmaClkChannel);



#elif defined(__STM32F4__) 

	dma_set_mem_addr(rgbDmaDev, datTxDmaStream, ptr);
	dma_clear_isr_bits(rgbDmaDev, datTxDmaStream);
	dma_set_num_transfers(rgbDmaDev, datTxDmaStream, x_len);

	// 2 nd dma stream

	dma_enable(rgbDmaDev, datTxDmaStream);
	
#endif
	
	DMA_TIMER_BASE->CNT = 0;
	DMA_TIMER_BASE->CR1 = (1 << 0);

#else   // end of if defined(RGB_DMA), start of non-DMA code
#if defined (DIRECT_OUTPUT)
#define pew                    \
      *datasetreg = clk_clrmask;     \
      *datasetreg = *ptr++;
#else
#define pew                    \
      *datasetreg = clk_clrmask;     \
      *datasetreg = expand[*ptr++];
#endif
	for (uint16_t uu = 0; uu < x_len; uu += 8)
	{
		// Loop is unrolled for speed:
		pew pew pew pew pew pew pew pew

	}

	*datasetreg = clkmask << 16; // Set clock low


#endif


	buffptr += displ_len;

#undef pew

}
#endif
/*--------------------------------------------------------------------------------------*/
void DMD_RGB_BASE::drawPixel(int16_t x, int16_t y, uint16_t c)  {
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


	bit = 1;
	limit = 1 << nPlanes;
	if (y % DMD_PIXELS_DOWN < pol_displ) {
		// Data for the upper half of the display is stored in the lower
		// bits of each byte.
	
		// Data is stored in the low 6 bits so it can be quickly
		// copied to the DATAPORT register w/6 output lines.
		for (; bit < limit; bit <<= 1) {

			*ptr |= output_mask;

			* ptr &= ~B000111;            // Mask out R,G,B in one op
			if (r & bit) *ptr |= B000001; // Plane N R: bit 2
			if (g & bit) *ptr |= B000010; // Plane N G: bit 3
			if (b & bit) *ptr |= B000100; // Plane N B: bit 4
			ptr += displ_len;                 // Advance to next bit plane
		}
	}
	else {
		// Data for the lower half of the display is stored in the upper
		// bits

		for (; bit < limit; bit <<= 1) {

			*ptr |= output_mask;

			* ptr &= ~B111000;            // Mask out R,G,B in one op
			if (r & bit) *ptr |= B001000; // Plane N R: bit 5
			if (g & bit) *ptr |= B010000; // Plane N G: bit 6
			if (b & bit) *ptr |= B100000; // Plane N B: bit 7
			ptr += displ_len;                 // Advance to next bit plane
		}
	}
	DEBUG_TIME_MARK;

}
/*--------------------------------------------------------------------------------------*/
void DMD_RGB_BASE::drawHByte(int16_t x, int16_t y, uint8_t hbyte, uint16_t bsize, uint8_t* fg_col_bytes,
	uint8_t* bg_col_bytes) {

	
	static uint8_t ColorByteMask[] = { B000111 , B111000 };
	if ((hbyte != 0xff)&& (bsize > 8)) bsize = 8;
	
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

		mask = ColorByteMask + 1;
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
		mask_ptr = mask;
		for (uint8_t b = 0; b < col_bytes_cnt; b++)
		{
			*ptr &= ~(*mask_ptr);

			*ptr |= output_mask | (col_bytes[b] & (*mask_ptr));


			ptr += displ_len;
		}

	}
	DEBUG_TIME_MARK;

}
/*--------------------------------------------------------------------------------------*/
void DMD_RGB_BASE::getColorBytes(uint8_t* cbytes, uint16_t color) {
	uint8_t r, g, b, bit, limit;
	uint8_t* ptr;

	uint8_t empty_col = output_mask;

	// special case color = 0
	if (color == 0) {
		memset(cbytes, empty_col, col_bytes_cnt);
		
		return;
	}
	// if color found in cash table
	if ((colors[last_color] == color) || (colors[last_color = !last_color] == color)) {
		ptr = col_cache + last_color * col_bytes_cnt;
		memcpy(cbytes, ptr, col_bytes_cnt);
		return;
	}

	// new color
	ptr = col_cache + last_color * col_bytes_cnt;
	colors[last_color] = color;
	memset(ptr, empty_col, col_bytes_cnt);


	// Adafruit_GFX uses 16-bit color in 5/6/5 format, while matrix needs
		// 4/4/4.  Pluck out relevant bits while separating into R,G,B:

	uint16_t c = color;
	r = c >> 12;        // RRRRrggggggbbbbb
	g = (c >> 7) & 0xF; // rrrrrGGGGggbbbbb
	b = (c >> 1) & 0xF; // rrrrrggggggBBBBb


	limit = 1 << nPlanes;
	bit = 1;
	for (; bit < limit; bit <<= 1) {
		// Mask out R,G,B in one op
		if (r & bit) *ptr |= B00001001; // Plane N R: bit 2
		if (g & bit) *ptr |= B00010010; // Plane N G: bit 3
		if (b & bit) *ptr |= B00100100; // Plane N B: bit 4

		ptr++;                 // Advance to next bit plane
	}
	ptr -= col_bytes_cnt;
	memcpy(cbytes, ptr, col_bytes_cnt); return;
}
/*--------------------------------------------------------------------------------------*/
void DMD_RGB_BASE::fillScreen(uint16_t c)  {
	if ((c == 0x0000) || (c == 0xffff)) {
		uint8_t b;

if (output_mask) b = 0b01000000 | (c & 0b00111111);
else b = c & 0xff;

		// For black or white, all bits in frame buffer will be identically
		// set or unset (regardless of weird bit packing), so it's OK to just
		// quickly memset the whole thing:
		memset(matrixbuff[backindex], b, this->mem_Buffer_Size);
	}
	else {
		// Otherwise, need to handle it the long way:
		Adafruit_GFX::fillScreen(c);
	}
}
/*--------------------------------------------------------------------------------------*/
void DMD_RGB_BASE::clearScreen(byte bNormal)  {
	// ToDo: bNornal flag should affect screen filling with background color
	if (bNormal)  {

	}

	fillScreen(0x0000);
}
/*--------------------------------------------------------------------------------------*/
void DMD_RGB_BASE::shiftScreen(int8_t step) {
	uint8_t* ptr = matrixbuff[backindex];
	uint8_t mm = output_mask;
	
	if (step < 0) {

		for (uint16_t i = 0; i < mem_Buffer_Size;i++) {
			if ((i % WIDTH) == (WIDTH - 1)) {
				ptr[i] = mm;
			}
			else {
				ptr[i] = ptr[i + 1];
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
		uint8_t fg_col_bytes[col_bytes_cnt];
		getColorBytes(fg_col_bytes, color);
		drawHByte(x, y, 255, w, fg_col_bytes, fg_col_bytes);

	}
	else {
		for (uint16_t xx = 0; xx < w; xx++) {
			drawPixel(x + xx, y, color);
		}
	}
}
/*--------------------------------------------------------------------------------------*/
void DMD_RGB_BASE::setMarqueeColor(uint16_t text_color, uint16_t bg_color)
	{
	this->setTextColor(text_color, bg_color);
	marqueeType_MultiColor = false;
	}
void DMD_RGB_BASE::setMarqueeColor(DMD_Colorlist* colors) {
	marqueeType_MultiColor = true;
	marqueeColors = colors;
	}
/*--------------------------------------------------------------------------------------
 Service routine to call drawString<color16> or drawString<DMD_Colorlist> instance 
 inside the marquee methods. Virtual, overrides base DMD method.
 --------------------------------------------------------------------------------------*/
void  DMD_RGB_BASE::drawMarqueeString(int bX, int bY, const char* bChars, int length,
	int16_t miny, int16_t maxy, byte orientation)
	{
	  if (marqueeType_MultiColor) {
		this->drawString(bX, bY, bChars, length, marqueeColors, miny, maxy, orientation);
		}
	else {
		this->drawString(bX, bY, bChars, length, textcolor, miny, maxy, orientation);
		}

	}


/*--------------------------------------------------------------------------------------*/
// Promote 3/3/3 RGB to Adafruit_GFX 5/6/5
uint16_t DMD_RGB_BASE::Color333(uint8_t r, uint8_t g, uint8_t b) {
	// RRRrrGGGgggBBBbb
	return ((r & 0x7) << 13) | ((r & 0x6) << 10) |
		((g & 0x7) << 8) | ((g & 0x7) << 5) |
		((b & 0x7) << 2) | ((b & 0x6) >> 1);
}
/*--------------------------------------------------------------------------------------*/
// Promote 4/4/4 RGB to Adafruit_GFX 5/6/5
uint16_t DMD_RGB_BASE::Color444(uint8_t r, uint8_t g, uint8_t b) {
	// RRRRrGGGGggBBBBb
	return ((r & 0xF) << 12) | ((r & 0x8) << 8) |
		((g & 0xF) << 7) | ((g & 0xC) << 3) |
		((b & 0xF) << 1) | ((b & 0x8) >> 3);
}
/*--------------------------------------------------------------------------------------*/
// Demote 8/8/8 to Adafruit_GFX 5/6/5
// If no gamma flag passed, assume linear color
uint16_t DMD_RGB_BASE::Color888(uint8_t r, uint8_t g, uint8_t b) {
	return ((uint16_t)(r & 0xF8) << 8) | ((uint16_t)(g & 0xFC) << 3) | (b >> 3);
}
#if defined(DEBUG2)
/*--------------------------------------------------------------------------------------*/
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
#endif
/*--------------------------------------------------------------------------------------*/
DMD_RGB_BASE::~DMD_RGB_BASE()
{
#if (defined(__STM32F1__) || defined(__STM32F4__))
	free(matrixbuff[0]);

#endif
#if defined(DEBUG2)
	free((uint16_t*)dd_ptr);
#endif	

}
