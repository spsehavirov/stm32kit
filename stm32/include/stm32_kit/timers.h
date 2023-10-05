/**
  **************************************************************************
  * @file     timers.h
  * @author   SPSE Havirov
  * @version  1.2
  * @date     13-June-2022 [v1.0]
  * @brief    Driver pro ovladani internich casovacu.
  *
  *           Podporovane desky:
  *             STM32F4-DISCOVERY (STM32F407VGTx)   -   skolni pripravek
  *               Kod pro makro STM32_TYPE:
  *                                               407
  *               CLK:
  *                                               16MHz   HSI
  *               Casovace zakladni (16bit):
  *                                               TIM6, TIM7
  *
  *             STM32NUCLEO-G071RB (STM32G071RBTx)
  *               Kod pro STM32_TYPE:
  *                                               71 (G071)
  *               CLK:
  *                                               16MHz   HSI
  *               Casovace zakladni (16bit):
  *                                               TIM6, TIM7
  *
  *
  **************************************************************************
  * @attention
  *
  *   Otestovano na: F407; G071
  *
  *   Netestovano: F401, F411, L152
  *
  **************************************************************************
  */
 
#ifndef STM32_KIT_TIMERS
#define STM32_KIT_TIMERS

#include "platform.h" /* Podpora pro desky */
#include "chrono.h"   /* Podpora pro casovani a delay smycky */
#include "gpio.h"     /* Podpora pro zjednodusene pinovani */
#include "pin.h"

#ifdef __cplusplus
extern "C" {
#endif

//#=========================================================================
//#=== Makra pro casovace - ZACATEK
#ifndef TIMx_PSC                              // Kontrola a pripadne vytvoreni makra pro nastaveni Prescaler (delicky).
# define TIMx_PSC 0
#endif

#ifndef TIMx_ARR                              // Kontrola a pripadne vytvoreni makra pro Auto-Reload Registr (kdy casovac pretece).
# define TIMx_ARR 65535
#endif

#ifndef TIMx_CNT                              // Kontrola a pripadne vytvoreni makra pro registr Counter (od ktere hodnoty se bude pricitat).
# define TIMx_CNT 0
#endif
//#=== Makra pro casovace - KONEC
//#=========================================================================

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
 * @brief  Pocatecni inicializace casovace.
 *
 */
void TIM6_setup(void) {
  RCC->TIM6_APB |=  TIM6_RST; // Reset
  RCC->TIM6_APB &= ~TIM6_RST; //  casovace
  RCC->TIM6_APB |=  TIM6_EN;  // Povoleni CLK pro casovac (vsechny periferie potrebuji mit povoleny hodiny pro svuj beh).
}

/**
 * @brief  Dodatecna konfigurace casovace (na zaklade nastavenych maker TIMx_PSC, TIMx_ARR, TIMx_CNT).
 *         Funkce nemusi byt pouzita, pak budou casovace v defaultnim stavu.
 *
 */
void TIM6_config(void) {
  TIM6->PSC = TIMx_PSC;                       // Prescaler - delicka vstupni frekvence (hodinoveho signalu)
                                              // Pro f =  16MHz zakomentovat radek      ; Pretece za 4.1ms
                                              // Pro f =   2MHz zadat:   8              ; Pretece za 32.768ms
                                              // Pro f =   1MHz zadat:   16             ; Pretece za 0.065s
                                              // Pro f = 100kHz zadat:   160            ; Pretece za 0.65s
                                              // Pro f =  10kHz zadat:   1600           ; Pretece za 6.5s

  TIM6->ARR = TIMx_ARR;                       // Auto-reload hodnota, pri ktere se ma citac restartovat. Staci zadat pouze jednou.
                                              // Pro f =  16MHz a TIM6->ARR = 65535 pretece za 4.1ms
                                              // Pro f = 100kHz a TIM6->ARR =  2016 pretece za 20ms
                                              // Pro f = 100kHz a TIM6->ARR = 20165 pretece za 200ms
                                              // Pro f =  10kHz a TIM6->ARR = 65535 pretece za 6.5s
                                              // Pro f =  10kHz a TIM6->ARR = 10000 pretece za 1s

  TIM6->CNT = TIMx_CNT;                       // Prednastavena hodnota od ktere zacne pricitani. Nutno zadat pro kazde citani.*/
}

/**
 * @brief  Casova funkce pro pozdrzeni provadeneho programu.
 *
 */
void TIM6_delay(void) {
  TIM6->SR &= ~(TIM_SR_UIF);                  // Nulovani priznaku preteceni casovace.
                                              // Status bit nutno nastavit na log. 0! ; Pri preteceni nebo dosazeni hodnoty Auto-reload hodnoty nastaven HW do log. 1!

  TIM6->CNT  = TIMx_CNT;                      // Prednastavena hodnota od ktere zacne pricitani.
  TIM6->CR1 |= TIM_CR1_CEN;                   // Spusteni casovace.

	while (!(TIM6->SR & TIM_SR_UIF))  {         // Kontrola, zda doslo k preteceni citace (UIF = Update Interrupt Flag).
    /* __NOP();*/
  }

  TIM6->CR1 &= ~TIM_CR1_CEN;                  // Vypnuti casovace.
}

#ifdef __cplusplus
}
#endif

#endif /* STM32_KIT_TIMERS */
