/*--------------------------------------------------------------------------------------
 SPIClass extension with DMA support for STM32duino (Arduino Core STM32) F1/F4 devices.

 Based on https://github.com/nlesc-recruit/STM32F4_SPI_DMA
 /--------------------------------------------------------------------------------------*/

#if defined(ARDUINO_ARCH_STM32)
#include "DMD_STM32duino_defs.h"
#endif

#if defined(DMD_STM32DUINO) && (defined(__STM32F1__) || defined(__STM32F4__))

#include "STM32_SPI_DMA.h"

#if defined(__STM32F4__)
#include <stm32f4xx_ll_bus.h>
#include <stm32f4xx_ll_dma.h>
#include <stm32f4xx_ll_spi.h>
#define DMD_SPI_DMA_ACTIVE_CNT 3
#define dmd_dma_disable(d, x) LL_DMA_DisableStream((d), (x))
#define dmd_dma_is_enabled(d, x) LL_DMA_IsEnabledStream((d), (x))
#define dmd_dma_deinit(d, x) LL_DMA_DeInit((d), (x))
#define dmd_dma_init(d, x, cfg) LL_DMA_Init((d), (x), (cfg))
#define dmd_dma_enable_it_tc(d, x) LL_DMA_EnableIT_TC((d), (x))
#define dmd_dma_set_memory(d, x, a) LL_DMA_SetMemoryAddress((d), (x), (a))
#define dmd_dma_set_length(d, x, l) LL_DMA_SetDataLength((d), (x), (l))
#define dmd_dma_enable(d, x) LL_DMA_EnableStream((d), (x))
#elif defined(__STM32F1__)
#include <stm32f1xx_ll_bus.h>
#include <stm32f1xx_ll_dma.h>
#include <stm32f1xx_ll_spi.h>
#define DMD_SPI_DMA_ACTIVE_CNT 2
#define dmd_dma_disable(d, x) LL_DMA_DisableChannel((d), (x))
#define dmd_dma_is_enabled(d, x) LL_DMA_IsEnabledChannel((d), (x))
#define dmd_dma_deinit(d, x) LL_DMA_DeInit((d), (x))
#define dmd_dma_init(d, x, cfg) LL_DMA_Init((d), (x), (cfg))
#define dmd_dma_enable_it_tc(d, x) LL_DMA_EnableIT_TC((d), (x))
#define dmd_dma_set_memory(d, x, a) LL_DMA_SetMemoryAddress((d), (x), (a))
#define dmd_dma_set_length(d, x, l) LL_DMA_SetDataLength((d), (x), (l))
#define dmd_dma_enable(d, x) LL_DMA_EnableChannel((d), (x))
#endif

static SPIDMAClass *dmd_spi_dma_active[DMD_SPI_DMA_ACTIVE_CNT] = {NULL};

#if defined(__STM32F4__)
static IRQn_Type dmd_dmaTxIrq(DMA_TypeDef *dma, uint32_t stream)
{
	if (dma == DMA1) {
		return (IRQn_Type)(DMA1_Stream0_IRQn + (int)stream);
	}
	return (IRQn_Type)(DMA2_Stream0_IRQn + (int)stream);
}
#elif defined(__STM32F1__)
static IRQn_Type dmd_dmaTxIrq(uint32_t channel)
{
	if (channel == LL_DMA_CHANNEL_3) {
		return DMA1_Channel3_IRQn;
	}
	if (channel == LL_DMA_CHANNEL_5) {
		return DMA1_Channel5_IRQn;
	}
	return (IRQn_Type)-1;
}
#endif

static void dmd_dma_enable_clock(DMA_TypeDef *dma)
{
#if defined(__STM32F4__)
	if (dma == DMA1) {
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	} else {
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
	}
#else
	(void)dma;
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
#endif
}

