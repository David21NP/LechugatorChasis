#include "LedsRGB.h"

namespace Lechugator
{

  LedsRGB::LedsRGB()
  {
  }
  LedsRGB::LedsRGB(PinName _rPin, PinName _gPin, PinName _bPin) : rPin(_rPin), gPin(_gPin), bPin(_bPin)
  {
  }
  LedsRGB::~LedsRGB()
  {
  }

  void LedsRGB::init()
  {
    Polyfill::pinMode(rPin, OUTPUT);
    Polyfill::pinMode(gPin, OUTPUT);
    Polyfill::pinMode(bPin, OUTPUT);

    // digitalWriteFast(rPin, LED_OFF);
    // digitalWriteFast(gPin, LED_OFF);
    // digitalWriteFast(bPin, LED_OFF);

    digitalWriteFast(rPin, LED_ON);
    digitalWriteFast(gPin, LED_ON);
    digitalWriteFast(bPin, LED_ON);

    Serial.print(F("Starting Leds OK."));
    Serial.println();
  }

  void LedsRGB::prenderBlanco()
  {
    if (timeDelta > 1000) {
      digitalToggleFast(rPin);
      digitalToggleFast(gPin);
      digitalToggleFast(bPin);
      timeDelta = 0;
    }
  }

} // namespace Lechugator
