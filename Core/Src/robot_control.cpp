#include "robot_control.hpp"
#include "mekanamu.hpp"
#include <stm32rcos/hal.hpp>
#include <stm32rcos_drivers/ps3.hpp>

using namespace stm32rcos_drivers;

void robot_control(Motor &FR, Motor &FL, Motor &BR, Motor &BL, PS3 &ps3,
                   TIM_HandleTypeDef *htim3) {
  Control control;
  MekanamuController mekanamu;
  Tire_speed Tire_speed;
  HAL_TIM_PWM_Start(htim3, TIM_CHANNEL_1);
  __HAL_TIM_SET_COMPARE(htim3, TIM_CHANNEL_1, 700);
  while (true) {
    ps3.update();

    control.x = 0.3;//-0.3 * ps3.get_axis(PS3Axis::RIGHT_X);
    control.y = 0.3 * ps3.get_axis(PS3Axis::RIGHT_Y);
    if (control.x == 0 && control.y == 0) {
      if (ps3.get_key(PS3Key::R1)) {
        control.turnspeed = -0.2;
      } else if (ps3.get_key(PS3Key::L1)) {
        control.turnspeed = 0.2;
      } else {
        control.turnspeed = 0;
      }
    } else {
      if (ps3.get_key(PS3Key::R1)) {
        control.turnspeed = -0.1;
      } else if (ps3.get_key(PS3Key::L1)) {
        control.turnspeed = 0.1;
      } else {
        control.turnspeed = 0;
      }
    }

    if (ps3.get_key_down(PS3Key::CIRCLE)) {
      __HAL_TIM_SET_COMPARE(htim3, TIM_CHANNEL_1, 700);
    } else if (ps3.get_key_down(PS3Key::TRIANGLE)) {
      __HAL_TIM_SET_COMPARE(htim3, TIM_CHANNEL_1, 1700);
    }

    Tire_speed = mekanamu.output(control);
    FR.set_speed(1.25 * Tire_speed.FR);
    FL.set_speed(1.25 * Tire_speed.FL);
    BR.set_speed(Tire_speed.BR);
    BL.set_speed(Tire_speed.BL);
    printf("FR: %f, FL: %f, BR: %f, BL: %f\n", Tire_speed.FR,
           Tire_speed.FL, Tire_speed.BR, Tire_speed.BL);
  }
}