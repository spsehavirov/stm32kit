/**
 ***************************************************************************
 * @file     chrono.h
 * @author   SPSE Havirov
 * @version  1.1.1
 * @date     10-April-2022
 * @brief    Definice a funkce pro praci s casem
 *
 ***************************************************************************
 * @attention
 *
 * Otestovano na: F407; F401, G071
 * Netestovano: F411, L152
 *
 *   SysTick konfigurace:
 *       Do vlastniho projektu vlozit nasledujici 2 radky:
 *         SystemCoreClockUpdate();                                // Do SystemCoreClock se nahraje frekvence jadra
 *         SysTick_Config(SystemCoreClock / <hodnota viz nize>);   // Konfigurace SysTick timeru viz hlavni popisek vyse
 *
 *       Do promenne "SystemCoreClock" je po restartu nahrana hodnota 16 0000 0000,
 *         coz odpovida 16MHz (vychozi takt po resetu/zapnuti pro: F407, F401, F411, L152, G071).
 *
 *       SysTick Timer je dekrementujici casovac.
 *
 *       SysTick_Config(SystemCoreClock);          // Konfigurace SysTick timeru na periodu 1s
 *         delay_ms(1);                            // 10s
 *         delay_ms(10);                           // 100s
 *         delay_us(1);                            // 1s
 *         delay_us(10);                           // 10s
 *
 *       SysTick_Config(SystemCoreClock / 10);     // Konfigurace SysTick timeru na periodu 0.1s (100ms)
 *         delay_ms(1);                            // 1s     (1000ms)
 *         delay_ms(10);                           // 10s
 *         delay_us(1);                            // 0.1s   (100ms)
 *         delay_us(10);                           // 1s     (1000ms)
 *
 *       SysTick_Config(SystemCoreClock / 100);    // Konfigurace SysTick timeru na periodu 0.01s (10ms)
 *         delay_ms(1);                            // 0.1s   (100ms)
 *         delay_ms(10);                           // 1s     (1000ms)
 *         delay_us(1);                            // 0.01s  (10ms)
 *         delay_us(10);                           // 0.1s   (100ms)
 *
 *       SysTick_Config(SystemCoreClock / 1000);   // Konfigurace SysTick timeru na periodu 1ms
 *         delay_ms(1);                            // 10ms
 *         delay_ms(10);                           // 0.1s   (100ms)
 *         delay_us(1);                            // 1ms    (1000us)
 *         delay_us(10);                           // 10ms
 *
 *       SysTick_Config(SystemCoreClock / 10000);  // Konfigurace SysTick timeru na periodu 0.1ms (100us)
 *         delay_ms(1);                            // 1ms    (1000us)
 *         delay_ms(10);                           // 10ms
 *         delay_us(1);                            // 0.1ms  (100us)
 *         delay_us(10);                           // 1ms    (1000us)
 *
 ***************************************************************************
 */
#ifndef STM32_KIT_CHRONO
#define STM32_KIT_CHRONO

#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif


//#=========================================================================
//#=== Casove funkce - ZACATEK

#if !defined(RTE_CMSIS_RTOS2) && !defined(__RL_ARM_VER)
static volatile uint32_t Ticks; // Vyuzito pro SysTick k nacitani Ticku pri podteceni.

/**
 * @brief  Rutina pro obsluhu preruseni SysTick.
 */
void SysTick_Handler(void) { Ticks++; }

/**
 * @brief Funkce pro umele pozdrzeni programu.
 *
 * @param[in] value Hodnota v rozmezi 0 - 65535.
 */
INLINE_STM32 void delay(uint16_t value) {
  uint16_t i, j;

  for (i = 0; i < value; i++) {
    for (j = 0; j < value; j++) {
      /* __NOP(); */
    }
  }
}

/**
 * @brief  Funkce pro pozdrzeni programu s vyuzitim SysTick Timeru.
 *         Zalezi na nastaveni SysTick_Config(), viz hl. komentar.
 *
 * @param  ms Hodnota odpovidajici poctu milisekund.
 */
INLINE_STM32 void delay_ms(uint32_t ms) {
  uint32_t start = Ticks;

  // Defaultni nastaveni podteceni SysTick Timeru
  // je 0.1ms -> SysTick_Config(SystemCoreClock / 10000)
  // <- pro spravny prepocet na ms nutno nasobit 10
  ms *= 10;

  while ((Ticks - start) < ms) {
    /* cekani na ubehnuti casu */
  }
}

/**
 * @brief  Funkce pro pozdrzeni programu s vyuzitim SysTick Timeru.
 *         Zalezi na nastaveni SysTick_Config().
 *
 * @param  us Hodnota odpovidajici poctu mikrosekund.
 */
INLINE_STM32 void delay_us(uint32_t us) {
  uint32_t start = Ticks;
  while ((Ticks - start) < us) {
    /* cekani na ubehnuti casu */
  }
}
#elif defined(__RL_ARM_VER)
INLINE_STM32 void delay(uint16_t value) {
    os_dly_wait((uint32_t)value);
}

INLINE_STM32 void delay_us(uint32_t us) {
    os_dly_wait(us);
}

INLINE_STM32 void delay_ms(uint32_t ms) {
    delay_us(10U * ms);
}
#else
#   ifndef CMSIS_OS2_H_
#       include "cmsis_os2.h"
#   endif

/** Jednoduchá abstrakce pro RTOS2
 *
 */
INLINE_STM32 void delay(uint16_t value) {
    osDelay((uint32_t)value);
}

CONSTEXPR INLINE_STM32 uint32_t delay_kernel_freq(void) {
    return osKernelGetTickFreq() / 100000U + 1;
}

INLINE_STM32 void delay_us(uint32_t us) {
    const uint32_t normalized_ticks_for_us = us * delay_kernel_freq();
    uint32_t wait_until = osKernelGetTickCount() + normalized_ticks_for_us;
    osDelayUntil(wait_until);
}

INLINE_STM32 void delay_ms(uint32_t ms) {
    delay_us(10U * ms);
}
#endif
//#=== Casove funkce - KONEC
//#=========================================================================

#ifdef __cplusplus
}
#endif

#endif /* STM32_KIT_CHRONO */
