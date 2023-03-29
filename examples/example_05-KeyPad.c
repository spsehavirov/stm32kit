/**
  ********************************************************************************************************************************************
  * @file    STM32_00_HelloWorld_05-KeyPad.c
  * @author  SPSE Havirov
  * @version 1.1
  * @date    29-March-2022 [v1.0]
  * @brief   Testovaci program pro keypad (s rozlozenim 3x4 nebo 4x4).
  *
  ********************************************************************************************************************************************
  * @attention
  *
  * Otestovano na: F407; F401, G071
  *
  * Netestovano: F411, L152
  *
  ********************************************************************************************************************************************
  * @history
  *
  *   v1.1  [29-March-2022]
  *         - Uprava makra pro definovani rozlozeni KeyPad
  *         - Otestovano pro pripravek G071
  *
  *   v1.0  [29-March-2022]
  *         - 1. verze programu pouze pro pripravky F407 a F401
  *
  ********************************************************************************************************************************************
*/

#define DELAY_STEP    750                                         // Krok v ms pro pozdrzeni programu

#define LCD_COLS      8                                          // Pocet sloupcu pouziteho displeje
#define LCD_ROWS      2                                           // Pocet radku pouziteho displeje

#define LCD_8x2 (((LCD_COLS) == 8) && ((LCD_ROWS) == 2))
#define LCD_16x2 (((LCD_COLS) == 16) && ((LCD_ROWS) == 2))

#define KEYPAD_COLS   4                                           // Pocet sloupcu pouziteho KeyPad
#define KEYPAD_ROWS   4                                           // Pocet radku pouziteho KeyPad
//#define KEYPAD_STYLE  2                                           // Vyber znaku pro keypad, mozno uzivatelsky rozsirit/menit. Pokud bude zakomnentovano, nastavi se defaultni rozlozeni

#include "stm32_kit.h"                                     // Pripojeni globalniho konfiguracniho souboru pro praci s pripravkem.                          
#include "stm32_kit/lcd.h"                                 // Pripojeni konfiguracniho souboru pro praci s LCD.
#include "stm32_kit/keypad.h"                              // Pripojeni konfiguracniho souboru pro praci s KeyPad.

#ifndef KEYPAD_STYLE
  static uint8_t KeyPad_KeyMap[KEYPAD_ROWS][KEYPAD_COLS] = {      // Defaultni rozlozeni pro 4x4 KeyPad
                            '1', '2', '3', 'A',
                            '4', '5', '6', 'B',
                            '7', '8', '9', 'C',
                            '*', '0', '#', 'D'
  };
#elif (KEYPAD_STYLE == 1)
  static uint8_t KeyPad_KeyMap[KEYPAD_ROWS][KEYPAD_COLS] = {      // Alternativni rozlozeni pro 4x4 KeyPad
                            'a', 'b', 'c', 'd',
                            'e', 'f', 'g', 'h',
                            'i', 'j', 'k', 'l',
                            'm', 'n', 'o', 'p'
  };
#elif (KEYPAD_STYLE == 2)
  static uint8_t KeyPad_KeyMap[KEYPAD_ROWS][KEYPAD_COLS] = {      // Alternativni rozlozeni pro 4x4 KeyPad
                            'q', 'r', 's', 't',
                            'u', 'v', 'w', 'x',
                            'y', 'z', '[', ']',
                            '.', ',', '-', '='
  };
#endif
  
BOARD_SETUP void setup(void) {
  SystemCoreClockUpdate();                                      // Do SystemCoreClock se nahraje frekvence jadra.
  SysTick_Config(SystemCoreClock / 10000);                      // Konfigurace SysTick timeru.
  LCD_setup();                                                  // Pocatecni inicializace LCD, nutne pro dalsi praci s LCD.
  KeyPad_setup();                                               // Pocatecni inicializace keypadu, nutne pro dalsi praci s keypad.
}

int main(void) {
                    //"        "
  char text0802_1[] = "  Test  ";
  char text0802_2[] = " KeyPad ";

                    //"                "
  char text1602_1[] = "      Test      ";
  char text1602_2[] = "     KeyPad     ";

  while (1) {
    LCD_set(LCD_CLR);
    LCD_set(LCD_CUR_OFF);

    if (LCD_8x2) {
      LCD_set(LCD_LINE1);
      LCD_print(text0802_1);

      LCD_set(LCD_LINE2);
      LCD_print(text0802_2);

      delay_ms(DELAY_STEP);
    }
    else if (LCD_16x2) {
      LCD_set(LCD_LINE1);
      LCD_print(text1602_1);

      LCD_set(LCD_LINE2);
      LCD_print(text1602_2);

      delay_ms(DELAY_STEP);
    } else {
        /* Jine varianty LCD zatim nepodporovany pro testy */
    }

    delay_ms(DELAY_STEP);

    LCD_set(LCD_CLR);
    LCD_set(LCD_LINE1);
    LCD_set(LCD_CUR_BLINK);

    //#=== Pro zmacknutou klavesu se vypise prislusny znak (omezeni vypisu podle rozliseni LCD) - ZACATEK
    uint8_t znak;

    for (int i = 0; i < (2 * LCD_COLS); i++) {
      if (LCD_COLS == i) {
          LCD_set(LCD_LINE2);
      }
      
      do {
        znak = KeyPad_getKey();
      } while(!znak);

      LCD_symbol(znak);
    }
    //#=== Pro zmacknutou klavesu se vypise prislusny znak (omezeni vypisu podle rozliseni LCD) - KONEC

    delay_ms(2 * DELAY_STEP);
  }

  // return 0;
}
