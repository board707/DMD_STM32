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


DMD_MonoChrome_SPI::DMD_MonoChrome_SPI(byte _pin_A, byte _pin_B, byte _pin_nOE, byte _pin_SCLK, 
	                                   byte panelsWide, byte panelsHigh, SPIClass _spi,
	                                   bool d_buf, byte dmd_pixel_x, byte dmd_pixel_y)
		:DMD(_pin_A, _pin_B, _pin_nOE, _pin_SCLK, panelsWide, panelsHigh, 
			d_buf, dmd_pixel_x, dmd_pixel_y), SPI_DMD(_spi)
	{

	mem_Buffer_Size = DisplaysTotal * ((DMD_PIXELS_ACROSS*DMD_BITSPERPIXEL / 8)*DMD_PIXELS_DOWN);
	row1 = DisplaysTotal << 4;
	row2 = DisplaysTotal << 5;
	row3 = ((DisplaysTotal << 2) * 3) << 2;
	rowsize = DisplaysTotal << 2;
	

	// Allocate and initialize matrix buffer:
	
	uint16_t allocsize = (dbuf == true) ? (mem_Buffer_Size * 2) : mem_Buffer_Size;
	matrixbuff[0] = (uint8_t *)malloc(allocsize);
	
	// If not double-buffered, both buffers then point to the same address:
	matrixbuff[1] = (dbuf == true) ? &matrixbuff[0][mem_Buffer_Size] : matrixbuff[0];
	backindex = 0;                         
	bDMDScreenRAM = matrixbuff[backindex]; // Back buffer
	front_buff = matrixbuff[1 - backindex]; // -> front buffer

#if defined(__STM32F1__)
		pin_DMD_CLK = SPI_DMD.sckPin();
		pin_DMD_R_DATA = SPI_DMD.mosiPin();
		SPI_DMD.begin(); //Initialize the SPI_2 port.
		
#if defined( DMD_USE_DMA )	
	dmd_dma_buf = (byte*)malloc(mem_Buffer_Size / DMD_MONO_SCAN);
	rx_dma_buf = (byte*)malloc(mem_Buffer_Size / DMD_MONO_SCAN);
		spiDmaDev = DMA1;
		if (SPI_DMD.dev() == SPI1) {
			spiTxDmaChannel = DMA_CH3;
			spi_num = 1;
		}
		else {
			spiTxDmaChannel = DMA_CH5;
			spi_num = 2;
		}

#endif
#elif defined(__AVR_ATmega328P__)
		pin_DMD_CLK = 13;
		pin_DMD_R_DATA = 11;
		
	  // initialize the SPI port
		SPI.begin();		// probably don't need this since it inits the port pins only, which we do just below with the appropriate DMD interface setup
		SPI.setBitOrder(MSBFIRST);	//
		SPI.setDataMode(SPI_MODE0);	// CPOL=0, CPHA=0
		SPI.setClockDivider(DMD_SPI_CLOCK);
#endif
        digitalWrite(pin_DMD_CLK, LOW);	// 
		digitalWrite(pin_DMD_R_DATA, HIGH);	// 
        pinMode(pin_DMD_CLK, OUTPUT);	//
		pinMode(pin_DMD_R_DATA, OUTPUT);	//


}

DMD_MonoChrome_SPI::~DMD_MonoChrome_SPI()
{
	free(matrixbuff[0]);
#if defined( DMD_USE_DMA )	
	free(dmd_dma_buf);
	free(rx_dma_buf);
#endif

}

