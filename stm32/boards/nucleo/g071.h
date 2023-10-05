/**
 * @author   SPSE Havirov
 * @version  1.0.0
 * @date     29-March-2023 [1.0.0]
 * @brief    Definice pinu a jejich funkci na desce Nucleo G071.
 *
 *  STM32NUCLEO-G071RB (STM32G071RBTx)
 *      Kod pro makro STM32_TYPE:
 *                  71
 *      CLK:
 *                  16MHz   HSI
 *      BTN:
 *                  B1      PC13    Blue      (Pokud neni sepnute tlacitko je na pinu log. 1)
 *      Vestavena LED:                                            (LED sviti v log. 1!)
 *                  LD2     PA5     Green
 *      Externi LED:                                              (LED sviti v log. 0!)
 *      (nepajive pole)
 *                  PC0     Red
 *                  PC1     Red
 *                  PC2     Red
 *                  PC3     Red
 *      Vestavene LED (pridane):                                  (LED sviti v log. 1!)
 *      (nepajive pole)
 *                  PD0     Green
 *                  PD1     Yellow
 *                  PD2     Red
 *                  PD3     Blue
 *      LCD:
 *                  RS      PA0
 *                  R/W     PF0   (mozno zapojit primo na GND - omezeni prace s LCD)
 *                  E       PA1
 *                  DB4     PA4
 *                  DB5     PB1
 *                  DB6     PB11
 *                  DB7     PB12
 *      KeyPad:
 *                  COL0    PB0
 *                  COL1    PB10
 *                  COL2    PB13
 *                  COL3    PB15
 *
 *                  ROW0    PC9
 *                  ROW1    PC10
 *                  ROW2    PC11
 *                  ROW3    PC12
 * 
 * @date       2023-03-29
 * @copyright  Copyright SPSE Havirov (c) 2023
 */

#ifndef STM32_KIT_BOARDS_G071
#define STM32_KIT_BOARDS_G071

#include "stm32_kit/gpio.h"

/* LED setup */
#   define LED_IN_0    (PD0)  // Vestavene LED (umele pridane, na pripravku je pouze jedna LED)
#   define LED_IN_1    (PD1)
#   define LED_IN_2    (PD2)
#   define LED_IN_3    (PD3)
#   define LED_EX_0    (PC0)  // Externi LED
#   define LED_EX_1    (PC1)
#   define LED_EX_2    (PC2)
#   define LED_EX_3    (PC3)

/* BTN setup */
#   define USER_BUTTON (PC13) // Uzivatelske tlacitko pro: F401, F411, G071, L152

/* LCD Screen setup */
#   define LCD_RS      (PA0)
#   define LCD_RW      (PF0)
#   define LCD_EN      (PA1)
#   define LCD_DB4     (PA4)
#   define LCD_DB5     (PB1)
#   define LCD_DB6     (PB11)
#   define LCD_DB7     (PB12)

/* Keypad setup */
#   define KEYPAD_C0   (PB0)
#   define KEYPAD_C1   (PB10)
#   define KEYPAD_C2   (PB13)
#   define KEYPAD_C3   (PB15)
#   define KEYPAD_R0   (PC9)
#   define KEYPAD_R1   (PC10)
#   define KEYPAD_R2   (PC11)
#   define KEYPAD_R3   (PC12)

/* ADC setup */
#   define ADC_1       (PA1)

/* UART setup */
#   define UART_TX     (NC)
#   define UART_RX     (NC)

#endif /* STM32_KIT_BOARDS_G071 */
