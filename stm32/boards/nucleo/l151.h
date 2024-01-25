/**
 * @file     l151.h
 * @brief    Definice pinu a jejich funkcí na desce Nucleo L151.
 *
 * @author   SPŠE Havířov (https://github.com/spsehavirov)
 * @date     2024-01-25
 *
 * @warning  L151 není podporována
 *
 * TODO: Popis
 *
 * @copyright  Copyright SPSE Havirov (c) 2024
 */

#ifndef STM32_KIT_BOARDS_L151
#define STM32_KIT_BOARDS_L151

#include "stm32_kit/gpio.h"

#warning "L151: Not supported Yet"

/**
 * Makra pro práci s LCD
 */
#define LCD_RS      (NC)
#define LCD_RW      (NC)
#define LCD_EN      (NC)
#define LCD_DB4     (NC)
#define LCD_DB5     (NC)
#define LCD_DB6     (NC)
#define LCD_DB7     (NC)

/**
 * Makra pro práci s Keypadem
 */
#define KEYPAD_C0  (NC)
#define KEYPAD_C1  (NC)
#define KEYPAD_C2  (NC)
#define KEYPAD_C3  (NC)
#define KEYPAD_R0  (NC)
#define KEYPAD_R1  (NC)
#define KEYPAD_R2  (NC)
#define KEYPAD_R3  (NC)

/**
 * Makra pro práci s adc převodníkem
 */
#define ADC_1      (PA1)

/**
 * Makra pro práci s UART
 */
#define UART_TX    (NC)
#define UART_RX    (NC)

#endif /* STM32_KIT_BOARDS_L151 */