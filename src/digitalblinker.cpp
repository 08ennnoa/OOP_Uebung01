#include <Arduino.h>
#include "digitalblinker.h"
void blinker::init(unsigned long _blinktime, bool _enable, uint8_t _pin1, uint8_t _pin2)
{
    blinktime = _blinktime;
    enable = _enable;
    pin1 = _pin1;
    pin2 = _pin2;
}

void blinker::poll()
{
    if (!enable)
    {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, HIGH);
        return;
    }

    if (millis() - last > blinktime)
    {
        state = !state;
        digitalWrite(pin1, state);
        digitalWrite(pin2, !state);
        last = millis();
    }
}