#include <Arduino.h>

#include <Eventually.h>
#include "engine.h"
#include "radar.h"
#include "guidance.h"
#include <TM1637Display.h>

EvtManager evtManager;
TM1637Display display(A3,A4);
//Engine engineRight(3,4, A0);
//Engine engineLeft(1,2, A1);

/*
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
*/

Vio vio;

Radar radar(&vio, A5, 9);

Speedometer sl(&vio, Left, A1);
Engine engineLeft(&vio, Left, 1,2);

Speedometer sr(&vio, Right, A0);
Engine engineRight(&vio, Right, 3,4);

Guidance guidance(&vio);

bool updateDisplay(EvtListener *l, EvtContext *c) 
{
  display.showNumberDec(vio.getRadarDist(Front) / 10);
  return false;
}

void setup() {
  Serial.begin(9600);
  display.setBrightness(1);
  sl.begin();
  sr.begin();
  engineLeft.begin();
  engineRight.begin();
  radar.begin();
  guidance.begin();
  evtManager.addListener(new EvtTimeListener(250, true, updateDisplay));

  //engineRight.begin();
  //engineLeft.begin();
  //radar.begin();
  //engineLeft.setSpeed(0.2);
  //engineRight.setSpeed(0.2);
}

void loop() {
  evtManager.loopIteration();
}