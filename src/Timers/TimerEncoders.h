#ifndef LECHUGATOR_TIMER_ENCODER_H
#define LECHUGATOR_TIMER_ENCODER_H

#include <Arduino.h>
#include <functional>
#include "../Motors/Motor.h"

#define TIMER_INTERRUPT_DEBUG 0
#define _TIMERINTERRUPT_LOGLEVEL_ 0

// #include <STM32_ISR_Timer.h>
#include <STM32TimerInterrupt.h>

#define TIMER_DEF TIM5
#define HW_TIMER_INTERVAL_US 100L


namespace Lechugator
{
  class TimerEncoders
  {
  private:
    // STM32_ISR_Timer ISR_Timer;
    STM32Timer ITimerEncoder = STM32Timer(TIMER_DEF);
    std::array<Motor, 4> &motors;

  public:
    TimerEncoders(std::array<Motor, 4> &);
    ~TimerEncoders();

    void init();
    void timerHandler();

    void readEncoder();
    void moveMotor();
  };
  
} // namespace Lechugator

#endif
