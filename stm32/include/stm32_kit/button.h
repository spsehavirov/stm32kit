/**
  * @file     led.h
  * @brief    Konfigurační soubor pro použivané LED diody a tlacitko.
  *
  * @author   SPŠE Havířov (https://github.com/spsehavirov)
  * @date     2022-04-10
  *
  *   Otestováno na: F407; F401, G071
  *
  *   Netestováno: F411, L152
  *
  * @copyright  Copyright SPSE Havirov (c) 2024
  */

#ifndef STM32_KIT_BTN
#define STM32_KIT_BTN

#include "config.h"
#include "boards.h"

#include "platform.h"
#include "chrono.h"
#include "gpio.h"
#include "pin.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Inicializace uživatelského tlačítka
 */
INLINE_STM32 void BTN_setup(void) {
  __disable_irq();
  
  pin_enable(USER_BUTTON);
  pin_mode(USER_BUTTON, PIN_MODE_INPUT);

  __enable_irq();
}

#ifdef __cplusplus
}
#endif

#endif /* STM32_KIT_BTN */
