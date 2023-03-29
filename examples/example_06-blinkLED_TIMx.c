/**
  ********************************************************************************************************************************************
  * @file     STM32_00_HelloWorld_06-blinkLED_TIMx.c
  * @author   SPSE Havirov
  * @version  1.2
  * @date     13-Jun-2022 [v1.0]
  * @brief    Blikani vestavene LED v nekonecne smycce s vyuzitim casovace TIMx (za x doplnit prislusny timer vybraneho pripravku).
  *             Casovac bezi neustale (jednou spusten a od te doby bezi).
  *
  ********************************************************************************************************************************************
  * @attention
  *
  * Otestovano na:  F407; G071
  *
  * Netestovano:  F401, F411, L152
  *
  ********************************************************************************************************************************************
  * @history
  *
  *   v1.2  [30-June-2022]
  *         - Vyuziti nove verze konfigu pro casovace (pouziti maker PSC, ARR a CNT)
  *
  *   v1.1  [28-June-2022]
  *         - Presun veskereho nastaveni do samostatneho konfiguracniho souboru
  *         - Dodatecne nastaveni casovace pomoci vstupnich parametru funkce "TIMx_config()"
  *
  *   v1.0  [13-June-2022]
  *         - 1. testovaci verze bez konfiguracniho souboru
  *
  ********************************************************************************************************************************************
*/

//# Makra pro casovace - ZACATEK - makra je mozno zakomentovat, prislusne registry budou nastaveny do vychoziho stavu.
//#define TIMx_PSC    160                   // Makro pro nastaveni registru Prescaler     (delicka vstupni frekvence).
//#define TIMx_ARR    20165                 // Makro pro nastaveni registru Auto-Reload   (pri ktere hodnote casovac pretece).
//#define TIMx_CNT    45370                 // Makro pro nastaveni registru Counter       (od ktere hodnoty zacne zvysovani obsahu).
//# Makra pro casovace - KONEC

#include "stm32_kit.h"                                     // Pripojeni globalniho konfiguracniho souboru pro praci s pripravkem.
#include "stm32_kit/led.h"
#include "stm32_kit/timers.h"                              // Pripojeni konfiguracniho souboru pro vyuziti internich casovacu.
#define LED_BLINK_STEP  50                                 // Krok blikani LED

BOARD_SETUP void setup(void) {
  LED_setup();                                                    // Pocatecni inicializace pripravku.
  TIM6_setup();                                                   // Pocatecni inicializace casovace.
}

volatile uint8_t out = 0;                   // Pro Debug.

int main(void) {
  TIM6_config();                            // Konfigurace vybraneho casovace (na zaklade nastavenych maker TIMx_PSC, TIMx_ARR, TIMx_CNT)
  TIM6->CR1 |= TIM_CR1_CEN;                 // Spusteni casovace.
    
  while (1) {
    if (TIM6->SR & TIM_SR_UIF) {            // Kontrola, zda doslo k preteceni citace (UIF = Update Interrupt Flag).
      /**/
      // 1. moznost zmeny stavu LED
        
      int is_led_on = io_get(LED_IN_0); // Kontrola stavu LED
      io_set(LED_IN_0, !is_led_on);     // Prepnuti stavu LED
      /**/
      
      // 2. moznost zmeny stavu LED (lehci varianta)
      //TOGGLE_BIT(LED_BUILTIN_PORT->ODR, LED_BUILTIN);             // Zmena stavu LED  

      out = ~out;                                                 // Pro Debug - zmena hodnoty.
      TIM6->SR &= ~(1UL << 0);                                    // Nulovani priznaku preteceni casovace.
                                                                  // Status bit nutno nastavit na log. 0!
                                                                  // Pri preteceni nebo dosazeni hodnoty Auto-reload hodnoty nastaven HW do log. 1!
      TIM6->CNT = TIMx_CNT;                                       // V pripade, ze casovac bezi neustale (bez vypinani), je nutno po kazdem preteceni znovu naplnit obsah registru Counter.
	}
  }

  return 0;
}
