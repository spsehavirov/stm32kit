/**
 *
 *
 */

#ifndef STM32_KIT_BOARDS_F401
#define STM32_KIT_BOARDS_F401

#include "stm32_kit/gpio.h"

/* LCD Screen setup */
#   define LCD_RS      (PA0)
#   define LCD_RW      (PD2)
#   define LCD_EN      (PA1)
#   define LCD_DB4     (PA4)
#   define LCD_DB5     (PB0)
#   define LCD_DB6     (PC1)
#   define LCD_DB7     (PC0)

/* Keypad setup */
#   define KEYPAD_C0  (PA5)
#   define KEYPAD_C1  (PA6)
#   define KEYPAD_C2  (PA7)
#   define KEYPAD_C3  (PA8)
#   define KEYPAD_R0  (PB1)
#   define KEYPAD_R1  (PB2)
#   define KEYPAD_R2  (PB4)
#   define KEYPAD_R3  (PB5)

#endif /* STM32_KIT_BOARDS_F401 */