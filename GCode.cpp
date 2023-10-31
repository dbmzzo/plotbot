#include "State.h"
#include "GCode.h"
#include "BLE_Service.h"
#include "Constants.h"
#include "Utils.h"
#include <cstdlib>
#include <cstring>
#include <Arduino.h>
#include <ESP32Servo.h>

void moveToPosition(float x, float y, float speed) {
    float stepsX = -x * STEPS_PER_MM * scale;
    float stepsY = y * STEPS_PER_MM * scale;
    float s1Dist = stepsX;
    float s2Dist = (-0.5 * stepsX - 0.86602540378 * stepsY);
    float s3Dist = (-0.5 * stepsX + 0.86602540378  * stepsY);
    long positions[3] = {s1Dist, s2Dist, s3Dist};
    steppers.moveTo(positions);
}

float getValueFromCommand(char letter, char* command) {
    char* ptr = strchr(command, letter);
    if (ptr) {
        return atof(ptr + 1);
    }
    return nan("");
}

void executeLinearMove(char* command) {
    float targetX = getValueFromCommand('X', command);
    float targetY = getValueFromCommand('Y', command);
    float targetZ = getValueFromCommand('Z', command);
    float feed = getValueFromCommand('F', command);
    if (targetZ >= 0.0) {
        raisePen();
    } else if (targetZ < 0.0) {
        lowerPen();
    }
    if (!isnan(targetX) && !isnan(targetY)) {
        setBusy();
        moveToPosition(targetX, targetY, feed);
    }
}

void handleJCommand(char* command) {
    setJoystick();
    float targetSpeed = getValueFromCommand('S', command);
    float targetAngle = getValueFromCommand('A', command);
    float targetRotation = getValueFromCommand('R', command);
    speed = targetSpeed;
    direction = targetAngle;
    rotation = targetRotation;
}

void handleGCommand(char* command) {
    setCommand();
    Serial.println(command);
    int commandNum = atoi(&command[1]);
    switch (commandNum) {
        case 0: // G0 rapid movement
        case 1: // G1 linear movement
            executeLinearMove(command);
            break;
        // ... Handle other G commands
        default:
            Serial.println("Unknown G command");
            break;
    }
}

void parseGcode(char* command) {
    switch (command[0]) {
        case 'G':
            handleGCommand(command);
            break;
        case 'J':
            handleJCommand(command);
            break;
        default:
            Serial.println("Unknown command");
            break;
    }
}