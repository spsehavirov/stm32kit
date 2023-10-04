/**
 * @file       lcd.h
 * @brief      Driver pro ovladani LCD v primem pripojeni (4bit komunikace).
 *
 * @author     Petr Madecki (petr.madecki@spsehavirov.cz)
 * @author     Tomas Michalek (tomas.michalek@spsehavirov.cz)
 *
 * @date       2023-03-29
 * @copyright  Copyright SPSE Havirov (c) 2022
 */
#ifndef STM32_KIT_LCD
#define STM32_KIT_LCD

#include "platform.h"
#include "chrono.h"
#include "gpio.h"
#include "pin.h"

#ifndef STRING_H_
# include <string.h>
#endif

#	include "boards.h"

//#========================================================================
//#=== Makra pro LCD - ZACATEK

#ifndef CUSTOM_HD44780_COMMANDS
# define LCD_ON           (0x0C)      // Zapnuti displeje (bez kurzoru)
# define LCD_OFF          (0x08)      // Vypnuti displeje
# define LCD_CLR          (0x01)      // Smazani displeje a navrat kurzoru na 1. radek a 1. sloupec
# define LCD_CUR_ON       (0x0E)      // Zapnuti kurzoru bez blikani (vcetne zapnuti displeje)
# define LCD_CUR_OFF      LCD_ON      // Vypnuti kurzoru (displej zustane zapnuty)
# define LCD_CUR_BLINK    (0x0F)      // Zapnuti blikajiciho kurzoru (vcetne zapnuti displeje)
# define LCD_CUR_NO_BLINK LCD_CUR_ON  // Zapnuti blikajiciho kurzoru (vcetne zapnuti displeje)
# define LCD_CUR_HOME     (0x03)      // Navrat kurzoru na prvni pozici prvniho radku
# define LCD_SL           (0x18)      // Rotace displeje vlevo
# define LCD_SR           (0x1C)      // Rotace displeje vpravo
# define LCD_LINE1        (0x80)      // Prvni radek prvni pozice	(0x00 + DDRAM = 0x80)
# define LCD_LINE2        (0xC0)      // Druhy radek prvni pozice	(0x40 + DDRAM = 0xC0)
# define LCD_LINE3        (0x94)      // Prvni radek prvni pozice (0x14 + DDRAM = 0x94)
# define LCD_LINE4        (0xD4)      // Prvni radek prvni pozice (0x54 + DDRAM = 0xD4)
#endif

//#=== Makra pro LCD - KONEC
//#========================================================================

//#========================================================================
//#=== Rutiny pro rizeni LCD - ZACATEK

/**
 * @brief  Umele pozdrzeni, pro vykonani instrukce LCD
 *
 */
INLINE_STM32 void LCD_busy(void) { delay_us(4); } // 400us; Pokud nebude fungovat spravne, zmenit na 10ms (doba, kdy by mel LCD radic mit prikaz zpracovan a busy flag volny).

/**
 * @brief  Zapis nibble informace (vyuziti 4bit komunikace, prikazy jsou vsak 8bit).
 *
 * @param  nibble Hodnota v rozmezi 0 - F.
 *
 */
INLINE_STM32 void LCD_write_nibble(uint8_t nibble) {
  io_set(LCD_RW, 0);
  io_set(LCD_EN, 0);
  delay_us(1);       // 100us
  io_set(LCD_EN, 1);

  nibble &= 0x0F; // Vymaskovani spodnich 4 bitu ze vstupni hodnoty
  
  io_set(LCD_DB4, (nibble & 0x1) >> 0); // Zapis informace
  io_set(LCD_DB5, (nibble & 0x2) >> 1); //  na prislusne
  io_set(LCD_DB6, (nibble & 0x4) >> 2); //  piny (zapis
  io_set(LCD_DB7, (nibble & 0x8) >> 3); //  bit po bitu).

  delay_us(1);
  io_set(LCD_EN, 0);
  delay_us(1);
}

/**
 * @brief  Funkce pro rizeni/nastaveni LCD.
 *
 * @param  cmd Kod pro ridici prikaz.
 *
 */
