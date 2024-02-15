#include "DigitalController.h"

namespace Lechugator
{
  DigitalController::DigitalController()
  {
  }
  DigitalController::DigitalController(std::initializer_list<double> const &_numerator, std::initializer_list<double> const &_denominator) : numerator(_numerator), denominator(_denominator)
  {
    if (denominator.at(0) == 0)
    {
      Serial.println("Error non zero parameter in denominator");
      return;
    }
    for (auto &&num : numerator)
    {
      error.push_back(0.0);
    }
    for (size_t i = 1; i < denominator.size(); i++)
    {
      uSignal.push_back(0.0);
    }
  }
  DigitalController::~DigitalController()
  {
  }

  double DigitalController::calcControlSignal(const double &_currValue)
  {
    // const double e = desiredValue - _currValue;

    // // eIntegral += e * ((double)timeDelta / 1000000.0);

    // // const double q2 = 0.2368;
    // // const double q1 = -0.2328;
    // // const double q1 = 0.85919;
    // // const double q2 = -0.848522;
    // // const double q1 = 1.2772;
    // // const double q2 = -1.2761;
    // // const double q1 = 9.3767;
    // // const double q2 = -9.3487;
    // const double q1 = 1.7876;
    // const double q2 = -1.7869;

    // // controlSignal = pidControllerConst.kp * e + pidControllerConst.ki * eIntegral;
    // // controlSignal = controlSignalPrev + 0.2368 * e - 0.2318 * ePrev;
    // controlSignal = controlSignalPrev + q1 * e + q2 * ePrev;
    // ePrev = e;
    // controlSignalPrev = controlSignal;

    // u         q1 + q2 * z^-1
    // ------ = ------------------- 
    // error     1 - z^-1

    // u = u1 + q1 * e + q2 * e1

    for (size_t i = 1; i < error.size(); i++)
    {
      error[i] = error[i-1];
    }
    error[0] = desiredValue - _currValue;

    double sumUTemp = 0;
    double sumETemp = 0;
    for (size_t i = 1; i < denominator.size(); i++)
    {
      sumUTemp += uSignal[i-1] * denominator[i] * -1;
    }
    for (size_t i = 0; i < numerator.size(); i++)
    {
      sumETemp += error[i] * numerator[i];
    }
    uSignal[0] = (sumUTemp + sumETemp)/denominator[0];
    for (size_t i = 1; i < uSignal.size(); i++)
    {
      uSignal[i] = uSignal[i-1];
    }

    return uSignal[0];
  }

  void DigitalController::setDesiredValue(const double &_desiredValue)
  {
    desiredValue = _desiredValue;
  }

  double DigitalController::getDesiredValue()
  {
    return desiredValue;
  }
  double DigitalController::getControlSignal()
  {
    return uSignal[0];
  }

} // namespace Lechugator
