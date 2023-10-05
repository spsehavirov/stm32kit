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
#include "pin.h"

#include "config.h"   // Nastaveni projektu
#include "boards.h"   // Piny ktere budeme pouzivat


#ifdef __cplusplus
extern "C" {
#endif

#ifndef KEYPAD_STEP // Prodleva mezi dalsim snimanim klaves
# define KEYPAD_STEP 100
#endif

#ifndef KBD_MAP // V pripade, ze nebude definovano pole pro rozlozeni KeyPad, definuje se
static uint8_t KBD_MAP[KEYPAD_ROWS][KEYPAD_COLS];
#endif

const enum pin KBD_rows[] = {
    KEYPAD_R0,
    KEYPAD_R1,
    KEYPAD_R2,
#if KEYPAD_ROWS >= 4
    KEYPAD_R3,
#endif
    P_INVALID
};
const enum pin KBD_cols[] = {
    KEYPAD_C0,
    KEYPAD_C1,
    KEYPAD_C2,
#if KEYPAD_COLS >= 4
    KEYPAD_C3,
#endif
    P_INVALID
};

INLINE_STM32 uint16_t KBD_read_wires(void) {
  uint16_t tmp = 0; // Pomocna promenna, ve ktere muze byt uchovana hodnota stisknute klavesy.
 
  tmp |= (io_get(KEYPAD_R0) << 4)
      |  (io_get(KEYPAD_R1) << 5)
      |  (io_get(KEYPAD_R2) << 6)
#if KEYPAD_ROWS > 3
      |  (io_get(KEYPAD_R3) << 7)
#else
      |  (1 << 7)
#endif
      ;
   
  tmp |= (io_read(KEYPAD_C0) << 0) // Vymaskovani sloupcu
      |  (io_read(KEYPAD_C1) << 1)
      |  (io_read(KEYPAD_C2) << 2)
#if KEYPAD_COLS > 3    
      |  (io_read(KEYPAD_C3) << 3)
#else
      |  (1 << 3)
#endif
      ;

  return tmp;
}

INLINE_STM32 void KBD_activateRow(int row) {
    io_set(KBD_rows[0], 0 != row);
    io_set(KBD_rows[1], 1 != row);
    io_set(KBD_rows[2], 2 != row);
#if KEYPAD_ROWS >= 4
    io_set(KBD_rows[3], 3 != row);
#endif
}

INLINE_STM32 int KBD_wireValueForRow(int row) {
  switch (row) {
    case 0: return 0xE; // 0x1110
    case 1: return 0xD; // 0x1101
    case 2: return 0xB; // 0x1011
    case 3: return 0x7; // 0x0111
  }
  return -1;
}

/**
 * @brief  Funkce pro zisteni hodnoty, vybrane v radku
 *
 * @return  Pokud neni stisknuta zadna klavesa vraci 0 (s nastavenim chyby),
 *          jinak prislusny znak, dle zadefinovaneho rozlozeni pro KeyPad.
 */
uint8_t KBD_findKeyInRow(uint16_t value, int row, int *error) {
  if (((value & 0xF0) >> 4) != KBD_wireValueForRow(row)) {
    *error = -1; // Not in this row
    return 0;
  }

  *error = 0; // No error if we find something
  // Kontrola, zda nebylo stisknuto tlacitko ve vybranem radku a sloupci
  int test = value & 0x0F;
  switch (test) {
    case 0xE: return KBD_MAP[row][0];
    case 0xD: return KBD_MAP[row][1];
    case 0xB: return KBD_MAP[row][2];
#if KEYPAD_COLS > 3
    case 0x7: return KBD_MAP[row][3];
#endif
  }
  
  *error = -2; // Not found
  return 0;
}

/**
 * @brief  Funkce pro zisteni stisknute klavesy.
 *
 * @return  Pokud neni stisknuta zadna klavesa vraci 0, jinak prislusny znak, dle zadefinovaneho rozlozeni pro KeyPad.
 */

uint8_t KBD_read(void) {
  delay_ms(KEYPAD_STEP);

  int err;
  uint8_t key;
  uint16_t wires;
  
  for (int row = 0; row < KEYPAD_ROWS; row++) {
    KBD_activateRow(row); // Aktivace radku n-teho radku a deaktivace zbylych radku
    wires = KBD_read_wires();
    key = KBD_findKeyInRow(wires, row, &err);
    if (err == 0) return key;
  }

  return 0;
}

/**
 * @brief  Pocatecni inicializace pro KeyPad
 *
 */
void KBD_setup(void) {
  __disable_irq();

  for (int i = 0; KBD_cols[i] != P_INVALID; i++) {
    pin_setup(KBD_cols[i], PIN_MODE_INPUT, PIN_PULL_UP, PIN_SPEED_DEFAULT, PIN_TYPE_DEFAULT);
  }
  for (int i = 0; KBD_rows[i] != P_INVALID; i++) {
    pin_setup(KBD_rows[i], PIN_MODE_OUTPUT, PIN_PULL_NONE, PIN_SPEED_HIGH, PIN_TYPE_PUSHPULL);
  }
  __enable_irq();
}

#ifdef __cplusplus
}
#endif

#endif /* STM32_KIT_STM32_KIT_KEYPAD */
