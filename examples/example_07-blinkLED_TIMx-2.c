/**
  ********************************************************************************************************************************************
  * @file     STM32_00_HelloWorld_07-blinkLED_TIMx-2.c
  * @author   SPSE Havirov
  * @version  1.2
  * @date     13-Jun-2022 [v1.0]
  * @brief    Blikani vestavene LED v nekonecne smycce s vyuzitim casovace TIMx (za x doplnit prislusny timer vybraneho pripravku).
  *             Casovac bezi pouze po urcitou (zadanou) dobu.
  *
  ********************************************************************************************************************************************
  * @attention
  *
  *   Otestovano na:  F407; G071
  *
  *   Netestovano:  F401, F411, L152
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
//#define TIMx_PSC    160                               // Makro pro nastaveni registru Prescaler     (delicka vstupni frekvence).
//#define TIMx_ARR    20165                             // Makro pro nastaveni registru Auto-Reload   (pri ktere hodnote casovac pretece).
//#define TIMx_CNT    45370                             // Makro pro nastaveni registru Counter       (od ktere hodnoty zacne zvysovani obsahu).
//# Makra pro casovace - KONEC

#include "stm32_kit.h"                                  // Pripojeni globalniho konfiguracniho souboru pro praci s pripravkem.
#include "stm32_kit/led.h"
#include "stm32_kit/timers.h"                           // Pripojeni konfiguracniho souboru pro vyuziti internich casovacu.

BOARD_SETUP void setup(void) {
  LED_setup();                                          // Pocatecni inicializace pripravku.
  TIM6_setup();                                         // Pocatecni inicializace casovace.
  TIM6_config();                                        // Konfigurace vybraneho casovace (na zaklade nastavenych maker TIMx_PSC, TIMx_ARR, TIMx_CNT).
}

volatile uint8_t out = 0;                               // Pro Debug.

int main(void) {
  
  while (1) {
    /*
    // 1. moznost zmeny stavu LED
    LED_off(LED_IN_0_PORT, (1UL << LED_IN_0_PIN));      // Zhasnuti LED.
    out = 0x00;                                         // Pro Debug - zmena hodnoty.
    
    TIM6_delay();                                       // Casova funkce pro pozdrzeni provadeneho programu.
		
    LED_on(LED_IN_0_PORT, (1UL << LED_IN_0_PIN));       // Roznuti LED.
    out = 0xFF;                                         // Pro Debug - zmena hodnoty.
    
    TIM6_delay();
    */
      
    // 2. moznost zmeny stavu LED (lehci varianta)
    TOGGLE_BIT(LED_IN_0_PORT->ODR, LED_IN_0_PIN);       // Zmena stavu LED
    
    out = ~out;                                         // Pro Debug - zmena hodnoty.
    
    TIM6_delay();                                       // Casova funkce pro pozdrzeni provadeneho programu.
  }

  return 0;
}
