#include "bluetooth.h"

Bluetooth* Bluetooth::ptr_instance = nullptr;

Bluetooth::Bluetooth() {}

void Bluetooth::begin() {
  BT.begin(9600);
  DEBUG_LOG("Bluetooth is ready");
}


void Bluetooth::handle() {
  if (BT.available()) {
    _cmd = BT.read();
    DEBUG_LOG_VAR(_cmd);
    switch (_cmd) {
    case BT_CMD_STOP:     _motors->stop(); break;
    case BT_CMD_FORWARD:  _motors->forward(_speed); break;
    case BT_CMD_BACKWARD: _motors->backward(_speed); break;
    case BT_CMD_LEFT:     _motors->turnLeft(_speed); break;
    case BT_CMD_RIGHT:    _motors->turnRight(_speed); break;
    case BT_CMD_RIGHT_FORWARD:  _motors->right(_speed); break;
    case BT_CMD_LEFT_FORWARD:   _motors->left(_speed); break;
    case BT_CMD_RIGHT_BACKWARD: _motors->backRight(_speed); break;
    case BT_CMD_LEFT_BACKWARD:  _motors->backLeft(_speed); break;
    case BT_CMD_EXTRA_ON: break;
    case BT_CMD_EXTRA_OFF: break;
    case BT_CMD_LIGHT_OFF: digitalWrite(34, LOW); break;
    case BT_CMD_LIGHT_ON: digitalWrite(34, HIGH); break;
    case BT_CMD_BACKLIGHT_OFF: break;
    case BT_CMD_BACKLIGHT_ON: break;
    case BT_CMD_HORN_OFF: {
      // dfMp3.playFolderTrack16(1, 1);
      delay(700);
      for (int i = 0; i < 16; i++) {
        if (i % 3 == 0 && i != 15) {
          // headServo.write(random(110, 150));
        }

        if (i == 15) {
          // headServo.write(130);
        }

        // leds[0] = CRGB(0, 255 - map(i, 0, 15, 0, 255), map(i, 0, 15, 0, 255));
        // leds[1] = CRGB(0, 255 - map(i, 0, 15, 0, 255), map(i, 0, 15, 0, 255));
        // FastLED.show();
        delay(60);
      }
      break;
    }
    case BT_CMD_HORN_ON: {
      // dfMp3.playFolderTrack16(1, 1);
      delay(700);
      for (int i = 0; i < 16; i++) {
        if (i % 3 == 0 && i != 15) {
          // headServo.write(random(110, 150));
        }

        if (i == 15) {
          // headServo.write(130);
        }

        // leds[0] = CRGB(0, 255 - map(i, 0, 15, 0, 255), map(i, 0, 15, 0, 255));
        // leds[1] = CRGB(0, 255 - map(i, 0, 15, 0, 255), map(i, 0, 15, 0, 255));
        // FastLED.show();
        delay(60);
      }
      break;
    }
    case '1': _speed = 1; break;
    case '2': _speed = 2; break;
    case '3': _speed = 3; break;
    case '4': _speed = 4; break;
    case '5': _speed = 5; break;
    case '6': _speed = 6; break;
    case '7': _speed = 7; break;
    case '8': _speed = 8; break;
    case '9': _speed = 9; break;
    case BT_CMD_MAX_SPEED: _speed = 10; break;
    default: break;
    }
  }
}
