#include "SPI_DMA.h"
static volatile DMD_MonoChrome_SPI* running_dmds[2];
static volatile uint8_t running_dmd_len = 0;
//static uint16_t scan_int = 2000;

void register_running_dmd(DMD_MonoChrome_SPI *dmd, uint16_t scan_int)
{
	uint8_t spi_num = dmd->spi_num;
	if (!spi_num) return;
	if (running_dmd_len == 0) {

		uint32 period_cyc = scan_int * CYCLES_PER_MICROSECOND;
		dmd->setup_main_timer(period_cyc, scan_running_dmds);
		
	}
	if (!running_dmds[spi_num - 1]) running_dmd_len++;

	running_dmds[spi_num - 1] = dmd;
}

void inline __attribute__((always_inline)) scan_running_dmds()
{
	static volatile uint8_t i = 0;

	DMD_MonoChrome_SPI *next = (DMD_MonoChrome_SPI*)running_dmds[i % 2];
	i++;
	if (next) {
#if defined( DMD_USE_DMA )
		next->scanDisplayByDMA();
#else
		next->scanDisplayBySPI();
#endif
	}

}
void SPI1_DMA_callback() {
	DMD_MonoChrome_SPI *next = (DMD_MonoChrome_SPI*)running_dmds[0];
	next->latchDMA();
}

void SPI2_DMA_callback() {
	DMD_MonoChrome_SPI *next = (DMD_MonoChrome_SPI*)running_dmds[1];
	next->latchDMA();
}
