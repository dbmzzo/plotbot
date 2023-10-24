#ifndef Constants_h
#define Constants_h

#include <Arduino.h>
#include <ArduinoBLE.h>

const int DELAY = 1000;
const int BT_DELAY = 3000;
const int CHAR_COUNT = 5;
const int CHAR_DESCRIPTOR_COUNT = 4;
const int STEPS_PER_MM = 12.423;
const int RUN_SPEED = 1000;
const int FEED_SPEED = 150;
const int MAX_COMMAND_SIZE = 512;
const int MAX_COMMAND_ARRAY_SIZE = 1024;
const int STEPS_PER_REV = 200;

const char DIR_UUID[37] = "a393436b-8be0-4280-bff8-b357bf1e30c7";
const char SPEED_UUID[37] = "bcdf77f1-7b10-41fa-9ed5-83bc69fd3fde";
const char ROTATION_UUID[37] = "7621b66b-10ee-4172-b3bf-dad42cd5972d";
const char STATE_UUID[37] = "930b5db3-a406-4a44-b9aa-666165e31b1e";
const char COMMAND_UUID[37] = "bbbf63c9-abf0-4344-aa50-7416e3487091";
const char PEN_UUID[37] = "40447395-2f51-48d3-95a6-9856424460f4";

const char SERVICE_UUID[37] = "66879f41-f094-44e2-8da7-2231d83bddd4";
const char DATA_TYPE_DESCRIPTOR_UUID[37] = "13ac0c9b-330b-46cd-9cc7-068e77da9ae1";

enum CharDataType {
  DATA_VELOCITY,
  DATA_MAX_SPEED,
  DATA_ROTATION,
  DATA_COMMAND,
  DATA_PEN
};

const char CHAR_DATA_TYPE_NAME[CHAR_DESCRIPTOR_COUNT][16] = {
  "Velocity", "Maximum Speed", "Rotation", "Command"
};

#endif

