#ifndef LECHUGATOR_TIMER_ENCODER_H
#define LECHUGATOR_TIMER_ENCODER_H

#include "../config/Pins.h"


namespace Lechugator
{
  class TimerEncoders
  {
  private:
    // STM32_ISR_Timer ISR_Timer;
    HardwareTimer *timerEncoder = new HardwareTimer(TIMER_ENCODER_DEF);
  public:
    TimerEncoders();
    ~TimerEncoders();

    void init();
    void run();

    HardwareTimer * getTimerRef();
  };
  
} // namespace Lechugator

#endif
