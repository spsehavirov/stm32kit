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

#ifndef STM32_KIT_LED
#define STM32_KIT_LED

#include "boards.h"

#include "platform.h" /* Podpora pro desky */
#include "chrono.h"   /* Podpora pro casovani a delay smycky */
#include "gpio.h"     /* Podpora pro zjednodusene pinovani */
#include "pin.h"

#ifdef __cplusplus
extern "C" {
#endif

//#============================================================================================================================================
//#=== Makra pro nastaveni cisel pinu pro uzivatelske tlacitko, vestavene a externi LED - ZACATEK

#define LED_IN_0_PIN    io_pin(LED_IN_0)
#define LED_IN_0_PORT   io_port(LED_IN_0)
#define LED_IN_1_PIN    io_pin(LED_IN_1)
#define LED_IN_1_PORT   io_port(LED_IN_1)
#define LED_IN_2_PIN    io_pin(LED_IN_2)
#define LED_IN_2_PORT   io_port(LED_IN_2)
#define LED_IN_3_PIN    io_pin(LED_IN_3)
#define LED_IN_3_PORT   io_port(LED_IN_3)
#define LED_EX_0_PIN    io_pin(LED_EX_0)
#define LED_EX_0_PORT   io_port(LED_EX_0)
#define LED_EX_1_PIN    io_pin(LED_EX_1)
#define LED_EX_1_PORT   io_port(LED_EX_1)
#define LED_EX_2_PIN    io_pin(LED_EX_2)
#define LED_EX_2_PORT   io_port(LED_EX_2)
#define LED_EX_3_PIN    io_pin(LED_EX_3)
#define LED_EX_3_PORT   io_port(LED_EX_3)

/**
 * @brief  Defaultni inicializace pro vybrany typ desky (skolni nebo domaci).
 *         Aktivace portu pro vestavenou(e) LED a uzivatelske tlacitko, vcetne nastaveni smeru pinu na nich.
 *         Vyuzito (nejen) pro otestovani pripravku.
 *
 */
void LED_setup(void) {
  __disable_irq();
  // Pro vestavene LED
  // Nejdrive Aktivace CLK na portu
  // Pak vynulovani MODERu pro dany pin (input mod)
  // A nasledne nastaveni smeru pinu (output mod)
  pin_enable(LED_IN_0);
  pin_enable(LED_IN_1);
  pin_enable(LED_IN_2);
  pin_enable(LED_IN_3);
  
  pin_mode(LED_IN_0, PIN_MODE_OUTPUT);
  pin_mode(LED_IN_1, PIN_MODE_OUTPUT);
  pin_mode(LED_IN_2, PIN_MODE_OUTPUT);
  pin_mode(LED_IN_3, PIN_MODE_OUTPUT);

  // Pro externi LED
  // Nejdrive Aktivace CLK na portu
  // Pak vynulovani MODERu pro dany pin (input mod)
  // A nasledne nastaveni smeru pinu (output mod)
  pin_enable(LED_EX_0);
  pin_enable(LED_EX_1);
  pin_enable(LED_EX_2);
  pin_enable(LED_EX_3);
  
  pin_mode(LED_EX_0, PIN_MODE_OUTPUT);
  pin_mode(LED_EX_1, PIN_MODE_OUTPUT);
  pin_mode(LED_EX_2, PIN_MODE_OUTPUT);
  pin_mode(LED_EX_3, PIN_MODE_OUTPUT);

  // Zhasnuti externich LED (sviti v log. 0)
  io_set(LED_EX_0, 1);
  io_set(LED_EX_1, 1);
  io_set(LED_EX_2, 1);
  io_set(LED_EX_3, 1);

  __enable_irq();
}

#ifdef __cplusplus
}
#endif

#endif /* STM32_KIT_LED */
