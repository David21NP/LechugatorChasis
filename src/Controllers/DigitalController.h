#ifndef DIGITAL_CONTROLLER_H
#define DIGITAL_CONTROLLER_H

#include "../config/Pins.h"

namespace Lechugator
{
  class DigitalController
  {
  private:
    double desiredValue = 0;
    double controlSignal = 0;
    double eIntegral = 0;
    double ePrev = 0;
    double controlSignalPrev = 0;

    std::vector<double> error;
    std::vector<double> uSignal;

    std::vector<double> numerator;
    std::vector<double> denominator;
  public:

    DigitalController();
    DigitalController(std::initializer_list<double> const &_numerator, std::initializer_list<double> const &_denominator);
    ~DigitalController();

    double calcControlSignal(const double &_currValue);
    void setDesiredValue(const double &_desiredValue);
    double getDesiredValue();
    double getControlSignal();
    void setControlSignal(const double &_val);
    void resetControlSignal();
  };
  
} // namespace Lechugator

#endif
