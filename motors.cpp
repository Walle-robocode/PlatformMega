#include "motors.h"

Motors* Motors::ptr_instance = nullptr;


////////////////////////////////////////
//    Motors implementation
////////////////////////////////////////

Motors::Motors() {
  pinMode(MOTOR_LEFT_IN_1, OUTPUT);
  pinMode(MOTOR_LEFT_IN_2, OUTPUT);
  pinMode(MOTOR_RIGHT_IN_1, OUTPUT);
  pinMode(MOTOR_RIGHT_IN_2, OUTPUT);
}

void Motors::forward(uint8_t speed) {
  _setSpeed(speed);
  _setMotorsSpeed(_leftSpeed, _rightSpeed);
}

void Motors::backward(uint8_t speed) {
  _setSpeed(speed);
  _setMotorsSpeed(-_leftSpeed, -_rightSpeed);
}

void Motors::left(uint8_t speed) {
  _setSpeed(speed);
  _setMotorsSpeed(0, _rightSpeed);
}

void Motors::right(uint8_t speed) {
  _setSpeed(speed);
  _setMotorsSpeed(_leftSpeed, 0);
}

void Motors::backLeft(uint8_t speed) {
  _setSpeed(speed);
  _setMotorsSpeed(-_leftSpeed, 0);
}

void Motors::backRight(uint8_t speed) {
  _setSpeed(speed);
  _setMotorsSpeed(0, -_rightSpeed);
}

void Motors::stop() {
  _setMotorsSpeed(0, 0);
}

void Motors::turnLeft(uint8_t speed) {
  _setSpeed(speed);
  _setMotorsSpeed(-_leftSpeed, _rightSpeed);
}

void Motors::turnRight(uint8_t speed) {
  _setSpeed(speed);
  _setMotorsSpeed(_leftSpeed, -_rightSpeed);
}

void Motors::_setSpeed(uint8_t speed) {
  if (speed > 10) speed = 10;
  _leftSpeed = map(speed, 0, 10, 0, MOTOR_MAX_LEFT_SPEED);
  _rightSpeed = map(speed, 0, 10, 0, MOTOR_MAX_RIGHT_SPEED);
}

void Motors::_setMotorsSpeed(int left, int right) {
  if (left < 0) {
    analogWrite(MOTOR_LEFT_IN_1, left * -1);
    analogWrite(MOTOR_LEFT_IN_2, 0);
  } else {
    analogWrite(MOTOR_LEFT_IN_1, 0);
    analogWrite(MOTOR_LEFT_IN_2, left);
  }

  if (right < 0) {
    analogWrite(MOTOR_RIGHT_IN_1, right * -1);
    analogWrite(MOTOR_RIGHT_IN_2, 0);
  } else {
    analogWrite(MOTOR_RIGHT_IN_1, 0);
    analogWrite(MOTOR_RIGHT_IN_2, right);
  }
}