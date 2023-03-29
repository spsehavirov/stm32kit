/**
  ********************************************************************************************************************************************
  * @file     STM32_00_HelloWorld_01-blinkLED.c
  * @author   SPSE Havirov
  * @version  1.0
  * @date     03-March-2022 [v1.0]
  * @brief    Blikani vestavene(ych) LED v nekonecne smycce, pokud neni stisknuto uzivatelske tlacitko.
  *           Pri stisku uzivatelskeho tlacitka LED sviti.
  *
  ********************************************************************************************************************************************
  * @attention
  *
  * Otestovano na: F407, F401, G071
  *
  * Netestovano: F411, L152
  *
  ********************************************************************************************************************************************
*/

#include "stm32_kit.h"                                     // Pripojeni globalniho konfiguracniho souboru pro praci s pripravkem.
#include "stm32_kit/led.h"

#define LED_BLINK_STEP  50                                        // Krok blikani LED

volatile uint8_t out;                                             // Pro Debug.

const enum pin ledky[] = {
    LED_IN_0,
    LED_IN_1,
    LED_IN_2,
    LED_IN_3
};

BOARD_SETUP void setup(void) {
  LED_setup();                                                    // Pocatecni inicializace pripravku.
  SystemCoreClockUpdate();                                        // Do SystemCoreClock se nahraje frekvence jadra.
  SysTick_Config(SystemCoreClock / 10000);                        // Konfigurace SysTick timeru.
}

int main(void) {
  uint8_t i;
    
  while (1) {
    if (!io_read(USER_BUTTON)) {    // Kontrola sepnuti tlacitka
      // Rozsviceni vestavenych LED.
      for (i = 0; i < 4; i++) {
          io_set(ledky[i], 0);
      }
        
    } else {
      // Rozsviceni vestavenych LED.
      for (i = 0; i < 4; i++) {
          io_set(ledky[i], 1);
      };

      out = 255;

      // Zhasnuti vestavenych LED.
      for (i = 0; i < 4; i++) {
          io_set(ledky[i], 0);
      }

      out = 0;
    }
  }

  // return 0;
}
