#include <Arduino.h>
#include <Chrono.h>
#include "radar.h"

Radar::Radar(uint8_t triggerPin, uint8_t echoPin, uint8_t servoPin) : 
    _triggerPin(triggerPin),
    _echoPin(echoPin),
    _servoPin(servoPin),
    _currPos(90),
    _radarChono(),
    _servo()
{
}

void Radar::begin()
{
    pinMode(_triggerPin, OUTPUT);
    pinMode(_echoPin, INPUT);
    digitalWrite(_triggerPin, LOW);
    _servo.attach(_servoPin);
    _servo.write(_currPos);
    _radarChono.start();
}

void Radar::loop()
{
    if (_radarChono.hasPassed(100)) {
        _radarChono.restart();
    }
}

float Radar::getDistance()
{
    digitalWrite(_triggerPin, LOW);
	delayMicroseconds(2);
    digitalWrite(_triggerPin, HIGH);
	delayMicroseconds(10);
    digitalWrite(_triggerPin, LOW);
    noInterrupts();
	float d=pulseIn(_echoPin, HIGH, 58 * 2 * 100);
	interrupts();

    if (_radarChono.hasPassed(100)) {
        _radarChono.restart();
        _currPos += 15;
        if (_currPos > 180) {
            _currPos = 0;
        }

        _servo.write(_currPos);
    }

	return d / 58.0;

}