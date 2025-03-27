#include <Arduino.h>

class blinker
{
private:
    uint8_t pin1, pin2;
    bool enable, state;
    unsigned long last;

public:
    void poll();
    uint16_t blinktime;
    blinker(unsigned long, bool, uint8_t, uint8_t);
};