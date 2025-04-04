#include "robot_control.hpp"
#include "mekanamu.hpp"
#include <stm32rcos/driver/ps3.hpp>

using namespace stm32rcos::driver;

void robot_control(Motor &FR, Motor &FL, Motor &BR, Motor &BL, PS3 &ps3) {

  while (true) {
    ps3.update();

    float speed = 0.3f; 

    FR.set_speed(speed);
    FL.set_speed(speed);
    BR.set_speed(speed);
    BL.set_speed(speed);
  }
}