#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <elapsedMillis.h>

namespace Lechugator
{
  struct PIDControllerConst
  {
    double kp = 0;
    double ki = 0;
    double kd = 0;

    PIDControllerConst()
    {
    }
    PIDControllerConst(const double & _kp, const double & _ki, const double & _kd) : kp(_kp), ki(_ki), kd(_kd)
    {
    }
  };

  class PIDController
  {
  private:
    double desiredValue = 0;
    double controlSignal = 0;
    double eIntegral = 0;
    double ePrev = 0;
    double controlSignalPrev = 0;

    elapsedMicros timeDelta = 0;

    PIDControllerConst pidControllerConst;
  public:

    PIDController();
    PIDController(PIDControllerConst _pidControllerConst);
    ~PIDController();

    double calcControlSignal(const double &_currValue);
    void setDesiredValue(const double &_desiredValue);
    double getDesiredValue();
    double getControlSignal();
  };
  
} // namespace Lechugator

#endif
