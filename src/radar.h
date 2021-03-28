#ifndef __RADAR_H__
#define __RADAR_H__

#include <stdint.h>
#include <Servo.h>
#include <Eventually.h>
#include "AsyncSonarLib.h"
#include "vio.h"
#include "device_base.h"

class Radar : DeviceBase, SonarCallback {
public:
    typedef Radar*(*_onPingFunc)(void);

    Radar(Vio *vio, uint8_t triggerPin, uint8_t servoPin);
    void begin();
    bool isEventTriggered();

    virtual void OnPing(AsyncSonar &as);
	virtual void OnTimeOut(AsyncSonar &as);

    friend bool Radar_Update(EvtListener *l, EvtContext *ctx);

private:
    void _updateServo();
    uint8_t _servoPin;
    AsyncSonar _sonar;
    uint8_t _curPos;
    Servo _servo;
    bool _shouldTrigger;
    uint8_t _servoPos;
}; 

#endif