

#include "stm32_kit.h"
#include "stm32_kit/i2c_lcd.h"
#include <stdio.h>


BOARD_SETUP void setup(void) {
  SystemCoreClockUpdate();                  // Do SystemCoreClock se nahraje frekvence jadra.
  SysTick_Config(SystemCoreClock / 10000);  // Konfigurace SysTick timeru.
	
	I2C_LCD_setup();
};

int main(void) {
	char *buff = "SPSE Havirov";
	I2C_LCD_print(buff);
	while(1){
	}
}
