/**
 *
 *
 */

#ifndef STM32_KIT_BOARDS_F411
#define STM32_KIT_BOARDS_F411

#include "stm32_kit/gpio.h"

#warning "F411: Not supported Yet"

/* LED setup */
#   define LED_IN_0    (PC0)  // Vestavene LED (umele pridane, na pripravku je pouze jedna LED)
#   define LED_IN_1    (PC1)
#   define LED_IN_2    (PC2)
#   define LED_IN_3    (PC3)
#   define LED_EX_0    (PC6)  // Externi LED
#   define LED_EX_1    (PC7)
#   define LED_EX_2    (PC8)
#   define LED_EX_3    (PC9)

/* BTN setup */
#   define USER_BUTTON (PC13) // Uzivatelske tlacitko pro: F401, F411, G071, L152

/* LCD Screen setup */
#   define LCD_RS      (NC)
#   define LCD_RW      (NC)
#   define LCD_EN      (NC)
#   define LCD_DB4     (NC)
#   define LCD_DB5     (NC)
#   define LCD_DB6     (NC)
#   define LCD_DB7     (NC)

/* Keypad setup */
#   define KEYPAD_C0  (NC)
#   define KEYPAD_C1  (NC)
#   define KEYPAD_C2  (NC)
#   define KEYPAD_C3  (NC)
#   define KEYPAD_R0  (NC)
#   define KEYPAD_R1  (NC)
#   define KEYPAD_R2  (NC)
#   define KEYPAD_R3  (NC)

/* ADC setup */
#   define ADC_1      (PA1)

/* UART setup */
#   define UART_TX    (NC)
#   define UART_RX    (NC)

#endif /* STM32_KIT_BOARDS_F411 */