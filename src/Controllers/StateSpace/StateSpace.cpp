#include "StateSpace.h"

namespace Lechugator
{
  StateSpace::StateSpace()
  {
  }

  StateSpace::StateSpace(StateSpaceConst _ssConst) : ssConst(_ssConst)
  {
  }

  StateSpace::~StateSpace()
  {
  }

  double StateSpace::calcStates(const double &_mesuredValue)
  {
    controlSignal = (desiredValue - we + suma_error_previo) * ssConst.KI + x1 * ssConst.K.at(0) + x2 * ssConst.K.at(1);
    suma_error_previo += desiredValue - we;
    // const double usat = constrain(controlSignal, 100, -100);

    const double diff = _mesuredValue * ((2 * PI) / 15) - ae;

    const double _x1 = x1;
    x1 = ssConst.H.at(0) * controlSignal + x1 * ssConst.G.at(0).at(0) + x2 * ssConst.G.at(0).at(1) + ssConst.Ke.at(0) * diff;
    x2 = ssConst.H.at(1) * controlSignal + _x1 * ssConst.G.at(1).at(0) + x2 * ssConst.G.at(1).at(1) + ssConst.Ke.at(1) * diff;

    we = ssConst.CkControl.at(0) * x1 + ssConst.CkControl.at(1) * x2;
    ae = ssConst.CkObserver.at(0) * x1 + ssConst.CkObserver.at(1) * x2;

    // Serial.print(_mesuredValue);
    // Serial.print(" ");
    // Serial.print(ae);
    // Serial.println();

    return controlSignal;
  }

  double StateSpace::getW()
  {
    return we;
  }
  double StateSpace::getA()
  {
    return ae;
  }

  void StateSpace::setDesiredValue(const double &_desiredValue)
  {
    desiredValue = _desiredValue;
  }

  double StateSpace::getDesiredValue()
  {
    return desiredValue;
  }
  double StateSpace::getControlSignal()
  {
    return controlSignal;
  }
}
