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
    attachInterrupt(digitalPinToInterrupt(encoderPins.pinPulso), std::bind(&Lechugator::Encoder::count, this), FALLING);
    Serial.print(F("Starting Encoder OK: "));
    Serial.println(motor_num);
  }

  void Encoder::count()
  {
    counter++;
  }

  void Encoder::calcSpeeds()
  {
    rpm = (((double)counter) / (double)timeDelta) * 564971.0 * 2.0;

    // Filtro pasabajos
    for (auto &&filt : filters)
    {
      rpm = filt.filter(rpm);
    }

    w = rpm * RPM_TO_RADS;

    //--------------------------- Contdor de pulsos a 0 ----------------------------------------
    counter = 0;
    //--------------------------- cambio del muestreo anterior----------------------------------
    timeDelta = 0;
  }

  unsigned int Encoder::getMotorNum()
  {
    return motor_num;
  }
  double Encoder::getW()
  {
    return w;
  }
  double Encoder::getRPM()
  {
    return rpm;
  }
  double Encoder::getVelLin(const double &radius)
  {
    return w * radius;
  }

} // namespace Lechugator