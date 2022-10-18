/**
  *********************************************************************************
  * @file     led.h
  * @author   SPSE Havirov
  * @version  1.5.8
  * @date     10-April-2022
  * @brief    Konfiguracni soubor pro pouzivane LED diody a tlacitko.
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
  *       Dodatecne LED pripojene jak ke skolnimu, tak domacimu pripravku, viz specifikace vyse.
  *
  *
  **********************************************************************************
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
#ifndef CUSTOM_USER_BTN
# if ((STM32_TYPE == 71) || (STM32_TYPE == 152) || (STM32_TYPE == 401) || (STM32_TYPE == 411))
#   define USER_BUTTON      (PC13) // Uzivatelske tlacitko pro: F401, F411, G071, L152
# else
#   define USER_BUTTON      (PA0)  // Uzivatelske tlacitko pro: F407
# endif
# define USER_BUTTON_PIN    io_pin(USER_BUTTON)
# define USER_BUTTON_PORT   io_port(USER_BUTTON)
#endif

#ifndef CUSTOM_LED
# if (STM32_TYPE == 71)          // Pro G071
#   define LED_IN_0        (PD0)  // Vestavene LED (umele pridane, na pripravku je pouze jedna LED)
#   define LED_IN_1        (PD1)
#   define LED_IN_2        (PD2)
#   define LED_IN_3        (PD3)
#   define LED_EX_0        (PC0)  // Externi LED
#   define LED_EX_1        (PC1)
#   define LED_EX_2        (PC2)
#   define LED_EX_3        (PC3)
# elif (STM32_TYPE == 401)       // Pro F401
#   define LED_IN_0        (PC0)  // Vestavene LED (umele pridane, na pripravku je pouze jedna LED)
#   define LED_IN_1        (PC1)
#   define LED_IN_2        (PC2)
#   define LED_IN_3        (PC3)
#   define LED_EX_0        (PC6)  // Externi LED
#   define LED_EX_1        (PC7)
#   define LED_EX_2        (PC8)
#   define LED_EX_3        (PC9)
# else                           // Pro F407 (skolni pripravek)
#   define LED_IN_0        (PD12) // Vestavene LED
#   define LED_IN_1        (PD13)
#   define LED_IN_2        (PD14)
#   define LED_IN_3        (PD15)
#   define LED_EX_0        (PE12) // Externi LED
#   define LED_EX_1        (PE13)
#   define LED_EX_2        (PE14)
#   define LED_EX_3        (PE15)
# endif
# define LED_IN_0_PIN    io_pin(LED_IN_0)
# define LED_IN_0_PORT   io_port(LED_IN_0)
# define LED_IN_1_PIN    io_pin(LED_IN_1)
# define LED_IN_1_PORT   io_port(LED_IN_1)
# define LED_IN_2_PIN    io_pin(LED_IN_2)
# define LED_IN_2_PORT   io_port(LED_IN_2)
# define LED_IN_3_PIN    io_pin(LED_IN_3)
# define LED_IN_3_PORT   io_port(LED_IN_3)
# define LED_EX_0_PIN    io_pin(LED_EX_0)
# define LED_EX_0_PORT   io_port(LED_EX_0)
# define LED_EX_1_PIN    io_pin(LED_EX_1)
# define LED_EX_1_PORT   io_port(LED_EX_1)
# define LED_EX_2_PIN    io_pin(LED_EX_2)
# define LED_EX_2_PORT   io_port(LED_EX_2)
# define LED_EX_3_PIN    io_pin(LED_EX_3)
# define LED_EX_3_PORT   io_port(LED_EX_3)
#endif
//#=== Makra pro nastaveni cisel pinu pro uzivatelske tlacitko, vestavene a externi LED - KONEC
//#============================================================================================================================================

//#============================================================================================================================================
//#=== Makra pro ovladani LED - ZACATEK
#define LED_on(GPIOx, BIT)      ((GPIOx)->BSRR = (BIT))           // Rozsviceni zadane LED.
#define LED_off(GPIOx, BIT)     ((GPIOx)->BSRR = ((BIT) << 16))   // Zhasnuti zadane LED.
//#=== Makra pro ovladani LED - KONEC
//#============================================================================================================================================

/**
 * @brief  Defaultni inicializace pro vybrany typ desky (skolni nebo domaci).
 *         Aktivace portu pro vestavenou(e) LED a uzivatelske tlacitko, vcetne nastaveni smeru pinu na nich.
 *         Vyuzito (nejen) pro otestovani pripravku.
 *
 */
void LED_setup(void) {
  __disable_irq();

  // Pro uzivatelske tlacitko (input mod)
  GPIO_clock_enable(USER_BUTTON);
  CLR_PIN_MODE(USER_BUTTON_PORT, 2 * USER_BUTTON);

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
}

#ifdef __cplusplus
}
#endif

#endif /* STM32_KIT_LED */
