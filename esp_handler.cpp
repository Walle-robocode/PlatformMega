#include "esp_handler.h"

ESPHandler::ESPHandler() {}

void ESPHandler::begin() {
  ESP.begin(9600);
}

void ESPHandler::handle() {
  if (ESP.available()) {
    char espCommand = ESP.read();
    Serial.println(espCommand);
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
      Serial.println(ip);
      delay(1000);
    }

    switch (espCommand) {
    case ENABLE_LIGHT: {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Добре");
      delay(1000);
      digitalWrite(34, HIGH);
      delay(1000);
      break;
    }
    case DISABLE_LIGHT: {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Зроблено");
      delay(1000);
      digitalWrite(34, LOW);
      delay(1000);
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
      } else {
        dfMp3.playFolderTrack16(1, 5);
        delay(2500);
        _sayNumber(temperature);
        dfMp3.playFolderTrack16(1, 2);
        delay(1500);
        dfMp3.playFolderTrack16(1, 6);
        delay(2300);
        lcd.clear();
        dfMp3.playFolderTrack16(1, 7);
        _lcdPrint("Temp: " + String(temperature) + "`C");
        delay(5000);
        break;
      }
    case MOVE_FORWARD: {
      motors.setMotorsSpeed(leftSpeed, rightSpeed);
      delay(1000);
      motors.setMotorsSpeed(0, 0);
      break;
    }
    case MOVE_BACKWARD: {
      // setMotorsSpeed(-leftSpeed, -rightSpeed);
      // delay(1000);
      // setMotorsSpeed(0, 0);
      break;
    }
    case MOVE_RIGHT: {
      // setMotorsSpeed(leftSpeed, -rightSpeed);
      // delay(1000);
      // setMotorsSpeed(0, 0);
      break;
    }
    case MOVE_LEFT: {
      // setMotorsSpeed(-leftSpeed, rightSpeed);
      // delay(1000);
      // setMotorsSpeed(0, 0);
      break;
    }
    case 'N': {
      dfMp3.playFolderTrack16(3, 1);
      break;
    }
    case ROBOCODE_POWER: {
      dfMp3.playFolderTrack16(3, 2);
      delay(5000);
      break;
    }
    case TIRED: {
      // humor();
      break;
    }
    case WHATS_YOUR_NAME: {
      dfMp3.playFolderTrack16(3, 6);
      delay(2000);
      break;
    }
    case WHERE_ARE_YOU_FROM: {
      dfMp3.playFolderTrack16(3, 3);
      delay(4000);
      break;
    }
    default: break;
    }

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

void ESPHandler::_sayNumber(int num) {
  int num1 = 0;
  int num2 = 0;
  if (num < 20) {
    num2 = num;
  } else {
    num2 = num % 10;
    num1 = num / 10;
  }
  if (num1 != 0) {
    dfMp3.playFolderTrack16(2, num1 * 10);
    delay(600);
  }

  dfMp3.playFolderTrack16(2, num2);
  delay(700);
}