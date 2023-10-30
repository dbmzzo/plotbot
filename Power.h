#ifndef Power_h
#define Power_h

#include <Arduino.h>
#include <Wire.h>

uint16_t ReadIna226Register(int addr, byte reg);
void initPowerMonitor();
void checkBattLoop();
float readVoltage();
float readPower();
float calcPercent(float voltage, float power, float maxVolts);

#endif