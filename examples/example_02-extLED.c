/**
  ********************************************************************************************************************************************
  * @file     STM32_00_HelloWorld_02-extLED.c
  * @author   SPSE Havirov
  * @version  1.0
  * @date     11-March-2022 [v1.0]
  * @brief    Blikani vestavene(ych) a externich LED v nekonecne smycce, pokud neni stisknuto uzivatelske tlacitko.
  *           Pri stisku uzivatelskeho tlacitka svitit vsechny LED.
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

const enum pin ledky[] = {
    LED_IN_0,
    LED_IN_1,
    LED_IN_2,
    LED_IN_3
};

const enum pin ex_ledky[] = {
    LED_EX_0,
    LED_EX_1,
    LED_EX_2,
    LED_EX_3
};


BOARD_SETUP void setup(void) {
  LED_setup();                                                    // Pocatecni inicializace pripravku.
  SystemCoreClockUpdate();                                        // Do SystemCoreClock se nahraje frekvence jadra.
  SysTick_Config(SystemCoreClock / 10000);                        // Konfigurace SysTick timeru.
}

int main(void)
{
  uint8_t i;

  while (1) {
    // Kontrola sepnuti tlacitka
    if (READ_BIT(USER_BUTTON_PORT->IDR, (1UL << USER_BUTTON))) {  
      // Rozsviceni vestavenych LED.
      for (i = 0; i < 4; i++) {
        LED_on(io_port(ledky[i]), (1UL << (io_pin(ledky[i]))));
      }

      // Rozsviceni externich LED.
      for (i = 0; i < 4; i++) {
        LED_off(io_port(ex_ledky[i]), (1UL << (io_pin(ex_ledky[i])))); 
      }
    } else {
      // Rozsviceni vestavenych LED.
      for (i = 0; i < 4; i++) {
        io_set(ledky[i], 1);
        delay_ms(LED_BLINK_STEP);
      }

      // Rozsviceni externich LED.
      for (i = 0; i < 4; i++) {
        io_set(ex_ledky[i], 0);
        delay_ms(LED_BLINK_STEP);
      }

      // Zhasnuti vestavenych LED.
      for (i = 0; i < 4; i++) {
        io_set(ledky[i], 0);
        delay_ms(LED_BLINK_STEP);
      }

      // Zhasnuti externich LED.
      for (i = 0; i < 4; i++) {
        io_set(ex_ledky[i], 1);
        delay_ms(LED_BLINK_STEP);
      }
    }
  }

  //return 0;
}
