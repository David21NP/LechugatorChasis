#include "Motor.h"

namespace Lechugator
{

  Motor::Motor(
      MotorPins _motorPins,
      EncoderPins _encoderPins,
      DigitalController _digitalController,
      const unsigned int &_motor_num) : motorPins(_motorPins), motor_num(_motor_num)
  {
    encoder = Encoder(_encoderPins, _motor_num);
    digitalController = _digitalController;
  }
  Motor::Motor(
      MotorPins _motorPins,
      EncoderPins _encoderPins,
      DigitalController _digitalController,
      const unsigned int &_motor_num,
      const uint8_t &_maxPwm) : motorPins(_motorPins), motor_num(_motor_num), maxPwm(_maxPwm)
  {
    encoder = Encoder(_encoderPins, _motor_num);
    digitalController = _digitalController;
  }
  Motor::Motor(
      MotorPins _motorPins,
      EncoderPins _encoderPins,
      DigitalController _digitalController,
      const unsigned int &_motor_num,
      const uint8_t &_maxPwm,
      const uint8_t &_minPwm) : motorPins(_motorPins), motor_num(_motor_num), maxPwm(_maxPwm), minPwm(_minPwm)
  {
    encoder = Encoder(_encoderPins, _motor_num);
    digitalController = _digitalController;
  }
  Motor::~Motor()
  {
  }

  Encoder &Motor::getEncoder()
  {
    return encoder;
  }
  DigitalController &Motor::getDigitalController()
  {
    return digitalController;
  }

  void Motor::init()
  {
    // pinMode(motorPins.pinEN, OUTPUT);
    // pinMode(motorPins.pinPwmCW, OUTPUT);
    // pinMode(motorPins.pinPwmCCW, OUTPUT);
    Polyfill::pinMode(motorPins.pinEN, OUTPUT);
    Polyfill::pinMode(motorPins.pinPwmCW, OUTPUT);
    Polyfill::pinMode(motorPins.pinPwmCCW, OUTPUT);

    Serial.print(F("Starting Motor OK: "));
    Serial.println(motor_num);

    encoder.init();
  }

  void Motor::move(const int8_t &_currPwm)
  {
    if (_currPwm > 0)
    {
      dir = 1;
      digitalWriteFast(motorPins.pinEN, HIGH);
      // analogWrite(motorPins.pinPwmCW, constrain(abs(_currPwm), 0, maxPwm));
      Polyfill::analogWrite(motorPins.pinPwmCW, constrain(abs(_currPwm), 0, maxPwm));
      // analogWrite(motorPins.pinPwmCCW, 0);
      Polyfill::analogWrite(motorPins.pinPwmCCW, 0);
      return;
    }
    if (_currPwm < 0)
    {
      dir = -1;
      digitalWriteFast(motorPins.pinEN, HIGH);
      // analogWrite(motorPins.pinPwmCW, 0);
      Polyfill::analogWrite(motorPins.pinPwmCW, 0);
      // analogWrite(motorPins.pinPwmCCW, constrain(abs(_currPwm), 0, minPwm));
      Polyfill::analogWrite(motorPins.pinPwmCCW, constrain(abs(_currPwm), 0, minPwm));
      return;
    }
    if (_currPwm == 0)
    {
      dir = 0;
      digitalWriteFast(motorPins.pinEN, LOW);
      // analogWrite(motorPins.pinPwmCW, 0);
      Polyfill::analogWrite(motorPins.pinPwmCW, 0);
      // analogWrite(motorPins.pinPwmCCW, 0);
      Polyfill::analogWrite(motorPins.pinPwmCCW, 0);
      return;
    }
  }

  void Motor::moveRpm(const double &_rpm)
  {
    moveW(_rpm * RPM_TO_RADS);
  }

  void Motor::moveW(const double &_w)
  {
    digitalController.setDesiredValue(_w);
  }

  void Motor::calcIteration()
  {
    // if (digitalController.getDesiredValue() == 0.0)
    // {
    //   move(0);
    // } else {
    //   move((uint8_t)fabs(digitalController.calcControlSignal((double)1 * encoder.getW())));
    // }
    // move(20);
    move(digitalController.getDesiredValue());
  }

  uint8_t Motor::getDir()
  {
    return dir;
  }

} // namespace Lechugator
