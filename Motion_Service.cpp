#include "State.h"
#include "GCode.h"
#include "Motion_Service.h"
#include "Constants.h"
#include "Utils.h"
#include <AccelStepper.h>
#include <MultiStepper.h>

void sleepAll()
{
  wakeTimer = 0.0;
  digitalWrite(18, LOW);
}

void wakeAll()
{
  wakeTimer = 0.0;
  digitalWrite(18, HIGH);
}

void checkSleepLoop()
{
  if (isReady() && (!hasJoystickValues() || !hasDistanceToGo()))
  {
    if (wakeTimer == 0.0)
    {
      wakeTimer = millis();
    }
    if (millis() - wakeTimer > 15000.0)
    {
      sleepAll();
    }
  }
  else
  {
    wakeAll();
  }
}

void initMotionService()
{
  w1.setMaxSpeed(RUN_SPEED);
  w3.setMaxSpeed(RUN_SPEED);
  w2.setMaxSpeed(RUN_SPEED);
  w1.setAcceleration(100);
  w2.setAcceleration(100);
  w3.setAcceleration(100);
  steppers.addStepper(w1);
  steppers.addStepper(w2);
  steppers.addStepper(w3);
  raisePen();
}

void joystickLoop()
{
  if (hasJoystickValues())
  {
    float x = (speed * RUN_SPEED) * cos(direction);
    float y = (speed * RUN_SPEED) * sin(direction);

    float wheelRotation = rotation * RUN_SPEED;

    float w1Speed = x + wheelRotation;

    float w2Speed = (-0.5 * x - 0.86602540378 * y + wheelRotation);
    float w3Speed = (-0.5 * x + 0.86602540378  * y + wheelRotation);

    w1Speed = constrain(w1Speed, -RUN_SPEED, RUN_SPEED);
    w2Speed = constrain(w2Speed, -RUN_SPEED, RUN_SPEED);
    w3Speed = constrain(w3Speed, -RUN_SPEED, RUN_SPEED);

    // Set speed for each motor
    w1.setSpeed(w1Speed);
    w2.setSpeed(w2Speed);
    w3.setSpeed(w3Speed);

    w1.runSpeed();
    w2.runSpeed();
    w3.runSpeed();
  }
}

void commandLoop()
{
  if (w1.distanceToGo() != 0 || w2.distanceToGo() != 0 || w3.distanceToGo() != 0)
  {
    Serial.print("Distance: ");
    Serial.print(w1.distanceToGo());
    Serial.print(" : ");
    Serial.print(w2.distanceToGo());
    Serial.print(" : ");
    Serial.println(w3.distanceToGo());
    steppers.runSpeedToPosition();
  } else {
    setReady();
  }
}

void motionLoop()
{
  if (commandType == 0)
  {
    joystickLoop();
  }
  if (commandType == 1)
  {
    commandLoop();
  }
}
