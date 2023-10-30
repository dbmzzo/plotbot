#include <Arduino.h>
#include "Utils.h"
#include "State.h"
#include "BLE_Service.h"

void resetAllPositions() {
  w1.setCurrentPosition(0);
  w2.setCurrentPosition(0);
  w3.setCurrentPosition(0);
}

void setJoystick() {
  if (commandType == 1) {
    resetAllPositions();
    commandType = 0;
  }
}

void setCommand() {
  if (commandType == 0) {
    resetAllPositions();
    commandType = 1;
  }
}

void setReady() {
  if (commandState == 0) {
    commandState = 1;
    stateChar.writeValue(1);
  }
}

void setBusy() {
    commandState = 0;
    stateChar.writeValue(0);
}

bool isReady() {
  return commandState == 1;
}

bool isBusy() {
  return commandState == 0;
}

bool isJoystick() {
  return commandType == 0;
}

bool isCommand() {
  return commandType == 1;
}

bool hasDistanceToGo() {
  return w1.distanceToGo() != 0 && w2.distanceToGo() != 0 && w3.distanceToGo() != 0; 
}

bool hasJoystickValues() {
  return speed != 0.0 || direction != 0.0 || rotation != 0.0;
}

void raisePen() {
    myServo.write(90);
    penState = 1;
    penChar.writeValue(1);
}

void lowerPen() {
    myServo.write(0);
    penState = 0;
    penChar.writeValue(0);
}
