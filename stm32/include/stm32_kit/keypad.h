/**
  * @file     keypad.h
  * @brief    Driver pro ovladani KeyPadu.
  *
  * @author   SPŠE Havířov (https://github.com/spsehavirov)
  * @date     2022-04-10
  *
  * Otestováno na: F407; F401, G071
  *
  * Netestováno: F411, L152
  *
  * @copyright  Copyright SPSE Havirov (c) 2024
  */
#ifndef STM32_KIT_KEYPAD
#define STM32_KIT_KEYPAD

#include "platform.h"
#include "chrono.h"
#include "gpio.h"
#include "pin.h"

#include "config.h"
#include "boards.h"


#ifdef __cplusplus
extern "C" {
#endif

#ifndef KEYPAD_STEP
    #define KEYPAD_STEP 100 // Prodleva mezi dalším snímaním kláves
#endif

#ifndef KBD_MAP
// V případě, že nebude definováno pole pro rozložení KeyPadu, definuje se
static uint8_t KBD_MAP[KEYPAD_ROWS][KEYPAD_COLS];
#endif

/**
 * Globalní proměnné
 */

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


/**
 * @brief  Funkce pro ziskani hodnoty z pinu
 *
 * @return Vraci hodnotu z pinu.
 */
INLINE_STM32 uint16_t KBD_read_wires(void) {
  uint16_t tmp = 0; // Pomocná proměnná, ve které může být uchována hodnota stisknuté klávesy.
 
  tmp |= (io_get(KEYPAD_R0) << 4)
      |  (io_get(KEYPAD_R1) << 5)
      |  (io_get(KEYPAD_R2) << 6)
#if KEYPAD_ROWS > 3
      |  (io_get(KEYPAD_R3) << 7)
#else
      |  (1 << 7)
#endif
      ;
   
  tmp |= (io_read(KEYPAD_C0) << 0) // Vymaskováni sloupců
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

/**
 * @brief  Funkce pro aktivaci řádku KeyPadu
 *
 * @param  row Číslo řádku
 */
INLINE_STM32 void KBD_activateRow(int row) {
    io_set(KBD_rows[0], 0 != row);
    io_set(KBD_rows[1], 1 != row);
    io_set(KBD_rows[2], 2 != row);
#if KEYPAD_ROWS >= 4
    io_set(KBD_rows[3], 3 != row);
#endif
}

/**
 * @brief  Funkce pro získání hodnoty, která je nastavená pro daný řádek
 *
 * @param row  Číslo řádku
 */
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
 * @brief   Funkce pro zjištění vybrané hodnoty v řádku
 *
 * @note    Pokud není stisknutá žadná klávesa, vrací 0, jinak příslušný znak, dle zadefinovaného rozložení pro KeyPad.
 */
INLINE_STM32 uint8_t KBD_findKeyInRow(uint16_t value, int row, int *error) {
  if (((value & 0xF0) >> 4) != KBD_wireValueForRow(row)) {
    *error = -1;  // Nenalezeno v daném řádku
    return 0;
  }

  *error = 0; // Chyba nenastala, klávesa nalezena
  // Kontrola, zda nebylo stisknuto tlačítko ve vybraném řádku a sloupci
  int test = value & 0x0F;
  switch (test) {
    case 0xE: return KBD_MAP[row][0];
    case 0xD: return KBD_MAP[row][1];
    case 0xB: return KBD_MAP[row][2];
#if KEYPAD_COLS > 3
    case 0x7: return KBD_MAP[row][3];
#endif
  }
  
  *error = -2; // Nenalezeno
  return 0;
}

/**
 * @brief  Funkce pro zjištění hodnoty stisknuté klávesy
 *
 * @note  Pokud není stisknutá žadná klávesa, vrací 0, jinak příslušný znak, dle zadefinovaného rozložení pro KeyPad.
 */

INLINE_STM32 uint8_t KBD_read(void) {
  delay_ms(KEYPAD_STEP);

  int err;
  uint8_t key;
  uint16_t wires;
  
  for (int row = 0; row < KEYPAD_ROWS; row++) {
    KBD_activateRow(row); // Aktivace řádku n-tého řádku a deaktivace zbylých řádků
    wires = KBD_read_wires();
    key = KBD_findKeyInRow(wires, row, &err);
    if (err == 0) return key;
  }

  return 0;
}

/**
 * @brief  Počateční inicializace pro KeyPad
 *
 */
INLINE_STM32 void KBD_setup(void) {
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
