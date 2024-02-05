#include "Motor.h"

namespace Lechugator
{

  Motor::Motor(MotorPins _motorPins, EncoderPins _encoderPins, PIDControllerConst _pidControllerConst, const unsigned int &_motor_num) : motorPins(_motorPins), motor_num(_motor_num)
  {
    encoder = Encoder(_encoderPins, _motor_num);
    pidController = PIDController(_pidControllerConst);
  }
  Motor::Motor(MotorPins _motorPins, EncoderPins _encoderPins, PIDControllerConst _pidControllerConst, const unsigned int &_motor_num, const uint8_t &_maxPwm) : motorPins(_motorPins), motor_num(_motor_num), maxPwm(_maxPwm)
  {
    encoder = Encoder(_encoderPins, _motor_num);
    pidController = PIDController(_pidControllerConst);
  }
  Motor::Motor(MotorPins _motorPins, EncoderPins _encoderPins, PIDControllerConst _pidControllerConst, const unsigned int &_motor_num, const uint8_t &_maxPwm, const uint8_t &_minPwm) : motorPins(_motorPins), motor_num(_motor_num), maxPwm(_maxPwm), minPwm(_minPwm)
  {
    encoder = Encoder(_encoderPins, _motor_num);
    pidController = PIDController(_pidControllerConst);
  }
  Motor::~Motor()
  {
  }

  Encoder &Motor::getEncoder()
  {
    return encoder;
  }
  PIDController &Motor::getPIDController()
  {
    return pidController;
  }

  void Motor::init()
  {
    pinMode(motorPins.pinEN, OUTPUT);
    pinMode(motorPins.pinPwmR, OUTPUT);
    pinMode(motorPins.pinPwmL, OUTPUT);

    Serial.print(F("Starting Motor OK: "));
    Serial.println(motor_num);

    encoder.init();
  }

  void Motor::move(const int8_t &_currPwm)
  {
    if (_currPwm > 0)
    {
      dir = 1;
      digitalWrite(motorPins.pinEN, HIGH);
      analogWrite(motorPins.pinPwmR, constrain(abs(_currPwm), 0, maxPwm));
      analogWrite(motorPins.pinPwmL, 0);
      return;
    }
    if (_currPwm < 0)
    {
      dir = -1;
      digitalWrite(motorPins.pinEN, HIGH);
      analogWrite(motorPins.pinPwmR, 0);
      analogWrite(motorPins.pinPwmL, constrain(abs(_currPwm), 0, minPwm));
      return;
    }
    if (_currPwm == 0)
    {
      dir = 0;
      digitalWrite(motorPins.pinEN, LOW);
      analogWrite(motorPins.pinPwmR, 0);
      analogWrite(motorPins.pinPwmL, 0);
      return;
    }
  }

  void Motor::moveRpm(const double &_rpm)
  {
    moveW(_rpm * RPM_TO_RADS);
  }

  void Motor::moveW(const double &_w)
  {
    pidController.setDesiredValue(_w);
  }

  void Motor::calcIteration()
  {
    if (pidController.getDesiredValue() == 0.0)
    {
      move(0);

    } else {
      move((uint8_t)fabs(pidController.calcControlSignal((double)1 * encoder.getW())));
    }
    // move(20);
  }

  uint8_t Motor::getDir()
  {
    return dir;
  }

} // namespace Lechugator
