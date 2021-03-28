#include "speedometer.h"
#include <Arduino.h>

#include <YetAnotherPcInt.h>

Speedometer::Speedometer(Vio *vio, ChassiSide side, uint8_t inputPin) : 
    DeviceBase(vio),
    _side(side),
    _inputPin(inputPin),
    _lastChange(0),
    _speeds{0},
    _ptSpeeds(0)
{
}

void Speedometer::begin() 
{
    DeviceBase::begin();
    pinMode(_inputPin, INPUT);
    _vio->setSpeed(_side, 0);
    PcInt::attachInterrupt(_inputPin, Speedometer::pinChanged, this, CHANGE);
}

void Speedometer::pinChanged(bool pinstate)
{
    if (pinstate) return;
    if (_lastChange == 0) {
        _lastChange = millis();
        return;
    }

    auto cur = millis();

    auto speed = ((220 / 20) * 1000) / (cur - _lastChange);
    _speeds[_ptSpeeds++] = speed;
    _ptSpeeds &= 0x03;
    for(uint8_t i = 0; i < 4; speed += _speeds[i++]);
    speed /= 4;

    _vio->setSpeed(_side, speed);
    _vio->incTachometer(_side);
    _lastChange = cur;
}

uint16_t Speedometer::getTimeLoop()
{
    return 200;
}

void Speedometer::loop()
{
    if ((millis() - _lastChange) > getTimeLoop()) {
        _vio->setSpeed(_side, 0);
    }
}