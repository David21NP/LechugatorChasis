#include "TimerEncoders.h"

namespace Lechugator
{
  TimerEncoders::TimerEncoders(std::array<Motor, 4> &_motors) : motors(_motors)
  {
  }

  TimerEncoders::~TimerEncoders()
  {
  }

  void TimerEncoders::init()
  {
    TimerEncoder.setPrescaleFactor(PRESCALER_FACTOR_ENCODERS);
    TimerEncoder.setOverflow(OVERFLOW_FACTOR_ENCODERS); // Max Period value to have the largest possible time to detect rising edge and avoid timer rollover

    // Compute this scale factor only once
    double input_freq = (double)TimerEncoder.getTimerClkFreq() / (double)TimerEncoder.getPrescaleFactor();

    Serial.println((String) "FreqTimer = " + TimerEncoder.getTimerClkFreq());
    Serial.println((String) "Prescaler = " + TimerEncoder.getPrescaleFactor());
    Serial.println((String) "Overflow = " + TimerEncoder.getOverflow());
    Serial.println((String) "InputFreq = " + input_freq);
    Serial.println();
  }
  void TimerEncoders::run()
  {
    TimerEncoder.resume();
  }

} // namespace Lechugator
