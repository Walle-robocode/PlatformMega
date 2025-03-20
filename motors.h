#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>

#define MOTOR_LEFT_IN_1 9
#define MOTOR_LEFT_IN_2 8
#define MOTOR_RIGHT_IN_1 7
#define MOTOR_RIGHT_IN_2 6

#define MOTOR_MIN_LEFT_SPEED 80
#define MOTOR_MIN_RIGHT_SPEED 80
#define MOTOR_MAX_LEFT_SPEED 220
#define MOTOR_MAX_RIGHT_SPEED 220



class Motors {
public:
  static volatile uint8_t ticks_per_compute;

  static Motors* getInstance() {
    if (ptr_instance == nullptr) {
      ptr_instance = new Motors();
    }
    return ptr_instance;
  }
  Motors(Motors const&) = delete;
  void operator=(Motors const&) = delete;

  void forward(uint8_t speed);
  void backward(uint8_t speed);
  void left(uint8_t speed);
  void right(uint8_t speed);
  void backLeft(uint8_t speed);
  void backRight(uint8_t speed);
  void stop();
  void turnLeft(uint8_t speed);
  void turnRight(uint8_t speed);

private:
  static Motors* ptr_instance;
  uint8_t _leftSpeed = 0;
  uint8_t _rightSpeed = 0;

  Motors();
  void _setMotorsSpeed(int left, int right);
  void _setSpeed(uint8_t speed);
};

#endif // MOTORS_H