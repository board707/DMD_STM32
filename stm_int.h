#pragma once
// STM integer types
#if (defined(__STM32F1__)|| defined(__STM32F4__))
#define uint8_t uint8
#define byte uint8
#define uint16_t uint16
#define int8_t int8
#define int16_t int16 
#endif
#if defined(__STM32F1__) 
#define uint32_t uint32
#endif

