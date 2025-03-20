#include <LiquidCrystal_I2C.h>
#include <FastLED.h>
#include <TimerOne.h>
#include "../libs/ServoSmooth/ServoSmooth.cpp"

#include "utils.h"
#include "LCD_1602_RUS_ALL.h"
#include "motors.h"
#include "bluetooth.h"
#include "dht.h"
#include "esp_handler.h"
#include "mp3.h"
#include "led.h"

#define TRIGGER_PIN  12
#define ECHO_PIN     13
#define MAX_DISTANCE 200

ServoSmooth headServo;
HTSensor dht;
LCD_1602_RUS lcd(0x20, 16, 2);


Motors* motors = Motors::getInstance();
Bluetooth* bluetooth = Bluetooth::getInstance();
ESPHandler* esp = ESPHandler::getInstance();
MP3* mp3 = MP3::getInstance();
LED* leds = LED::getInstance();
