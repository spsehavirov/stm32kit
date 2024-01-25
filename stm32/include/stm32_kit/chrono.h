/**
  * @file     chrono.h
  * @brief    Definice a funkce pro práci s časem.
  *
  * @author   SPŠE Havířov (https://github.com/spsehavirov)
  * @date     2022-04-10
  *
  * Otestováno na: F407; F401, G071
  *
  * Netestováno: F411, L152
  *
  *   SysTick konfigurace:
  *       Do vlastního projektu vložte následující 2 řádky:
  * @code
  *             SystemCoreClockUpdate();                                // Do SystemCoreClock se nahraje frekvence jadra
  *             SysTick_Config(SystemCoreClock / <hodnota viz nize>);   // Konfigurace SysTick timeru viz hlavni popisek vyse
  * @endcode
  *       Do proměnne "SystemCoreClock" je po restartu nahrána hodnota 16 0000 0000,
  *         což odpovídá 16MHz (výchozí takt po resetu/zapnutí pro: F407, F401, F411, L152, G071).
  *
  *       SysTick Timer je dekrementující časovač.
  *
  *       Příklady použití:
  * @code
  *             SysTick_Config(SystemCoreClock);          // Konfigurace SysTick timeru na periodu 1s
  *               delay_ms(1);                            // 10s
  *               delay_ms(10);                           // 100s
  *               delay_us(1);                            // 1s
  *               delay_us(10);                           // 10s
  *
  *             SysTick_Config(SystemCoreClock / 10);     // Konfigurace SysTick timeru na periodu 0.1s (100ms)
  *               delay_ms(1);                            // 1s     (1000ms)
  *               delay_ms(10);                           // 10s
  *               delay_us(1);                            // 0.1s   (100ms)
  *               delay_us(10);                           // 1s     (1000ms)
  *
  *             SysTick_Config(SystemCoreClock / 100);    // Konfigurace SysTick timeru na periodu 0.01s (10ms)
  *               delay_ms(1);                            // 0.1s   (100ms)
  *               delay_ms(10);                           // 1s     (1000ms)
  *               delay_us(1);                            // 0.01s  (10ms)
  *               delay_us(10);                           // 0.1s   (100ms)
  *
  *             SysTick_Config(SystemCoreClock / 1000);   // Konfigurace SysTick timeru na periodu 1ms
  *               delay_ms(1);                            // 10ms
  *               delay_ms(10);                           // 0.1s   (100ms)
  *               delay_us(1);                            // 1ms    (1000us)
  *               delay_us(10);                           // 10ms
  *
  *             SysTick_Config(SystemCoreClock / 10000);  // Konfigurace SysTick timeru na periodu 0.1ms (100us)
  *               delay_ms(1);                            // 1ms    (1000us)
  *               delay_ms(10);                           // 10ms
  *               delay_us(1);                            // 0.1ms  (100us)
  *               delay_us(10);                           // 1ms    (1000us)
  * @endcode
  *
  */
#ifndef STM32_KIT_CHRONO
#define STM32_KIT_CHRONO

#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(RTE_CMSIS_RTOS2) && !defined(__RL_ARM_VER)

static volatile uint32_t Ticks; // Využito pro SysTick k načátání Ticku při podtečení.

/**
 * @brief  Rutina pro obsluhu přerušení SysTick.
 */
INLINE_STM32 void SysTick_Handler(void) { Ticks++; }

/**
 * @brief Funkce pro umělé pozdržení programu.
 *
 * @param value Hodnota v rozmezi 0 - 65535.
 */
INLINE_STM32 void delay(uint16_t value) {
  uint16_t i, j;

  for (i = 0; i < value; i++) {
    for (j = 0; j < value; j++) {
      // TODO: __NOP();
    }
  }
}

/**
 * @brief  Funkce pro pozdržení programu s využitím SysTick Timeru.
 * @param  ms Hodnota odpovidající počtu milisekund.
 *
 * @note   Záleži na nastavení SysTick_Config(), viz hl. komentář.
 */
INLINE_STM32 void delay_ms(uint32_t ms) {
  uint32_t start = Ticks;

  // Defaultni nastavení podtečení SysTick Timeru
  // je 0.1ms -> SysTick_Config(SystemCoreClock / 10000)
  // <- pro správny přepočet na ms, nutno násobit 10
  ms *= 10;

  while ((Ticks - start) < ms) {
    // čekání na uběhnutí času
  }
}

/**
 * @brief  Funkce pro pozdržení programu s využitím SysTick Timeru.
 *
 * @param  us Hodnota odpovidající počtu mikrosekund.
 * @note   Záleži na nastavení SysTick_Config(), viz hl. komentář.
 *
 */
INLINE_STM32 void delay_us(uint32_t us) {
  uint32_t start = Ticks;
  while ((Ticks - start) < us) {
      // čekání na uběhnutí času
  }
}
#elif defined(__RL_ARM_VER)

/**
 * Pro RL-ARM je nutné vytvořit vlastní funkce pro čekání.
 */

/**
 * @brief  Funkce pro pozdržení programu s využitím RTL
 * @param  value Hodnota odpovidající počtu mikrosekund
 *
 */
INLINE_STM32 void delay(uint16_t value) {
    os_dly_wait((uint32_t)value);
}

/**
 * @brief  Funkce pro pozdržení programu s využitím RTL
 * @param  us Hodnota odpovidající počtu mikrosekund
 *
 */
INLINE_STM32 void delay_us(uint32_t us) {
    os_dly_wait(us);
}

/**
 * @brief  Funkce pro pozdržení programu s využitím RTL
 * @param  ms Hodnota odpovidající počtu milisekund
 *
 */
INLINE_STM32 void delay_ms(uint32_t ms) {
    delay_us(10U * ms);
}

#else
    #ifndef CMSIS_OS2_H_
        #include "cmsis_os2.h"
    #endif

/**
 * Jednoduchá abstrakce pro RTOS2
 */

/**
 * @brief  Funkce pro pozdržení programu s využitím CMSIS RTOS2
 * @param  value Hodnota odpovidající počtu
 *
 */
INLINE_STM32 void delay(uint16_t value) {
    osDelay((uint32_t)value);
}

/**
 *  TODO: Dokumentace
 */
CONSTEXPR INLINE_STM32 uint32_t delay_kernel_freq(void) {
    return osKernelGetTickFreq() / 100000U + 1;
}

/**
 * @brief  Funkce pro pozdržení programu s využitím CMSIS RTOS2
 * @param  us Hodnota odpovidající počtu mikrosekund
 *
 */
INLINE_STM32 void delay_us(uint32_t us) {
    const uint32_t normalized_ticks_for_us = us * delay_kernel_freq();
    uint32_t wait_until = osKernelGetTickCount() + normalized_ticks_for_us;
    osDelayUntil(wait_until);
}

/**
 * @brief  Funkce pro pozdržení programu s využitím CMSIS RTOS2
 * @param  ms Hodnota odpovidající počtu milisekund
 *
 */
INLINE_STM32 void delay_ms(uint32_t ms) {
    delay_us(10U * ms);
}
#endif

#ifdef __cplusplus
}
#endif

#endif /* STM32_KIT_CHRONO */
