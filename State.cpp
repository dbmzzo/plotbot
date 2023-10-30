#include "State.h"

BLEService controlService("66879f41-f094-44e2-8da7-2231d83bddd4");
AccelStepper w1(AccelStepper::DRIVER, 5, 4);
AccelStepper w2(AccelStepper::DRIVER, 7, 6);
AccelStepper w3(AccelStepper::DRIVER, 16, 15);
MultiStepper steppers;
Servo myServo;

float speed = 0.0; 
float battLevel = 100.0; 
float direction = 0.0;
float rotation = 0.0;
char command[MAX_COMMAND_SIZE] = {0};
int commandState = 1;
int commandType = 0;
int penState = 1;
long unsigned int wakeTimer = 0.0; 