#include "speedometer.h"
#include <Arduino.h>

#include <YetAnotherPcInt.h>

extern EvtManager evtManager;
const uint16_t Speedometer::_timeout = 200;

bool Speedometer_onTimer(EvtListener *l, EvtContext *ctx) 
{
    static_cast<Speedometer*>(l->extraData)->onTimer();
    return false;
}

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
    auto t = new EvtTimeListener(_timeout, true, Speedometer_onTimer);
    t->extraData = this;
    evtManager.addListener(t);

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

void Speedometer::onTimer()
{
    if ((millis() - _lastChange) > _timeout) {
        _vio->setSpeed(_side, 0);
    }
}