#include <Arduino.h>
#include <Chrono.h>
#include "radar.h"

Radar::Radar(EvtManager &evtManager, uint8_t triggerPin, uint8_t servoPin, EvtAction action) : 
    distLeft(0.0),
    distFront(0.0),
    distRight(0.0),
    _evtManager(evtManager),
    _sonar(triggerPin, *this),
    _servoPin(servoPin),
    _currPos(Front),
    _spin(false),
    _servo(),
    _shouldTrigger(false)
{
    this->triggerAction = action;
    _evtManager.addListener(this);
    this->extraData = this;
    _sonar.SetTimeOutDistance(2000);
}

void Radar::begin()
{   
    _servo.attach(_servoPin);
    _servo.write(_currPos);
    _sonar.Start(100);
}

void Radar::loop()
{
    _sonar.Update();
}


void Radar::_updateServo()
{
    if (_currPos == Left) { 
        _currPos = Front;
        _spin = true;
    } else if (_currPos == Right) {
        _currPos = Front;
        _spin = false;
    } else {
        if (_spin) {
            _currPos = Right;
        } else {
            _currPos = Left;
        }
        _shouldTrigger = true;
    }

    _servo.write(_currPos);
}


void Radar::OnPing(AsyncSonar& as)
{
    switch (_currPos)
    {
    case Right:
        distRight = as.GetMeasureMM(); 
        break;
    case Front:
        distFront = as.GetMeasureMM();
        _shouldTrigger = true;
        break;
    case Left:
        distLeft = as.GetMeasureMM(); 
        break;
    }

    _updateServo();
    _sonar.Start(333);
}

void Radar::OnTimeOut(AsyncSonar& as)
{
    switch (_currPos)
    {
    case Right:
        distRight = 0; 
        break;
    case Front:
        distFront = 0; 
        break;
    case Left:
        distLeft = 0; 
        break;
    }
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


