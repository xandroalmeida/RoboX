#include <Arduino.h>

#include <Chrono.h>
#include "engine.h"
#include "radar.h"

Chrono logChrono;

Engine engineRight(3,4, A0);
Engine engineLeft(1,2, A1);
Radar radar(10,10, 9);

void setup() {
  Serial.begin(9600);
  logChrono.start();
  engineRight.begin();
  engineLeft.begin();
  radar.begin();

  engineLeft.setSpeed(0.2);
  engineRight.setSpeed(0.2);
}

void loop() {
  engineRight.loop();
  engineLeft.loop();
  radar.loop();

    #ifdef NOCODE
    if (radar.getDistance() < 50) {
      engineLeft.setSpeed(-0.2);
      engineRight.setSpeed(0.2);
    } else {
      engineLeft.setSpeed(0.2);
      engineRight.setSpeed(0.2);
    }
    #endif

  if (logChrono.hasPassed(1000)) {
    logChrono.restart();
    Serial.print("Right: ");
    Serial.print(engineRight.getSpeed());
    Serial.print("ms/s ");
    Serial.print(engineRight.getPower());
    Serial.print("% | Left: ");
    Serial.print(engineLeft.getSpeed());
    Serial.print("ms/s ");
    Serial.print(engineLeft.getPower());
    Serial.print("% Dist: ");
    Serial.print(radar.getDistance());
    Serial.println("cms");
  }
}