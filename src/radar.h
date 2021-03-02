#ifndef __RADAR_H__
#define __RADAR_H__

#include <stdint.h>
#include <Servo.h>

class Radar {
public:
    Radar(uint8_t triggerPin, uint8_t echoPin, uint8_t servoPin);
    void begin();
    void loop();
    float getDistance();

private:
    uint8_t _triggerPin;
    uint8_t _echoPin;
    uint8_t _servoPin;
    uint8_t _currPos;
    Chrono _radarChono;
    Servo _servo;
};

#endif