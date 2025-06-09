/**
 * @file     example_09-I2C_slave_display.c
 * @brief    Receives a message over I2C and shows it on the LCD.
 *           Intended to run on a second board configured as I2C slave.
 */

/* Configuration overrides */
#define I2C2_ENABLE       1
#define I2C2_MASTER       0
#define I2C2_PINPACK      0
#define I2C2_OWN_ADDRESS  0x42

#include "stm32_kit.h"
#include "stm32_kit/i2c.h"
#include "stm32_kit/lcd.h"

BOARD_SETUP void setup(void) {
  SystemCoreClockUpdate();
  SysTick_Config(SystemCoreClock / 10000);
  LCD_setup();
  I2C_setup(I2C2);                         /* use I2C2 slave */
}

int main(void) {
  uint8_t text[32];
  while (1) {
    int n = I2C_slave_read(I2C2, text, sizeof(text)-1);
    text[n] = '\0';
    LCD_set(LCD_CLR);
    LCD_set(LCD_LINE1);
    LCD_print((char*)text);
  }
}

