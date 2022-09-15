#if (defined(__STM32F1__) || defined(__STM32F4__))
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
	:DMD(_pin_A, _pin_B, _pin_nOE, _pin_SCLK, panelsWide, panelsHigh, d_buf, dmd_pixel_x, dmd_pixel_y)
{
	mem_Buffer_Size = DMD_PIXELS_ACROSS * panelsWide * DMD_PIXELS_DOWN;
	mux_size = mem_Buffer_Size / DMD_MONO_SCAN;
	column_size = 8 * DMD_MONO_SCAN;


	// Allocate and initialize matrix buffer:
	uint16_t allocsize = (dbuf == true) ? (mem_Buffer_Size * 2) : mem_Buffer_Size;
	matrixbuff[0] = (uint8_t*)malloc(allocsize);

	// If not double-buffered, both buffers then point to the same address:
	matrixbuff[1] = (dbuf == true) ? &matrixbuff[0][mem_Buffer_Size] : matrixbuff[0];
	backindex = 0;
	bDMDScreenRAM = matrixbuff[backindex]; // Back buffer
	front_buff = matrixbuff[1 - backindex]; // -> front buffer

	byte clk_pin = pinlist[0];
	datasetreg = portSetRegister(clk_pin);
	clk_clrmask = clkmask = digitalPinToBitMask(clk_pin);
	memcpy(row_pins, pinlist, panelsHigh + 1);

#ifdef USE_UPPER_8BIT
	clk_clrmask_low = clk_clrmask >> 8;
	clkmask_low = clkmask >> 8;
#endif // USE_UPPER_8BIT
	running_dmd = this;
}
/*--------------------------------------------------------------------------------------*/
DMD_Monochrome_Parallel::~DMD_Monochrome_Parallel()
{
	free(matrixbuff[0]);
}
/*--------------------------------------------------------------------------------------*/
void DMD_Monochrome_Parallel::set_pin_modes() {

	DMD::set_pin_modes();
	byte clk_pin = this->row_pins[0];
	pinMode(clk_pin, OUTPUT);

	for (byte i = 1; i <= this->DisplaysHigh; i++) {
		this->row_mask[i - 1] = digitalPinToBitMask(this->row_pins[i]);
		pinMode(this->row_pins[i], OUTPUT);
		this->clk_clrmask |= this->row_mask[i - 1];
	}
}
/*--------------------------------------------------------------------------------------*/
void DMD_Monochrome_Parallel::init(uint16_t scan_interval)
{
	DMD::init(scan_interval);
	// clean both buffers
	if (matrixbuff[0] != matrixbuff[1]) {
		bDMDScreenRAM = matrixbuff[1 - backindex];
		clearScreen(true);
	}
	bDMDScreenRAM = matrixbuff[backindex];
	clearScreen(true);

	uint32 period_cyc = scan_interval * CYCLES_PER_MICROSECOND;
	setup_main_timer(period_cyc, scan_running_dmd);
}

/*--------------------------------------------------------------------------------------*/
void DMD_Monochrome_Parallel::drawPixel(int16_t x, int16_t y, uint16_t color) {

	unsigned int uiDMDRAMPointer;
	uint8_t bPixel = color;
	int16_t bX = x;
	int16_t bY = y;
	if (bX >= (WIDTH) || bY >= (HEIGHT)) {
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
	uiDMDRAMPointer = mux * mux_size + (bX / 8) * column_size + (3 - mux_byte_cnt) * 8 + bX % 8;

#ifdef USE_UPPER_8BIT
	byte lookup = row_mask[panel_row] >> 8;
#else
	byte lookup = row_mask[panel_row];
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
	uint16_t offset = mux_size * bDMDByte;
	uint8_t* fr_buff = matrixbuff[1 - backindex]; // -> front buffer
	uint8_t* ptr = fr_buff + offset;
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

	for (uint16_t uu = 0; uu < WIDTH; uu += 8)
	{
		// Loop is unrolled for speed:
		pew pew pew pew pew pew pew pew
			pew pew pew pew pew pew pew pew
			pew pew pew pew pew pew pew pew
			pew pew pew pew pew pew pew pew
			/*
					pew pew pew pew pew pew pew pew
					pew pew pew pew pew pew pew pew
					pew pew pew pew pew pew pew pew
					pew pew pew pew pew pew pew pew

					pew pew pew pew pew pew pew pew
					pew pew pew pew pew pew pew pew
					pew pew pew pew pew pew pew pew
					pew pew pew pew pew pew pew pew

					pew pew pew pew pew pew pew pew
					pew pew pew pew pew pew pew pew
					pew pew pew pew pew pew pew pew
					pew pew pew pew pew pew pew pew*/
	}

	*datasetreg = all_clr_mask; // Set clock low
	DEBUG_TIME_MARK;
	switch_row();
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
#endif



