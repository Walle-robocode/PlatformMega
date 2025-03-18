#ifndef MOTORS_H
#define MOTORS_H


#define MOTOR_A_IN_1 9
#define MOTOR_A_IN_2 8
#define MOTOR_B_IN_1 7
#define MOTOR_B_IN_2 6

class Motors {
public:
  Motors() {
    pinMode(MOTOR_A_IN_1, OUTPUT);
    pinMode(MOTOR_A_IN_2, OUTPUT);
    pinMode(MOTOR_B_IN_1, OUTPUT);
    pinMode(MOTOR_B_IN_2, OUTPUT);
  }

  void setMotorsSpeed(int left, int right) {
    if (left > 255) left = 255;
    if (left < -255) left = -255;
    if (right > 255) right = 255;
    if (right < -255) right = -255;

    if (left < 0) {
      left *= -1;
      analogWrite(MOTOR_A_IN_1, left);
      analogWrite(MOTOR_A_IN_2, 0);
    } else {
      analogWrite(MOTOR_A_IN_1, 0);
      analogWrite(MOTOR_A_IN_2, left);
    }

    if (right < 0) {
      right *= -1;
      analogWrite(MOTOR_B_IN_1, right);
      analogWrite(MOTOR_B_IN_2, 0);
    } else {
      analogWrite(MOTOR_B_IN_1, 0);
      analogWrite(MOTOR_B_IN_2, right);
    }
  }
};


#endif // MOTORS_H