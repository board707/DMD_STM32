#pragma once

#if defined(ARDUINO_ARCH_STM32)

#include <Arduino.h>
#include <HardwareTimer.h>
#include "PinNamesTypes.h"
#include "pinmap.h"
#include "PeripheralPins.h"

#define DMD_STM32DUINO 1

typedef void (*voidFuncPtr)(void);
typedef TIM_TypeDef timer_dev;
typedef uint32_t PortType;
typedef uint16_t uint16;

#define TIMER1 ((timer_dev *)TIM1)
#define TIMER2 ((timer_dev *)TIM2)
#define TIMER3 ((timer_dev *)TIM3)
#define TIMER4 ((timer_dev *)TIM4)

#define TIMER_UPDATE_INTERRUPT 0
#define TIM_MAX_RELOAD ((1 << 16) - 1)

enum timer_oc_mode {
  TIMER_OC_MODE_PWM_1 = 0,
  TIMER_OC_MODE_PWM_2 = 1,
  TIMER_OC_MODE_FROZEN = 2,
};

enum OE_PWM_Polarity {
  OE_PWM_POSITIVE = TIMER_OC_MODE_PWM_1,
  OE_PWM_NEGATIVE = TIMER_OC_MODE_PWM_2
};

#ifdef portSetRegister
#undef portSetRegister
#endif

static inline volatile uint32_t *dmd_portSetRegister(uint32_t pin) {
  return &(digitalPinToPort(pin)->BSRR);
}
#define portSetRegister(pin) dmd_portSetRegister(pin)

uint8_t dmd_get_oe_channel(uint32_t pin);
void dmd_init_oe_pwm(uint32_t pin, uint8_t channel);
void dmd_set_pin_high_speed(uint32_t pin);
void dmd_oe_blank_gpio(uint32_t pin);
void dmd_hw_timer_prepare(TIM_TypeDef *tim);
void dmd_force_timers_stop(void);

void timer_init(const timer_dev *dev);
void timer_pause(const timer_dev *dev);
void timer_resume(const timer_dev *dev);
void timer_set_prescaler(const timer_dev *dev, uint16_t prescaler);
uint16_t timer_get_prescaler(const timer_dev *dev);
void timer_set_reload(const timer_dev *dev, uint32_t reload);
void timer_set_count(const timer_dev *dev, uint32_t count);
void timer_generate_update(const timer_dev *dev);
void timer_set_compare(const timer_dev *dev, uint8_t channel, uint32_t compare);
void timer_oc_set_mode(const timer_dev *dev, uint8_t channel, timer_oc_mode mode, uint8_t flags);
void timer_cc_enable(const timer_dev *dev, uint8_t channel);
void timer_attach_interrupt(const timer_dev *dev, uint8_t type, voidFuncPtr handler);

#endif
