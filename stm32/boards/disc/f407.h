/**
 * @file       f407.h
 * @brief      Definice pinů a jejich funkcí na desce DISCOVERY F407 (skolni kit).
 *
 * @author     SPŠE Havířov (https://github.com/spsehavirov)
 * @date       2024-01-25
 *
 *  STM32NUCLEO-G071RB (STM32G071RBTx)
 *      Kód pro makro STM32_TYPE:
 *                  407
 *      CLK:
 *                  16MHz   HSI
 *      BTN:
 *                  B1      PA0     Blue      (Pokud není sepnuté tlačítko je na pinu log. 0)
 *      Vestavěné LED:                                                  (LED svítí v log. 1)
 *                  LD3     PD13    Yellow
 *                  LD4     PD12    Green
 *                  LD5     PD14    Red
 *                  LD6     PD15    Blue
 *      Externí LED:                                                    (LED svítí v log. 0)
 *                  PE12    Red
 *                  PE13    Red
 *                  PE14    Red
 *                  PE15    Red
 *      LCD:
 *                  RS      PE3
 *                  R/W     PE4    (Možno zapojit přímo na GND - omezení práce s LCD)
 *                  E       PE5
 *                  DB4     PE6
 *                  DB5     PE7
 *                  DB6     PE8
 *                  DB7     PE9
 *      KeyPad:
 *                  COL0    PD0
 *                  COL1    PD1
 *                  COL2    PD2
 *                  COL3    PD3    (Školní přípravek ma keypad pouze 3x4; domácí přípravky mají keypad 4x4)
 *
 *                  ROW0    PD6
 *                  ROW1    PD7
 *                  ROW2    PD8
 *                  ROW3    PD9
 *      UART:
 *                  TX      PA2
 *                  RX      PA3
 *
 * @copyright  Copyright SPSE Havirov (c) 2024
 */

#ifndef STM32_KIT_BOARDS_F407
#define STM32_KIT_BOARDS_F407

#include "stm32_kit/gpio.h"

/**
 * @brief Makra pro práci s LED
 */
#define LED_IN_0     (PD12) // Vestavěné LED
#define LED_IN_1     (PD13)
#define LED_IN_2     (PD14)
#define LED_IN_3     (PD15)
#define LED_EX_0     (PE12) // Externí LED
#define LED_EX_1     (PE13)
#define LED_EX_2     (PE14)
#define LED_EX_3     (PE15)

/**
 * @brief Makro pro práci s tlačítkem
 * */
#define USER_BUTTON  (PA0)

/**
 * @brief Makra pro práci s LCD
 */
#define LCD_RS       (PE3)
#define LCD_RW       (PE4)
#define LCD_EN       (PE5)
#define LCD_DB4      (PE6)
#define LCD_DB5      (PE7)
#define LCD_DB6      (PE8)
#define LCD_DB7      (PE9)

/**
 * @brief Makra pro práci s Keypadem
 */
#define KEYPAD_C0    (PD0)
#define KEYPAD_C1    (PD1)
#define KEYPAD_C2    (PD2)
#define KEYPAD_C3    (PD3)
#define KEYPAD_R0    (PD6)
#define KEYPAD_R1    (PD7)
#define KEYPAD_R2    (PD8)
#define KEYPAD_R3    (PD9)

/**
 * @brief Makra pro práci s adc převodníkem
 */
#define ADC_1        (PA1)

/**
 * @brief Makra pro práci s UART
 */
#define UART_TX      (PA2)
#define UART_RX      (PA3)

#endif /* STM32_KIT_BOARDS_F407 */
