/**
 * @file   <nazev>.c
 * @author <Adam W>
 * 
 */

#include "stm32_kit.h"
#include "stm32_kit/lcd.h"
#include "stm32_kit/led.h"

#define I2C_FREQ 100000
#define I2C_DUTY 0.5
#define I2C_RISE 0.000001

uint8_t clear_byte;
uint8_t I2C_LCD_addr = 0;

void I2C_LCD_busy(){
	delay_us(20);
}

void I2C1_start(){
	I2C1->CR1 |= I2C_CR1_ACK;
	I2C1->CR1 |= I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB));
	io_set(LED_IN_0, 1);	// status
}

void I2C1_write(uint8_t data){
	while(!(I2C1->SR1 & I2C_SR1_TXE));
	io_set(LED_IN_1, 1);	// status
	I2C1->DR = data;
	while(!(I2C1->SR1 & I2C_SR1_BTF));
	io_set(LED_IN_1, 0);	// status
}

void I2C1_send_addr(uint8_t addr){
	I2C1->DR = addr;
	io_set(LED_IN_1, 1);	// status
	while(!(I2C1->SR1 & I2C_SR1_ADDR));
	clear_byte = (I2C1->SR1 | I2C1->SR2);
	io_set(LED_IN_1, 0);	// status
}

void I2C1_stop(){
	I2C1->CR1 |= I2C_CR1_STOP;
	io_set(LED_IN_0, 0);	// status
}

void I2C_LCD_set(uint8_t cmd){
	I2C_LCD_busy();
	I2C1_start();
	io_set(LED_IN_2, 1);	// status
	
	I2C1_send_addr(I2C_LCD_addr);
	I2C1_write(0x00);		// inst reg.
	
	I2C1_write((cmd & 0xF0) | 0x0C);
	delay_us(10);
	I2C1_write((cmd & 0xF0) | 0x08);
	
	I2C1_write((cmd << 4) | 0x0C);
	delay_us(10);
	I2C1_write((cmd << 4) | 0x08);
	
	I2C1_stop();
	io_set(LED_IN_2, 0);	// status
}

void I2C_LCD_symbol(uint8_t data){
	I2C_LCD_busy();
	I2C1_start();
	io_set(LED_IN_2, 1);	// status
	
	I2C1_send_addr(I2C_LCD_addr);
	I2C1_write(0x40);		// data reg.
	
	I2C1_write((data & 0xF0) | 0x0D);
	delay_us(10);
	I2C1_write((data & 0xF0) | 0x09);
	
	I2C1_write((data << 4) | 0x0D);
	delay_us(10);
	I2C1_write((data << 4) | 0x09);
	
	I2C1_stop();
	io_set(LED_IN_2, 0);	// status
}

void I2C1_setup(){
	io_set(LED_IN_3, 1);	// status
	__disable_irq();
	
	pin_setup_af(I2C1_SCL, PIN_MODE_AF, PIN_PULL_UP, PIN_SPEED_VERYHIGH, PIN_TYPE_OPENDRAIN, PIN_AF4);
	pin_setup_af(I2C1_SDA, PIN_MODE_AF, PIN_PULL_UP, PIN_SPEED_VERYHIGH, PIN_TYPE_OPENDRAIN, PIN_AF4);
	
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	
	I2C1->CR1 |= I2C_CR1_SWRST;
	I2C1->CR1 &= ~I2C_CR1_SWRST;
	
	// neni duvod optimalizovat, bezi pouze jednou
	I2C1->CR2 |= (SystemCoreClock / 1000000) & I2C_CR2_FREQ_Msk;
	I2C1->CCR |= (uint16_t)((1.0/I2C_FREQ * I2C_DUTY) / (1.0 / SystemCoreClock)) & I2C_CCR_CCR_Msk;
	I2C1->TRISE |= (uint16_t)(I2C_RISE / (1.0 / SystemCoreClock)) & I2C_TRISE_TRISE_Msk;
	
	I2C1->CR1 |= I2C_CR1_PE;
	
	__enable_irq();
	io_set(LED_IN_3, 0);	// status
}

void I2C1_find_device(){
	uint8_t addr = 2;
	while(!I2C_LCD_addr){
		I2C1_start();
		io_set(LED_IN_3, 1);	// status
		
		I2C1->DR = addr;
		delay_us(100);
		if(!(I2C1->SR1 & I2C_SR1_ADDR)){
			io_set(LED_IN_3, 0);	// status
			addr += 2;
			clear_byte = (I2C1->SR1 | I2C1->SR2);
			continue;
		}
		
		I2C_LCD_addr = addr;
		clear_byte = (I2C1->SR1 | I2C1->SR2);
		I2C1_stop();
	}
}

void I2C_LCD_setup(){
	I2C1_setup();
	I2C1_find_device();
	
	I2C_LCD_set(0x3);
	I2C_LCD_set(0x3);
	I2C_LCD_set(0x2);
	
	I2C_LCD_set(0x28);
	I2C_LCD_set(0x0F);
	I2C_LCD_set(0x06);
	I2C_LCD_set(0x01);
}

void I2C_LCD_print(const char *__restrict__ text){
  uint8_t i;

  for (i = 0; i < strlen(text); i++) {
    I2C_LCD_symbol(text[i]);
  }
}

BOARD_SETUP void setup(void) {
  SystemCoreClockUpdate();                  // Do SystemCoreClock se nahraje frekvence jadra.
  SysTick_Config(SystemCoreClock / 10000);  // Konfigurace SysTick timeru.
	
	LED_setup();
	I2C_LCD_setup();
};

int main(void) {
	I2C_LCD_print("SUPER PRESTIZNI");
	I2C_LCD_set(LCD_LINE2);
	I2C_LCD_print("SKOLA ELIT");
	while(1){
		
	}
}
