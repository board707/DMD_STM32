/*--------------------------------------------------------------------------------------
 This file is a part of the library DMD_STM32

 DMD_STM32.h  - STM32 port of DMD.h library

 https://github.com/board707/DMD_STM32
 Dmitry Dmitriev (c) 2019-2023
 /--------------------------------------------------------------------------------------*/

#include "SPI_DMA.h"
#if (defined(__STM32F1__)|| defined(__STM32F4__)) 
#if defined(__STM32F1__)
#define DMD_SPI_CNT 2
#elif defined(__STM32F4__)
#define DMD_SPI_CNT 3
#endif
static volatile DMD_MonoChrome_SPI* running_dmds[DMD_SPI_CNT];
static volatile uint8_t running_dmd_len = 0;

/*--------------------------------------------------------------------------------------*/
void register_running_dmd(DMD_MonoChrome_SPI* dmd, uint16_t scan_int)
{
	uint8_t spi_num = dmd->spi_num;
	if (!spi_num) return;
	
	if (running_dmd_len == 0) {

			dmd->initialize_timers(scan_running_dmds);

	}
	else dmd->initialize_timers( NULL);
	if (!running_dmds[spi_num - 1]) running_dmd_len++;

	running_dmds[spi_num - 1] = dmd;
}
/*--------------------------------------------------------------------------------------*/
void inline __attribute__((always_inline)) scan_running_dmds()
{
	static volatile uint8_t i = 0;
    
	if (!running_dmd_len) return;

	
	DMD_MonoChrome_SPI* next = NULL;

	// search next valid DMD instance (for multi-SPI configuration)
	while (!next) {
		next = (DMD_MonoChrome_SPI*)running_dmds[i % DMD_SPI_CNT];
		i++;
	}

	if (next) {
#if defined( DMD_USE_DMA )
		next->scanDisplayByDMA();
#else
		next->scanDisplayBySPI();
#endif
	}
}
/*--------------------------------------------------------------------------------------*/
#if defined(__STM32F1__) 
void SPI1_DMA_callback() {
	DMD_MonoChrome_SPI* next = (DMD_MonoChrome_SPI*)running_dmds[0];
	next->latchDMA();
}
/*--------------------------------------------------------------------------------------*/
void SPI2_DMA_callback() {
	DMD_MonoChrome_SPI* next = (DMD_MonoChrome_SPI*)running_dmds[1];
	next->latchDMA();
}
/*--------------------------------------------------------------------------------------*/
#elif defined(__STM32F4__) 
void SPI1_DMA_callback(uint32_t spi) {
	DMD_MonoChrome_SPI* next = (DMD_MonoChrome_SPI*)running_dmds[0];
	next->latchDMA();
}
void SPI2_DMA_callback(uint32_t spi) {
	DMD_MonoChrome_SPI* next = (DMD_MonoChrome_SPI*)running_dmds[1];
	next->latchDMA();
}
void SPI3_DMA_callback(uint32_t spi) {
	DMD_MonoChrome_SPI* next = (DMD_MonoChrome_SPI*)running_dmds[2];
	next->latchDMA();
}
#endif
#endif