/**
  * @file     led.h
  * @brief    Konfigurační soubor pro použivané LED diody a tlačitko.
  *
  * @author     SPŠE Havířov (https://github.com/spsehavirov)
  * @date       2022-04-10
  *
  *   Otestovéno na: F407; F401, G071
  *
  *   Netestovéno: F411, L152
  *
  * @copyright  Copyright SPSE Havirov (c) 2024
  */

#ifndef STM32_KIT_LED
#define STM32_KIT_LED

#include "boards.h"

#include "platform.h"
#include "chrono.h"
#include "gpio.h"
#include "pin.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Makra pro nastevní čísel pinů pro uživatelské tlačítko, vestavěné a externí LED.
 */
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
 * @brief  Defaultni inicializace pro vybraný typ desky.
 *
 *  Aktivace portu pro vestavěnou(e) LED a uživatelské tlačítko, včetně nastavení směru pinu.
 *  Využito (nejen) pro otestování přípravků.
 *
 */
INLINE_STM32 void LED_setup(void) {
  __disable_irq();
  // Pro vestavěné LED
  // Nejdříve aktivace CLK na portu.
  // Pak vynulováni MODERu pro daný pin (input mod)
  // A následné nastavení směru pinu (output mod)
  pin_enable(LED_IN_0);
  pin_enable(LED_IN_1);
  pin_enable(LED_IN_2);
  pin_enable(LED_IN_3);
  
  pin_mode(LED_IN_0, PIN_MODE_OUTPUT);
  pin_mode(LED_IN_1, PIN_MODE_OUTPUT);
  pin_mode(LED_IN_2, PIN_MODE_OUTPUT);
  pin_mode(LED_IN_3, PIN_MODE_OUTPUT);

  // Pro externí LED
  // Nejdříve aktivace CLK na portu.
  // Pak vynulování MODERu pro daný pin (input mod)
  // A nasledné nastavení směru pinu (output mod)
  pin_enable(LED_EX_0);
  pin_enable(LED_EX_1);
  pin_enable(LED_EX_2);
  pin_enable(LED_EX_3);
  
  pin_mode(LED_EX_0, PIN_MODE_OUTPUT);
  pin_mode(LED_EX_1, PIN_MODE_OUTPUT);
  pin_mode(LED_EX_2, PIN_MODE_OUTPUT);
  pin_mode(LED_EX_3, PIN_MODE_OUTPUT);

  // Zhasnutí externích LED (svítí v log. 0)
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
