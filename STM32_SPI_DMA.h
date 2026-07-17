#pragma once
/*--------------------------------------------------------------------------------------
 SPIClass extension with DMA support for STM32duino (Arduino Core STM32) F1/F4 devices.

 Based on https://github.com/nlesc-recruit/STM32F4_SPI_DMA
 Extended with async dmaSend/onTransmit API compatible with DMD_STM32 libmaple path.
 /--------------------------------------------------------------------------------------*/

#if defined(DMD_STM32DUINO) && (defined(__STM32F1__) || defined(__STM32F4__))

#include <SPI.h>

#define DMD_SPI_DMA_ASYNC 1

typedef void (*SPI_DMA_Callback)(uint32_t spi);

class SPIDMAClass : public SPIClass {
public:
	using SPIClass::SPIClass;

	SPIDMAClass(const SPIClass& _spi)
		: SPIClass(_spi) {}

	void begin(SPIDeviceMode device = SPI_MASTER);
	void end();

	void onTransmit(SPI_DMA_Callback callback) { _txCallback = callback; }

	void dmaSend(const void *transmitBuf, uint16_t length, uint16_t flags = 0);
	void finishDmaTx();

	uint8_t spiIndex() const { return _spiIndex; }
	bool dmaReady() const { return _dma != NULL; }
	bool dmaBusy() const { return _busy; }
	void handleDmaIrq();

private:
	void setupDma();
	void waitAndDisableDma();

	SPI_TypeDef *_hwspi = NULL;
	DMA_TypeDef *_dma = NULL;
	uint32_t _txdma = 0;
#if defined(__STM32F4__)
	uint32_t _txmux = 0;
#endif
	uint8_t _spiIndex = 0;
	volatile bool _busy = false;
	SPI_DMA_Callback _txCallback = NULL;

	uint32_t (*_LL_DMATX_IsActiveFlag_TC)(DMA_TypeDef *DMAx) = NULL;
	void (*_LL_DMATX_ClearFlag_TC)(DMA_TypeDef *DMAx) = NULL;
};

#endif
