#ifndef LECHUGATOR_ENCODER_H
#define LECHUGATOR_ENCODER_H

#include <Arduino.h>
#include <functional>
#include <elapsedMillis.h>
// #include <SimpleKalmanFilter.h>

#include "../Filters/LowpassFilter.h"

#define TIMER1_INTERVAL_MS 1

#define RPM_TO_RADS ((2.0 * PI) / 60.0)

namespace Lechugator
{
  class Encoder
  {
  private:
    unsigned int motor_num = 0;
    uint32_t counter = 0;

    double w = 0;
    double rpm = 0;

    // uint32_t timeDelta = 100;
    elapsedMicros timeDelta = 0;
    // elapsedMillis timeDelta = 0;

    // LowpassFilter filter1 = LowpassFilter(0.969, 0.0155);
    // LowpassFilter filter2 = LowpassFilter(0.969, 0.0155);

    // LowpassFilter filter3 = LowpassFilter(0.969, 0.0155);
    // LowpassFilter filter4 = LowpassFilter(0.975, 0.00455);

    std::array<std::array<LowpassFilter, 5>, 4> filters = {{
      {
        // LowpassFilter(TIMER1_INTERVAL_MS * 1000, 10),
        LowpassFilter(TIMER1_INTERVAL_MS * 1000, 5),
        LowpassFilter(TIMER1_INTERVAL_MS * 1000, 2),
        LowpassFilter(TIMER1_INTERVAL_MS * 1000, 1),
        LowpassFilter(TIMER1_INTERVAL_MS * 1000, 0.7),
        LowpassFilter(TIMER1_INTERVAL_MS * 1000, 0.5)
      },
      {
        // LowpassFilter(TIMER1_INTERVAL_MS * 1000, 10),
        LowpassFilter(TIMER1_INTERVAL_MS * 1000, 5),
        LowpassFilter(TIMER1_INTERVAL_MS * 1000, 2),
        LowpassFilter(TIMER1_INTERVAL_MS * 1000, 1),
        LowpassFilter(TIMER1_INTERVAL_MS * 1000, 0.7),
        LowpassFilter(TIMER1_INTERVAL_MS * 1000, 0.5)
      },
      {
        // LowpassFilter(TIMER1_INTERVAL_MS * 1000, 10),
        LowpassFilter(TIMER1_INTERVAL_MS * 1000, 5),
        LowpassFilter(TIMER1_INTERVAL_MS * 1000, 2),
        LowpassFilter(TIMER1_INTERVAL_MS * 1000, 1),
        LowpassFilter(TIMER1_INTERVAL_MS * 1000, 0.7),
        LowpassFilter(TIMER1_INTERVAL_MS * 1000, 0.5)
      },
      {
        // LowpassFilter(TIMER1_INTERVAL_MS * 1000, 10),
        LowpassFilter(TIMER1_INTERVAL_MS * 1000, 5),
        LowpassFilter(TIMER1_INTERVAL_MS * 1000, 2),
        LowpassFilter(TIMER1_INTERVAL_MS * 1000, 1),
        LowpassFilter(TIMER1_INTERVAL_MS * 1000, 0.7),
        LowpassFilter(TIMER1_INTERVAL_MS * 1000, 0.5)
      }
    }};
    // LowpassFilter filter1 = LowpassFilter(TIMER1_INTERVAL_MS * 1000, 5);
    // LowpassFilter filter2 = LowpassFilter(TIMER1_INTERVAL_MS * 1000, 5);

    // LowpassFilter filter3 = LowpassFilter(TIMER1_INTERVAL_MS * 1000, 5);
    // LowpassFilter filter4 = LowpassFilter(TIMER1_INTERVAL_MS * 1000, 5);

    // Pines
    PinName pinPulso;
    PinName pinVuelta;
  public:
    Encoder(PinName _pinPulso, const unsigned int &_motor_num);
    Encoder(PinName _pinPulso, PinName _pinVuelta, const unsigned int &_motor_num);
    ~Encoder();

    void count();

    void calcSpeeds();
    void init();

    unsigned int getMotorNum();
    double getW();
    double getRPM();
    double getVelLin(const double &);
  };
} // namespace Lechugator

#endif
