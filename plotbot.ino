#include <Wire.h>
#include "Power.h"
#include "State.h"
#include "Utils.h"
#include "Handlers.h"
#include "BLE_Service.h"
#include "Motion_Service.h"
#include "Constants.h"

void setup()
{
  initPowerMonitor();
  Serial.begin(115200);
  pinMode(18, OUTPUT);
  digitalWrite(18, HIGH);
  myServo.attach(17);
  initBLEService();
  initMotionService();
}

void loop()
{
  BLE.poll();
  motionLoop();
  //checkSleepLoop();
  //checkBattLoop();
}