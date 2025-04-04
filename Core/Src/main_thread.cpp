#include <stm32rcos/core.hpp>
#include <stm32rcos/peripheral/uart.hpp>

extern UART_HandleTypeDef huart2;

extern "C" void main_thread(void *) {
  using namespace stm32rcos::core;
  using namespace stm32rcos::peripheral;

  UART uart2(&huart2);
  uart2.enable_stdout();

  while (true) {
    printf("Hello, world!\n");
    osDelay(1000);
  }
}