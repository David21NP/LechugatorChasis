#include "TimerMuestreo.h"

namespace Lechugator
{
  TimerMuestreo::TimerMuestreo(std::array<Motor, 4> &_motors) : motors(_motors), ITimerEncoder(STM32Timer(TIMER_MUESTREO_DEF))
  {
  }

  TimerMuestreo::~TimerMuestreo()
  {
  }

  void TimerMuestreo::init()
  {
    if (
        ITimerEncoder.attachInterruptInterval(
            // HW_TIMER_INTERVAL_US,
            TIMER_ENCODER_INTERVAL_MS * 1000,
            std::bind(&TimerMuestreo::timerHandler, this)))
    {
      Serial.print((String)"Starting ITimer1 OK, millis() = " + millis());
      Serial.println();
    }
    else
    {
      Serial.println(F("Can't set ITimer1. Select another freq. or timer"));
    }
  }

  void TimerMuestreo::timerHandler()
  {
    // ISR_Timer.run();
    readEncoder();
    moveMotor();
    customCall();
  }

  void TimerMuestreo::readEncoder()
  {
    for (auto &&motor : motors)
    {
      Serial.print(motor.getDigitalController().getDesiredValue());
      Serial.print(" ");
      Serial.print(motor.getEncoder().getW());
      Serial.print(" ");
    }
    Serial.println();
  }

  void TimerMuestreo::moveMotor()
  {
    for (auto &&motor : motors)
    {
      motor.calcIteration();
    }
  }

} // namespace Lechugator
