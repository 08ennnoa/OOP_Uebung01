#ifndef DIGITALBLINKER_H
#define DIGITALBLINKER_H

#include <Arduino.h>

class blinken
{
    private:
    unsigned long last = 0;
    bool state = false, inv1, inv2, inv3, enable;
    unsigned long blinktime;
    uint8_t led1, led2, led3;

    // Blinkzeit[ms], LED1[PinNr], Invertiert1[T/F], LED2[PinNr], Invertiert2[T/F], Enable[T/F]
    void init(unsigned long, uint8_t, bool, uint8_t, bool, bool);
    void poll();
    void off();
};
#endif