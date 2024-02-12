#include "Motor.h"

namespace Lechugator
{

  Motor::Motor(
      MotorPins _motorPins,
      EncoderPins _encoderPins,
      PIDControllerConst _pidControllerConst,
      StateSpaceConst _stateSpaceConst,
      const unsigned int &_motor_num) : motorPins(_motorPins), motor_num(_motor_num)
  {
    encoder = Encoder(_encoderPins, _motor_num);
    pidController = PIDController(_pidControllerConst);
    stateSpaceController = StateSpace(_stateSpaceConst);
  }
  Motor::Motor(
      MotorPins _motorPins,
      EncoderPins _encoderPins,
      PIDControllerConst _pidControllerConst,
      StateSpaceConst _stateSpaceConst,
      const unsigned int &_motor_num,
      const uint8_t &_maxPwm) : motorPins(_motorPins), motor_num(_motor_num), maxPwm(_maxPwm)
  {
    encoder = Encoder(_encoderPins, _motor_num);
    pidController = PIDController(_pidControllerConst);
    stateSpaceController = StateSpace(_stateSpaceConst);
  }
  Motor::Motor(
      MotorPins _motorPins,
      EncoderPins _encoderPins,
      PIDControllerConst _pidControllerConst,
      StateSpaceConst _stateSpaceConst,
      const unsigned int &_motor_num,
      const uint8_t &_maxPwm,
      const uint8_t &_minPwm) : motorPins(_motorPins), motor_num(_motor_num), maxPwm(_maxPwm), minPwm(_minPwm)
  {
    encoder = Encoder(_encoderPins, _motor_num);
    pidController = PIDController(_pidControllerConst);
    stateSpaceController = StateSpace(_stateSpaceConst);
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
  StateSpace &Motor::getStateSpaceController()
  {
    return stateSpaceController;
  }

  void Motor::init()
  {
    // pinMode(motorPins.pinEN, OUTPUT);
    // pinMode(motorPins.pinPwmR, OUTPUT);
    // pinMode(motorPins.pinPwmL, OUTPUT);
    Polyfill::pinMode(motorPins.pinEN, OUTPUT);
    Polyfill::pinMode(motorPins.pinPwmR, OUTPUT);
    Polyfill::pinMode(motorPins.pinPwmL, OUTPUT);

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
      // analogWrite(motorPins.pinPwmR, constrain(abs(_currPwm), 0, maxPwm));
      Polyfill::analogWrite(motorPins.pinPwmR, constrain(abs(_currPwm), 0, maxPwm));
      // analogWrite(motorPins.pinPwmL, 0);
      Polyfill::analogWrite(motorPins.pinPwmL, 0);
      return;
    }
    if (_currPwm < 0)
    {
      dir = -1;
      digitalWriteFast(motorPins.pinEN, HIGH);
      // analogWrite(motorPins.pinPwmR, 0);
      Polyfill::analogWrite(motorPins.pinPwmR, 0);
      // analogWrite(motorPins.pinPwmL, constrain(abs(_currPwm), 0, minPwm));
      Polyfill::analogWrite(motorPins.pinPwmL, constrain(abs(_currPwm), 0, minPwm));
      return;
    }
    if (_currPwm == 0)
    {
      dir = 0;
      digitalWriteFast(motorPins.pinEN, LOW);
      // analogWrite(motorPins.pinPwmR, 0);
      Polyfill::analogWrite(motorPins.pinPwmR, 0);
      // analogWrite(motorPins.pinPwmL, 0);
      Polyfill::analogWrite(motorPins.pinPwmL, 0);
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
    stateSpaceController.setDesiredValue(_w);
  }

  void Motor::calcIteration()
  {
    // if (pidController.getDesiredValue() == 0.0)
    // {
    //   move(0);
    // } else {
    //   move((uint8_t)fabs(pidController.calcControlSignal((double)1 * encoder.getW())));
    // }
    // stateSpaceController.calcStates(encoder.getCounter());
    // if (stateSpaceController.getDesiredValue() == 0.0)
    // {
    //   move(0);
    // } else {
    //   move((uint8_t)fabs(stateSpaceController.getControlSignal()));
    // }
    // move(20);
    move(stateSpaceController.getDesiredValue());
  }

  uint8_t Motor::getDir()
  {
    return dir;
  }

} // namespace Lechugator
