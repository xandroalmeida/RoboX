#include <Arduino.h>

#include <Eventually.h>
#include "speedometer.h"
#include "engine.h"
#include "radar.h"
#include "guidance.h"
#include <TM1637Display.h>

EvtManager evtManager;
TM1637Display display(A3,A4);

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
}

void loop() {
  evtManager.loopIteration();
}