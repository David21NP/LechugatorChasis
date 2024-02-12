#include "PinMode.h"
#include <PinConfigured.h>

namespace Polyfill
{
  static uint32_t g_anOutputPinConfigured[MAX_NB_PORT];

  void pinMode(PinName ulPin, uint32_t ulMode)
  {
    PinName p = ulPin;

    if (p != NC)
    {
      // If the pin that support PWM or DAC output, we need to turn it off
#if (defined(HAL_DAC_MODULE_ENABLED) && !defined(HAL_DAC_MODULE_ONLY)) || \
    (defined(HAL_TIM_MODULE_ENABLED) && !defined(HAL_TIM_MODULE_ONLY))
      if (is_pin_configured(p, g_anOutputPinConfigured))
      {
#if defined(HAL_DAC_MODULE_ENABLED) && !defined(HAL_DAC_MODULE_ONLY)
        if (pin_in_pinmap(p, PinMap_DAC))
        {
          dac_stop(p);
        }
        else
#endif // HAL_DAC_MODULE_ENABLED && !HAL_DAC_MODULE_ONLY
#if defined(HAL_TIM_MODULE_ENABLED) && !defined(HAL_TIM_MODULE_ONLY)
            if (pin_in_pinmap(p, PinMap_TIM))
        {
          pwm_stop(p);
        }
#endif // HAL_TIM_MODULE_ENABLED && !HAL_TIM_MODULE_ONLY
        {
          reset_pin_configured(p, g_anOutputPinConfigured);
        }
      }
#endif
      switch (ulMode)
      {
      case INPUT: /* INPUT_FLOATING */
        pin_function(p, STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, 0));
        break;
      case INPUT_PULLUP:
        pin_function(p, STM_PIN_DATA(STM_MODE_INPUT, GPIO_PULLUP, 0));
        break;
      case INPUT_PULLDOWN:
        pin_function(p, STM_PIN_DATA(STM_MODE_INPUT, GPIO_PULLDOWN, 0));
        break;
      case INPUT_ANALOG:
        pin_function(p, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0));
        break;
      case OUTPUT:
        pin_function(p, STM_PIN_DATA(STM_MODE_OUTPUT_PP, GPIO_NOPULL, 0));
        break;
      case OUTPUT_OPEN_DRAIN:
        pin_function(p, STM_PIN_DATA(STM_MODE_OUTPUT_OD, GPIO_NOPULL, 0));
        break;
      default:
        Error_Handler();
        break;
      }
    }
  }

  void attachInterrupt(PinName pin, callback_function_t callback, uint32_t mode)
  {
#if !defined(HAL_EXTI_MODULE_DISABLED)
    uint32_t it_mode;
    PinName p = pin;
    GPIO_TypeDef *port = set_GPIO_Port_Clock(STM_PORT(p));
    if (!port)
    {
      return;
    }

    switch (mode)
    {
    case CHANGE:
      it_mode = GPIO_MODE_IT_RISING_FALLING;
      Serial.println("Configurado con cambio");
      break;
    case FALLING:
    case LOW:
      it_mode = GPIO_MODE_IT_FALLING;
      Serial.println("Configurado de bajada");
      break;
    case RISING:
    case HIGH:
      it_mode = GPIO_MODE_IT_RISING;
      Serial.println("Configurado de subida");
      break;
    default:
      it_mode = GPIO_MODE_IT_RISING;
      break;
    }

#ifdef STM32F1xx
    pinF1_DisconnectDebug(p);
#endif /* STM32F1xx */

    stm32_interrupt_enable(port, STM_GPIO_PIN(p), callback, it_mode);
#else
    UNUSED(pin);
    UNUSED(callback);
    UNUSED(mode);
#endif
  }

  void attachInterrupt(PinName pin, void (*callback)(void), uint32_t mode)
  {
#if !defined(HAL_EXTI_MODULE_DISABLED)
    callback_function_t _c = callback;
    attachInterrupt(pin, _c, mode);
#else
    UNUSED(pin);
    UNUSED(callback);
    UNUSED(mode);
#endif
  }

  void detachInterrupt(PinName pin)
  {
#if !defined(HAL_EXTI_MODULE_DISABLED)
    PinName p = pin;
    GPIO_TypeDef *port = get_GPIO_Port(STM_PORT(p));
    if (!port)
    {
      return;
    }
    stm32_interrupt_disable(port, STM_GPIO_PIN(p));
#else
    UNUSED(pin);
#endif
  }

} // namespace Polyfill
