/*--------------------------------------------------------------------------------------
 This file is a part of the library DMD_STM32

 DMD_STM32.h  - STM32 port of DMD.h library

 https://github.com/board707/DMD_STM32
 Dmitry Dmitriev (c) 2019-2023
 /--------------------------------------------------------------------------------------*/

#include "DMD_Monochrome_Parallel.h"
static volatile DMD_Monochrome_Parallel* running_dmd;
void inline __attribute__((always_inline)) scan_running_dmd()
{
	DMD_Monochrome_Parallel* next = (DMD_Monochrome_Parallel*)running_dmd;
	next->scan_dmd();
}

/*--------------------------------------------------------------------------------------*/
DMD_Monochrome_Parallel::DMD_Monochrome_Parallel(byte _pin_A, byte _pin_B, byte _pin_nOE, byte _pin_SCLK, uint8_t* pinlist,
	byte panelsWide, byte panelsHigh,
	bool d_buf, byte dmd_pixel_x, byte dmd_pixel_y)
	:DMD(new DMD_Pinlist(_pin_A, _pin_B), _pin_nOE, _pin_SCLK, panelsWide, panelsHigh, DMD_MONO_SCAN, new DMD_Pinlist(panelsHigh+1, pinlist),
		d_buf, dmd_pixel_x, dmd_pixel_y)
{
	mem_Buffer_Size = DMD_PIXELS_ACROSS * panelsWide * DMD_PIXELS_DOWN;
	x_len = mem_Buffer_Size / DMD_MONO_SCAN;
	
	// Allocate and initialize matrix buffer:
	uint16_t allocsize = (dbuf == true) ? (mem_Buffer_Size * 2) : mem_Buffer_Size;
	matrixbuff[0] = (uint8_t*)malloc(allocsize);

	// If not double-buffered, both buffers then point to the same address:
	matrixbuff[1] = (dbuf == true) ? &matrixbuff[0][mem_Buffer_Size] : matrixbuff[0];
	backindex = 0;
	bDMDScreenRAM = matrixbuff[backindex]; // Back buffer
	front_buff = matrixbuff[1 - backindex]; // -> front buffer
	
	running_dmd = this;
}
/*--------------------------------------------------------------------------------------*/
DMD_Monochrome_Parallel::~DMD_Monochrome_Parallel()
{
	free(matrixbuff[0]);
}
/*--------------------------------------------------------------------------------------*/
void DMD_Monochrome_Parallel::set_pin_modes() {

#if (defined(__STM32F1__) || defined(__STM32F4__))
	DMD::set_pin_modes();
#ifdef USE_UPPER_8BIT
	clk_clrmask_low = clk_clrmask >> 8;
	clkmask_low = clkmask >> 8;
#endif // USE_UPPER_8BIT
#endif

	for (byte i = 0; i < this->data_pins_cnt; i++) {
#if (defined(__STM32F1__) || defined(__STM32F4__))
		this->row_mask[i] = digitalPinToBitMask(this->data_pins[i]);
		pinMode(this->data_pins[i], OUTPUT);
        this->clk_clrmask |= this->row_mask[i];
#elif  (defined(ARDUINO_ARCH_RP2040))
        this->clk_clrmask |= (1 << (i));		
#endif
	}

}
/*--------------------------------------------------------------------------------------*/
void DMD_Monochrome_Parallel::init(uint16_t scan_interval)
{
	DMD::init(scan_interval);
	this->initialize_timers(scan_running_dmd);

}
/*--------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------*/
void DMD_Monochrome_Parallel::drawPixel(int16_t x, int16_t y, uint16_t color) {

	unsigned int uiDMDRAMPointer;
	uint8_t bPixel = color;
	int16_t bX = x;
	int16_t bY = y;
	if (bX >= (_width) || bY >= (_height)) {
		return;
	}

	if (bX < 0 || bY < 0) {
		return;
	}
	// transform X & Y for Rotate and connect scheme
	transform_XY(bX, bY);

	// inverse data bits for some panels
	bPixel = bPixel ^ inverse_ALL_flag;
	byte panel_row = bY / DMD_PIXELS_DOWN;
	byte panel_bY = bY % DMD_PIXELS_DOWN;
	byte mux = panel_bY % 4;
	byte mux_byte_cnt = panel_bY / 4;
	uiDMDRAMPointer = mux * x_len + (bX / 8) * column_size + (3 - mux_byte_cnt) * 8 + bX % 8;

#if (defined(ARDUINO_ARCH_RP2040))
    byte lookup = (1<<panel_row);
#elif (defined(__STM32F1__) || defined(__STM32F4__))	
#ifdef USE_UPPER_8BIT
	byte lookup = row_mask[panel_row] >> 8;
#else
	byte lookup = row_mask[panel_row];
#endif
#endif

	switch (graph_mode) {
	case GRAPHICS_NORMAL:
		if (bPixel == true)
			bDMDScreenRAM[uiDMDRAMPointer] &= ~lookup;	// zero bit is pixel on
		else
			bDMDScreenRAM[uiDMDRAMPointer] |= lookup;	// one bit is pixel off
		break;
		/*case GRAPHICS_INVERSE:
			if (bPixel == false)
				bDMDScreenRAM[uiDMDRAMPointer] &= ~lookup;	// zero bit is pixel on
			else
				bDMDScreenRAM[uiDMDRAMPointer] |= lookup;	// one bit is pixel off
			break;
		case GRAPHICS_TOGGLE:
			if (bPixel == true) {
			if ((bDMDScreenRAM[uiDMDRAMPointer] & lookup) == 0)
				bDMDScreenRAM[uiDMDRAMPointer] |= lookup;	// one bit is pixel off
			else
				bDMDScreenRAM[uiDMDRAMPointer] &= ~lookup;	// one bit is pixel off
			}
			break;
		case GRAPHICS_OR:
			//only set pixels on
			if (bPixel == true)
				bDMDScreenRAM[uiDMDRAMPointer] &= ~lookup;	// zero bit is pixel on
			break;*/
	case GRAPHICS_NOR:
		//only clear on pixels
		if ((bPixel == true) &&
			((bDMDScreenRAM[uiDMDRAMPointer] & lookup) == 0))
			bDMDScreenRAM[uiDMDRAMPointer] |= lookup;	// one bit is pixel off
		break;
	}
}
/*--------------------------------------------------------------------------------------*/
void  DMD_Monochrome_Parallel::scan_dmd() {
	
#if (defined(ARDUINO_ARCH_RP2040))
	uint32_t duration = this->scan_cycle_len;
	pwm_clear_irq(MAIN_slice_num);				// clear PWM irq
	pwm_set_enabled(MAIN_slice_num, false);		// stop MAIN timer
	pwm_set_enabled(OE_slice_num, false);		// stop OE timer
	pwm_set_wrap(MAIN_slice_num, duration);     // set new TOP value
												// setup CC value for OE 
	pwm_set_gpio_level(pin_DMD_nOE, ((uint32_t)duration * this->brightness) / 255);
	
	
#endif
	switch_row();

	uint16_t offset = x_len * bDMDByte;
	uint8_t* fr_buff = matrixbuff[1 - backindex]; // -> front buffer
	uint8_t* ptr = fr_buff + offset;

#if (defined(ARDUINO_ARCH_RP2040))
	
	dmd_out_program_reinit(pio, sm_data, data_prog_offs, &pio_config);
	dma_channel_set_read_addr(dma_chan, ptr, true);
	pwm_set_counter(MAIN_slice_num, 0);
	pwm_set_counter(OE_slice_num, 0);
	pwm_set_enabled(MAIN_slice_num, true);
	pwm_set_enabled(OE_slice_num, true);

#elif (defined(__STM32F1__) || defined(__STM32F4__))
	uint16_t cnt = 0;
	static const PortType all_clr_mask = clk_clrmask << 16;
	
#ifdef USE_UPPER_8BIT
#define pew                    \
      *datasetreg = all_clr_mask;    \
      *datasetreg = (ptr[cnt++]) << 8 ;\
      //*datasetreg = clkmask;
#else
#define pew                    \
      *datasetreg = all_clr_mask;     \
      *datasetreg = ptr[cnt++] ;\
      //*datasetreg = clkmask;
#endif

	
#if (defined(__STM32F1__))
	for (uint16_t uu = 0; uu < WIDTH; uu += 8)
	{
		// Loop is unrolled for speed:
		pew pew pew pew pew pew pew pew
			pew pew pew pew pew pew pew pew
			pew pew pew pew pew pew pew pew
			pew pew pew pew pew pew pew pew
#elif  (defined(__STM32F4__))
	for (uint16_t uu = 0; uu < WIDTH*4; uu++)
	{
		*datasetreg = all_clr_mask;     
//#if (CYCLES_PER_MICROSECOND > 100)
		*datasetreg = (clkmask << 16);
//#endif
		*datasetreg = ptr[cnt++];

#endif
			
	}

	*datasetreg = all_clr_mask; // Set clock low
#endif
	DEBUG_TIME_MARK;
	//switch_row();
	DEBUG_TIME_MARK;

}
/*--------------------------------------------------------------------------------------*/
void DMD_Monochrome_Parallel::clearScreen(byte bNormal)
{
	uint8_t mask;
#ifdef USE_UPPER_8BIT
	if (bNormal ^ inverse_ALL_flag) // clear all pixels
		mask = clk_clrmask_low & 0x00FF;
	else // set all pixels
		mask = clkmask_low & 0x00FF;
#else
	if (bNormal ^ inverse_ALL_flag) // clear all pixels
	//	mask = 0x03;
	mask = clk_clrmask & 0x00FF;
	
	else // set all pixels
		mask = clkmask & 0x00FF;
#endif
	
	memset(bDMDScreenRAM, mask, mem_Buffer_Size);

}
/*--------------------------------------------------------------------------------------*/
void DMD_Monochrome_Parallel::shiftScreen(int8_t step) {
	uint8_t mask;
#ifdef USE_UPPER_8BIT
	if (inverse_ALL_flag)
		mask = clkmask_low & 0x00FF;
	else
		mask = clk_clrmask_low & 0x00FF;
#else
	if (inverse_ALL_flag)
		mask = clkmask & 0x00FF;
	else
		mask = clk_clrmask & 0x00FF;
#endif
	uint16_t column_cnt = WIDTH / 8;

	if (step < 0) {
		uint16_t ptr = 0;

		for (byte j = 0; j < 4; j++) {  // mux
			// columns
			for (byte k = 0; k < column_cnt;k++) {
				bool last_column = (k == (column_cnt - 1));
				// four lines
				for (byte jj = 0; jj < 4; jj++) {
					// seven points
					for (byte i = 0; i < 7;i++) {
						bDMDScreenRAM[ptr] = bDMDScreenRAM[ptr + 1];
						ptr++;
					}
					// eighth point
					if (last_column) bDMDScreenRAM[ptr] = mask;
					else bDMDScreenRAM[ptr] = bDMDScreenRAM[ptr + (column_size - 7)];
					ptr++;
				}
			}

		}
	}

	else if (step > 0) {
		uint16_t ptr = mem_Buffer_Size - 1;

		for (byte j = 0; j < 4; j++) {  // mux
			// columns
			for (byte k = 0; k < column_cnt;k++) {
				bool last_column = (k == (column_cnt - 1));
				// four lines
				for (byte jj = 0; jj < 4; jj++) {
					// seven points
					for (byte i = 0; i < 7;i++) {
						bDMDScreenRAM[ptr] = bDMDScreenRAM[ptr - 1];
						ptr--;
					}
					// eighth point
					if (last_column) bDMDScreenRAM[ptr] = mask;
					else bDMDScreenRAM[ptr] = bDMDScreenRAM[ptr - (column_size - 7)];
					ptr--;
				}
			}

		}
	}
}




