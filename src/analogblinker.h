#ifndef ANALONGBLINKER_H
#define ANALONGBLINKER_H


#include <Arduino.h>
#include "analogblinker.h"


class analogblinker
{
private:
    uint8_t pin;
    uint16_t blinkTime;
    uint8_t polltime;
    bool enable;
    uint32_t lastpoll;
    uint16_t dutycycle;
    uint16_t step;

public:
    analogblinker();
    void init(uint8_t _pin, uint16_t _blinkTime, uint8_t _polltime, bool _enable);
    void poll();
};

#endif

