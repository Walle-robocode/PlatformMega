#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include <HardwareSerial.h>
#include "utils.h"
#include "motors.h"

#define BT Serial2

#define BT_CMD_STOP           'S'
#define BT_CMD_FORWARD        'F'
#define BT_CMD_BACKWARD       'B'
#define BT_CMD_LEFT           'L'
#define BT_CMD_RIGHT          'R'
#define BT_CMD_RIGHT_FORWARD  'I'
#define BT_CMD_LEFT_FORWARD   'G'
#define BT_CMD_RIGHT_BACKWARD 'H'
#define BT_CMD_LEFT_BACKWARD  'J'
#define BT_CMD_HORN_ON        'V'
#define BT_CMD_HORN_OFF       'v'
#define BT_CMD_LIGHT_ON       'W'
#define BT_CMD_LIGHT_OFF      'w'
#define BT_CMD_BACKLIGHT_ON   'U'
#define BT_CMD_BACKLIGHT_OFF  'u'
#define BT_CMD_EXTRA_ON       'X'
#define BT_CMD_EXTRA_OFF      'x'
#define BT_CMD_MAX_SPEED      'q'


class Bluetooth {
public:
  static Bluetooth* getInstance() {
    if (ptr_instance == nullptr) {
      ptr_instance = new Bluetooth();
    }
    return ptr_instance;
  }
  Bluetooth(Bluetooth const&) = delete;
  void operator=(Bluetooth const&) = delete;

  void begin();
  void handle();

private:
  uint8_t _speed = 8; // 0 - 10
  char _cmd;
  Bluetooth();
  static Bluetooth* ptr_instance;
  Motors* _motors = Motors::getInstance();
};


#endif // BLUETOOTH_H_