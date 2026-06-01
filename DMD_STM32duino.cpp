#include "DMD_STM32duino.h"

#if defined(DMD_STM32DUINO)

#include "timer.h"
#include "stm32yyxx_ll_gpio.h"
#include "stm32yyxx_ll_tim.h"

void dmd_hw_timer_prepare(TIM_TypeDef *tim);

static voidFuncPtr dmdMainHandler = nullptr;
static HardwareTimer *dmdMainTimer = nullptr;
static uint32_t dmdOePin = NC;
static PinName dmdOePinName = NC;
static uint8_t dmdOeChannel = 1;

static uint32_t dmd_ll_channel(uint8_t channel) {
  switch (channel) {
    case 1: return LL_TIM_CHANNEL_CH1;
    case 2: return LL_TIM_CHANNEL_CH2;
    case 3: return LL_TIM_CHANNEL_CH3;
    case 4: return LL_TIM_CHANNEL_CH4;
    default: return LL_TIM_CHANNEL_CH1;
  }
}

static TIM_TypeDef *dmd_tim(const timer_dev *dev) {
  return (TIM_TypeDef *)dev;
}

static bool dmd_find_tim3_mapping(uint32_t pin, PinName *outPin, uint8_t *channel) {
  PinName base = digitalPinToPinName(pin);
  if (base == NC) {
    return false;
  }

  const PinName variants[] = {
    base,
    (PinName)(base | ALT1),
    (PinName)(base | ALT2),
  };

  for (PinName variant : variants) {
    for (const PinMap *map = PinMap_TIM; map->pin != NC; map++) {
      if (map->pin == variant && map->peripheral == TIM3) {
        *outPin = variant;
        *channel = STM_PIN_CHANNEL(map->function);
        return true;
      }
    }
  }
  return false;
}

static void dmd_main_timer_isr(void) {
  if (dmdMainHandler) {
    dmdMainHandler();
  }
}

void dmd_force_timers_stop(void) {
  if (dmdMainTimer) {
    dmdMainTimer->pause();
    dmdMainTimer->detachInterrupt();
    delete dmdMainTimer;
    dmdMainTimer = nullptr;
  }
  dmd_hw_timer_prepare(TIM3);
  dmd_hw_timer_prepare(TIM4);
  dmdMainHandler = nullptr;
}

void dmd_set_pin_high_speed(uint32_t pin) {
  if (!digitalPinIsValid(pin)) {
    return;
  }
  PinName pn = digitalPinToPinName(pin);
  GPIO_TypeDef *port = get_GPIO_Port(STM_PORT(pn));
#if defined(STM32F1xx) || defined(__STM32F1__)
  LL_GPIO_SetPinSpeed(port, STM_GPIO_PIN(pn), LL_GPIO_SPEED_FREQ_HIGH);
#else
  LL_GPIO_SetPinSpeed(port, STM_GPIO_PIN(pn), LL_GPIO_SPEED_FREQ_VERY_HIGH);
#endif
}

void dmd_oe_blank_gpio(uint32_t pin) {
  LL_TIM_DisableCounter(TIM3);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
}

void dmd_hw_timer_prepare(TIM_TypeDef *tim) {
  if (!tim) {
    return;
  }

  timer_index_t index = get_timer_index(tim);
  if (HardwareTimer_Handle[index] != nullptr) {
    HardwareTimer_Handle[index] = nullptr;
  }

  if (tim == TIM3) {
    __HAL_RCC_TIM3_FORCE_RESET();
    __HAL_RCC_TIM3_RELEASE_RESET();
    __HAL_RCC_TIM3_CLK_ENABLE();
  } else if (tim == TIM4) {
    __HAL_RCC_TIM4_FORCE_RESET();
    __HAL_RCC_TIM4_RELEASE_RESET();
    __HAL_RCC_TIM4_CLK_ENABLE();
  }
}

uint8_t dmd_get_oe_channel(uint32_t pin) {
  PinName timPin;
  uint8_t channel;
  if (dmd_find_tim3_mapping(pin, &timPin, &channel)) {
    return channel;
  }

  uint32_t function = pinmap_function(digitalPinToPinName(pin), PinMap_TIM);
  if (function == NP) {
    return 1;
  }
  return STM_PIN_CHANNEL(function);
}

