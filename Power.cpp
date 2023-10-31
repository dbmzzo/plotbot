#include "Power.h"
#include "BLE_Service.h"
#include "State.h"
#include <Arduino.h>

unsigned long previousMillis = 0;
const long interval = 10000;

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

// TODO: calc percent -- currently returns voltage
float calcPercent(float voltage) {
    return voltage;
}

void checkBattLoop()
{
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval || previousMillis == 0)
    {
        previousMillis = currentMillis;
        float currentLevel = calcPercent(readVoltage());
        battLevel = currentLevel;
        battChar.writeValue(currentLevel);
    }
}