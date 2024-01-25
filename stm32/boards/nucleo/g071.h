/**
 * @file     g071.h
 * @brief    Definice pinu a jejich funkcí na desce Nucleo G071.
 *
 * @author   SPŠE Havířov (https://github.com/spsehavirov)
 * @date     2024-01-25
 *
 *  STM32NUCLEO-G071RB (STM32G071RBTx)
 *      Kód pro makro STM32_TYPE:
 *                  71
 *      CLK:
 *                  16MHz   HSI
 *      BTN:
 *                  B1      PC13    Blue      (Pokud není sepnuté tlačítko je na pinu log. 1)
 *      Vestavěná LED:                                            (LED svítí v log. 1)
 *                  LD2     PA5     Green
 *      Externí LED:                                              (LED svítí v log. 0)
 *                  PC0     Red
 *                  PC1     Red
 *                  PC2     Red
 *                  PC3     Red
 *      Vestavěná LED (přidané):                                  (LED svítí v log. 1)
 *      (nepajivé pole)
 *                  PD0     Green
 *                  PD1     Yellow
 *                  PD2     Red
 *                  PD3     Blue
 *      LCD:
 *                  RS      PA0
 *                  R/W     PF0   (Možno zapojit přímo na GND - omezení práce s LCD)
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
 * @copyright  Copyright SPSE Havirov (c) 2024
 */

#ifndef STM32_KIT_BOARDS_G071
#define STM32_KIT_BOARDS_G071

#include "stm32_kit/gpio.h"

/**
 * Makra pro práci s LED
 */
#define LED_IN_0    (PD0)  // Vestavěne LED
#define LED_IN_1    (PD1)
#define LED_IN_2    (PD2)
#define LED_IN_3    (PD3)
#define LED_EX_0    (PC0)  // Externí LED
#define LED_EX_1    (PC1)
#define LED_EX_2    (PC2)
#define LED_EX_3    (PC3)

/**
 * Makro pro práci s tlačítkem
 */
#define USER_BUTTON (PC13)

/**
 * Makra pro práci s LCD
 */
#define LCD_RS      (PA0)
#define LCD_RW      (PF0)
#define LCD_EN      (PA1)
#define LCD_DB4     (PA4)
#define LCD_DB5     (PB1)
#define LCD_DB6     (PB11)
#define LCD_DB7     (PB12)

/**
 * Makra pro práci s Keypadem
 */
#define KEYPAD_C0   (PB0)
#define KEYPAD_C1   (PB10)
#define KEYPAD_C2   (PB13)
#define KEYPAD_C3   (PB15)
#define KEYPAD_R0   (PC9)
#define KEYPAD_R1   (PC10)
#define KEYPAD_R2   (PC11)
#define KEYPAD_R3   (PC12)

/**
 * Makra pro práci s adc převodníkem
 */
#define ADC_1       (PA1)

/**
 * Makra pro práci s UART
 */
#define UART_TX     (NC)
#define UART_RX     (NC)

#endif /* STM32_KIT_BOARDS_G071 */
