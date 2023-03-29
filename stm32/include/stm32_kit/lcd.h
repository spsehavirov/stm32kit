/**
 *************************************************************************
 * @author   SPSE Havirov
 * @version  1.5.8
 * @date     10-April-2022 [v1.0]
 * @brief    Driver pro ovladani LCD v primem pripojeni (4bit komunikace).
 *
 *           Podporovane desky:
 *             STM32F4-DISCOVERY (STM32F407VGTx)   -   skolni pripravek
 *               Kod pro makro STM32_TYPE:
 *                                               407
 *               CLK:
 *                                               16MHz   HSI
 *               LCD:
 *                                               RS      PE3
 *                                               R/W     PE4   (mozno zapojit primo na GND - omezeni prace s LCD)
 *                                               E       PE5
 *                                               DB4     PE6
 *                                               DB5     PE7
 *                                               DB6     PE8
 *                                               DB7     PE9
 *
 *             STM32NUCLEO-F401RE (STM32F401RETx)
 *               Kod pro makro STM32_TYPE:
 *                                               401
 *               CLK:
 *                                               16MHz   HSI
 *               LCD:
 *                                               RS      PA0
 *                                               R/W     PD2   (mozno zapojit primo na GND - omezeni prace s LCD)
 *                                               E       PA1
 *                                               DB4     PA4
 *                                               DB5     PB0
 *                                               DB6     PC1
 *                                               DB7     PC0
 *
 *             STM32NUCLEO-G071RB (STM32G071RBTx)
 *               Kod pro makro STM32_TYPE:
 *                                               71
 *               CLK:
 *                                               16MHz   HSI
 *               LCD:
 *                                               RS      PA0
 *                                               R/W     PF0   (mozno zapojit primo na GND - omezeni prace s LCD)
 *                                               E       PA1
 *                                               DB4     PA4
 *                                               DB5     PB1
 *                                               DB6     PB11
 *                                               DB7     PB12
 *
 **************************************************************************
 * @attention
 *
 * Otestovano na: F407; F401, G071
 *
 * Netestovano: F411, L152
 *
 **************************************************************************
 */
#ifndef STM32_KIT_LCD
#define STM32_KIT_LCD

#include "platform.h"
#include "chrono.h"
#include "gpio.h"

#ifndef STRING_H_
# include <string.h>
#endif

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


#ifndef CUSTOM_LCD
# if (STM32_TYPE == 71) // Pro G071
#   define LCD_RS      (PA0)
#   define LCD_RW      (PF0)
#   define LCD_EN      (PA1)
#   define LCD_DB4     (PA4)
#   define LCD_DB5     (PB1)
#   define LCD_DB6     (PB11)
#   define LCD_DB7     (PB12)
# elif (STM32_TYPE == 401) // Pro F401
#   define LCD_RS      (PA0)
#   define LCD_RW      (PD2)
#   define LCD_EN      (PA1)
#   define LCD_DB4     (PA4)
#   define LCD_DB5     (PB0)
#   define LCD_DB6     (PC1)
#   define LCD_DB7     (PC0)
# else // Pro F407 (skolni pripravek)
#   define LCD_RS      (PE3)
#   define LCD_RW      (PE4)
#   define LCD_EN      (PE5)
#   define LCD_DB4     (PE6)
#   define LCD_DB5     (PE7)
#   define LCD_DB6     (PE8)
#   define LCD_DB7     (PE9)
# endif
# define LCD_RS_PIN    io_pin(LCD_RS)
# define LCD_RS_PORT   io_port(LCD_RS)
# define LCD_RW_PIN    io_pin(LCD_RW)
# define LCD_RW_PORT   io_port(LCD_RW)
# define LCD_EN_PIN    io_pin(LCD_EN)
# define LCD_EN_PORT   io_port(LCD_EN)
# define LCD_DB4_PIN   io_pin(LCD_DB4)
# define LCD_DB4_PORT  io_port(LCD_DB4)
# define LCD_DB5_PIN   io_pin(LCD_DB5)
# define LCD_DB5_PORT  io_port(LCD_DB5)
# define LCD_DB6_PIN   io_pin(LCD_DB6)
# define LCD_DB6_PORT  io_port(LCD_DB6)
# define LCD_DB7_PIN   io_pin(LCD_DB7)
# define LCD_DB7_PORT  io_port(LCD_DB7)
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
INLINE_STM32 void LCD_write_nibble(uint8_t nibble)
{
  io_set(LCD_RW, 0);
  io_set(LCD_EN, 0);
  delay_us(1);       // 100us
  io_set(LCD_EN, 1);

  nibble &= 0x0F; // Vymaskovani spodnich 4 bitu ze vstupni hodnoty

  MODIFY_REG(LCD_DB4_PORT->ODR, (1UL << LCD_DB4_PIN), (((nibble & 0x1) >> 0) << LCD_DB4_PIN)); // Zapis informace
  MODIFY_REG(LCD_DB5_PORT->ODR, (1UL << LCD_DB5_PIN), (((nibble & 0x2) >> 1) << LCD_DB5_PIN)); //  na prislusne
  MODIFY_REG(LCD_DB6_PORT->ODR, (1UL << LCD_DB6_PIN), (((nibble & 0x4) >> 2) << LCD_DB6_PIN)); //  piny (zapis
  MODIFY_REG(LCD_DB7_PORT->ODR, (1UL << LCD_DB7_PIN), (((nibble & 0x8) >> 3) << LCD_DB7_PIN)); //  bit po bitu).

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
INLINE_STM32 void LCD_set(uint8_t cmd)
{
  LCD_busy(); // Casova prodleva pro zpracovani ridicich prikazu.

  io_set(LCD_RS, 0);
  LCD_write_nibble(cmd >> 4); // Poslani 4 hornich bitu na zapis
  LCD_write_nibble(cmd);      // Poslani 4 dolnich bitu na zapis
  // delay_us(4);                                              // 400us; V pripade potreby odkomentovat.
}

INLINE_STM32 void LCD_io_setup(enum pin pin) {
  GPIO_clock_enable(pin);

  MODIFY_REG(io_port(pin)->MODER,   (3UL << (2 * io_pin(pin))), (1UL << 2 * io_pin(pin)));   // Output
   CLEAR_BIT(io_port(pin)->OTYPER,  (1UL << io_pin(pin)));                                   // Push-pull
  MODIFY_REG(io_port(pin)->OSPEEDR, (3UL << (2 * io_pin(pin))), (2UL << 2 * io_pin(pin)));   // High speed
   CLEAR_BIT(io_port(pin)->PUPDR,   (3UL << 2 * io_pin(pin)));                               // Push-pull
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

void LCD_print(const char *__restrict__ text)
{
  uint8_t i;

  for (i = 0; i < strlen(text); i++) {
    LCD_symbol(text[i]);
  }
}
//#=== Rutiny pro praci s LCD - KONEC
//#========================================================================

#endif /* STM32_LCD */
