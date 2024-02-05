#ifndef LECHUGATOR_ENCODER_H
#define LECHUGATOR_ENCODER_H

#include <Arduino.h>
#include <functional>
#include <elapsedMillis.h>
// #include <SimpleKalmanFilter.h>

#include "../Filters/LowpassFilter.h"

#define TIMER_ENCODER_INTERVAL_MS 1

#define RPM_TO_RADS ((2.0 * PI) / 60.0)
#define RADS_TO_RPM (60.0 / (2.0 * PI))

namespace Lechugator
{
  struct EncoderPins
  {
    PinName pinPulso;
    PinName pinVuelta;

    EncoderPins()
    {
    }
    EncoderPins(PinName _pinPulso) : pinPulso(_pinPulso)
    {
    }
    EncoderPins(PinName _pinPulso, PinName _pinVuelta) : pinPulso(_pinPulso), pinVuelta(_pinVuelta)
    {
    }
  };

  class Encoder
  {
  private:
    unsigned int motor_num = 0;
    uint32_t counter = 0;

    double w = 0;
    double rpm = 0;

    elapsedMicros timeDelta = 0;
    // elapsedMillis timeDelta = 0;

    std::vector<LowpassFilter> filters = {
        {
            LowpassFilter(TIMER_ENCODER_INTERVAL_MS * 1000, 0.8),
            LowpassFilter(TIMER_ENCODER_INTERVAL_MS * 1000, 0.8),
            LowpassFilter(TIMER_ENCODER_INTERVAL_MS * 1000, 0.8),
            LowpassFilter(TIMER_ENCODER_INTERVAL_MS * 1000, 0.8),
            LowpassFilter(TIMER_ENCODER_INTERVAL_MS * 1000, 0.5),
            LowpassFilter(TIMER_ENCODER_INTERVAL_MS * 1000, 0.5),
            LowpassFilter(TIMER_ENCODER_INTERVAL_MS * 1000, 0.3),
        }};

    // Pines
    EncoderPins encoderPins;

  public:
    Encoder();
    Encoder(EncoderPins _encoderPins, const unsigned int &_motor_num);
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
