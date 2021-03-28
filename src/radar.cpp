#include <Arduino.h>
#include <Chrono.h>
#include "radar.h"

extern EvtManager evtManager;

static const uint8_t _angles[] PROGMEM = {45, 90, 135, 90};
static const ChassiSide _sides[] PROGMEM= {Right, Front, Left, Front};

Radar::Radar(Vio *vio, uint8_t triggerPin, uint8_t servoPin) : 
    DeviceBase(vio),
    _servoPin(servoPin),
    _sonar(triggerPin, *this),
    _curPos(0),
    _servo(),
    _shouldTrigger(false)
{
}

void Radar::begin()
{   
    DeviceBase::begin();
    _sonar.SetTimeOutDistance(2000);
    _servo.attach(_servoPin);
    _servo.write(pgm_read_byte_near(_angles + _curPos));
    _curPos &= 0x03;
    _sonar.Start(100);
}

void Radar::loop()
{
    this->_sonar.Update();
}

uint16_t Radar::getTimeLoop()
{
    return 10;
}

void Radar::_updateServo()
{
    _curPos++;
    _curPos &= 0x03;    
    _servo.write(pgm_read_byte_near(_angles + _curPos));
}

void Radar::OnPing(AsyncSonar& as)
{
    ChassiSide side = static_cast<ChassiSide>(pgm_read_byte_near(_sides + _curPos));
    _vio->setRadarDist(side, as.GetMeasureMM());
    _updateServo();
    _sonar.Start(333);
}

void Radar::OnTimeOut(AsyncSonar& as)
{
    ChassiSide side = static_cast<ChassiSide>(pgm_read_byte_near(_sides + _curPos));
    _vio->setRadarDist(side, 0);    
    _updateServo();
    _sonar.Start(333);
}

bool Radar::isEventTriggered() {
    if (_shouldTrigger) {
        _shouldTrigger = false;
        return true;
    }
    return false;
}


