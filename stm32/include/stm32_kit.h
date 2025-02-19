/**
  * @file     stm32_kit.h
  * @brief    Obecny konfiguracni soubor pro pouzivane pripravky.
  *
  * @author   SPŠE Havířov (https://github.com/spsehavirov)
  * @date     2022-04-10
  *
  * @note     Pro zobrazení použítí (připojení LCD, ext. ledky, etc.) pro daný přípravek, běžte do složky boards (../boards)
  *
  *
  *   Otestováno na: F407; F401, G071
  *
  *   Netestováno: F411, L152
  *
  */
#ifndef STM32_KIT
#define STM32_KIT

#include "config.h"
#if USE_RTOS == 1
#include <RTL.h>
#endif

#include "stm32_kit/platform.h"
#include "stm32_kit/chrono.h"
#include "stm32_kit/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  Vrátí string literal s názvem aktuálního přípravku.
 */
INLINE_STM32 char *current_platform(void) {
#if (STM32_TYPE == 71)
  return "G071";
#elif (STM32_TYPE == 407)
  return "F407";
#elif (STM32_TYPE == 152)
  return "L151";
#else
  return "Unknown";
#endif
}

#ifdef __cplusplus
}
#endif

#endif /* STM32_KIT */
