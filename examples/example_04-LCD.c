/**
  ******************************************************************************
  * @file     STM32_00_HelloWorld_04-LCD.c
  * @author   SPSE Havirov
  * @version  1.0
  * @date     12-March-2022
  * @brief    Testovaci program pro LCD (s rozlisenim 8x2 nebo 16x2).
  *
  ******************************************************************************
  * @attention
  *
  * Otestovano na: F407; F401, G071
  *
  * Netestovano: F411, L152
  *
  ******************************************************************************
*/
#include "stm32_kit.h"                        // Pripojeni globalniho konfiguracniho souboru pro praci s pripravkem.

#define STEP        750                       // Krok v ms pro pozdrzeni programu

#define LCD_8x2 (((LCD_COLS) == 8) && ((LCD_ROWS) == 2))
#define LCD_16x2 (((LCD_COLS) == 16) && ((LCD_ROWS) == 2))

#include "stm32_kit/lcd.h"                    // Pripojeni konfiguracniho souboru pro praci s LCD.

BOARD_SETUP void setup(void) {
  SystemCoreClockUpdate();                    // Do SystemCoreClock se nahraje frekvence jadra.
  SysTick_Config(SystemCoreClock / 10000);    // Konfigurace SysTick timeru.
  LCD_setup();                                // Pocatecni inicializace LCD, nutne pro dalsi praci s LCD.
}

int main(void) {
                    //"        "
  char text0802_1[] = "Hello...";
  char text0802_2[] = "..World!";

                    //"                "
  char text1602_1[] = "! Hello  World !";
  char text1602_2[] = "Test LCD HD44780";   

  char *line1;
  char *line2;

  // Uvodni ozkouseni kurzoru a mazani obrazovky - ZACATEK
  LCD_set(LCD_CUR_BLINK);
  delay_ms(STEP);

  LCD_set(LCD_LINE1);
  delay_ms(STEP);

  LCD_set(LCD_CUR_NO_BLINK);
  delay_ms(STEP);

  LCD_set(LCD_CUR_OFF);
  delay_ms(STEP);
  // Uvodni ozkouseni kurzoru a mazani obrazovky - KONEC

  while (1) {
    if (!LCD_8x2 && !LCD_16x2) {
      // Nepodporovany display pro HW testy, upravte rucne
      line1 = "UNSUPPORTED";
      line2 = "LCD DISPLAY";
    }
    
    if (LCD_8x2) {
      line1 = text0802_1;
      line2 = text0802_2;
    }
    else if (LCD_16x2) {
      line1 = text1602_1;
      line2 = text1602_2;
    }
    
    LCD_set(LCD_LINE1);
    LCD_print(line1);

    LCD_set(LCD_LINE2);
    LCD_print(line2);

    delay_ms(STEP);

    // 1. testovaci sekvence znaku - ZACATEK
    for (int x = 0; x < 2; x++) {
      for (int i = 0; i < LCD_ROWS; i++) {
        LCD_set(i ? LCD_LINE2 : LCD_LINE1);

        for (int j = 0; j < LCD_COLS; j++) {
            LCD_symbol((i%2)^x ? '0' : 'H'); // Otoc a invertuj znaky na lince
        }
      }
      delay_ms(STEP);
    }
    // 1. testovaci sekvence znaku - KONEC

    LCD_set(LCD_CLR);
    LCD_set(LCD_LINE1);

    // 2. testovaci sekvence znaku - ZACATEK
    for (int i = 0; i < LCD_ROWS; i++) {
      LCD_set(i ? LCD_LINE2 : LCD_LINE1);

      for (int j = 0; j < LCD_COLS; j++) {
        LCD_symbol('#');
      }
    }
    // 2. testovaci sekvence znaku - KONEC

    delay_ms(STEP);
    LCD_set(LCD_CLR);
    delay_ms(STEP);
  }

  // return 0;
}
