#include <Arduino.h>

#include <Chrono.h>
#include "engine.h"
#include "radar.h"

Chrono logChrono;
Chrono radarChrono;

Engine engineRight(3,4, A0);
Engine engineLeft(1,2, A1);
Radar radar(10,9);

void setup() {
  Serial.begin(9600);
  engineRight.begin();
  engineLeft.begin();
  radar.begin();

  engineLeft.setSpeed(0.5);
  engineRight.setSpeed(0.5);
}

void loop() {
  engineRight.loop();
  engineLeft.loop();

  if (radarChrono.hasPassed(250)) {
    radarChrono.restart();
    if (radar.getDistance() < 50) {
      engineLeft.setSpeed(-1);
      engineRight.setSpeed(1);
    } else {
      engineLeft.setSpeed(0.5);
      engineRight.setSpeed(0.5);
    }
  }

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