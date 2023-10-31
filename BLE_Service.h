#ifndef BLE_Service_h
#define BLE_Service_h

#include <Arduino.h>
#include <ArduinoBLE.h>
#include <AccelStepper.h>

extern BLEIntCharacteristic stateChar;
extern BLEIntCharacteristic penChar;
extern BLEFloatCharacteristic battChar;

void characteristicWrittenHandler(BLEDevice central, BLECharacteristic characteristic);
void initBLEService();
void serviceLoop();
void sleepAll();
void wakeAll();

#endif
