/**
 * @file       lcd.h
 * @brief      Driver pro ovladani LCD v přímém připojení (4bit komunikace).
 *
 * @author     SPŠE Havířov (https://github.com/spsehavirov)
 * @date       2023-03-29
 *
 * @copyright  Copyright SPSE Havirov (c) 2024
 */
#ifndef STM32_KIT_LCD
#define STM32_KIT_LCD

#include  "platform.h"
#include "chrono.h"
#include "gpio.h"
#include "pin.h"

#ifndef STRING_H_
# include <string.h>
#endif

#	include "boards.h"

/**
 * Makra pro ovládání LCD
 */
#ifndef CUSTOM_HD44780_COMMANDS
# define LCD_ON           (0x0C)      // Zapnutí displeje (bez kurzoru)
# define LCD_OFF          (0x08)      // Vypnuti displeje
# define LCD_CLR          (0x01)      // Smazání displeje a návrat kurzoru na 1. řádek a 1. sloupec
# define LCD_CUR_ON       (0x0E)      // Zapnutí kurzoru bez blikáni (včetně zapnutí displeje)
# define LCD_CUR_OFF      LCD_ON      // Vypnutí kurzoru (displej zůstane zapnutý)
# define LCD_CUR_BLINK    (0x0F)      // Zapnutí blikajícího kurzoru (včetně zapnutí displeje)
# define LCD_CUR_NO_BLINK LCD_CUR_ON  // Zapnutí blikajícího kurzoru (včetně zapnutí displejee)
# define LCD_CUR_HOME     (0x03)      // Návrat kurzoru na první pozici prvního řádku
# define LCD_SL           (0x18)      // Rotace displeje vlevo
# define LCD_SR           (0x1C)      // Rotace displeje vpravo
# define LCD_LINE1        (0x80)      // První řádek, první pozice (0x00 + DDRAM = 0x80)
# define LCD_LINE2        (0xC0)      // Druhý řádek, první pozice (0x40 + DDRAM = 0xC0)
# define LCD_LINE3        (0x94)      // Třetí řádek, první pozice (0x14 + DDRAM = 0x94)
# define LCD_LINE4        (0xD4)      // Čtvrtý řádek, první pozice (0x54 + DDRAM = 0xD4)
#endif



/**
 * @brief  Umělé pozdržení, pro vykonání instrukce LCD
 *
 */
INLINE_STM32 void LCD_busy(void) { delay_us(4); } // 400us; Pokud nebude fungovat správně, změnit na 10ms (doba, kdy by měl LCD řadič mít příkaz zpracován, a busy flag volný).

/**
 * @brief  Zápis nibble informace (využití 4bit komunikace, příkazy jsou však 8bit).
 *
 * @param  nibble Hodnota v rozmezí 0 - F.
 */
INLINE_STM32 void LCD_write_nibble(uint8_t nibble) {
  io_set(LCD_RW, 0);
  io_set(LCD_EN, 0);
  delay_us(1); // 100us
  io_set(LCD_EN, 1);

  nibble &= 0x0F; // Vymaskování spodních 4 bitu ze vstupní hodnoty

  // Zápis informace na příslušné piny (zapis bit po bitu).
  io_set(LCD_DB4, (nibble & 0x1) >> 0);
  io_set(LCD_DB5, (nibble & 0x2) >> 1);
  io_set(LCD_DB6, (nibble & 0x4) >> 2);
  io_set(LCD_DB7, (nibble & 0x8) >> 3);

  delay_us(1);
  io_set(LCD_EN, 0);
  delay_us(1);
}

/**
 * @brief  Funkce pro řízení/nastavení LCD.
 *
 * @param  cmd Kod pro řídící příkaz.
 *
 */
INLINE_STM32 void LCD_set(uint8_t cmd) {
  LCD_busy(); // Časová prodleva pro zpracování řídících příkazů.

  io_set(LCD_RS, 0);
  LCD_write_nibble(cmd >> 4); // Posláni 4 hornich bitu na zápis
  LCD_write_nibble(cmd);      // Posláni 4 dolnich bitu na zápis
  // delay_us(4);                   // 400us; V připadě potřeby odkomentovat.
}

/**
 * @brief Nastavení pinu pro komunikaci s LCD.
 *
 * @param pin Pin, který se má nastavit.
 *
 */
INLINE_STM32 void LCD_io_setup(enum pin pin) {
  pin_enable(pin);
  pin_setup(pin, PIN_MODE_OUTPUT, PIN_PULL_DEFAULT, PIN_SPEED_HIGH, PIN_TYPE_PUSHPULL);
}

/**
 * @brief  Funkce pro inicializaci LCD.
 *
 */
INLINE_STM32 void LCD_setup(void) {
  /**
   * Řešení napájení (školné kit)
   */
#if (STM32_TYPE == 407) // Pro F407 (školní přípravek); u domácích není nutno zapojovat PE10
  const enum pin pwr = PE10;
  LCD_io_setup(pwr);
  io_set(pwr, 0); // DIR = 0; Použít převodník '245 (z 3.3V na 5V a naopak)
#endif

  /**
   * Nastavení pinu a portu
   */
  __disable_irq();
  LCD_io_setup(LCD_RS);
  LCD_io_setup(LCD_RW);
  LCD_io_setup(LCD_EN);
  LCD_io_setup(LCD_DB4);
  LCD_io_setup(LCD_DB5);
  LCD_io_setup(LCD_DB6);
  LCD_io_setup(LCD_DB7);
  __enable_irq();

  /**
   * Nastavení/inicializace LCD
   */

  LCD_set(0x3);  // Resetuje LCD
  LCD_set(0x3);
  LCD_set(0x2);

  LCD_set(0x28); // Nastavení komunikace, počtu řádku a rozlišení: 4bit ; 2 řádky ; 5x8 bodů
  LCD_set(0x0F); // Aktivace displeje: zapnutí displeje a blikajícího kurzoru
  LCD_set(0x06); // Chování displeje při výpisu znaku: inkrementace adresy a posun kurzoru vpravo po vypsání znaku na LCD
  LCD_set(0x01); // Smazáni displeje
}

/**
 * @brief  Funkce pro výpis jednoho znaku na LCD.
 *
 * @param  data Kód pro vypisovaný znak, případně konkrétní znak.
 *
 */
INLINE_STM32 void LCD_symbol(uint8_t data)
{
  LCD_busy(); // Časová prodleva pro zpracování řídících příkazů.

  io_set(LCD_RS, 1);
  LCD_write_nibble(data >> 4);   // Horní 4bity
  LCD_write_nibble(data & 0x0F); // Dolní 4bity
}

/**
 * @brief  Funkce pro výpis řetězce znaků na LCD.
 *
 * @warning Funkce neřeší počet znaků na řádek, ani počet řádků, nutno řešit v samotném programu nebo si napsat vl. funkci.
 *
 * @param  text Řetezec znaků, jež se mají vypsat na LCD.
 *
 */
INLINE_STM32 void LCD_print(const char *__restrict__ text) {
  uint8_t i;

  for (i = 0; i < strlen(text); i++) {
    LCD_symbol(text[i]);
  }
}

/**
 * @brief Nastavení kurzoru na zadanou pozici.
 *
 * @param x Pozice na ose X (Sloupec)
 * @param y Pozice na ose Y (Řádek)
 */
INLINE_STM32 void LCD_goto(int x, int y) {
  const uint8_t row_offset[] = { 0x00, 0x40 };
  LCD_set(0x80 | (x + row_offset[y - 1]));
}

#endif /* STM32_LCD */
