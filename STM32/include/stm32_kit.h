/**
  **********************************************************************
  * @file     stm32_kit.h
  * @author   SPSE Havirov
  * @version  1.5.8
  * @date     10-April-2022
  * @brief    Obecny konfiguracni soubor pro pouzivane pripravky.
  *
  *           Podporovane desky:
  *             STM32F4-DISCOVERY (STM32F407VGTx)   -   skolni pripravek
  *               Kod pro makro STM32_TYPE:
  *                                               407
  *               CLK:
  *                                               16MHz		HSI
  *               Uzivatelske tlacitko:
  *                                               B1      PA0     Blue      (Pokud neni sepnute tlacitko je na pinu log. 0)
  *               Vestavene LED:                                            (LED sviti v log. 1!)
  *                                               LD3     PD13    Yellow
  *                                               LD4     PD12    Green
  *                                               LD5     PD14    Red
  *                                               LD6     PD15    Blue
  *               Externi LED:                                              (LED sviti v log. 0!)
  *                 (nepajive pole)                       PE12    Red
  *                                                       PE13    Red
  *                                                       PE14    Red
  *                                                       PE15    Red
  *
  *             STM32NUCLEO-F401RE (STM32F401RETx)
  *               Kod pro makro STM32_TYPE:
  *                                               401
  *               CLK:
  *                                               16MHz   HSI
  *               Uzivatelske tlacitko:
  *                                               B1      PC13    Blue      (Pokud neni sepnute tlacitko je na pinu log. 1)
  *               Vestavena LED:                                            (LED sviti v log. 1!)
  *                                               LD2     PA5     Green
  *               Externi LED:                                              (LED sviti v log. 0!)
  *                 (nepajive pole)                       PC5     Red
  *                                                       PC6     Red
  *                                                       PC7     Red
  *                                                       PC8     Red
  *               Vestavene LED (pridane):                                  (LED sviti v log. 1!)
  *                  (nepajive pole)                      PA5     Green     (Vyuzita i jedina vestavena LED)
  *                                                       PA6     Yellow
  *                                                       PA7     Red
  *                                                       PA8     Blue
  *
  *               STM32NUCLEO-G071RB (STM32G071RBTx)
  *               Kod pro makro STM32_TYPE:
  *                                               71
  *               CLK:
  *                                               16MHz   HSI
  *               Uzivatelske tlacitko:
  *                                               B1      PC13    Blue      (Pokud neni sepnute tlacitko je na pinu log. 1)
  *               Vestavena LED:                                            (LED sviti v log. 1!)
  *                                               LD2     PA5     Green
  *               Externi LED:                                              (LED sviti v log. 0!)
  *                 (nepajive pole)                       PC0     Red
  *                                                       PC1     Red
  *                                                       PC2     Red
  *                                                       PC3     Red
  *               Vestavene LED (pridane):                                  (LED sviti v log. 1!)
  *                  (nepajive pole)                      PD0     Green
  *                                                       PD1     Yellow
  *                                                       PD2     Red
  *                                                       PD3     Blue
  *
  *
  **********************************************************************
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
  *       Dodatecne LED pripojene jak ke skolnimu, tak domacimu pripravku, viz specifikace vyse.
  *
  **********************************************************************
  */
#ifndef STM32_KIT
#define STM32_KIT

#include "config.h"
#if USE_RTOS == 1
#include <RTL.h>
#endif

#include "stm32_kit/platform.h" /* Podpora pro desky */
#include "stm32_kit/chrono.h"   /* Podpora pro casovani a delay smycky */
#include "stm32_kit/gpio.h"     /* Podpora pro zjednodusene pinovani */

#ifdef __cplusplus
extern "C" {
#endif

INLINE_STM32 char *current_platform(void) {
#if (STM32_TYPE == 71)
  return "G071";
#elif (STM32_TYPE == 407)
  return "F407";
#elif (STM32_TYPE == 152)
  return "L151";
#else
  return "Unknown";
#endif
}

#ifdef __cplusplus
}
#endif

#endif /* STM32_KIT */
