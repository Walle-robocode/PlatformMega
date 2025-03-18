#ifndef ESP_HANDLER_H
#define ESP_HANDLER_H

#include <Arduino.h>
#include "LCD_1602_RUS_ALL.h"
#include "dfmp3.h"
#include "dht.h"
#include "motors.h"

#define ESP Serial3

////////////////////////////////////////
//    ESP Commands
////////////////////////////////////////

#define ENABLE_LIGHT 'L'
#define DISABLE_LIGHT 'Q'
#define SPEAK_TEMPERATURE 'T'
#define MOVE_FORWARD 'F'
#define MOVE_BACKWARD 'B'
#define MOVE_LEFT 'l'
#define MOVE_RIGHT 'r'
#define ROBOCODE_POWER 'f'
#define TIRED 't'
#define WHATS_YOUR_NAME 'n'
#define WHERE_ARE_YOU_FROM 'w'
#define IP 'I'
#define SPEAK 'S'
#define RECOGNIZE 'R'

extern HTSensor dht;
extern LCD_1602_RUS lcd;
extern DfMp3 dfMp3;
extern Motors motors;

int leftSpeed = 100;
int rightSpeed = 100;

class ESPHandler {
public:
  ESPHandler();
  void begin();
  void handle();

private:
  char* ip = "";
  void _lcdPrint(String);
  void _sayNumber(int);
};

#endif // ESP_HANDLER_H