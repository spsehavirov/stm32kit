/**
 * @file       f401.h
 * @brief      Definice pinů a jejich funkcí na desce Nucleo F401.
 *
 * @author     SPŠE Havířov (https://github.com/spsehavirov)
 * @date       2024-01-25
 *
 *  STM32NUCLEO-F401RE (STM32F401RETx)
 *      Kód pro makro STM32_TYPE:
 *                  401
 *      CLK:
 *                  16MHz   HSI
 *      BTN:
 *                  B1      PC13    Blue  (Pokud není sepnuté tlačítko je na pinu log. 1)
 *      Vestavěné LED:                                            (LED svítí v log. 1)
 *                  LD2     PA5     Green
 *      Externí LED:                                              (LED svítí v log. 0)
 *                  PC5     Red
 *                  PC6     Red
 *                  PC7     Red
 *                  PC8     Red
 *      Vestavěné LED (přidané):                                  (LED svítí v log. 1)
 *                  PA5     Green     (Využita i jediná vestavšna LED)
 *                  PA6     Yellow
 *                  PA7     Red
 *                  PA8     Blue
 *      LCD:
 *                  RS      PA0
 *                  R/W     PD2   (Možno zapojit přímo na GND - omezení práce s LCD)
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
 * @copyright  Copyright SPSE Havirov (c) 2024
 */

#ifndef STM32_KIT_BOARDS_F401
#define STM32_KIT_BOARDS_F401

#include "stm32_kit/gpio.h"

/**
 * Makra pro práci s LED
 */
#define LED_IN_0    (PC0) // Vestavěné LED
#define LED_IN_1    (PC1)
#define LED_IN_2    (PC2)
#define LED_IN_3    (PC3)
#define LED_EX_0    (PC6) // Externí LED
#define LED_EX_1    (PC7)
#define LED_EX_2    (PC8)
#define LED_EX_3    (PC9)

/**
 * Makro pro práci s tlačítkem
 * */
#define USER_BUTTON (PC13)

/**
 * Makra pro práci s LCD
 */
#define LCD_RS      (PA0)
#define LCD_RW      (PD2)
#define LCD_EN      (PA1)
#define LCD_DB4     (PA4)
#define LCD_DB5     (PB0)
#define LCD_DB6     (PC1)
#define LCD_DB7     (PC0)

/**
 * Makra pro práci s Keypadem
 */
#define KEYPAD_C0   (PA5)
#define KEYPAD_C1   (PA6)
#define KEYPAD_C2   (PA7)
#define KEYPAD_C3   (PA8)
#define KEYPAD_R0   (PB1)
#define KEYPAD_R1   (PB2)
#define KEYPAD_R2   (PB4)
#define KEYPAD_R3   (PB5)

/**
 * Makra pro práci s adc převodníkem
 */
#define ADC_1       (PA1)

/**
 * Makra pro práci s UART
 */
#define UART_TX     (NC)
#define UART_RX     (NC)

#endif /* STM32_KIT_BOARDS_F401 */
