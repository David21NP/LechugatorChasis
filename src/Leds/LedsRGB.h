#ifndef LEDS_RGB_H
#define LEDS_RGB_H

#include <elapsedMillis.h>
#include "../Polyfill/PinMode.h"

#define LED_ON HIGH
#define LED_OFF LOW

namespace Lechugator
{
  class LedsRGB
  {
  private:
    elapsedMicros timeDelta = 0;

    PinName rPin;
    PinName gPin;
    PinName bPin;

  public:
    LedsRGB();
    LedsRGB(PinName _rPin, PinName _gPin, PinName _bPin);
    ~LedsRGB();

    void init();

    void prenderBlanco();
    void prenderRojo();
    void prenderGreen();
    void prenderAzul();
    void prenderRosado();
    void prenderAmarillo();
    void prenderAzulClaro();
    void prenderApagado();
  };

} // namespace Lechugator

#endif
