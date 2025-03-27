#include "analogblinker.h"

analogblinker::analogblinker() : lastpoll(0), dutycycle(0), step(0) {}

void analogblinker::init(uint8_t _pin, uint16_t _blinkTime, uint8_t _polltime, bool _enable)
{
    pin = _pin;
    blinkTime = _blinkTime;
    polltime = _polltime;
    enable = _enable;
    lastpoll = millis();
    dutycycle = 0;
}

void analogblinker::poll()
{
    if (!enable)
    {
        analogWrite(pin, 0);
        return;
    }

    if (millis() - lastpoll > polltime)
    {
        if (blinkTime == 0 || polltime == 0)
        {
            step = 0; // Verhindert Division durch Null
        }
        else
        {
            step = 256 / (blinkTime / polltime);
        }

        dutycycle += step;
        if (dutycycle >= 511)
        {
            dutycycle = 0;
        }
        analogWrite(pin, dutycycle > 255 ? 511 - dutycycle : dutycycle);
        lastpoll = millis();
    }
}