/*--------------------------------------------------------------------------------------*/
void DMD_MonoChrome_SPI::init(uint16_t scan_interval) {
	
	DMD::init(scan_interval);
	
#if defined(__STM32F1__)
	
	SPI_DMD.begin(); //Initialize the SPI_2 port.
	SPI_DMD.setBitOrder(MSBFIRST); // Set the SPI_2 bit order
	SPI_DMD.setDataMode(SPI_MODE0); //Set the  SPI_2 data mode 0
	//SPI_DMD.setClockDivider(SPI_CLOCK_DIV16);  // Use a different speed to SPI 1 */
	SPI_DMD.beginTransaction(SPISettings(DMD_SPI_CLOCK, MSBFIRST, SPI_MODE0));
	register_running_dmd(this, scan_interval);
	
#endif
	// clean both buffers
	if (matrixbuff[0] != matrixbuff[1]) {
		bDMDScreenRAM = matrixbuff[1 - backindex];
		clearScreen(true);
	}
	bDMDScreenRAM = matrixbuff[backindex];
	clearScreen(true);
}
/*--------------------------------------------------------------------------------------*/
void DMD_MonoChrome_SPI::drawPixel(int16_t x, int16_t y, uint16_t color)
{
	unsigned int uiDMDRAMPointer;
	uint8_t bPixel = color;
	uint16_t bX = x;
	uint16_t bY = y;
	if (bX >= (WIDTH) || bY >= (HEIGHT)) {
		return;
	}
	if (bX < 0 || bY < 0) {
		return;
	}
	// inverse data bits for some panels
	bPixel = bPixel ^ inverse_ALL_flag;

	byte panel = (bX / DMD_PIXELS_ACROSS) + (DisplaysWide*(bY / DMD_PIXELS_DOWN));
	bX = (bX % DMD_PIXELS_ACROSS) + (panel << 5);
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

#if defined(__STM32F1__)

void DMD_MonoChrome_SPI::latchDMA() {
	//SPI_DMD.dmaTransferFinish();
	while (spi_is_tx_empty(SPI_DMD.dev()) == 0); // "5. Wait until TXE=1 ..."
	while (spi_is_busy(SPI_DMD.dev()) != 0); // "... and then wait until BSY=0 before disabling the SPI." 
	spi_tx_dma_disable(SPI_DMD.dev());

	dma_disable(spiDmaDev, spiTxDmaChannel);
	dma_clear_isr_bits(spiDmaDev, spiTxDmaChannel);
#if defined(DEBUG2)
	if (dd_cnt < 100) dd_ptr[dd_cnt++] = Timer4.getCount();
#endif	
	
	switch_row();
#if defined(DEBUG2)
	if (dd_cnt < 100) dd_ptr[dd_cnt++] = Timer4.getCount();
#endif	

}

/*--------------------------------------------------------------------------------------*/
void DMD_MonoChrome_SPI::scanDisplayByDMA()
{
	
	uint8_t* fr_buff = matrixbuff[1 - backindex]; // -> front buffer
    uint16_t offset = rowsize * bDMDByte;
	
	//pwmWrite(pin_DMD_nOE, 0);

	uint8_t* buf_ptr = dmd_dma_buf;

	for (int i = 0;i < rowsize;i++) {
		//SPI_DMD.dmaSendAsync(bDMDScreenRAM, 16);
		*buf_ptr = (fr_buff[offset + i + row3]);buf_ptr++;
		*buf_ptr = (fr_buff[offset + i + row2]);buf_ptr++;
		*buf_ptr = (fr_buff[offset + i + row1]);buf_ptr++;
		*buf_ptr = (fr_buff[offset + i]);buf_ptr++;
	}

	
	if (SPI_DMD.dev() == SPI1) {
		SPI_DMD.onTransmit(SPI1_DMA_callback);
		dma_attach_interrupt(spiDmaDev, spiTxDmaChannel, SPI1_DMA_callback);
	}
	else if (SPI_DMD.dev() == SPI2) {
		SPI_DMD.onTransmit(SPI2_DMA_callback);
		dma_attach_interrupt(spiDmaDev, spiTxDmaChannel, SPI2_DMA_callback);
	}
	
	SPI_DMD.dmaSend(dmd_dma_buf, rowsize * 4, 1);
#if defined(DEBUG2)
	if (dd_cnt < 100) dd_ptr[dd_cnt++] = Timer4.getCount();
#endif	
}
#endif	
/*--------------------------------------------------------------------------------------
 Scan the dot matrix LED panel display, from the RAM mirror out to the display hardware.
 Call 4 times to scan the whole display which is made up of 4 interleaved rows within the 16 total rows.
 Insert the calls to this function into the main loop for the highest call rate, or from a timer interrupt
--------------------------------------------------------------------------------------*/
//int i = 0;
void DMD_MonoChrome_SPI::scanDisplayBySPI()
{
	uint16_t offset = rowsize * bDMDByte;
	
#if defined(__STM32F1__)
	//pwmWrite(pin_DMD_nOE, 0);
	

#if defined(DMD_USE_DMA)
	uint8_t* buf_ptr = dmd_dma_buf;
	for (int i = 0;i < rowsize;i++) {

		*buf_ptr = (bDMDScreenRAM[offset + i + row3]);buf_ptr++;
		*buf_ptr = (bDMDScreenRAM[offset + i + row2]);buf_ptr++;
		*buf_ptr = (bDMDScreenRAM[offset + i + row1]);buf_ptr++;
		*buf_ptr = (bDMDScreenRAM[offset + i]);buf_ptr++;
	}

	SPI_DMD.dmaTransfer(dmd_dma_buf, rx_dma_buf, rowsize * 4);
#else   //  not DMA

	for (int i = 0;i < rowsize;i++) {
		SPI_DMD.write(bDMDScreenRAM[offset + i + row3]);
		SPI_DMD.write(bDMDScreenRAM[offset + i + row2]);
		SPI_DMD.write(bDMDScreenRAM[offset + i + row1]);
		SPI_DMD.write(bDMDScreenRAM[offset + i]);
	}
#endif  //   DMA
	
   //pwmWrite(pin_DMD_nOE, 0);	//for stm32
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
void DMD_MonoChrome_SPI::dumpMatrix(void) {

	int i, buffsize = mem_Buffer_Size;

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


