#include "Encoder.h"

namespace Lechugator
{
  Encoder::Encoder()
  {
  }
  Encoder::Encoder(EncoderPins _encoderPins, const unsigned int &_motor_num) : encoderPins(_encoderPins), motor_num(_motor_num)
  {
  }

  Encoder::~Encoder()
  {
  }

  void Encoder::init()
  {
    String initStatus = "";

    channel = STM_PIN_CHANNEL(pinmap_function(encoderPins.pinPulso, PinMap_PWM));

    TimerReader.setMode(channel, TIMER_INPUT_CAPTURE_RISING, encoderPins.pinPulso);

    TimerReader.attachInterrupt(channel, std::bind(&Encoder::calcSpeeds, this));

    input_freq = (double)TimerReader.getTimerClkFreq() / (double)TimerReader.getPrescaleFactor();
    overFlow = TimerReader.getOverflow();

    Serial.print((String) "Starting Encoder [" + motor_num + "] Status: Ok");

    pinMode(encoderPins.pinVuelta, INPUT);
  }

  void Encoder::calcSpeeds()
  {
    currentCapture = TimerReader.getCaptureCompare(channel);
    if (currentCapture > lastCapture)
    {
      if ((currentCapture - lastCapture) > 1)
      {
        filteredFreq = (double)input_freq / (double)(currentCapture - lastCapture);
      }
    }
    if (currentCapture <= lastCapture)
    {
      if (filteredFreq <= 7)
      {
        filteredFreq = (double)input_freq / (double)(overFlow + currentCapture - lastCapture);
      }
    }
    for (auto &&filt : filters)
    {
      filteredFreq = filt.filter(filteredFreq);
    }

    lastCapture = currentCapture;
  }

  double Encoder::getW()
  {
    return filteredFreq * (TWO_PI / 15);
  }
  double Encoder::getRPM()
  {
    return filteredFreq * 564971.0 * 2.0;
    ;
  }
  double Encoder::getVelLin(const double &radius)
  {
    return filteredFreq * (TWO_PI / 15) * radius;
  }

} // namespace Lechugator
