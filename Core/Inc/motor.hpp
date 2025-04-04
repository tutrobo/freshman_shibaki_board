#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>

#include <stm32rcos/hal.hpp>

class Motor {
public:
  Motor(TIM_HandleTypeDef *htim, uint32_t channel, GPIO_TypeDef *in1_port,
        uint16_t in1_pin, GPIO_TypeDef *in2_port, uint16_t in2_pin,
        bool reversed = false)
      : htim_{htim}, channel_{channel}, in1_port_{in1_port}, in1_pin_{in1_pin},
        in2_port_{in2_port}, in2_pin_{in2_pin}, reversed_{reversed} {
    HAL_TIM_PWM_Start(htim_, channel_);
  }

  void set_speed(float speed) {
    if (reversed_ ? (speed > 0) : (speed < 0)) { // 逆転
      HAL_GPIO_WritePin(in1_port_, in1_pin_, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(in2_port_, in2_pin_, GPIO_PIN_SET);
    } else {
      HAL_GPIO_WritePin(in1_port_, in1_pin_, GPIO_PIN_SET);
      HAL_GPIO_WritePin(in2_port_, in2_pin_, GPIO_PIN_RESET);
    }
    uint32_t compare =
        htim_->Init.Period * std::clamp(std::abs(speed), 0.0f, 1.0f);
    __HAL_TIM_SET_COMPARE(htim_, channel_, compare);
  }

private:
  TIM_HandleTypeDef *htim_;
  uint32_t channel_;
  GPIO_TypeDef *in1_port_;
  uint16_t in1_pin_;
  GPIO_TypeDef *in2_port_;
  uint16_t in2_pin_;
  bool reversed_;
};