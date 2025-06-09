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
#include "i2c.h"
#include "config.h"
#include "lcd_cmd.h"

#ifndef STRING_H_
# include <string.h>
#endif

#	include "boards.h"
#if LCD_USE_I2C
#if (LCD_I2C_PORT == 1)
#define LCD_I2C_SCL I2C1_SCL
#define LCD_I2C_SDA I2C1_SDA
#elif (LCD_I2C_PORT == 2)
#define LCD_I2C_SCL I2C2_SCL
#define LCD_I2C_SDA I2C2_SDA
#elif (LCD_I2C_PORT == 3)
#define LCD_I2C_SCL I2C3_SCL
#define LCD_I2C_SDA I2C3_SDA
#else
#error "Unsupported LCD_I2C_PORT"
#endif
#endif


//#========================================================================
//#=== Makra pro LCD - ZACATEK
# define LCD_I2C_EN  (1 << 2)
# define LCD_I2C_BL  (1 << 3)
#ifndef LCD_I2C_ADDR
# define LCD_I2C_ADDR 0x27
#endif
#endif

#if LCD_USE_I2C
static uint8_t lcd_ctrl = LCD_I2C_BL;
static I2C_TypeDef *lcd_i2c;
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
INLINE_STM32 void LCD_write_nibble_i2c(uint8_t nibble) {
  uint8_t data = ((nibble & 0x0F) << 4) | lcd_ctrl;
  uint8_t tmp = data | LCD_I2C_EN;
  I2C_write(lcd_i2c, LCD_I2C_ADDR, &tmp, 1);
  tmp = data;
  I2C_write(lcd_i2c, LCD_I2C_ADDR, &tmp, 1);
}

INLINE_STM32 void LCD_write_nibble_gpio(uint8_t nibble) {
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

#if LCD_USE_I2C
# define LCD_write_nibble(n) LCD_write_nibble_i2c(n)
#else
# define LCD_write_nibble(n) LCD_write_nibble_gpio(n)
#endif

/**
 * @brief  Funkce pro rizeni/nastaveni LCD.
 *
 * @param  cmd Kod pro ridici prikaz.
 *
 */
INLINE_STM32 void LCD_set_i2c(uint8_t cmd) {
  LCD_busy();
  lcd_ctrl &= ~LCD_I2C_RS;
  LCD_write_nibble_i2c(cmd >> 4);
  LCD_write_nibble_i2c(cmd);
}

INLINE_STM32 void LCD_set_gpio(uint8_t cmd) {
  LCD_busy();
  io_set(LCD_RS, 0);
  LCD_write_nibble_gpio(cmd >> 4);
  LCD_write_nibble_gpio(cmd);
}

#if LCD_USE_I2C
# define LCD_set(cmd) LCD_set_i2c(cmd)
#else
# define LCD_set(cmd) LCD_set_gpio(cmd)
#endif

INLINE_STM32 void LCD_io_setup(enum pin pin) {
#if !LCD_USE_I2C
  pin_enable(pin);
  pin_setup(pin, PIN_MODE_OUTPUT, PIN_PULL_DEFAULT, PIN_SPEED_HIGH, PIN_TYPE_PUSHPULL);
#else
  (void)pin;
#endif
}

/**
 * @brief  Funkce pro inicializaci LCD.
 *
 */
void LCD_setup(void) {
#if LCD_USE_I2C
  lcd_i2c = I2C_setup(I2C_autoselect(LCD_I2C_SCL, LCD_I2C_SDA));
  delay_ms(50);
#else
  // 1. Reseni napajeni (skolni kit) - ZACATEK
#if (STM32_TYPE == 407)
  const enum pin pwr = PE10;
  LCD_io_setup(pwr);
  io_set(pwr, 0);
#endif
  // 1. Reseni napajeni (skolni kit) - KONEC

  __disable_irq();
  LCD_io_setup(LCD_RS);
  LCD_io_setup(LCD_RW);
  LCD_io_setup(LCD_EN);
  LCD_io_setup(LCD_DB4);
  LCD_io_setup(LCD_DB5);
  LCD_io_setup(LCD_DB6);
  LCD_io_setup(LCD_DB7);
  __enable_irq();
#endif

  LCD_set(LCD_CMD_FUNCTION(LCD_FUNC_8BIT));
  LCD_set(LCD_CMD_FUNCTION(LCD_FUNC_8BIT));
  LCD_set(LCD_CMD_FUNCTION(LCD_FUNC_4BIT));

  LCD_set(LCD_CMD_FUNCTION(((LCD_ROWS>1)?LCD_FUNC_2LINE:0) | LCD_FUNC_5x8));
  LCD_set(LCD_CMD_DISPLAY(LCD_DISP_ON | LCD_CURSOR_ON | LCD_BLINK_ON));
  LCD_set(LCD_CMD_ENTRY_MODE(LCD_ENTRY_INC));
  LCD_set(LCD_CMD_CLEAR);
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
INLINE_STM32 void LCD_symbol_i2c(uint8_t data)
{
  LCD_busy();
  lcd_ctrl |= LCD_I2C_RS;
  LCD_write_nibble_i2c(data >> 4);
  LCD_write_nibble_i2c(data & 0x0F);
}

INLINE_STM32 void LCD_symbol_gpio(uint8_t data)
{
  LCD_busy();
  io_set(LCD_RS, 1);
  LCD_write_nibble_gpio(data >> 4);
  LCD_write_nibble_gpio(data & 0x0F);
}

#if LCD_USE_I2C
# define LCD_symbol(d) LCD_symbol_i2c(d)
#else
# define LCD_symbol(d) LCD_symbol_gpio(d)
#endif

/**
 * @brief  Funkce pro vypis retezce znaku na LCD.
 *         Funkce neresi pocet znaku na radek, ani pocet radku, nutno resit v samotnem programu nebo si napsat vl. funkci.
 *
 * @param  text Retezec/pole znaku, jez se maji vypsat na LCD.
 *
 */

INLINE_STM32 void LCD_write(const char *__restrict__ text, int len) {
  for (int i = 0; i < len; i++) {
    LCD_symbol(text[i]);
  }
}

INLINE_STM32 void LCD_print(const char *__restrict__ text) {
  LCD_write(text, strlen(text));
}

INLINE_STM32 void LCD_create_char(uint8_t index, const uint8_t bitmap[8]) {
  LCD_set(LCD_CMD_SET_CGRAM(index * 8));
  for (int i = 0; i < 8; i++) {
    LCD_symbol(bitmap[i]);
  }
  LCD_set(LCD_CMD_SET_DDRAM(0));
}

static const uint8_t lcd_battery_char[8] = {
  0x0E,
  0x11,
  0x1F,
  0x11,
  0x11,
  0x1F,
  0x11,
  0x0E
};

INLINE_STM32 void LCD_test_battery(void) {
  LCD_create_char(0, lcd_battery_char);
  LCD_symbol(0);
}

INLINE_STM32 void LCD_goto(int x, int y) {
  const uint8_t row_offset[] = { 0x00, 0x40 };
  LCD_set(LCD_CMD_SET_DDRAM(x + row_offset[y - 1]));
}
//#=== Rutiny pro praci s LCD - KONEC
//#========================================================================

#endif /* STM32_LCD */
