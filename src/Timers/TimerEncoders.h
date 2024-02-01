#ifndef LECHUGATOR_TIMER_ENCODER_H
#define LECHUGATOR_TIMER_ENCODER_H

#include <Arduino.h>
#include <functional>
#include "../Encoder/Encoder.h"

#define TIMER_INTERRUPT_DEBUG 0
#define _TIMERINTERRUPT_LOGLEVEL_ 0

#include <STM32TimerInterrupt.h>

#define TIMER_DEF TIM5


namespace Lechugator
{
  class TimerEncoders
  {
  private:
    unsigned int debounce;
    STM32Timer ITimerEncoder = STM32Timer(TIMER_DEF);
    std::array<Encoder, 4> &encoders;

  public:
    TimerEncoders(std::array<Encoder, 4> &);
    ~TimerEncoders();

    void init();
    void timerHandler();
  };
  
} // namespace Lechugator

#endif
