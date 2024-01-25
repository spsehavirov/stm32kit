/**
  * @file     timers.h
  * @brief    Driver pro ovladani internich casovacu.
  *
  * @author   SPŠE Havířov (https://github.com/spsehavirov)

  * @date     2022-06-12
  *
  *   Podporované desky:
  *     STM32F4-DISCOVERY (STM32F407VGTx)
  *       Kód pro makro STM32_TYPE:
  *                                       407
  *       CLK:
  *                                       16MHz   HSI
  *       Časovače základní (16bit):
  *                                       TIM6, TIM7
  *
  *     STM32NUCLEO-G071RB (STM32G071RBTx)
  *       Kód pro STM32_TYPE:
  *                                       71 (G071)
  *       CLK:
  *                                       16MHz   HSI
  *       Časovače základní (16bit):
  *                                       TIM6, TIM7
  *
  *   Otestováno na: F407; G071
  *
  *   Netestováno: F401, F411, L152
  *
  *
  */
 
#ifndef STM32_KIT_TIMERS
#define STM32_KIT_TIMERS

#include "platform.h"
#include "chrono.h"
#include "gpio.h"
#include "pin.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Makra pro časovače
 */
#ifndef TIMx_PSC         // Kontrola, a případně vytvoření makra pro nastavení Prescaler (děličky).
# define TIMx_PSC 0
#endif

#ifndef TIMx_ARR         // Kontrola, a případně vytvoření makra pro Auto-Reload Registr (kdy časovač přeteče).
# define TIMx_ARR 65535
#endif

#ifndef TIMx_CNT         // Kontrola, a případně vytvoření makra pro registr Counter (od které hodnoty se bude přičítat).
# define TIMx_CNT 0
#endif


#if (STM32_TYPE == 71)
# define TIM6_APB APBRSTR1
# define TIM6_RST RCC_APBRSTR1_TIM6RST
# define TIM6_EN  RCC_APBENR1_TIM6EN
#else
# define TIM6_APB APB1ENR
# define TIM6_RST RCC_APB1RSTR_TIM6RST
# define TIM6_EN  RCC_APB1ENR_TIM6EN
#endif

/**
 * @brief  Počáteční inicializace časovače.
 */
INLINE_STM32 void TIM6_setup(void) {
  RCC->TIM6_APB |=  TIM6_RST; // reset
  RCC->TIM6_APB &= ~TIM6_RST; // časovač
  RCC->TIM6_APB |=  TIM6_EN;  // Povolení CLK pro časovač (všechny periferie potřebují mit povolené hodiny pro svůj běh).
}

/**
 * @brief  Dodatečná konfigurace časovače
 *
 * Na základě nastavených maker TIMx_PSC, TIMx_ARR, TIMx_CNT
 *
 * @note Funkce nemusí být použita, pak budou časovače v defaultním stavu.
 *
 */
INLINE_STM32 void TIM6_config(void) {
  TIM6->PSC = TIMx_PSC;  // Prescaler - dělička vstupní frekvence (hodinovího signálu)
                         // Pro f =  16MHz zakomentovat radek      ; Přeteče za 4.1ms
                         // Pro f =   2MHz zadat:   8              ; Přeteče za 32.768ms
                         // Pro f =   1MHz zadat:   16             ; Přeteče za 0.065s
                         // Pro f = 100kHz zadat:   160            ; Přeteče za 0.65s
                         // Pro f =  10kHz zadat:   1600           ; Přeteče za 6.5s

  TIM6->ARR = TIMx_ARR;  // Auto-reload hodnota, při které se má čítač restartovat. Stačí zadat pouze jednou.
                         // Pro f =  16MHz a TIM6->ARR = 65535 přeteče za 4.1ms
                         // Pro f = 100kHz a TIM6->ARR =  2016 přeteče za 20ms
                         // Pro f = 100kHz a TIM6->ARR = 20165 přeteče za 200ms
                         // Pro f =  10kHz a TIM6->ARR = 65535 přeteče za 6.5s
                         // Pro f =  10kHz a TIM6->ARR = 10000 přeteče za 1s

  TIM6->CNT = TIMx_CNT;  // Přednastavená hodnota od které začné přičítání. Nutno zadat pro každé čítání.*/
}

/**
 * @brief  Časová funkce pro pozdržení prováděného programu.
 *
 */
INLINE_STM32 void TIM6_delay(void) {
  TIM6->SR &= ~(TIM_SR_UIF);                  // Nulováni přiznaku přetečeni časovače.
                                              // Status bit nutno nastavit na log. 0! ; Pri přetečení nebo dosazení hodnoty Auto-reload hodnoty nastavené HW do log. 1!

  TIM6->CNT  = TIMx_CNT;                      // Přednastavená hodnota od které začne přičítání.
  TIM6->CR1 |= TIM_CR1_CEN;                   // Spuštění časovače.

	while (!(TIM6->SR & TIM_SR_UIF))  {       // Kontrola, zda došlo k přetečení čítače (UIF = Update Interrupt Flag).
    /* __NOP();*/
  }

  TIM6->CR1 &= ~TIM_CR1_CEN;                  // Vypnuti časovače.
}

#ifdef __cplusplus
}
#endif

#endif /* STM32_KIT_TIMERS */
