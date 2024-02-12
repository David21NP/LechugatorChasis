#include <Arduino.h>
// #include <wiring_constants.h>

#define TIMER_ENCODER_DEF TIM1
#define PRESCALER_FACTOR_ENCODERS 0xFFFFFFFF
#define OVERFLOW_FACTOR_ENCODERS 0xFFFFFFFF

#define TIMER_INTERRUPT_DEBUG 0
#define _TIMERINTERRUPT_LOGLEVEL_ 0

#define TIMER_MUESTREO_DEF TIM5
#define HW_TIMER_INTERVAL_US 100L
#define TIMER_ENCODER_INTERVAL_MS 1

#define RADS_TO_RPM 60.0 / TWO_PI
#define RPM_TO_RADS 1 / RADS_TO_RPM
