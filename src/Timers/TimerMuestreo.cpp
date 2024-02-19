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
    const bool timerConfigured = ITimerEncoder.attachInterruptInterval(
        // HW_TIMER_INTERVAL_US,
        TIMER_MUESTREO_INTERVAL_MS * 1000,
        std::bind(&TimerMuestreo::timerHandler, this));
    #if DEBUG_LECHUGATOR
    Serial.println("========== TIMER MUESTREO ===============");
    if (timerConfigured)
    {
      Serial.print((String)"Starting ITimer1 OK, millis() = " + millis());
      Serial.println();
    }
    else
    {
      Serial.println(F("Can't set ITimer1. Select another freq. or timer"));
    }
    Serial.println("========================================");
    #endif
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
      motor.getEncoder().filterFreq();
    }
    // // Serial.print(motors.at(3).getDigitalController().getDesiredValue());
    // // Serial.print(" ");
    // // Serial.print(motors.at(3).getEncoder().getW());
    // Serial.print(motors.at(3).getDigitalController().getControlSignal());
    // // Serial.print(" ");
    // // Serial.print(motors.at(3).getDigitalController().getControlSignal());
    // Serial.println();

    // Serial.print(motors.at(3).getDigitalController().getDesiredValue());
    // Serial.print(" ");
    // Serial.print(motors.at(3).getEncoder().getW());
    // Serial.println();
  }

  void TimerMuestreo::moveMotor()
  {
    for (auto &&motor : motors)
    {
      motor.calcIteration();
    }
  }

} // namespace Lechugator
