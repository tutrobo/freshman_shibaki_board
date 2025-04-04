#include "robot_control.hpp"
#include "mekanamu.hpp"
#include <stm32rcos/driver/ps3.hpp>

using namespace stm32rcos::driver;

void robot_control(Motor &FR, Motor &FL, Motor &BR, Motor &BL, PS3 &ps3) {
  Control control;
  MekanamuController mekanamu;
  Tire_speed Tire_speed;
  while (true) {
    ps3.update();
/*
    control.x = 0.5 * ps3.get_axis(PS3Axis::RIGHT_X);
    control.y = 0.5 * ps3.get_axis(PS3Axis::RIGHT_Y);
    if (ps3.get_key(PS3Key::R1)) {
      control.turnspeed = 0.3;
    } else if (ps3.get_key(PS3Key::L1)) {
      control.turnspeed = -0.3;
    } else {
      control.turnspeed = 0;
    }
      */
     
    Tire_speed = mekanamu.output(control);
    FR.set_speed(Tire_speed.FR);
    FL.set_speed(Tire_speed.FL);
    BR.set_speed(Tire_speed.BR);
    BL.set_speed(Tire_speed.BL);
  }
}