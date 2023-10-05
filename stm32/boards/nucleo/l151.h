/**
 * @author   SPSE Havirov
 * @version  1.0.0
 * @date     29-March-2023 [1.0.0]
 * @brief    Definice pinu a jejich funkci na desce Nucleo L151.
 *
 *  STM32NUCLEO-L151RB (STM32L151RBTx)
 *      Kod pro makro STM32_TYPE:
 *                  151
 *      CLK:
 *                  16MHz   HSI
 *      LCD:
 *
 *      KeyPad:
 *
 */



#ifndef STM32_KIT_BOARDS_L151
#define STM32_KIT_BOARDS_L151

#include "stm32_kit/gpio.h"

#warning "L151: Not supported Yet"

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

#endif /* STM32_KIT_BOARDS_L151 */