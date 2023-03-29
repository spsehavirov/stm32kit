/**
 *
 *
 */

#ifndef STM32_KIT_BOARDS_F407
#define STM32_KIT_BOARDS_F407

#include "stm32_kit/gpio.h"

/* LCD Screen setup */
#   define LCD_RS      (PE3)
#   define LCD_RW      (PE4)
#   define LCD_EN      (PE5)
#   define LCD_DB4     (PE6)
#   define LCD_DB5     (PE7)
#   define LCD_DB6     (PE8)
#   define LCD_DB7     (PE9)

/* Keypad setup */
#   define KEYPAD_C0  (PD0)
#   define KEYPAD_C1  (PD1)
#   define KEYPAD_C2  (PD2)
#   define KEYPAD_C3  (PD3)
#   define KEYPAD_R0  (PD6)
#   define KEYPAD_R1  (PD7)
#   define KEYPAD_R2  (PD8)
#   define KEYPAD_R3  (PD9)

#endif /* STM32_KIT_BOARDS_F407 */
