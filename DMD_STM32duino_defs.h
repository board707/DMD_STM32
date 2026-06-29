#if defined(ARDUINO_ARCH_STM32)

#ifndef DMD_STM32DUINO
#define DMD_STM32DUINO 1
#endif

#if defined(STM32F4xx) && !defined(__STM32F4__)
#define __STM32F4__ 1
#endif

#if defined(STM32F1xx) && !defined(__STM32F1__)
#define __STM32F1__ 1
#endif

#endif
