#include <LiquidCrystal_I2C.h>
#include "LCD_1602_RUS_ALL.h"
#include <FastLED.h>
#include <Servo.h>
#include <HardwareSerial.h>
#include "motors.h"
#include "dht.h"
#include "dfmp3.h"
#include "esp_handler.h"


#define NUM_LEDS 2
#define DATA_PIN 42

#define TRIGGER_PIN  12
#define ECHO_PIN     13
#define MAX_DISTANCE 200

#define BT Serial2
#define MP3Com Serial1

// int leftSpeed = 100;
// int rightSpeed = 100;

Servo headServo;
HTSensor dht;
LCD_1602_RUS lcd(0x20, 16, 2);
DfMp3 dfMp3(MP3Com);
CRGB leds[NUM_LEDS];
ESPHandler esp;
Motors motors;