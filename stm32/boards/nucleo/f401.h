/**
 * @file       f401.h
 * @brief      Definice pinu a jejich funkci na desce Nucleo F401.
 *
 * @author     Petr Madecki (petr.madecki@spsehavirov.cz)
 * @author     Tomas Michalek (tomas.michalek@spsehavirov.cz)
 *
 *  STM32NUCLEO-F401RE (STM32F401RETx)
 *      Kod pro makro STM32_TYPE:
 *                  401
 *      CLK:
 *                  16MHz   HSI
 *      BTN:
 *                  B1      PC13    Blue  (Pokud neni sepnute tlacitko je na pinu log. 1)
 *      Vestavena LED:                                            (LED sviti v log. 1!)
 *                  LD2     PA5     Green
 *      Externi LED:                                              (LED sviti v log. 0!)
 *      (nepajive pole)
 *                  PC5     Red
 *                  PC6     Red
 *                  PC7     Red
 *                  PC8     Red
 *      Vestavene LED (pridane):                                  (LED sviti v log. 1!)
 *      (nepajive pole)
 *                  PA5     Green     (Vyuzita i jedina vestavena LED)
 *                  PA6     Yellow
 *                  PA7     Red
 *                  PA8     Blue
 *      LCD:
 *                  RS      PA0
 *                  R/W     PD2   (mozno zapojit primo na GND - omezeni prace s LCD)
 *                  E       PA1
 *                  DB4     PA4
 *                  DB5     PB0
 *                  DB6     PC1
 *                  DB7     PC0
 *      KEYPAD:
 *                  COL0    PA5
 *                  COL1    PA6
 *                  COL2    PA7
 *                  COL3    PA8
 *
 *                  ROW0    PB1
 *                  ROW1    PB2
 *                  ROW2    PB4
 *                  ROW3    PB5
 *      ADC:
 *                  ADC1    PA1
 *      UART:
 *                  UART_RX ?
 *                  UART_TX ?
 *
 * @date       2023-03-29
 * @copyright  Copyright SPSE Havirov (c) 2023
 */

#ifndef STM32_KIT_BOARDS_F401
#define STM32_KIT_BOARDS_F401

#include "stm32_kit/gpio.h"

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
#   define LCD_RS      (PA0)
#   define LCD_RW      (PD2)
#   define LCD_EN      (PA1)
#   define LCD_DB4     (PA4)
#   define LCD_DB5     (PB0)
#   define LCD_DB6     (PC1)
#   define LCD_DB7     (PC0)

/* Keypad setup */
#   define KEYPAD_C0   (PA5)
#   define KEYPAD_C1   (PA6)
#   define KEYPAD_C2   (PA7)
#   define KEYPAD_C3   (PA8)
#   define KEYPAD_R0   (PB1)
#   define KEYPAD_R1   (PB2)
#   define KEYPAD_R2   (PB4)
#   define KEYPAD_R3   (PB5)

/* ADC setup */
#   define ADC_1       (PA1)

/* UART setup */
#   define UART_TX     (NC)
#   define UART_RX     (NC)

/* TODO: remove this commment */

#endif /* STM32_KIT_BOARDS_F401 */
