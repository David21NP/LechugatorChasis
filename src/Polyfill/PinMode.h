#ifndef POLYFILL_PIN_MODE_H
#define POLYFILL_PIN_MODE_H

#include <Arduino.h>

namespace Polyfill
{
  void pinMode(PinName ulPin, uint32_t ulMode);
  void attachInterrupt(PinName pin, callback_function_t callback, uint32_t mode);
  void attachInterrupt(PinName pin, void (*callback)(void), uint32_t mode);
  void detachInterrupt(PinName pin);
} // namespace Polyfill

#endif
