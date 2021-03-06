#ifndef __RADAR_H__
#define __RADAR_H__

#include <stdint.h>
#include <Servo.h>
#include <Eventually.h>
#include "AsyncSonarLib.h"

enum Direction : uint16_t {
    Left = 135,
    Front = 90,
    Right = 45
};

class Radar : EvtListener, SonarCallback {
public:
    typedef Radar*(*_onPingFunc)(void);

    Radar(EvtManager &evtManager, uint8_t triggerPin, uint8_t servoPin, EvtAction action);
    void begin();
    void loop();
    bool isEventTriggered();

    unsigned int distLeft, distFront, distRight;
    virtual void OnPing(AsyncSonar &as);
	virtual void OnTimeOut(AsyncSonar &as);

private:
    void _updateServo();
    EvtManager _evtManager;
    AsyncSonar _sonar;
    uint8_t _servoPin;
    Direction _currPos;
    bool _spin;
    Servo _servo;
    bool _shouldTrigger;
}; 

#endif