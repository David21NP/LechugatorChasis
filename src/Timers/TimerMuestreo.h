#ifndef LECHUGATOR_TIMER_MUESTREO_H
#define LECHUGATOR_TIMER_MUESTREO_H

#include <Arduino.h>
#include <functional>

#include "../Motors/Motor.h"

// #include <STM32_ISR_Timer.h>
#include <STM32TimerInterrupt.h>


namespace Lechugator
{
  class TimerMuestreo
  {
  private:
    // STM32_ISR_Timer ISR_Timer;
    STM32Timer ITimerEncoder = STM32Timer(TIMER_MUESTREO_DEF);
    std::array<Motor, 4> &motors;

  public:
    TimerMuestreo(std::array<Motor, 4> &);
    ~TimerMuestreo();

    void init();
    void timerHandler();

    void readEncoder();
    void moveMotor();
    void customCall() {}
  };
  
} // namespace Lechugator

#endif
