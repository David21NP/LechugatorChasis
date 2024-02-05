#ifndef LOWPASS_FILTER_H
#define LOWPASS_FILTER_H

#define PI 3.1415926535897932384626433832795

namespace Lechugator
{
  class LowpassFilter
  {
  private:
    double filteredData = 0;
    double prevValue = 0;

    double ts = 0;
    double f_cut = 0;

    double a1 = 0;
    double b0 = 0;
    double b1 = 0;
  public:

    LowpassFilter(const double &_ts, const double &_cutFreq);
    ~LowpassFilter();

    double filter(const double &_v);
  };
  
} // namespace Lechugator

#endif