void dmd_init_oe_pwm(uint32_t pin, uint8_t channel) {
  dmdOePin = pin;
  dmdOeChannel = channel;

  PinName timPin;
  uint8_t timCh;
  if (dmd_find_tim3_mapping(pin, &timPin, &timCh)) {
    dmdOePinName = timPin;
    dmdOeChannel = timCh;
  } else {
    dmdOePinName = digitalPinToPinName(pin);
  }

  dmd_hw_timer_prepare(TIM3);
  pinmap_pinout(dmdOePinName, PinMap_TIM);

  LL_TIM_DisableCounter(TIM3);
  LL_TIM_SetPrescaler(TIM3, 0);
  LL_TIM_SetAutoReload(TIM3, TIM_MAX_RELOAD);
  LL_TIM_SetCounter(TIM3, 0);

  uint32_t ll_ch = dmd_ll_channel(dmdOeChannel);
  LL_TIM_OC_SetMode(TIM3, ll_ch, LL_TIM_OCMODE_PWM2);
  LL_TIM_CC_EnableChannel(TIM3, ll_ch);
  switch (dmdOeChannel) {
    case 1: LL_TIM_OC_SetCompareCH1(TIM3, 0); break;
    case 2: LL_TIM_OC_SetCompareCH2(TIM3, 0); break;
    case 3: LL_TIM_OC_SetCompareCH3(TIM3, 0); break;
    case 4: LL_TIM_OC_SetCompareCH4(TIM3, 0); break;
  }
}

void timer_init(const timer_dev *dev) {
  TIM_TypeDef *tim = dmd_tim(dev);
  LL_TIM_DisableCounter(tim);
  LL_TIM_SetCounter(tim, 0);
}

void timer_pause(const timer_dev *dev) {
  LL_TIM_DisableCounter(dmd_tim(dev));
}

void timer_resume(const timer_dev *dev) {
  TIM_TypeDef *tim = dmd_tim(dev);
  if (dev == TIMER4) {
    LL_TIM_ClearFlag_UPDATE(tim);
    LL_TIM_EnableIT_UPDATE(tim);
  }
  LL_TIM_EnableCounter(tim);
}

void timer_set_prescaler(const timer_dev *dev, uint16_t prescaler) {
  LL_TIM_SetPrescaler(dmd_tim(dev), prescaler);
}

uint16_t timer_get_prescaler(const timer_dev *dev) {
  return LL_TIM_GetPrescaler(dmd_tim(dev));
}

void timer_set_reload(const timer_dev *dev, uint32_t reload) {
  if (reload == 0) {
    reload = 1;
  }
  LL_TIM_SetAutoReload(dmd_tim(dev), reload);
}

void timer_set_count(const timer_dev *dev, uint32_t count) {
  LL_TIM_SetCounter(dmd_tim(dev), count);
}

void timer_generate_update(const timer_dev *dev) {
  LL_TIM_GenerateEvent_UPDATE(dmd_tim(dev));
}

void timer_set_compare(const timer_dev *dev, uint8_t channel, uint32_t compare) {
  TIM_TypeDef *tim = dmd_tim(dev);
  switch (channel) {
    case 1: LL_TIM_OC_SetCompareCH1(tim, compare); break;
    case 2: LL_TIM_OC_SetCompareCH2(tim, compare); break;
    case 3: LL_TIM_OC_SetCompareCH3(tim, compare); break;
    case 4: LL_TIM_OC_SetCompareCH4(tim, compare); break;
  }
}

void timer_oc_set_mode(const timer_dev *dev, uint8_t channel, timer_oc_mode mode, uint8_t flags) {
  (void)flags;
  TIM_TypeDef *tim = dmd_tim(dev);
  uint32_t ll_ch = dmd_ll_channel(channel);

  switch (mode) {
    case TIMER_OC_MODE_PWM_1:
      LL_TIM_OC_SetMode(tim, ll_ch, LL_TIM_OCMODE_PWM1);
      break;
    case TIMER_OC_MODE_PWM_2:
      LL_TIM_OC_SetMode(tim, ll_ch, LL_TIM_OCMODE_PWM2);
      break;
    case TIMER_OC_MODE_FROZEN:
    default:
      LL_TIM_OC_SetMode(tim, ll_ch, LL_TIM_OCMODE_FROZEN);
      break;
  }
  LL_TIM_CC_EnableChannel(tim, ll_ch);
}

void timer_cc_enable(const timer_dev *dev, uint8_t channel) {
  LL_TIM_CC_EnableChannel(dmd_tim(dev), dmd_ll_channel(channel));
}

void timer_attach_interrupt(const timer_dev *dev, uint8_t type, voidFuncPtr handler) {
  (void)type;
  if (dev != TIMER4 || !handler) {
    return;
  }

  dmdMainHandler = handler;

  if (dmdMainTimer) {
    dmdMainTimer->pause();
    dmdMainTimer->detachInterrupt();
    delete dmdMainTimer;
    dmdMainTimer = nullptr;
  }

  timer_index_t index = get_timer_index(TIM4);
  if (HardwareTimer_Handle[index] != nullptr) {
    HardwareTimer_Handle[index] = nullptr;
  }

  dmdMainTimer = new HardwareTimer(TIM4);
  dmdMainTimer->setPreloadEnable(true);
  dmdMainTimer->attachInterrupt(dmd_main_timer_isr);
}

#endif
