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


ESPHandler* ESPHandler::ptr_instance = nullptr;

///////////////////////////
///// Implementation  /////
///////////////////////////

ESPHandler::ESPHandler() {}

void ESPHandler::begin() {
  ESP.begin(9600);
  DEBUG_LOG("ESP Handler started");
  _sendAck();
}

void ESPHandler::handle() {
  if (ESP.available()) {
    char espCommand = ESP.read();
    DEBUG_LOG_VAR(espCommand);
    if (espCommand == IP && ip == "") {
      while (true) {
        espCommand = ESP.read();
        if (espCommand != 'P' && (espCommand > 47 && espCommand < 58 || espCommand == '.')) {
          ip += espCommand;
        } else {
          break;
        }
      }
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Налаштуй мене:");
      lcd.setCursor(0, 1);
      lcd.print(ip);
      DEBUG_LOG_VAR(ip);
      delay(1000);
    }

    switch (espCommand) {
    case ENABLE_LIGHT: {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Добре");
      delay(1000);
      _led->setAllLeds(LED_WHITE);
      _led->show();
      digitalWrite(34, HIGH);
      delay(1000);
      _sendAck();
      break;
    }
    case DISABLE_LIGHT: {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Зроблено");
      _led->setAllLeds(LED_DEFAULT_COLOR);
      _led->show();
      delay(1000);
      digitalWrite(34, LOW);
      delay(1000);
      _sendAck();
      break;
    }
    case SPEAK: {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Слухаю");
      break;
    }
    case RECOGNIZE: {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Зачекайте");
      break;
    }
    case SPEAK_TEMPERATURE: {
      int temperature = dht.getTemperature();
      if (temperature == -255) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Temperature error");
        _led->setAllLeds(LED_RED);
        _led->show();
      } else {
        _led->pickTemperatureColor(temperature);
        _mp3->play(MP3_SOUND_AROUND_TEMPERATURE);
        delay(2500);
        _mp3->sayNumber(temperature);
        _mp3->play(MP3_SOUND_DEGREE_BY_CELSIY);
        delay(1500);
        _mp3->play(MP3_SOUND_MAY_TYPE_ON_THE_DISPLAY);
        delay(2300);
        lcd.clear();
        _mp3->play(MP3_SOUND_TYPING_SONG);
        _lcdPrint("Temp: " + String(temperature) + "`C");
        delay(5000);
        _led->setAllLeds(LED_DEFAULT_COLOR);
        _led->show();
        _sendAck();
        break;
      }
    }
    case MOVE_FORWARD: {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Рухаюсь вперед");
      _motors->forward(ESP_MOTOR_SPEED);
      delay(1000);
      _motors->stop();
      lcd.clear();
      _sendAck();
      break;
    }
    case MOVE_BACKWARD: {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Рухаюсь назад");
      _motors->backward(ESP_MOTOR_SPEED);
      delay(1000);
      _motors->stop();
      lcd.clear();
      _sendAck();
      break;
    }
    case MOVE_RIGHT: {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Рухаюсь вправо");
      _motors->right(ESP_MOTOR_SPEED);
      delay(1000);
      _motors->stop();
      lcd.clear();
      _sendAck();
      break;
    }
    case MOVE_LEFT: {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Рухаюсь вліво");
      _motors->left(ESP_MOTOR_SPEED);
      delay(1000);
      _motors->stop();
      lcd.clear();
      _sendAck();
      break;
    }
    case 'N': {
      // dfMp3.playFolderTrack16(3, 1);
      break;
    }
    case ROBOCODE_POWER: {
      _mp3->play(MP3_SOUND_ROBOCODE_POWER_SONG);
      delay(5000);
      _sendAck();
      break;
    }
    case TIRED: {
      _mp3->play(MP3_SOUND_TIRED_SOUND);
      delay(1500);
      for (int i = 0; i < 10; i++) {
        _led->setLed(LED_LEFT, 0, 255 - random(0, 200), 0);
        _led->setLed(LED_RIGHT, 0, 255 - random(0, 200), 0);
        _led->show();
        delay(random(20, 100));
        _led->setAllLeds(LED_BLACK);
        _led->show();
        lcd.noBacklight();
        delay(random(20, 100));
      }
      delay(2000);
      _led->setAllLeds(LED_RED);
      _led->show();
      delay(100);
      _mp3->play(MP3_SOUND_HA_HA_JOKE);
      delay(2000);
      lcd.backlight();
      _sendAck();
      break;
    }
    case WHATS_YOUR_NAME: {
      _mp3->play(MP3_SOUND_WALL_E_VOICE);
      delay(2000);
      _sendAck();
      break;
    }
    case WHERE_ARE_YOU_FROM: {
      _mp3->play(MP3_SOUND_WHO_I_AM_SOUND);
      delay(4000);
      _sendAck();
      break;
    }
    default: _sendAck(); break;
    }
  }
}


void ESPHandler::_lcdPrint(String str) {
  for (int i = 0; i < str.length(); i++) {
    lcd.setCursor(i, 0);
    lcd.print(String(str.charAt(i)));
    delay(100);
  }
}

void ESPHandler::_sendAck() {
  DEBUG_LOG("Sending ACK");
  ESP.print(ESP_ACK_CODE);
}

#endif // ESP_HANDLER_H