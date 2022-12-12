#pragma once
//====== General setting for all DMD classes =======


// ===== TIMERs setup  ======
#if (defined(__STM32F1__) || defined(__STM32F4__))
// Default timers are 
// MAIN_TIMER = Timer4
// OE_TIMER = Timer3
// OE pin may be one of PA6 PA7 PB0 PB1
//
// Alternative timers setup
// MAIN_TIMER = Timer3
// OE_TIMER = Timer4
// so OE pin may be one of PB6 PB7 PB8 PB9
//
// for alternative timers setup uncomment line below
//#define ALTERNATIVE_DMD_TIMERS
#endif

//comment line below if you need free selections of RGB pins for 1bit color mode
#define DIRECT_OUTPUT

// with STM32F4 use DMA where available
#if ((defined(__STM32F4__)) && ( defined(DIRECT_OUTPUT)))
#define RGB_DMA
#endif


#if (defined(__STM32F1__) || defined(__STM32F4__))
// OE PWM period in us (for Monochrome)
#define OE_PWM_PERIOD  30

// === for Monochrome SPI ===
#define DMD_USE_DMA	1

// === for Monochrome Parallel ===
/* Normally, CLK pin and DATA pins for all parallel matrix rows 
 
    uint8_t pins[] = { PA5, PA7, PA6, PA3 };  // CLK , row1, row 2, row3...
  
  must be selected at lower byte of the same GPIO port.
  By uncommenting the line below, we get the opportunity to select out these 
  pins in the upper byte of the port.
  */
//#define USE_UPPER_8BIT
#endif
