#include "robot_control.hpp"

void robot_control(Motor &motor1, Motor &motor2, Motor &motor3, Motor &motor4) {
  while (true) {
    motor1.set_speed(0.5f);
    motor2.set_speed(0.5f);
    motor3.set_speed(0.5f);
    motor4.set_speed(0.5f);
    delay(1000);

    motor1.set_speed(-0.5f);
    motor2.set_speed(-0.5f);
    motor3.set_speed(-0.5f);
    motor4.set_speed(-0.5f);
    delay(1000);
  }
}