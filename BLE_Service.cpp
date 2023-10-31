#include "State.h"
#include "Handlers.h"
#include "BLE_Service.h"
#include "Constants.h"

BLEFloatCharacteristic directionChar(DIR_UUID, BLEWriteWithoutResponse);
BLEDescriptor directionDesc(DESC_UUID, "Direction");
BLEDescriptor directionTypeDescriptor(DATA_TYPE_DESCRIPTOR_UUID, CHAR_DATA_TYPE_NAME[CharDataType::DATA_VELOCITY]);

BLEFloatCharacteristic rotationChar(ROTATION_UUID, BLEWriteWithoutResponse);
BLEDescriptor rotationDesc(DESC_UUID, "Rotation");
BLEDescriptor rotationTypeDescriptor(DATA_TYPE_DESCRIPTOR_UUID, CHAR_DATA_TYPE_NAME[CharDataType::DATA_ROTATION]);

BLEFloatCharacteristic speedChar(SPEED_UUID, BLEWriteWithoutResponse);
BLEDescriptor speedDesc(DESC_UUID, "Speed");
BLEDescriptor speedTypeDescriptor(DATA_TYPE_DESCRIPTOR_UUID, CHAR_DATA_TYPE_NAME[CharDataType::DATA_VELOCITY]);

BLEFloatCharacteristic battChar(BATT_UUID, BLERead | BLENotify);
BLEDescriptor battDesc(DESC_UUID, "Battery");
BLEDescriptor battTypeDescriptor(DATA_TYPE_DESCRIPTOR_UUID, "Battery");

BLEStringCharacteristic commandChar(COMMAND_UUID, BLENotify | BLERead | BLEWrite, 512);
BLEDescriptor commandDesc(DESC_UUID, "Command");
BLEDescriptor commandTypeDescriptor(DATA_TYPE_DESCRIPTOR_UUID, CHAR_DATA_TYPE_NAME[CharDataType::DATA_COMMAND]);

BLEIntCharacteristic penChar(PEN_UUID, BLERead | BLEWriteWithoutResponse | BLENotify);
BLEDescriptor penDesc(DESC_UUID, "Pen");
BLEDescriptor penTypeDescriptor(DATA_TYPE_DESCRIPTOR_UUID, CHAR_DATA_TYPE_NAME[CharDataType::DATA_PEN]);

BLEIntCharacteristic stateChar(STATE_UUID, BLERead | BLENotify);
BLEDescriptor stateDesc(DESC_UUID, "State");
BLEDescriptor stateTypeDescriptor(DATA_TYPE_DESCRIPTOR_UUID, CHAR_DATA_TYPE_NAME[CharDataType::DATA_COMMAND]);

void initBLEService() {
  if (!BLE.begin())
  {
    if (Serial)
    {
      Serial.println("starting Bluetooth® Low Energy failed!");
    }
    while (1)
      ;
  }
  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
  BLE.setLocalName("PlotBot");
  directionChar.addDescriptor(directionDesc);
  directionChar.addDescriptor(directionTypeDescriptor);
  directionChar.setEventHandler(BLEWritten, characteristicWrittenHandler);
  
  controlService.addCharacteristic(directionChar);
  directionChar.writeValue(0);

  rotationChar.addDescriptor(rotationDesc);
  rotationChar.addDescriptor(rotationTypeDescriptor);
  rotationChar.setEventHandler(BLEWritten, characteristicWrittenHandler);
  
  controlService.addCharacteristic(rotationChar);
  rotationChar.writeValue(0);

  speedChar.addDescriptor(speedDesc);
  speedChar.addDescriptor(speedTypeDescriptor);
  speedChar.setEventHandler(BLEWritten, characteristicWrittenHandler);
  controlService.addCharacteristic(speedChar);
  speedChar.writeValue(0);

  commandChar.addDescriptor(commandDesc);
  commandChar.addDescriptor(commandTypeDescriptor);
  commandChar.setEventHandler(BLEWritten, characteristicWrittenHandler);
  controlService.addCharacteristic(commandChar);

  penChar.addDescriptor(penDesc);
  penChar.addDescriptor(penTypeDescriptor);
  penChar.setEventHandler(BLEWritten, characteristicWrittenHandler);
  controlService.addCharacteristic(penChar);
  penChar.writeValue(0);

  stateChar.addDescriptor(stateDesc);
  stateChar.addDescriptor(stateTypeDescriptor);
  stateChar.setEventHandler(BLEWritten, characteristicWrittenHandler);
  controlService.addCharacteristic(stateChar);
  stateChar.writeValue(1);

  battChar.addDescriptor(battDesc);
  battChar.addDescriptor(battTypeDescriptor);
  battChar.setEventHandler(BLEWritten, characteristicWrittenHandler);
  controlService.addCharacteristic(battChar);
  battChar.writeValue(100.0);

  BLE.setAdvertisedService(controlService);
  BLE.addService(controlService);
  BLE.advertise();
}