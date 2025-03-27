#ifndef DIGITALBLINKER_H
#define DIGITALBLINKER_H

#include <Arduino.h>
#include "digitalblinker.h"

void blinken::init(unsigned long _blinktime,
    uint8_t _led1,
    bool _inv1,
    uint8_t _led2,
    bool _inv2,
    uint8_t _led3,
    bool _inv3,
    bool _enable)
{
blinktime = _blinktime;
led1 = _led1;
inv1 = _inv1;
led2 = _led2;
inv2 = _inv2;
led3 = _led3;
inv3 = _inv3;
enable = _enable;

pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);

digitalWrite(led1, inv1 ? HIGH : LOW);
digitalWrite(led2, inv2 ? HIGH : LOW);
digitalWrite(led3, inv3 ? HIGH : LOW);
}

void blinken::poll()
{
if (!enable)
{
return;
}

if (millis() - last > blinktime)
{
state = !state;
digitalWrite(led1, state ? !inv1 : inv1);
digitalWrite(led2, state ? !inv2 : inv2);
digitalWrite(led3, state ? !inv3 : inv3);

last = millis();
}
}

void blinken::off()
{
digitalWrite(led1, inv1 ? HIGH : LOW);
digitalWrite(led2, inv2 ? HIGH : LOW);
digitalWrite(led3, inv3 ? HIGH : LOW);
}







#endif