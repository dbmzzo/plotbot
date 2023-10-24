#include "State.h"
#include "Handlers.h"
#include "BLE_Service.h"
#include "Motion_Service.h"
#include "Constants.h"

void setup()
{
  Serial.begin(115200);
  pinMode(18, OUTPUT);
  myServo.attach(17);
  initBLEService();
  initMotionService();
}

void loop()
{
  BLE.poll();
  checkSleepLoop();
  motionLoop();
}