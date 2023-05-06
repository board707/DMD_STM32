#if (defined(__STM32F1__) || defined(__STM32F4__))
#include "DMD_MonoChrome_SPI.h"
#include "SPI_DMA.h"

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

/*--------------------------------------------------------------------------------------*/
DMD_MonoChrome_SPI::DMD_MonoChrome_SPI(byte _pin_A, byte _pin_B, byte _pin_nOE, byte _pin_SCLK,
	byte panelsWide, byte panelsHigh, SPIClass _spi,
	bool d_buf, byte dmd_pixel_x, byte dmd_pixel_y)
	:DMD(new DMD_Pinlist(_pin_A, _pin_B), _pin_nOE, _pin_SCLK, panelsWide, panelsHigh,
		DMD_MONO_SCAN, new DMD_Pinlist(_spi.sckPin(), _spi.mosiPin()), d_buf, dmd_pixel_x, dmd_pixel_y), SPI_DMD(_spi)
{
	mem_Buffer_Size = DisplaysTotal * ((DMD_PIXELS_ACROSS * DMD_BITSPERPIXEL / 8) * DMD_PIXELS_DOWN);
	row1 = DisplaysTotal << 4;
	row2 = DisplaysTotal << 5;
	row3 = ((DisplaysTotal << 2) * 3) << 2;
	rowsize = DisplaysTotal << 2;

	// Allocate and initialize matrix buffer:
	uint16_t allocsize = (dbuf == true) ? (mem_Buffer_Size * 2) : mem_Buffer_Size;
	matrixbuff[0] = (uint8_t*)malloc(allocsize);

	// If not double-buffered, both buffers then point to the same address:
	matrixbuff[1] = (dbuf == true) ? &matrixbuff[0][mem_Buffer_Size] : matrixbuff[0];
	backindex = 0;
	bDMDScreenRAM = matrixbuff[backindex]; // Back buffer
	front_buff = matrixbuff[1 - backindex]; // -> front buffer


#if ( DMD_USE_DMA )	
	dmd_dma_buf = (byte*)malloc(mem_Buffer_Size / DMD_MONO_SCAN);
#endif
#if defined(__STM32F1__) 
	spiDmaDev = DMA1;
	if (SPI_DMD.dev() == SPI1) {
		spiTxDmaChannel = DMA_CH3;
		spi_num = 1;
	}
	else {
		spiTxDmaChannel = DMA_CH5;
		spi_num = 2;
	}
#elif defined(__STM32F4__) 

	if (SPI_DMD.dev() == SPI1) {
		spiDmaDev = DMA2;
		spiTxDmaChannel = DMA_CH3;
		spiTxDmaStream = DMA_STREAM3;
		spi_num = 1;
	}
	else if (SPI_DMD.dev() == SPI2) {
		spiDmaDev = DMA1;
		spiTxDmaChannel = DMA_CH0;
		spiTxDmaStream = DMA_STREAM4;
		spi_num = 2;
	}
	else if (SPI_DMD.dev() == SPI3) {
		spiDmaDev = DMA1;
		spiTxDmaChannel = DMA_CH0;
		spiTxDmaStream = DMA_STREAM5;
		spi_num = 3;
	}

#endif

}
/*--------------------------------------------------------------------------------------*/
DMD_MonoChrome_SPI::~DMD_MonoChrome_SPI()
{
	free(matrixbuff[0]);
#if ( DMD_USE_DMA )	
	free(dmd_dma_buf);
#endif
}
/*--------------------------------------------------------------------------------------*/
void DMD_MonoChrome_SPI::set_pin_modes() {

	DMD::set_pin_modes();
	pin_DMD_R_DATA = SPI_DMD.mosiPin();
	digitalWrite(pin_DMD_R_DATA, HIGH);	
	pinMode(pin_DMD_R_DATA, OUTPUT);

}
/*--------------------------------------------------------------------------------------*/
void DMD_MonoChrome_SPI::init(uint16_t scan_interval) {

	DMD::init(scan_interval);

#if (defined(__STM32F1__) || defined(__STM32F4__))

	SPI_DMD.begin(); //Initialize the SPI port.
	SPI_DMD.setBitOrder(MSBFIRST); // Set the SPI bit order
	SPI_DMD.setDataMode(SPI_MODE0); //Set the  SPI data mode 0
	//SPI_DMD.setClockDivider(SPI_CLOCK_DIV16);  // Use a different speed to SPI 1 */
	SPI_DMD.beginTransaction(SPISettings(DMD_SPI_CLOCK, MSBFIRST, SPI_MODE0));
	register_running_dmd(this, scan_interval);

#elif  (defined(ARDUINO_ARCH_RP2040))
#error "Monochrome SPI mode is not supported for RP2040 boards"
#endif
	
}
/*--------------------------------------------------------------------------------------*/
void DMD_MonoChrome_SPI::drawPixel(int16_t x, int16_t y, uint16_t color)
{
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

	//byte panel = (bX / DMD_PIXELS_ACROSS) + (DisplaysWide*(bY / DMD_PIXELS_DOWN));
	bX += (this->WIDTH * (bY / DMD_PIXELS_DOWN));
	bY = bY % DMD_PIXELS_DOWN;
	//set pointer to DMD RAM byte to be modified
	uiDMDRAMPointer = bX / 8 + bY * (DisplaysTotal << 2);

	byte lookup = bPixelLookupTable[bX & 0x07];
	/*if (bPixel == true)
		bDMDScreenRAM[uiDMDRAMPointer] &= ~lookup;	// zero bit is pixel on
	else
		bDMDScreenRAM[uiDMDRAMPointer] |= lookup;	// one bit is pixel off
	*/
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
#if ( DMD_USE_DMA )

void DMD_MonoChrome_SPI::latchDMA() {

	while (spi_is_tx_empty(SPI_DMD.dev()) == 0); // "5. Wait until TXE=1 ..."
	while (spi_is_busy(SPI_DMD.dev()) != 0); // "... and then wait until BSY=0 before disabling the SPI." 
	spi_tx_dma_disable(SPI_DMD.dev());

#if defined(__STM32F1__) 
	dma_disable(spiDmaDev, spiTxDmaChannel);
	dma_clear_isr_bits(spiDmaDev, spiTxDmaChannel);
#elif defined(__STM32F4__) 
	dma_disable(spiDmaDev, spiTxDmaStream);
	dma_clear_isr_bits(spiDmaDev, spiTxDmaStream);
#endif
	DEBUG_TIME_MARK;
	//switch_row();   // move to scanDisplay
	DEBUG_TIME_MARK;
}

/*--------------------------------------------------------------------------------------*/
void DMD_MonoChrome_SPI::scanDisplayByDMA()
{

	switch_row();

	uint8_t* fr_buff = matrixbuff[1 - backindex]; // -> front buffer
	//uint16_t offset = rowsize * bDMDByte;
	uint8_t* offset_ptr = fr_buff + rowsize * bDMDByte;
	uint8_t* row1_ptr = offset_ptr + row1;
	uint8_t* row2_ptr = offset_ptr + row2;
	uint8_t* row3_ptr = offset_ptr + row3;
	uint8_t* buf_ptr = dmd_dma_buf;

	for (int i = 0;i < rowsize;i++) {
		*buf_ptr++ = *(row3_ptr++);
		*buf_ptr++ = *(row2_ptr++);
		*buf_ptr++ = *(row1_ptr++);
		*buf_ptr++ = *(offset_ptr++);
	}
#if defined(__STM32F1__) 
	if (SPI_DMD.dev() == SPI1) {
		SPI_DMD.onTransmit(SPI1_DMA_callback);
		dma_attach_interrupt(spiDmaDev, spiTxDmaChannel, SPI1_DMA_callback);
	}
	else if (SPI_DMD.dev() == SPI2) {
		SPI_DMD.onTransmit(SPI2_DMA_callback);
		dma_attach_interrupt(spiDmaDev, spiTxDmaChannel, SPI2_DMA_callback);
	}
#elif defined(__STM32F4__) 
	//SPI_DMD.onTransmit(SPI_DMA_callback);

	if (SPI_DMD.dev() == SPI1) {
		SPI_DMD.onTransmit(SPI1_DMA_callback);
		//dma_attach_interrupt(spiDmaDev, spiTxDmaStream, SPI1_DMA_callback);
	}
	else if (SPI_DMD.dev() == SPI2) {
		SPI_DMD.onTransmit(SPI2_DMA_callback);
		//dma_attach_interrupt(spiDmaDev, spiTxDmaStream, SPI2_DMA_callback);
	}
	else if (SPI_DMD.dev() == SPI3) {
		SPI_DMD.onTransmit(SPI3_DMA_callback);
	}
#endif
	SPI_DMD.dmaSend(dmd_dma_buf, rowsize * 4, 1);
	DEBUG_TIME_MARK;
}

#else
/*--------------------------------------------------------------------------------------
 Scan the dot matrix LED panel display, from the RAM mirror out to the display hardware.
 Call 4 times to scan the whole display which is made up of 4 interleaved rows within the 16 total rows.
 Insert the calls to this function into the main loop for the highest call rate, or from a timer interrupt
--------------------------------------------------------------------------------------*/
//int i = 0;
void DMD_MonoChrome_SPI::scanDisplayBySPI()
{
	uint16_t offset = rowsize * bDMDByte;

#if (defined(__STM32F1__) || defined(__STM32F4__))
	//pwmWrite(pin_DMD_nOE, 0);

	for (int i = 0;i < rowsize;i++) {
		SPI_DMD.write(bDMDScreenRAM[offset + i + row3]);
		SPI_DMD.write(bDMDScreenRAM[offset + i + row2]);
		SPI_DMD.write(bDMDScreenRAM[offset + i + row1]);
		SPI_DMD.write(bDMDScreenRAM[offset + i]);
	}

#elif defined(__AVR_ATmega328P__)
	for (int i = 0;i < rowsize;i++) {
		SPI.transfer(bDMDScreenRAM[offset + i + row3]);
		SPI.transfer(bDMDScreenRAM[offset + i + row2]);
		SPI.transfer(bDMDScreenRAM[offset + i + row1]);
		SPI.transfer(bDMDScreenRAM[offset + i]);
	}
	//OE_DMD_ROWS_OFF();
#endif
	switch_row();
}
// Shift entire screen one pixel
#endif
/*--------------------------------------------------------------------------------------*/
void DMD_MonoChrome_SPI::shiftScreen(int8_t step) {
	uint8_t msb_bit = 0x80;
	uint8_t lsb_bit = 0x01;

	if (inverse_ALL_flag) {
		msb_bit = 0;
		lsb_bit = 0;
	}
	if (step < 0) {
		for (int i = 0; i < mem_Buffer_Size;i++) {
			if ((i % (DisplaysWide * 4)) == (DisplaysWide * 4) - 1) {
				bDMDScreenRAM[i] = (bDMDScreenRAM[i] << 1) + lsb_bit;
			}
			else {
				bDMDScreenRAM[i] = (bDMDScreenRAM[i] << 1) + ((bDMDScreenRAM[i + 1] & 0x80) >> 7);
			}
		}
	}
	else if (step > 0) {
		for (int i = (mem_Buffer_Size)-1; i >= 0;i--) {
			if ((i % (DisplaysWide * 4)) == 0) {
				bDMDScreenRAM[i] = (bDMDScreenRAM[i] >> 1) + msb_bit;
			}
			else {
				bDMDScreenRAM[i] = (bDMDScreenRAM[i] >> 1) + ((bDMDScreenRAM[i - 1] & 1) << 7);
			}
		}
	}
}

#endif

