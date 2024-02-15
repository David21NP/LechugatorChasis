#ifndef LECHUGATOR_ENCODER_H
#define LECHUGATOR_ENCODER_H

#include <Arduino.h>
#include <functional>
#include <exception>
#include <elapsedMillis.h>

#include "../Filters/LowpassFilter.h"

#include "../config/Pins.h"

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

    HardwareTimer *timerReader;
    // HardwareTimer timerReader = HardwareTimer(TIMER_ENCODER_DEF);
    uint32_t channel;

    uint32_t currentCapture = 0;
    uint32_t lastCapture = 0;
    uint32_t overFlow = 0xFFFFFFFF;

    double filteredFreq = 0;
    double input_freq = 0;

    // elapsedMicros timeDelta = 0;
    elapsedMillis timeDelta = 0;

    std::vector<LowpassFilter> filters = {
        {
            // LowpassFilter(TIMER_MUESTREO_INTERVAL_MS * 1000, 500),
            // LowpassFilter(TIMER_MUESTREO_INTERVAL_MS * 1000, 100),
            // LowpassFilter(TIMER_MUESTREO_INTERVAL_MS * 1000, 50),
            // LowpassFilter(TIMER_MUESTREO_INTERVAL_MS * 1000, 25),
            // LowpassFilter(TIMER_MUESTREO_INTERVAL_MS * 1000, 10),
            // LowpassFilter(TIMER_MUESTREO_INTERVAL_MS * 1000, 5),
            // LowpassFilter(TIMER_MUESTREO_INTERVAL_MS * 1000, 1),
        }};

    // Pines
    EncoderPins encoderPins;

  public:
    Encoder();
    Encoder(EncoderPins _encoderPins, const unsigned int &_motor_num);
    ~Encoder();

    void init(HardwareTimer *_timerReader);
    void calcSpeeds();
    void filterFreq();

    void serTimer();

    double getFreq();
    double getW();
    double getRPM();
    double getVelLin(const double &);
  };
} // namespace Lechugator

#endif
