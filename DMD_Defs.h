#ifndef DMD_DEFS_H_
#define DMD_DEFS_H_
#include "stm_int.h"
//#define DEBUG2		1
#define DEBUG_PRINT( x )   Serial1.print( #x );Serial1.print(" = ");Serial1.println( x )

#define UNUSED1(x) (void)(x)
#define UNUSED2(x,y) (void)(x),(void)(y)
#define UNUSED3(x,y,z) (void)(x),(void)(y),(void)(z)
//Arduino toolchain header, version dependent
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#if (defined(ARDUINO_ARCH_RP2040))
#include <hardware/irq.h>
#include <hardware/pwm.h>
#include <hardware/dma.h>
#include <hardware/gpio.h>
#include <pico/stdlib.h> 
#include "dmd_out.pio.h"
#endif
#include "DMD_List.h"
//#define TICS_IN_uS (F_CPU / 1000000ul)
#ifndef CYCLES_PER_MICROSECOND
#define CYCLES_PER_MICROSECOND (F_CPU / 1000000ul)
#endif

#if (defined(__STM32F1__) || defined(__STM32F4__))
typedef uint32 PortType;
#define TIM_MAX_RELOAD ((1 << 16) - 1)
enum OE_PWM_Polarity{ OE_PWM_POSITIVE = TIMER_OC_MODE_PWM_1, OE_PWM_NEGATIVE = TIMER_OC_MODE_PWM_2 };
#elif (defined(ARDUINO_ARCH_RP2040))
#define TIM_MAX_RELOAD ((1 << 16) - 1)
#define MAX_PANEL_CLK 15
enum OE_PWM_Polarity { OE_PWM_POSITIVE = false, OE_PWM_NEGATIVE = true };
typedef uint16_t PortType;
#endif

//Pixel/graphics writing modes (bGraphicsMode)
#define GRAPHICS_NORMAL    1
#define GRAPHICS_INVERSE   0
#define GRAPHICS_TOGGLE    2
#define GRAPHICS_OR        3
#define GRAPHICS_NOR       4

//Panel inverse mode (for some panels)
#define PANEL_INVERSE 0

//Max length of scrolling text
#define MAX_STRING_LEN 300

//drawTestPattern Patterns
#define PATTERN_ALT_0     0
#define PATTERN_ALT_1     1
#define PATTERN_STRIPE_0  2
#define PATTERN_STRIPE_1  3

//Monochrome panel settings
#define DMD_BITSPERPIXEL           1     
#define DMD_MONO_SCAN              4

// Panel connections variants
#define CONNECT_NORMAL 0
#define CONNECT_ROTATE90 1
#define CONNECT_ZIGZAG 2

// Shift marquee result codes
#define MARQUEE_OUT_OF_SCREEN 1					// text has left the screen
#define MARQUEE_JUSTIFY_ON_LEFT 2				// text justify on the left border
#define MARQUEE_JUSTIFY_ON_RIGHT 4				// ...on the right border

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif
#endif