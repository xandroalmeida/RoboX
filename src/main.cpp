#include <Arduino.h>

#include <Eventually.h>
#include "engine.h"
#include "radar.h"

EvtManager mgr;
Engine engineRight(3,4, A0);
Engine engineLeft(1,2, A1);

bool radarListener(EvtListener *listener, EvtContext *ctx) {
  Radar *radar = static_cast<Radar*>(listener->extraData);

  Serial.print("Left: ");
  Serial.print(radar->distLeft);
  Serial.print(" Front: ");
  Serial.print(radar->distFront);
  Serial.print(" Righ: ");
  Serial.print(radar->distRight);
  Serial.println();

  if (radar->distFront > 0 && radar->distFront < 400) {
    if (radar->distLeft > radar->distRight) {
      engineLeft.setSpeed(0.2);
      engineRight.setSpeed(-0.2);
    } else {
      engineLeft.setSpeed(-0.2);
      engineRight.setSpeed(0.2);
    }
  } else if(radar->distLeft < 100) {
    engineLeft.setSpeed(0.2);
    engineRight.setSpeed(-0.2);
  } else if(radar->distLeft < 100) {
    engineLeft.setSpeed(-0.2);
    engineRight.setSpeed(0.2);
  } else {
    engineLeft.setSpeed(0.4);
    engineRight.setSpeed(0.4);
  }

  return false;
}

Radar radar(mgr, A5, 9, radarListener);


void setup() {
  Serial.begin(9600);
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
  mgr.loopIteration();
}