INLINE_STM32 void LCD_set(uint8_t cmd) {
  LCD_busy(); // Casova prodleva pro zpracovani ridicich prikazu.

  io_set(LCD_RS, 0);
  LCD_write_nibble(cmd >> 4); // Poslani 4 hornich bitu na zapis
  LCD_write_nibble(cmd);      // Poslani 4 dolnich bitu na zapis
  // delay_us(4);                                              // 400us; V pripade potreby odkomentovat.
}

INLINE_STM32 void LCD_io_setup(enum pin pin) {
  pin_enable(pin);
  pin_setup(pin, PIN_MODE_OUTPUT, PIN_PULL_DEFAULT, PIN_SPEED_HIGH, PIN_TYPE_PUSHPULL);
}

/**
 * @brief  Funkce pro inicializaci LCD.
 *
 */
void LCD_setup(void) {
  // 1. Reseni napajeni (skolni kit) - ZACATEK
#if (STM32_TYPE == 407) // Pro F407 (skolni pripravek)
  // Nasledujici radky jsou pouze pro skolni pripravek, u domacich neni nutno zapojovat PE10
  const enum pin pwr = PE10;
  LCD_io_setup(pwr);
  io_set(pwr, 0); // DIR = 0; Pouzit prevodnik '245 (z 3.3V na 5V a naopak)
#endif
  // 1. Reseni napajeni (skolni kit) - KONEC

  // 2. Nastaveni pinu a portu - ZACATEK
  __disable_irq();
  LCD_io_setup(LCD_RS);
  LCD_io_setup(LCD_RW);
  LCD_io_setup(LCD_EN);
  LCD_io_setup(LCD_DB4);
  LCD_io_setup(LCD_DB5);
  LCD_io_setup(LCD_DB6);
  LCD_io_setup(LCD_DB7);
  __enable_irq();
  // 2. Nastaveni pinu a portu - KONEC

  // 3. Nastaveni/inicializace LCD - ZACATEK
  LCD_set(0x3); // 1) Reset LCD
  LCD_set(0x3);
  LCD_set(0x2);

  LCD_set(0x28); // 2) Nastaveni komunikace, poctu radku a rozliseni: 4bit ; 2 radky ; 5x8 bodu
  LCD_set(0x0F); // 3) Aktivace displeje: zapnuti displeje a blikajiciho kurzoru
  LCD_set(0x06); // 4) Chovani displeje pri vypisu znaku: inkrementace adresy a posun kurzoru vpravo po vypsani znaku na LCD
  LCD_set(0x01); // 5) Smazani displeje
  // 3. Nastaveni/inicializace LCD - KONEC
}
//#=== Rutiny pro rizeni LCD - KONEC
//#========================================================================

//#========================================================================
//#=== Rutiny pro praci s LCD - ZACATEK

/**
 * @brief  Funkce pro vypis 1 znaku na LCD.
 *
 * @param  data Kod pro vypisovany znak, pripadne konkretni znak.
 *
 */
void LCD_symbol(uint8_t data)
{
  LCD_busy(); // Casova prodleva pro zpracovani ridicich prikazu.

  io_set(LCD_RS, 1);
  LCD_write_nibble(data >> 4);   // Horni 4bity
  LCD_write_nibble(data & 0x0F); // Dolni 4bity
}

/**
 * @brief  Funkce pro vypis retezce znaku na LCD.
 *         Funkce neresi pocet znaku na radek, ani pocet radku, nutno resit v samotnem programu nebo si napsat vl. funkci.
 *
 * @param  text Retezec/pole znaku, jez se maji vypsat na LCD.
 *
 */

void LCD_print(const char *__restrict__ text) {
  uint8_t i;

  for (i = 0; i < strlen(text); i++) {
    LCD_symbol(text[i]);
  }
}

void LCD_goto(int x, int y) {
  const uint8_t row_offset[] = { 0x00, 0x40 };
  LCD_set(0x80 | (x + row_offset[y - 1]));
}
//#=== Rutiny pro praci s LCD - KONEC
//#========================================================================

#endif /* STM32_LCD */
