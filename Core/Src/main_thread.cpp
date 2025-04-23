#include <stm32rcos/core.hpp>
#include <stm32rcos/hal.hpp>
#include <stm32rcos/peripheral.hpp>
#include <stm32rcos_drivers/ps3.hpp>

#include "motor.hpp"
#include "robot_control.hpp"

#include "main.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;

extern "C" void main_thread(void *) {
  using namespace stm32rcos::core;
  using namespace stm32rcos::peripheral;
  using namespace stm32rcos_drivers;

  Uart uart1(&huart1);
  PS3 ps3(uart1);

  Uart uart2(&huart2);
  enable_stdout(uart2);

  HAL_GPIO_WritePin(STBY0_GPIO_Port, STBY0_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(STBY1_GPIO_Port, STBY1_Pin, GPIO_PIN_SET);

  Motor FR(&htim1, TIM_CHANNEL_2, BIN1_1_GPIO_Port, BIN1_1_Pin,
           BIN1_2_GPIO_Port, BIN1_2_Pin);
  Motor FL(&htim1, TIM_CHANNEL_1, AIN1_1_GPIO_Port, AIN1_1_Pin,
           AIN1_2_GPIO_Port, AIN1_2_Pin);
  Motor BR(&htim1, TIM_CHANNEL_3, AIN0_1_GPIO_Port, AIN0_1_Pin,
           AIN0_2_GPIO_Port, AIN0_2_Pin);
  Motor BL(&htim1, TIM_CHANNEL_4, BIN0_1_GPIO_Port, BIN0_1_Pin,
           BIN0_2_GPIO_Port, BIN0_2_Pin);

  robot_control(FR, FL, BR, BL, ps3, &htim3);
}