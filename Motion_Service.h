#ifndef Motion_Service_h
#define MotionService_h

#include <Arduino.h>
#include <ArduinoBLE.h>
#include <AccelStepper.h>

void checkSleepLoop();
void joystickLoop();
void initMotionService();
void motionLoop();
void sleepAll();
void wakeAll();

#endif
