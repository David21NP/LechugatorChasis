#ifndef LECHUGATOR_TIMER_ENCODER_H
#define LECHUGATOR_TIMER_ENCODER_H

#include <Arduino.h>
#include <functional>

#include "../Motors/Motor.h"
#include "../config/Pins.h"

// #include <STM32_ISR_Timer.h>
#include <STM32TimerInterrupt.h>


namespace Lechugator
{
  class TimerEncoders
  {
  private:
    // STM32_ISR_Timer ISR_Timer;
    HardwareTimer TimerEncoder = HardwareTimer(TIMER_ENCODER_DEF);
    std::array<Motor, 4> &motors;

  public:
    TimerEncoders(std::array<Motor, 4> &);
    ~TimerEncoders();

    void init();
    void run();
  };
  
} // namespace Lechugator

#endif
