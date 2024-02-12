#ifndef RETRO_STATE_SPACE_CONTROLLER_H
#define RETRO_STATE_SPACE_CONTROLLER_H

#include <elapsedMillis.h>

namespace Lechugator
{
  struct StateSpaceConst
  {
    std::vector<std::vector<double>> G;
    std::vector<double> H;
    std::vector<double> CkObserver;
    std::vector<double> CkControl;
    std::vector<double> Ke;
    std::vector<double> K;
    double KI;

    // std::vector<std::vector<double>> G = {{0, 1}, {-0.1023, 1.1023}};
    // std::vector<double> H = {0, 1};
    // std::vector<double> CkObserver = {0.00082852, -0.00042325};
    // std::vector<double> CkControl = {-0.1053, 1.0292};
    // std::vector<double> Ke = {-1131.8, -115.71};
    // std::vector<double> K = {0.052736, -0.061271};
    // double KI = 0.00002559;

    StateSpaceConst()
    {
    }
    StateSpaceConst(std::vector<std::vector<double>> _G,
      std::vector<double> _H,
      std::vector<double> _CkObserver,
      std::vector<double> _CkControl,
      std::vector<double> _Ke,
      std::vector<double> _K,
      const double &_KI
      ) : G(_G), H(_H), CkObserver(_CkObserver), CkControl(_CkControl), Ke(_Ke), K(_K), KI(_KI)
    {
    }
  };

  class StateSpace
  {
  private:
    double desiredValue = 0;
    double controlSignal = 0;

    // std::vector<std::vector<double>> G;
    // std::vector<double> H;
    // std::vector<double> CkObserver;
    // std::vector<double> CkControl;
    // std::vector<double> Ke;
    // std::vector<double> K;
    // double KI;

    StateSpaceConst ssConst;

    double x1 = 0;
    double x2 = 0;
    double we = 0;
    double ae = 0;
    double suma_error_previo = 0;

    elapsedMicros timeDelta = 0;
  public:
    StateSpace();
    StateSpace(StateSpaceConst _ssConst);
    ~StateSpace();

    void setDesiredValue(const double &_desiredValue);
    double getDesiredValue();
    double getControlSignal();

    double calcStates(const double &_mesuredValue);
    double getW();
    double getA();
  };

} // namespace Lechugator

#endif
