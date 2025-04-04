#pragma once

#include <cmath>
#include <cstdio>

struct Control {
  float x;
  float y;
  float turnspeed;
};

struct Tire_speed {
  float FR, FL, BR, BL;
};
class MekanamuController {
private:
  Control control_;

public:
  MekanamuController() : control_({0, 0, 0}) {}

  Tire_speed output(Control control) {
    control_ = control;
    Tire_speed tire_speed;
    // 平行移動の速さと角度を計算
    float move_speed =
        sqrt(control_.x * control_.x + control_.y * control_.y); // 速さ
    float move_theta;                                                // 目標角度
    if (control_.y != 0) {
      move_theta = atan2(control_.x, control_.y);
    } else if (control_.x > 0) {
      move_theta = M_PI / 2;
    } else {
      move_theta = -M_PI / 2;
    }
    // 平行移動の目標出力
    tire_speed.FR = -1 * (move_speed * cos(move_theta + M_PI / 4) -
                          control_.turnspeed); // 平行移動＋回転
    tire_speed.FL =
        move_speed * cos(move_theta - M_PI / 4) + control_.turnspeed;
    tire_speed.BR =
        -1 * (move_speed * cos(move_theta - M_PI / 4) - control_.turnspeed);
    tire_speed.BL =
        move_speed * cos(move_theta + M_PI / 4) + control_.turnspeed;

    return tire_speed;
  }
};

/* 実行例
extern CAN_HandleTypeDef hcan1;
extern "C" void main_thread(void*) {
  using namespace tutrcos::core;
  using namespace tutrcos::peripheral;
  using namespace tutrcos::module;

  CAN can1(&hcan1);
  PS3 ps3(can1);
  C6x0::Manager c620_manager(can1);
  C6x0 c620_FR(c620_manager, C6x0::Type::C620, C6x0::ID::_1);
  C6x0 c620_FL(c620_manager, C6x0::Type::C620, C6x0::ID::_2);
  C6x0 c620_BR(c620_manager, C6x0::Type::C620, C6x0::ID::_3);
  C6x0 c620_BL(c620_manager, C6x0::Type::C620, C6x0::ID::_4);

  Control control_(0, 0, 0);
  MekanamuController controller;

  while (true) {
    uint32_t start = Kernel::get_ticks();
    c620_manager.update();
    ps3.update();
    control_.x_ = ps3.get_axis(PS3::Axis::RIGHT_X);
    control_.y_ = ps3.get_axis(PS3::Axis::RIGHT_Y);
    control_.turnspeed = ps3.get_axis(PS3::Axis::LEFT_X);

    Tire_speed speed = controller.output(control_);

    c620_FR.set_current(speed.FR);
    c620_FL.set_current(speed.FL);
    c620_BR.set_current(speed.BR);
    c620_BL.set_current(speed.BL);
    Thread::delay_until(start + 10);
  }
}
*/