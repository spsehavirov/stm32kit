/**
  * @file     platform.h
  * @brief    Obecná podpora pro desky a některé vybrané definice platforem
  *
  * @author   SPŠE Havířov (https://github.com/spsehavirov)
  * @date     2022-06-30
  *
  * @copyright Copyright SPSE Havirov (c) 2024
  */
#ifndef STM32_KIT_PLATFORM
#define STM32_KIT_PLATFORM

#include <stdint.h>
#include "RTE_Components.h"
#include CMSIS_device_header

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__ARMCC_VERSION)
    #define INLINE_STM32 static inline __attribute__((always_inline, flatten))
    #define CONSTEXPR __attribute__((const))
    #define BOARD_SETUP __attribute__((constructor))
#else
    #define INLINE_STM32 static inline
    #define CONSTEXPR
    #define BOARD_SETUP __attribute__((constructor))
#endif

/**
 * Výběr device headeru pro daný přípravek.
 */
#if !defined(STM32_TYPE) // V připadě, že není vytvořeno makro pro práci s deskou NUCLEO, bude veškeré nastavení provedeno pro školní přípravek
    #if defined(STM32F4)
        #if defined(STM32F401xE)
            // Nastavení makra pro NUCLEO F401
            #define STM32_TYPE (401)
        #elif defined(STM32F407xx)
            // Nastavení makra na školní přípravek (F407)
            #define STM32_TYPE (407)
        #else
            #error "Vybrana deska rady F4 neni podporovana, zvolte manualni definici nebo dopiste driver."
        #endif
    #elif defined(STM32G0)
        #if defined(STM32G070xx)
            // Nastavení makra pro NUCLEO G070
            #define STM32_TYPE (70)
        #elif defined(STM32G071xx)
             // Nastavení makra pro NUCLEO G071
            #define STM32_TYPE (71)
        #else
            #error "Vybrana deska rady G0 neni podporovana, zvolte manualni definici nebo dopiste driver."
        #endif
    #elif defined(STM32L1)
        #if defined(STM32L151xC)
            // Nastavení makra pro NUCLEO L151
            #define STM32_TYPE (151)
        #elif defined(STM32L152xE)
            // Nastavení makra pro NUCLEO L152
            #define STM32_TYPE (152)
        #else
            #error "Vybrana deska rady L1 neni podporovana, zvolte manualni definici nebo dopiste driver."
        #endif
    #else
        #error "Neni vybrana zadna podporovana rada desek, zkontrolujte nastaveni!"
    #endif
#endif


/**
 *  Makra pro zvolení typu clocku pro daný přípravek.
 */
#if (STM32_TYPE == 71)
# define IO_ENABLE IOPENR
#elif (STM32_TYPE == 152)
# define IO_ENABLE AHBENR
#else
# define IO_ENABLE AHB1ENR
#endif

#ifdef __cplusplus
}
#endif

#endif
