/**
  ******************************************************************************
  * @file     STM32_00_HelloWorld_03-userButton.c
  * @author   SPSE Havirov
  * @version  0.9
  * @date     11-March-2022 [v0.9]
  * @brief    Pri stisku uzivatelskeho tlacitka se meni rychlost blikani LED.
  *
  * !!! PROZATIM FUNKCNI JEN PRO F407 !!!
  *
  ******************************************************************************
  * @attention
  *
  * Otestovano na: F407
  *
  * Netestovano: F401, F411, G071, L152
  *
  ******************************************************************************
*/

#include "stm32_kit.h"
#include "stm32_kit/led.h"
#include "stm32_kit/button.h"

#define LED_BLINK_STEP  1000              // Krok blikani LED
volatile uint16_t step = LED_BLINK_STEP;  // Vychozi krok pozdrzeni programu

const enum pin ledky_in[] = {
    LED_IN_0,
    LED_IN_1,
    LED_IN_2,
    LED_IN_3,
    P_INVALID
};

const enum pin ledky_ex[] = {
    LED_EX_0,
    LED_EX_1,
    LED_EX_2,
    LED_EX_3,
    P_INVALID
};

BOARD_SETUP void setup(void) {
  SystemCoreClockUpdate();                     // Do SystemCoreClock se nahraje frekvence jadra.
  SysTick_Config(SystemCoreClock / 10000);     // Konfigurace SysTick timeru.
  
  LED_setup();
  BTN_setup();
  
  //=== Nastaveni prerusovaciho systemu - prozatim pouze pro F407 - ZACATEK
  RCC->APB2ENR |= (1UL << 14);          // Enable SYSCNFG
  SYSCFG->EXTICR[0] &= ~(0x0F << 0);    // Bits[3:2:1:0] = (0:0:0:0)  -> configure EXTI0 line for PA0
  EXTI->IMR |= (1UL << 0);              // Bit[0] = 1  --> Disable the Mask on EXTI 0
  EXTI->RTSR |= (1UL << 0);             // Enable Rising Edge Trigger for PA0
  EXTI->FTSR &= ~(1UL << 0);            // Disable Falling Edge Trigger for PA0
  NVIC_SetPriority (EXTI0_IRQn, 1);     // Set Priority
  NVIC_EnableIRQ (EXTI0_IRQn);          // Enable Interrupt
  //=== Nastaveni prerusovaciho systemu - prozatim pouze pro F407 - KONEC
}

void LED_toggle(const pin_t leds[], int state, int delay) {
  for (int i = 0; leds[i] != P_INVALID; i++) {
    io_set(leds[i], state);
    delay_ms(delay);
  }
}

int main(void) {
  uint8_t i;

  while (1) {
      LED_toggle(ledky_in, 1, step); // Rozsviceni vestavenych LED.
      LED_toggle(ledky_ex, 0, step); // Rozsviceni externich LED.
      LED_toggle(ledky_in, 0, step); // Zhasnuti vestavenych LED.
      LED_toggle(ledky_ex, 1, step); // Zhasnuti externich LED.
  }

  // return 0;
}

// Handler pro preruseni - prozatim pouze pro F407
void EXTI0_IRQHandler(void) {
  if (EXTI->PR & (1UL << 0)) {
    // EXTI0 interrupt pending?                        
    EXTI->PR |= (1UL << 0); // Clear pending interrupt

    step /= 2;
    if (step < 100) {
      step = LED_BLINK_STEP;
    }
  }
}
