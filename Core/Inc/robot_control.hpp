#pragma once

#include <cmath>
#include <cstdint>
#include <cstdio>

#include <stm32rcos/core.hpp>
#include <stm32rcos/driver/ps3.hpp>

#include "motor.hpp"

inline void delay(uint32_t ms) { osDelay(ms); }

void robot_control(Motor &motor1, Motor &motor2, Motor &motor3, Motor &motor4, stm32rcos::driver::PS3 &ps3);