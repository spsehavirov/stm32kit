/**
 ************************************************************************
 * @file     keypad.h
 * @author   SPSE Havirov
 * @version  1.5.8
 * @date     10-April-2022 [v1.0]
 * @brief    Driver pro ovladani LCD v primem pripojeni (4bit komunikace).
 *
 ************************************************************************
 * @attention
 *
 * Otestovano na: F407; F401, G071
 *
 * Netestovano: F411, L152
 *
 ************************************************************************
 */
#ifndef STM32_KIT_KEYPAD
#define STM32_KIT_KEYPAD

#include "platform.h" // Podpora pro zjednodusene pinouty
#include "chrono.h"
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef KEYPAD_STEP // Prodleva mezi dalsim snimanim klaves
# define KEYPAD_STEP 100
#endif

#ifndef KeyPad_KeyMap // V pripade, ze nebude definovano pole pro rozlozeni KeyPad, definuje se
static uint8_t KeyPad_KeyMap[KEYPAD_ROWS][KEYPAD_COLS];
#endif


#include "boards.h"
#define KEYPAD_C0_PIN    io_pin(KEYPAD_C0)
#define KEYPAD_C0_PORT   io_port(KEYPAD_C0)
#define KEYPAD_C1_PIN    io_pin(KEYPAD_C1)
#define KEYPAD_C1_PORT   io_port(KEYPAD_C1)
#define KEYPAD_C2_PIN    io_pin(KEYPAD_C2)
#define KEYPAD_C2_PORT   io_port(KEYPAD_C2)
#define KEYPAD_C3_PIN    io_pin(KEYPAD_C3)
#define KEYPAD_C3_PORT   io_port(KEYPAD_C3)
#define KEYPAD_R0_PIN    io_pin(KEYPAD_R0)
#define KEYPAD_R0_PORT   io_port(KEYPAD_R0)
#define KEYPAD_R1_PIN    io_pin(KEYPAD_R1)
#define KEYPAD_R1_PORT   io_port(KEYPAD_R1)
#define KEYPAD_R2_PIN    io_pin(KEYPAD_R2)
#define KEYPAD_R2_PORT   io_port(KEYPAD_R2)
#define KEYPAD_R3_PIN    io_pin(KEYPAD_R3)
#define KEYPAD_R3_PORT   io_port(KEYPAD_R3)


INLINE_STM32 uint16_t KBD_read(void) {
  uint16_t tmp; // Pomocna promenna, ve ktere muze byt uchovana hodnota stisknute klavesy.

  tmp = ((READ_BIT(KEYPAD_R0_PORT->ODR, (1UL << KEYPAD_R0_PIN)) >> KEYPAD_R0_PIN) << 4) | // Vymaskovani radku
        ((READ_BIT(KEYPAD_R1_PORT->ODR, (1UL << KEYPAD_R1_PIN)) >> KEYPAD_R1_PIN) << 5) |
        ((READ_BIT(KEYPAD_R2_PORT->ODR, (1UL << KEYPAD_R2_PIN)) >> KEYPAD_R2_PIN) << 6) |
        ((READ_BIT(KEYPAD_R3_PORT->ODR, (1UL << KEYPAD_R3_PIN)) >> KEYPAD_R3_PIN) << 7);

  tmp |= ((READ_BIT(KEYPAD_C0_PORT->IDR, (1UL << KEYPAD_C0_PIN)) >> KEYPAD_C0_PIN) << 0) | // Vymaskovani sloupcu
         ((READ_BIT(KEYPAD_C1_PORT->IDR, (1UL << KEYPAD_C1_PIN)) >> KEYPAD_C1_PIN) << 1) |
         ((READ_BIT(KEYPAD_C2_PORT->IDR, (1UL << KEYPAD_C2_PIN)) >> KEYPAD_C2_PIN) << 2) |
         ((READ_BIT(KEYPAD_C3_PORT->IDR, (1UL << KEYPAD_C3_PIN)) >> KEYPAD_C3_PIN) << 3);

  return tmp;
}

INLINE_STM32 void KBD_activateRow(int row) {
  io_set(KEYPAD_R0, 0 != row);
  io_set(KEYPAD_R1, 1 != row);
  io_set(KEYPAD_R2, 2 != row);
  io_set(KEYPAD_R3, 3 != row);
}

/**
 * @brief  Funkce pro zisteni stisknute klavesy.
 *
 * @return  Pokud neni stisknuta zadna klavesa vraci 0, jinak prislusny znak, dle zadefinovaneho rozlozeni pro KeyPad.
 */
