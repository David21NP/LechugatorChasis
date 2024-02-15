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

  void aver123()
  {
    Serial.println((String)"Run callback: ");
  }

  void Encoder::init(HardwareTimer *_timerReader)
  {
    timerReader = _timerReader;
    String initStatus = "";

    channel = STM_PIN_CHANNEL(pinmap_function(encoderPins.pinPulso, PinMap_PWM));

    timerReader->setMode(channel, TIMER_INPUT_CAPTURE_RISING, encoderPins.pinPulso);

    timerReader->attachInterrupt(channel, std::bind(&Encoder::calcSpeeds, this));

    input_freq = (double)timerReader->getTimerClkFreq() / (double)timerReader->getPrescaleFactor();
    overFlow = timerReader->getOverflow();

    #if DEBUG_LECHUGATOR
    Serial.println("=============== ENCODER ================");
    Serial.print((String) "Starting Encoder [" + motor_num + "] Status: Ok");
    Serial.println();
    Serial.println("========================================");
    #endif;

    pinMode(encoderPins.pinVuelta, INPUT);
  }

  void Encoder::calcSpeeds()
  {
    // Serial.println((String)"Run callback: " + motor_num);
    currentCapture = timerReader->getCaptureCompare(channel);
    if (currentCapture > lastCapture)
    {
      if ((currentCapture - lastCapture) > 1)
      {
        filteredFreq = (double)input_freq / (double)(currentCapture - lastCapture);
      }
    }
    if (currentCapture < lastCapture)
    {
      // if (filteredFreq <= 7)
      // {
      // }
      filteredFreq = (double)input_freq / (double)(overFlow + currentCapture - lastCapture);
    }

    lastCapture = currentCapture;
    timeDelta = 0;
  }

  void Encoder::filterFreq()
  {
    if (timeDelta > 500)
    {
      filteredFreq = 0;
    }
    for (auto &&filt : filters)
    {
      filteredFreq = filt.filter(filteredFreq);
    }
  }

  double Encoder::getFreq()
  {
    return filteredFreq;
  }
  double Encoder::getW()
  {
    return filteredFreq * (TWO_PI / 15);
  }
  double Encoder::getRPM()
  {
    return filteredFreq * 4;
    // return filteredFreq * (TWO_PI / 15) * RADS_TO_RPM;
    // return filteredFreq * 564971.0 * 2.0;
  }
  double Encoder::getVelLin(const double &radius)
  {
    return filteredFreq * (TWO_PI / 15) * radius;
  }

} // namespace Lechugator
