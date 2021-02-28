#ifndef __RADAR_H__
#define __RADAR_H__

#include <stdint.h>

class Radar {
public:
    Radar(uint8_t triggerPin, uint8_t echoPin);
    void begin();
    float getDistance();

private:
    uint8_t _triggerPin;
    uint8_t _echoPin;
};

#endif