#pragma once

#if (defined(__STM32F1__)|| defined(__STM32F4__)) 
#include "DMD_MonoChrome_SPI.h"
void register_running_dmd(DMD_MonoChrome_SPI *dmd, uint16_t scan_int =2000);

void inline __attribute__((always_inline)) scan_running_dmds();


#if defined(__STM32F1__) 
void SPI1_DMA_callback();

void SPI2_DMA_callback();
#elif defined(__STM32F4__) 
void SPI1_DMA_callback(uint32_t spi);
void SPI2_DMA_callback(uint32_t spi);
void SPI3_DMA_callback(uint32_t spi);

#endif

#endif
