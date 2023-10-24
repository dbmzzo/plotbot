#ifndef GCode_h
#define GCode_h

#include "State.h"
#include <Arduino.h>

void parseGcode(char* command);
void handleGCommand(char* command);
void handleJCommand(char* command);
void executeLinearMove(char* command);
float getValueFromCommand(char letter, char* command);
void moveToPosition(float x, float y);

#endif