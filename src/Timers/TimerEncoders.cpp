#include "TimerEncoders.h"

namespace Lechugator
{
  TimerEncoders::TimerEncoders()
  {
  }

  TimerEncoders::~TimerEncoders()
  {
  }

  void Rollover_IT_callback()
  {
    // Serial.println((String)"Run rollback: ");
  }

  void TimerEncoders::init()
  {
    timerEncoder->setPrescaleFactor(PRESCALER_FACTOR_ENCODERS);
    timerEncoder->setOverflow(OVERFLOW_FACTOR_ENCODERS); // Max Period value to have the largest possible time to detect rising edge and avoid timer rollover

    // // Compute this scale factor only once
    // double input_freq = (double)timerEncoder->getTimerClkFreq() / (double)timerEncoder->getPrescaleFactor();

    // Serial.println((String) "FreqTimer = " + timerEncoder->getTimerClkFreq());
    // Serial.println((String) "Prescaler = " + timerEncoder->getPrescaleFactor());
    // Serial.println((String) "Overflow = " + timerEncoder->getOverflow());
    // Serial.println((String) "InputFreq = " + input_freq);
    // Serial.println();

    timerEncoder->attachInterrupt(Rollover_IT_callback);
  }
  void TimerEncoders::run()
  {
    timerEncoder->resume();

    #if DEBUG_LECHUGATOR
    double input_freq = (double)timerEncoder->getTimerClkFreq() / (double)timerEncoder->getPrescaleFactor();

    Serial.println("========== TIMER ENCODERS ===============");
    Serial.println((String) "FreqTimer = " + timerEncoder->getTimerClkFreq());
    Serial.println((String) "Prescaler = " + timerEncoder->getPrescaleFactor());
    Serial.println((String) "Overflow = " + timerEncoder->getOverflow());
    Serial.println((String) "InputFreq = " + input_freq);
    Serial.println("========================================");
    Serial.println("============= CHECK INTERRUPTS ===============");
    for (size_t i = 1; i < 5; i++)
    {
      const bool hasInt = timerEncoder->hasInterrupt(i);
      const bool isRunn = timerEncoder->isRunningChannel(i);
      if (!hasInt)
      {
        Serial.println((String)"Channel [" + i + "] don't have interrupt");
      }
      if (!isRunn)
      {
        Serial.println((String)"Channel [" + i + "] is not running");
      }
    }
    const bool isTimRunn = timerEncoder->isRunning();
    if (!isTimRunn)
    {
      Serial.println((String)"Timer is not running");
    }

    Serial.println("========================================");

    Serial.println();
    #endif
  }

  HardwareTimer * TimerEncoders::getTimerRef()
  {
    return timerEncoder;
  }

} // namespace Lechugator
