#include "speedometer.h"
#include <Arduino.h>

#include <YetAnotherPcInt.h>


Speedometer::Speedometer(uint8_t inputPin) : 
    _inputPin(inputPin),
    _lastPinState(0x02),
    _tachometer(0),
    _partialTachometer(0),
    _lastMillis(0),
    _currentRPS(0)
{
}

void Speedometer::begin() 
{
    pinMode(_inputPin, INPUT);
    PcInt::attachInterrupt(_inputPin, Speedometer::pinChanded, this, CHANGE);
}

void Speedometer::pinChanded(bool pinstate)
{
    unsigned long _curMillis = millis();
    if (_lastMillis == 0) _lastMillis = _curMillis;

    _tachometer++;
    _partialTachometer++;

    if ((_curMillis - _lastMillis) > 200) {
        _currentRPS = (_partialTachometer / 40.0) /  ((_curMillis - _lastMillis) / 1000.0);
        _lastMillis = _curMillis;
        _partialTachometer = 0;
    }
}

/*
void Speedometer::loop() {
    unsigned long _curMillis = millis();
    if (_lastMillis == 0) _lastMillis = _curMillis;

    uint8_t state = digitalRead(_inputPin);
    if (state != _lastPinState) {
        _lastPinState = state;
        _tachometer++;
        _partialTachometer++;
    }

    if ((_curMillis - _lastMillis) > 200) {
        _currentRPS = (_partialTachometer / 40.0) /  ((_curMillis - _lastMillis) / 1000.0);
        _lastMillis = _curMillis;
        _partialTachometer = 0;
    }
}
*/
float Speedometer::getRPM()
{
    return _currentRPS * 60.0;
}

float Speedometer::getRPS()
{
    return (_lastMillis == 0 || (millis() - _lastMillis) > 200) ? 0 : _currentRPS;
}