/**
 * @file     example_08-I2C_master_send.c
 * @brief    Demonstrates sending a short text over I2C in master mode.
 *           Configure the address and port using the macros below.
 */

/* Configuration overrides */
#define I2C2_ENABLE       1
#define I2C2_MASTER       1
#define I2C2_PINPACK      0
#define I2C2_SPEED        100000U

#include "stm32_kit.h"
#include "stm32_kit/i2c.h"

BOARD_SETUP void setup(void) {
  SystemCoreClockUpdate();
  SysTick_Config(SystemCoreClock / 10000);
  I2C_setup(I2C2);                         /* use I2C2 master */
}

int main(void) {
  static const char msg[] = "Hello slave";
  while (1) {
    I2C_write(I2C2, 0x42, msg, sizeof(msg) - 1);
    delay_ms(1000);
  }
}

