#include <ArduinoBLE.h>


void sendJoystick();
void blePeripheralConnectHandler(BLEDevice central);
void blePeripheralDisconnectHandler(BLEDevice central);
void characteristicWrittenHandler(BLEDevice central, BLECharacteristic characteristic);


