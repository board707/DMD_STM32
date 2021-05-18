#pragma once
#include "DMD_MonoChrome_SPI.h"
#if defined(__STM32F1__)

void register_running_dmd(DMD_MonoChrome_SPI *dmd, uint16_t scan_int =2000);

void inline __attribute__((always_inline)) scan_running_dmds();

void SPI1_DMA_callback();

void SPI2_DMA_callback();

#endif