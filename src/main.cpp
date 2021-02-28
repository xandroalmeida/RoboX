#include <Arduino.h>

#include <Chrono.h>
#include "engine.h"

Chrono logChrono;

Engine engineRight(3,4, A0);
Engine engineLeft(1,2, A1);


void setup() {
  Serial.begin(9600);
  engineRight.begin();
  engineLeft.begin();

  engineLeft.setRPS(1);
  engineRight.setRPS(4);
}

void loop() {
  engineRight.loop();
  engineLeft.loop();

  if (logChrono.hasPassed(1000)) {
    logChrono.restart();
  }
}