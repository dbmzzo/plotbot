#include "State.h"
#include "Handlers.h"
#include "Constants.h"
#include "GCode.h"

void blePeripheralConnectHandler(BLEDevice central) {
  // central connected event handler
  if (Serial) {
    Serial.print("Connected event, central: ");
    Serial.println(central.address());
  }
}

void blePeripheralDisconnectHandler(BLEDevice central) {
  // central disconnected event handler
  if (Serial) {
    Serial.print("Disconnected event, central: ");
    Serial.println(central.address());
  }
}

void sendCommand() {
  wakeTimer = millis();
  parseGcode(command);
}

void sendJoystick() {
  wakeTimer = millis();
  String command = "JS" + String(speed) + "A" + String(direction) + "R" + String(rotation);
  char sendCommand[command.length() + 1];
  command.toCharArray(sendCommand, command.length() + 1);
  parseGcode(sendCommand);
}

void characteristicWrittenHandler(BLEDevice central, BLECharacteristic characteristic) {
  if (strcmp(characteristic.uuid(), DIR_UUID) == 0) {
    float floatValue;
    characteristic.readValue(&floatValue, 4);
    direction = floatValue;
    sendJoystick();
    } else if (strcmp(characteristic.uuid(), SPEED_UUID) == 0) {
      float floatValue;
      characteristic.readValue( &floatValue, 4);
      speed = floatValue;
      sendJoystick();
    } else if (strcmp(characteristic.uuid(), ROTATION_UUID) == 0) {
      float floatValue;
      characteristic.readValue( &floatValue, 4);
      rotation = floatValue;
      sendJoystick();
    } else if (strcmp(characteristic.uuid(), STATE_UUID) == 0) {
      int intValue;
      characteristic.readValue( &intValue, 4);
      commandState = intValue;
    } else if (strcmp(characteristic.uuid(), BATT_UUID) == 0) {
      float floatValue;
      characteristic.readValue( &floatValue, 4);
      battLevel = floatValue;
    } else if (strcmp(characteristic.uuid(), COMMAND_UUID) == 0) {
      BLEStringCharacteristic& stringChar = static_cast<BLEStringCharacteristic&>(characteristic);
      stringChar.value().toCharArray(command, MAX_COMMAND_SIZE);
      sendCommand();
    } else if (strcmp(characteristic.uuid(), PEN_UUID) == 0) {
      int intValue;
      characteristic.readValue( &intValue, 4);
      penState = intValue;
      if (penState == 0) {
        char *downCommand = "G1Z-1";
        strcpy(command, downCommand);
        sendCommand();
      } else if (penState == 1) {
        char *upCommand = "G1Z1";
        strcpy(command, upCommand);
        sendCommand();
      }
    }
}
