#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "../Encoder/Encoder.h"
#include "../Controllers/DigitalController.h"
#include "../Polyfill/PinMode.h"
#include "../Polyfill/Analog.h"

#define TIMER_MOTOR_INTERVAL_MS 10

namespace Lechugator
{
  struct MotorPins
  {
    PinName pinEN;
    PinName pinPwmCW;
    PinName pinPwmCCW;

    MotorPins()
    {
    }
    MotorPins(PinName _pinEN, PinName _pinPwmCW, PinName _pinPwmCCW) : pinEN(_pinEN), pinPwmCW(_pinPwmCW), pinPwmCCW(_pinPwmCCW)
    {
    }
  };

  class Motor
  {
  private:
    unsigned int motor_num = 0;
    uint8_t maxPwm = 100;
    uint8_t minPwm = 100;
    uint8_t dir = 0;

    Encoder encoder;
    DigitalController digitalController;

    // Pines
    MotorPins motorPins;

  public:
    Motor(
        MotorPins _motorPins,
        EncoderPins _encoderPins,
        DigitalController _digitalController,
        const unsigned int &_motor_num);
    Motor(
        MotorPins _motorPins,
        EncoderPins _encoderPins,
        DigitalController _digitalController,
        const unsigned int &_motor_num,
        const uint8_t &_maxPwm);
    Motor(
        MotorPins _motorPins,
        EncoderPins _encoderPins,
        DigitalController _digitalController,
        const unsigned int &_motor_num,
        const uint8_t &_maxPwm,
        const uint8_t &_minPwm);
    ~Motor();

    Encoder &getEncoder();
    DigitalController &getDigitalController();

    void init();

    void move(const int8_t &_currPwm);
    void moveRpm(const double &_rpm);
    void moveW(const double &_w);

    void calcIteration();

    uint8_t getDir();
  };

} // namespace Lechugator

#endif
