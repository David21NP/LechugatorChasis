#include "TimerEncoders.h"

namespace Lechugator
{
  TimerEncoders::TimerEncoders(std::array<Motor, 4> &_motors) : motors(_motors), ITimerEncoder(STM32Timer(TIMER_DEF))
  {
  }

  TimerEncoders::~TimerEncoders()
  {
  }

  void TimerEncoders::init()
  {
    if (
        ITimerEncoder.attachInterruptInterval(
            // HW_TIMER_INTERVAL_US,
            TIMER_ENCODER_INTERVAL_MS * 1000,
            std::bind(&TimerEncoders::timerHandler, this)))
    {
      Serial.print(F("Starting ITimer1 OK, millis() = "));
      Serial.println(millis());
    }
    else
    {
      Serial.println(F("Can't set ITimer1. Select another freq. or timer"));
    }
    Serial.println("Ejemplo 1");

    // ISR_Timer.setInterval(TIMER_ENCODER_INTERVAL_MS * 1000, std::bind(&TimerEncoders::readEncoder, this));
    // ISR_Timer.setInterval(TIMER_MOTOR_INTERVAL_MS * 1000, std::bind(&TimerEncoders::moveMotor, this));
  }

  void TimerEncoders::timerHandler()
  {
    // ISR_Timer.run();
    readEncoder();
    moveMotor();
  }

  void TimerEncoders::readEncoder()
  {
    for (auto &&motor : motors)
    {
      motor.getEncoder().calcSpeeds();
    }
  }

  void TimerEncoders::moveMotor()
  {
    for (auto &&motor : motors)
    {
      motor.calcIteration();
    }

    // Serial.print(20);
    // Serial.print(motors.at(3).getPIDController().getDesiredValue());
    // Serial.print(" ");
    // Serial.print(motors.at(3).getEncoder().getW());
    // Serial.println();
  }

} // namespace Lechugator