void SPIDMAClass::setupDma()
{
	_hwspi = getHandle()->Instance;

#if defined(__STM32F4__)
	if (_hwspi == SPI1) {
		_dma = DMA2;
		_txdma = LL_DMA_STREAM_3;
		_txmux = LL_DMA_CHANNEL_3;
		_spiIndex = 1;
		_LL_DMATX_IsActiveFlag_TC = LL_DMA_IsActiveFlag_TC3;
		_LL_DMATX_ClearFlag_TC = LL_DMA_ClearFlag_TC3;
	} else if (_hwspi == SPI2) {
		_dma = DMA1;
		_txdma = LL_DMA_STREAM_4;
		_txmux = LL_DMA_CHANNEL_0;
		_spiIndex = 2;
		_LL_DMATX_IsActiveFlag_TC = LL_DMA_IsActiveFlag_TC4;
		_LL_DMATX_ClearFlag_TC = LL_DMA_ClearFlag_TC4;
	} else if (_hwspi == SPI3) {
		_dma = DMA1;
		_txdma = LL_DMA_STREAM_5;
		_txmux = LL_DMA_CHANNEL_0;
		_spiIndex = 3;
		_LL_DMATX_IsActiveFlag_TC = LL_DMA_IsActiveFlag_TC5;
		_LL_DMATX_ClearFlag_TC = LL_DMA_ClearFlag_TC5;
	} else {
		_dma = NULL;
		return;
	}
#elif defined(__STM32F1__)
	if (_hwspi == SPI1) {
		_dma = DMA1;
		_txdma = LL_DMA_CHANNEL_3;
		_spiIndex = 1;
		_LL_DMATX_IsActiveFlag_TC = LL_DMA_IsActiveFlag_TC3;
		_LL_DMATX_ClearFlag_TC = LL_DMA_ClearFlag_TC3;
	} else if (_hwspi == SPI2) {
		_dma = DMA1;
		_txdma = LL_DMA_CHANNEL_5;
		_spiIndex = 2;
		_LL_DMATX_IsActiveFlag_TC = LL_DMA_IsActiveFlag_TC5;
		_LL_DMATX_ClearFlag_TC = LL_DMA_ClearFlag_TC5;
	} else {
		_dma = NULL;
		return;
	}
#endif

	dmd_spi_dma_active[_spiIndex - 1] = this;

	dmd_dma_disable(_dma, _txdma);
	while (dmd_dma_is_enabled(_dma, _txdma)) {
	}
	dmd_dma_deinit(_dma, _txdma);

	dmd_dma_enable_clock(_dma);

	LL_DMA_InitTypeDef dmaConfig;
	LL_DMA_StructInit(&dmaConfig);
	dmaConfig.PeriphOrM2MSrcAddress = LL_SPI_DMA_GetRegAddr(_hwspi);
	dmaConfig.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
	dmaConfig.Mode = LL_DMA_MODE_NORMAL;
	dmaConfig.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	dmaConfig.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	dmaConfig.PeriphOrM2MSrcDataSize =
		LL_SPI_GetDataWidth(_hwspi) == LL_SPI_DATAWIDTH_8BIT
			? LL_DMA_PDATAALIGN_BYTE
			: LL_DMA_PDATAALIGN_HALFWORD;
	dmaConfig.MemoryOrM2MDstDataSize =
		LL_SPI_GetDataWidth(_hwspi) == LL_SPI_DATAWIDTH_8BIT
			? LL_DMA_MDATAALIGN_BYTE
			: LL_DMA_MDATAALIGN_HALFWORD;
#if defined(__STM32F4__)
	dmaConfig.Channel = _txmux;
#endif
	dmaConfig.Priority = LL_DMA_PRIORITY_VERYHIGH;
	dmd_dma_init(_dma, _txdma, &dmaConfig);

	dmd_dma_enable_it_tc(_dma, _txdma);
#if defined(__STM32F4__)
	NVIC_SetPriority(dmd_dmaTxIrq(_dma, _txdma), 3);
	NVIC_EnableIRQ(dmd_dmaTxIrq(_dma, _txdma));
#else
	NVIC_SetPriority(dmd_dmaTxIrq(_txdma), 3);
	NVIC_EnableIRQ(dmd_dmaTxIrq(_txdma));
#endif
}

void SPIDMAClass::begin(SPIDeviceMode device)
{
	SPIClass::begin(device);
	setupDma();
}

