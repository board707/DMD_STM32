#pragma once
/*--------------------------------------------------------------------------------------
 This file is a part of the library DMD_STM32

 DMD_STM32.h  - STM32 port of DMD.h library

 https://github.com/board707/DMD_STM32
 Dmitry Dmitriev (c) 2019-2023
 /--------------------------------------------------------------------------------------*/
#if (defined(ARDUINO_ARCH_RP2040))
#error Monochrome_SPI mode unsupported for Rasberry Pico RP2040 
//#elif (defined(__STM32F1__) || defined(__STM32F4__))
#else
#if defined(ARDUINO_ARCH_STM32)
#include "DMD_STM32duino_defs.h"
#endif
#include "DMD_STM32a.h"
#include <SPI.h>
#define DMD_SPI_CLOCK_18MHZ     18000000
#define DMD_SPI_CLOCK_10_5MHZ   10500000
#define DMD_SPI_CLOCK_9MHZ      9000000
#define DMD_SPI_CLOCK_4_5MHZ    4500000
#define DMD_SPI_CLOCK_2_2MHZ    2300000
#define DMD_SPI_CLOCK_1MHZ     1000000

#if defined(DMD_STM32DUINO) 
#if defined(__STM32F1__)
#define DMD_SPI_CLOCK DMD_SPI_CLOCK_9MHZ
#elif defined(__STM32F4__)
/* STM32duino core waits for RXNE after every transmitted byte, 
   so the effective SPI frequency will be lower than the configured one.*/
#define DMD_SPI_CLOCK DMD_SPI_CLOCK_10_5MHZ 
#endif
#else  // libmaple core
#if defined(__STM32F1__)
#define DMD_SPI_CLOCK DMD_SPI_CLOCK_9MHZ
#elif defined(__STM32F4__)
/* The Maple F4 code has a bug that causes the SPI frequency to be 2 * Settings for certain dividers; 
   therefore, we choose a value that is not too high.
*/
#define DMD_SPI_CLOCK DMD_SPI_CLOCK_9MHZ
#endif

#endif

#if defined(DMD_STM32DUINO) && (DMD_USE_DMA)
#include "STM32_SPI_DMA.h"
#endif



class DMD_MonoChrome_SPI :
	public DMD
{
public:
	DMD_MonoChrome_SPI(byte _pin_A, byte _pin_B, byte _pin_nOE, byte _pin_SCLK,
		byte panelsWide, byte panelsHigh, SPIClass& _spi,
		bool d_buf = false, byte dmd_pixel_x = 32, byte dmd_pixel_y = 16);

	~DMD_MonoChrome_SPI();

	void init(uint16_t scan_interval = 1000) override;
	void drawPixel(int16_t x, int16_t y, uint16_t color) override;
	void shiftScreen(int8_t step) override;
	
#if (defined(__STM32F1__)|| defined(__STM32F4__)) 
	uint8_t spi_num = 0;
#endif

#if ( DMD_USE_DMA )
	void scanDisplayByDMA();
	void latchDMA();
#else
	void scanDisplayBySPI();
#endif
protected:
	void set_pin_modes() override;
private:
	byte pin_DMD_R_DATA;   // is SPI Master Out 
	const uint8_t column_size = DMD_MONO_SCAN;
	uint8_t* dmd_dma_ptr = nullptr;
	SPIClass& SPI_DMD;

#if (DMD_USE_DMA)

#if defined(DMD_STM32DUINO)
    SPIDMAClass* spi_dma = nullptr;
#elif defined(__STM32F1__) 
	dma_dev* spiDmaDev;
	dma_channel  spiTxDmaChannel;
#elif defined(__STM32F4__) 
	const dma_dev* spiDmaDev;
	dma_channel  spiTxDmaChannel;
	dma_stream   spiTxDmaStream;
#endif
	
#endif

};

#endif


