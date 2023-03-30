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

#include "platform.h" /* Podpora pro desky */
#include "chrono.h"   /* Podpora pro casovani a delay smycky */
#include "gpio.h"     /* Podpora pro zjednodusene pinovani */

#ifdef __cplusplus
extern "C" {
#endif

//#============================================================================================================================================
//#=== Makra pro nastaveni cisel pinu pro uzivatelske tlacitko, vestavene a externi LED - ZACATEK

#include "boards.h"
#define USER_BUTTON_PIN    io_pin(USER_BUTTON)
#define USER_BUTTON_PORT   io_port(USER_BUTTON)
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

//#=== Makra pro nastaveni cisel pinu pro uzivatelske tlacitko, vestavene a externi LED - KONEC
//#============================================================================================================================================

//#============================================================================================================================================
//#=== Makra pro ovladani LED - ZACATEK
#define LED_on(GPIOx, BIT)      ((GPIOx)->BSRR = (BIT))           // Rozsviceni zadane LED.
#define LED_off(GPIOx, BIT)     ((GPIOx)->BSRR = ((BIT) << 16))   // Zhasnuti zadane LED.
//#=== Makra pro ovladani LED - KONEC
//#============================================================================================================================================

/**
 * @brief Inicializace uzivatelskeho tlacitka
 */
void BTN_setup(void) {
  __disable_irq();

  // Pro uzivatelske tlacitko (input mod)
  GPIO_clock_enable(USER_BUTTON);
  CLR_PIN_MODE(USER_BUTTON_PORT, 2 * USER_BUTTON);

  __enable_irq();
}

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
  GPIO_clock_enable(LED_IN_0);
  GPIO_clock_enable(LED_IN_1);
  GPIO_clock_enable(LED_IN_2);
  GPIO_clock_enable(LED_IN_3);

  MODIFY_REG(LED_IN_0_PORT->MODER, 3UL << (2 * LED_IN_0_PIN), 1UL << (2 * LED_IN_0_PIN));
  MODIFY_REG(LED_IN_1_PORT->MODER, 3UL << (2 * LED_IN_1_PIN), 1UL << (2 * LED_IN_1_PIN));
  MODIFY_REG(LED_IN_2_PORT->MODER, 3UL << (2 * LED_IN_2_PIN), 1UL << (2 * LED_IN_2_PIN));
  MODIFY_REG(LED_IN_3_PORT->MODER, 3UL << (2 * LED_IN_3_PIN), 1UL << (2 * LED_IN_3_PIN));

  // Pro externi LED
  // Nejdrive Aktivace CLK na portu
  // Pak vynulovani MODERu pro dany pin (input mod)
  // A nasledne nastaveni smeru pinu (output mod)
  GPIO_clock_enable(LED_EX_0);
  GPIO_clock_enable(LED_EX_1);
  GPIO_clock_enable(LED_EX_2);
  GPIO_clock_enable(LED_EX_3);

  MODIFY_REG(LED_EX_0_PORT->MODER, 3UL << (2 * LED_EX_0_PIN), 1UL << (2 * LED_EX_0_PIN));
  MODIFY_REG(LED_EX_1_PORT->MODER, 3UL << (2 * LED_EX_1_PIN), 1UL << (2 * LED_EX_1_PIN));
  MODIFY_REG(LED_EX_2_PORT->MODER, 3UL << (2 * LED_EX_2_PIN), 1UL << (2 * LED_EX_2_PIN));
  MODIFY_REG(LED_EX_3_PORT->MODER, 3UL << (2 * LED_EX_3_PIN), 1UL << (2 * LED_EX_3_PIN));

  // Zhasnuti externich LED (sviti v log. 0)
  io_set(LED_EX_0, 1);
  io_set(LED_EX_1, 1);
  io_set(LED_EX_2, 1);
  io_set(LED_EX_3, 1);

  __enable_irq();

  // Z historicky duvodu:
  BTN_setup(); //TODO: move to separate file
}

#ifdef __cplusplus
}
#endif

#endif /* STM32_KIT_LED */
