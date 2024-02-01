#include "TimerEncoders.h"

namespace Lechugator
{
  TimerEncoders::TimerEncoders(std::array<Encoder, 4> &_encoders) : encoders(_encoders), ITimerEncoder(STM32Timer(TIMER_DEF))
  {
  }

  TimerEncoders::~TimerEncoders()
  {
  }

  void TimerEncoders::init()
  {
    if (
        ITimerEncoder.attachInterruptInterval(
            TIMER1_INTERVAL_MS * 1000,
            std::bind(&TimerEncoders::timerHandler, this)))
    {
      Serial.print(F("Starting ITimer1 OK, millis() = "));
      Serial.println(millis());
    }
    else
    {
      Serial.println(F("Can't set ITimer1. Select another freq. or timer"));
    }
  }

  void TimerEncoders::timerHandler()
  {
    for (Encoder &encoder : encoders)
    {
      encoder.calcSpeeds();
    }
    // encoders.at(2).calcSpeeds();
    // encoders.at(3).calcSpeeds();

    Serial.print(0);
    Serial.print(",");
    Serial.print(10);
    Serial.print(",");
    Serial.print(encoders.at(2).getW());
    Serial.print(",");
    Serial.println(encoders.at(3).getW());

    // for (Encoder &encoder : encoders)
    // {
    //   // Serial.print("W");
    //   // Serial.print("_");
    //   // Serial.print(motor_num);
    //   // Serial.print(":");
    //   // Serial.print(w);
    //   // Serial.print(",");
    //   Serial.print("RPM_PROMEDIO");
    //   Serial.print("_");
    //   Serial.print(encoder.getMotorNum());
    //   Serial.print(":");
    //   Serial.print(encoder.getAvgRPM());

    //   Serial.print(",");

    //   Serial.print("RPM");
    //   Serial.print("_");
    //   Serial.print(encoder.getMotorNum());
    //   Serial.print(":");
    //   Serial.print(encoder.getRPM());
    //   // Serial.print(",");
    //   // Serial.print("Vel_lineal");
    //   // Serial.print("_");
    //   // Serial.print(motor_num);
    //   // Serial.print(":");
    //   // Serial.print(vel_lin);
    //   Serial.println();
    // }

    // for (Encoder &encoder : encoders)
    // {
      // Serial.print("W");
      // Serial.print("_");
      // Serial.print(motor_num);
      // Serial.print(":");
      // Serial.print(w);
      // Serial.print(",");


      // Serial.print("RPM_PROMEDIO");
      // Serial.print("_");
      // Serial.print(encoders.at(3).getMotorNum());
      // Serial.print(":");
      // Serial.print(encoders.at(3).getAvgRPM());

      // Serial.print(",");

      // Serial.print("RPM");
      // Serial.print("_");
      // Serial.print(encoders.at(3).getMotorNum());
      // Serial.print(":");
      // Serial.print(encoders.at(3).getRPM());

    // if (encoders.at(3).getAvgRPM() > 0)
    // {
    // }
      // Serial.println(encoders.at(3).getAvgRPM());

      // Serial.print(",");
      // Serial.print("Vel_lineal");
      // Serial.print("_");
      // Serial.print(motor_num);
      // Serial.print(":");
      // Serial.print(vel_lin);
      // Serial.println();
    // }
  }
} // namespace Lechugator
