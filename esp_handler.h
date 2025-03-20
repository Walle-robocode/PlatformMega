#ifndef ESP_HANDLER_H
#define ESP_HANDLER_H

#include <Arduino.h>
#include "utils.h"
#include "LCD_1602_RUS_ALL.h"
#include "dht.h"
#include "motors.h"
#include "mp3.h"
#include "led.h"

#define ESP Serial3

////////////////////////////////////////
//    ESP Commands
////////////////////////////////////////

#define ENABLE_LIGHT      'L'
#define DISABLE_LIGHT     'Q'
#define SPEAK_TEMPERATURE 'T'
#define MOVE_FORWARD      'F'
#define MOVE_BACKWARD     'B'
#define MOVE_LEFT         'l'
#define MOVE_RIGHT        'r'
#define ROBOCODE_POWER    'f'
#define TIRED             't'
#define WHATS_YOUR_NAME   'n'
#define WHERE_ARE_YOU_FROM 'w'
#define IP                'I'
#define SPEAK             'S'
#define RECOGNIZE         'R'
#define BATTERY_LEVEL     'C'

#define ESP_ACK_CODE      '#'

#define ESP_MOTOR_SPEED 7 // 0 - 10

extern HTSensor dht;
extern LCD_1602_RUS lcd;

class ESPHandler {
public:
  static ESPHandler* getInstance() {
    if (ptr_instance == nullptr) {
      ptr_instance = new ESPHandler();
    }
    return ptr_instance;
  }
  void begin();
  void handle();

private:
  ESPHandler();
  static ESPHandler* ptr_instance;
  char* ip = "";
  void _lcdPrint(String);
  void _sendAck();

  Motors* _motors = Motors::getInstance();
  MP3* _mp3 = MP3::getInstance();
  LED* _led = LED::getInstance();
};

#endif // ESP_HANDLER_H