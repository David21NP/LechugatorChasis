#include "PIDController.h"

namespace Lechugator
{
  PIDController::PIDController()
  {
  }
  PIDController::PIDController(PIDControllerConst _pidControllerConst) : pidControllerConst(_pidControllerConst)
  {
  }
  PIDController::~PIDController()
  {
  }

  double PIDController::calcControlSignal(const double &_currValue)
  {
    const double e = desiredValue - _currValue;

    // eIntegral += e * ((double)timeDelta / 1000000.0);
    ePrev = e;

    // const double q2 = 0.2368;
    // const double q1 = -0.2328;
    // const double q1 = 0.85919;
    // const double q2 = -0.848522;
    // const double q1 = 1.2772;
    // const double q2 = -1.2761;
    // const double q1 = 9.3767;
    // const double q2 = -9.3487;
    const double q1 = 1.7876;
    const double q2 = -1.7869;

    // controlSignal = pidControllerConst.kp * e + pidControllerConst.ki * eIntegral;
    // controlSignal = controlSignalPrev + 0.2368 * e - 0.2318 * ePrev;
    controlSignal = controlSignalPrev + q1 * e + q2 * ePrev;
    controlSignalPrev = controlSignal;

    // u         q2 * z^-1 + q1
    // ------ = ------------------- 
    // error     1 - z^-1


    // u = u1 + q2 * e1 + q1 * e


    return controlSignal;
  }

  void PIDController::setDesiredValue(const double &_desiredValue)
  {
    desiredValue = _desiredValue;
  }

  double PIDController::getDesiredValue()
  {
    return desiredValue;
  }
  double PIDController::getControlSignal()
  {
    return controlSignal;
  }

} // namespace Lechugator