uint8_t KeyPad_getKey(void) {
  delay_ms(KEYPAD_STEP);

  uint16_t readout = 0;

  KBD_activateRow(0); // Aktivace radku 0. radku a deaktivace zbylych radku
  readout = KBD_read();
  switch (readout) // Kontrola, zda nebylo stisknuto tlacitko ve vybranem radku a sloupci
  {
    case 0xEE: return KeyPad_KeyMap[0][0];
    case 0xED: return KeyPad_KeyMap[0][1];
    case 0xEB: return KeyPad_KeyMap[0][2];
    case 0xE7: return KeyPad_KeyMap[0][3];
  }

  KBD_activateRow(1); // Aktivace radku 1. radku a deaktivace zbylych radku
  readout = KBD_read();
  switch (readout) // Kontrola, zda nebylo stisknuto tlacitko ve vybranem radku a sloupci
  {
    case 0xDE: return KeyPad_KeyMap[1][0];
    case 0xDD: return KeyPad_KeyMap[1][1];
    case 0xDB: return KeyPad_KeyMap[1][2];
    case 0xD7: return KeyPad_KeyMap[1][3];
  }

  KBD_activateRow(2);  // Aktivace radku 2. radku a deaktivace zbylych radku
  readout = KBD_read();
  switch (readout) // Kontrola, zda nebylo stisknuto tlacitko ve vybranem radku a sloupci
  {
    case 0xBE: return KeyPad_KeyMap[2][0];
    case 0xBD: return KeyPad_KeyMap[2][1];
    case 0xBB: return KeyPad_KeyMap[2][2];
    case 0xB7: return KeyPad_KeyMap[2][3];
  }

  KBD_activateRow(3); // Aktivace radku 3. radku a deaktivace zbylych radku
  readout = KBD_read();
  switch (readout) // Kontrola, zda nebylo stisknuto tlacitko ve vybranem radku a sloupci
  {
    case 0x7E: return KeyPad_KeyMap[3][0];
    case 0x7D: return KeyPad_KeyMap[3][1];
    case 0x7B: return KeyPad_KeyMap[3][2];
    case 0x77: return KeyPad_KeyMap[3][3];
  }

  return 0;
}

INLINE_STM32 void KBD_ioSetupRow(enum pin pin) {
  // 1. Aktivace CLK na portu - ZACATEK
  GPIO_clock_enable(pin);
  // 1. Aktivace CLK na portu - KONEC

  MODIFY_REG(io_port(pin)->MODER,   (3UL << (2 * io_pin(pin))), (1UL << 2 * io_pin(pin)));   // Output
   CLEAR_BIT(io_port(pin)->OTYPER,  (1UL << (1 * io_pin(pin))));                             // Push-pull
  MODIFY_REG(io_port(pin)->OSPEEDR, (3UL << (2 * io_pin(pin))), (2UL << 2 * io_pin(pin)));   // High speed
   CLEAR_BIT(io_port(pin)->PUPDR,   (3UL << (2 * io_pin(pin))));                             // No pull-up, pull-down
}

INLINE_STM32 void KBD_ioSetupCol(enum pin pin) {
  GPIO_clock_enable(pin);

   CLEAR_BIT(io_port(pin)->MODER, (3UL << (2 * io_pin(pin))));                             // Input
  MODIFY_REG(io_port(pin)->PUPDR, (3UL << (2 * io_pin(pin))), (1UL << 2 * io_pin(pin)));   // Pull-up
}

/**
 * @brief  Pocatecni inicializace pro KeyPad
 *
 */
void KeyPad_setup(void)
{
  __disable_irq();
  // 1. Nastaveni pinu na portu - ZACATEK
  //  Pro sloupce
  KBD_ioSetupCol(KEYPAD_C0);
  KBD_ioSetupCol(KEYPAD_C1);
  KBD_ioSetupCol(KEYPAD_C2);
  KBD_ioSetupCol(KEYPAD_C3);
  // Pro radky
  KBD_ioSetupRow(KEYPAD_R0);
  KBD_ioSetupRow(KEYPAD_R1);
  KBD_ioSetupRow(KEYPAD_R2);
  KBD_ioSetupRow(KEYPAD_R3);
  // 1. Nastaveni pinu na portu - KONEC
  __enable_irq();
}

#ifdef __cplusplus
}
#endif

#endif /* STM32_KEYPAD */
