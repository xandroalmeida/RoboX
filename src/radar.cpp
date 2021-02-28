#include <Arduino.h>
#include "radar.h"

Radar::Radar(uint8_t triggerPin, uint8_t echoPin) : 
    _triggerPin(triggerPin),
    _echoPin(echoPin)
{
}

void Radar::begin()
{
    pinMode(_triggerPin, OUTPUT);
    pinMode(_echoPin, INPUT);
    digitalWrite(_triggerPin, LOW);
}

float Radar::getDistance()
{
    digitalWrite(_triggerPin, LOW);
	delayMicroseconds(2);
    digitalWrite(_triggerPin, HIGH);
	delayMicroseconds(10);
    digitalWrite(_triggerPin, LOW);
    noInterrupts();
	float d=pulseIn(_echoPin, HIGH);
	interrupts();
	return d / 58.0;
}