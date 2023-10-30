#include "Power.h"
#include <Arduino.h>

unsigned long previousMillis = 0;
const long interval = 30000;

const int BATT_DATA_PIN = 8;
const int BATT_CLOCK_PIN = 9;
const int BATT_DATA_SPEED = 400000;
const int BATT_DATA_ADDRESS = 0x40;
const int BATT_VOLTAGE_ADDRESS = 0x02;
const int BATT_CURRENT_ADDRESS = 0x03;

void initPowerMonitor()
{
    Wire.begin(BATT_DATA_PIN, BATT_CLOCK_PIN, BATT_DATA_SPEED);
}

uint16_t ReadIna226Register(int addr, byte reg)
{
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(addr, 2);
    if (Wire.available() != 2)
    {
        if (Serial)
        {
            Serial.println(String("Read failed. Expected 2 bytes, got ") + Wire.available());
        }
        while (Wire.available())
        {
            Wire.read();
        }
        return 0;
    }
    uint16_t ret = 0;
    ret = Wire.read();
    ret <<= 8;
    ret |= Wire.read();
    return ret;
}

float readVoltage()
{
    auto voltage_raw = ReadIna226Register(BATT_DATA_ADDRESS, BATT_VOLTAGE_ADDRESS);
    float voltage = static_cast<float>(voltage_raw) * 0.00125f;
    return voltage;
}

float readPower()
{
    auto power_raw = ReadIna226Register(BATT_DATA_ADDRESS, BATT_CURRENT_ADDRESS);
    float power = static_cast<float>(power_raw) * 0.00125f;
    return power;
}

float calcPercent(float voltage, float power, float maxVolts) {
    return ((voltage + (power / 10)) / maxVolts) * 100; ;
}

void checkBattLoop()
{
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval || previousMillis == 0)
    {
        previousMillis = currentMillis;
        float currentLevel = calcPercent(readVoltage(), readPower(), 10.0);
        Serial.println(currentLevel);
    }
}