#pragma once

#include <cmath>
#include <cstdint>
#include <cstdio>

#include <stm32rcos/core.hpp>

#include "motor.hpp"

inline void delay(uint32_t ms) { osDelay(ms); }

void robot_control(Motor &motor1, Motor &motor2, Motor &motor3, Motor &motor4);