void SPIDMAClass::end()
{
	if (_dma != NULL) {
		dmd_dma_disable(_dma, _txdma);
		while (dmd_dma_is_enabled(_dma, _txdma)) {
		}
		dmd_dma_deinit(_dma, _txdma);
#if defined(__STM32F4__)
		NVIC_DisableIRQ(dmd_dmaTxIrq(_dma, _txdma));
#else
		NVIC_DisableIRQ(dmd_dmaTxIrq(_txdma));
#endif
	}
	if (_spiIndex > 0 && _spiIndex <= DMD_SPI_DMA_ACTIVE_CNT) {
		dmd_spi_dma_active[_spiIndex - 1] = NULL;
	}
	_hwspi = NULL;
	_dma = NULL;
	_busy = false;
	_txCallback = NULL;
	SPIClass::end();
}

void SPIDMAClass::waitAndDisableDma()
{
	if (_hwspi == NULL || _dma == NULL) {
		return;
	}

	while (!LL_SPI_IsActiveFlag_TXE(_hwspi)) {
	}
	while (LL_SPI_IsActiveFlag_BSY(_hwspi)) {
	}

	LL_SPI_DisableDMAReq_TX(_hwspi);
	dmd_dma_disable(_dma, _txdma);
	if (_LL_DMATX_ClearFlag_TC != NULL) {
		_LL_DMATX_ClearFlag_TC(_dma);
	}
	_busy = false;
}

void SPIDMAClass::finishDmaTx()
{
	waitAndDisableDma();
}

void SPIDMAClass::handleDmaIrq()
{
	if (_dma == NULL || _LL_DMATX_IsActiveFlag_TC == NULL) {
		return;
	}
	if (!_LL_DMATX_IsActiveFlag_TC(_dma)) {
		return;
	}

	_LL_DMATX_ClearFlag_TC(_dma);
	dmd_dma_disable(_dma, _txdma);

	while (_hwspi != NULL && !LL_SPI_IsActiveFlag_TXE(_hwspi)) {
	}
	while (_hwspi != NULL && LL_SPI_IsActiveFlag_BSY(_hwspi)) {
	}

	if (_hwspi != NULL) {
		LL_SPI_DisableDMAReq_TX(_hwspi);
	}
	_busy = false;

	if (_txCallback != NULL) {
		_txCallback(_spiIndex);
	}
}

void SPIDMAClass::dmaSend(const void *transmitBuf, uint16_t length, uint16_t flags)
{
	if (_dma == NULL || _hwspi == NULL || transmitBuf == NULL || length == 0) {
		return;
	}

	while (_busy) {
	}

	dmd_dma_disable(_dma, _txdma);
	while (dmd_dma_is_enabled(_dma, _txdma)) {
	}

	dmd_dma_set_memory(_dma, _txdma, (uint32_t)transmitBuf);
	dmd_dma_set_length(_dma, _txdma, length);
	if (_LL_DMATX_ClearFlag_TC != NULL) {
		_LL_DMATX_ClearFlag_TC(_dma);
	}

	LL_SPI_EnableDMAReq_TX(_hwspi);
	_busy = true;
	dmd_dma_enable(_dma, _txdma);

	if (!(flags & DMD_SPI_DMA_ASYNC)) {
		while (_busy) {
		}
	}
}

extern "C" {

#if defined(__STM32F4__)
void DMA2_Stream3_IRQHandler(void)
{
	if (dmd_spi_dma_active[0] != NULL) {
		dmd_spi_dma_active[0]->handleDmaIrq();
	}
}

void DMA1_Stream4_IRQHandler(void)
{
	if (dmd_spi_dma_active[1] != NULL) {
		dmd_spi_dma_active[1]->handleDmaIrq();
	}
}

void DMA1_Stream5_IRQHandler(void)
{
	if (dmd_spi_dma_active[2] != NULL) {
		dmd_spi_dma_active[2]->handleDmaIrq();
	}
}
#elif defined(__STM32F1__)
void DMA1_Channel3_IRQHandler(void)
{
	if (dmd_spi_dma_active[0] != NULL) {
		dmd_spi_dma_active[0]->handleDmaIrq();
	}
}

void DMA1_Channel5_IRQHandler(void)
{
	if (dmd_spi_dma_active[1] != NULL) {
		dmd_spi_dma_active[1]->handleDmaIrq();
	}
}
#endif

}

#endif
