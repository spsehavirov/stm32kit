/**
  * @file     led.h
  * @brief    Konfiguracni soubor pro pouzivane LED diody a tlacitko.
  *
  * @author     Petr Madecki (petr.madecki@spsehavirov.cz)
  * @author     Tomas Michalek (tomas.michalek@spsehavirov.cz)
  *
  *********************************************************************************
  * @attention
  *
  *   Otestovano na: F407; F401, G071
  *
  *   Netestovano: F411, L152
  *
  *   Vestavene LED pro domaci pripravek:
  *       Jelikoz pripravek obsahuje pouze jednu vestavenou LED oproti skolnimu,
  *         je zapotrebi vestavene LED simulovat - zapojit na nepajivem poli.
  *       Pouzite piny viz specifikace vyse (vestavene LED (pridane)).
  *
  *   Externi LED:
  *       Dodatecne LED pripojene jak ke skolnimu, tak domacimu pripravku, viz specifikace
  *       v pinout souboru desky.
  *
  *
  **********************************************************************************
  *
  * @date       2022-04-10
  * @copyright  Copyright SPSE Havirov (c) 2022
  */

#ifndef STM32_KIT_BTN
#define STM32_KIT_BTN

#include "config.h"
#include "boards.h"

#include "platform.h" /* Podpora pro desky */
#include "chrono.h"   /* Podpora pro casovani a delay smycky */
#include "gpio.h"     /* Podpora pro zjednodusene pinovani */
#include "pin.h"      /* Manipulace s pinem */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Inicializace uzivatelskeho tlacitka
 */
void BTN_setup(void) {
  __disable_irq();
  
  pin_enable(USER_BUTTON);
  pin_mode(USER_BUTTON, PIN_MODE_INPUT);

  __enable_irq();
}

#ifdef __cplusplus
}
#endif

#endif /* STM32_KIT_BTN */
