#ifndef Utils_h
#define Utils_h

void setReady();
void setBusy();
void setJoystick();
void setCommand();
void raisePen();
void lowerPen();
bool isReady();
bool isBusy();
bool hasDistanceToGo();
bool hasJoystickValues();
bool isJoystick();
bool isCommand();

#endif
