#include "LowpassFilter.h"

namespace Lechugator
{
  LowpassFilter::LowpassFilter(const double &_ts, const double &_cutFreq)
  {
    f_cut = _cutFreq;
    const double w0 = 2 * PI * _cutFreq;
    ts = _ts / 1000000.0;

    a1 = -((ts * w0) - 2) / ((ts * w0) + 2);
    b0 = (ts * w0) / ((ts * w0) + 2);
    b1 = b0;
  }

  LowpassFilter::~LowpassFilter()
  {
  }

  double LowpassFilter::filter(const double &_v)
  {
    filteredData = a1 * filteredData + b0 * _v + b1 * prevValue;
    prevValue = _v;

    return filteredData;
  }

} // namespace Lechugator
