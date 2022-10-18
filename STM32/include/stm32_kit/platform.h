/**
 * @file platform.h
 * @author SPSE Havirov
 * @author Petr Madecki (petr.madecki@spsehavirov.cz)
 * @author Tomas Michalek (tomas.michalek@spsehavirov.cz)
 *
 * @brief Obecna podpora pro desky a nektere vybrane definice platforem
 *
 * @version 1.5.8
 * @date 2022-06-30
 *
 * @copyright Copyright SPSE Havirov (c) 2022
 ***********************************************************************************************************************
 * @history
 *
 *   v1.5.8  [30-June-2022]
 *         - Vytvoreni solo hlavickoveho souboru pro praci s I/O
 *         - pridani auto-detekce compiler-u pro vetsi granularitu nastaveni
 *         - umozneni pouzivani pinoutu pomoci `enum pin`
 *
 ***********************************************************************************************************************
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
#   define INLINE_STM32 static inline __attribute__((always_inline, flatten))
#   define CONSTEXPR __attribute__((const))
#   define BOARD_SETUP __attribute__((constructor))
#else
#   define INLINE_STM32 static inline
#   define CONSTEXPR
#   define BOARD_SETUP __attribute__((constructor))
#endif

//#============================================================================================================================================
//#=== Vyber "device header" pro pouzity pripravek - ZACATEK
#if !defined(STM32_TYPE)                           // V pripade ze neni vytvoreno makro pro praci s deskou NUCLEO, bude veskere nastaveni provedeno pro skolni pripravek
#		if defined(STM32F4)
#			if defined(STM32F401xE)
#				define STM32_TYPE (401)           // Nastaveni makra pro NUCLEO F401
#			elif defined(STM32F407xx)
#				define STM32_TYPE (407)           // Nastaveni makra na skolni pripravek (F407)
#			else
#				error "Vybrana deska rady F4 neni podporovana, zvolte manualni definici nebo dopiste driver."
#			endif
#		elif defined(STM32G0)
#			if defined(STM32G070xx)
#				define STM32_TYPE (70)            // Nastaveni makra pro NUCLEO G070
#			elif defined(STM32G071xx)
#				define STM32_TYPE (71)            // Nastaveni makra pro NUCLEO G071
#			else
#				error "Vybrana deska rady G0 neni podporovana, zvolte manualni definici nebo dopiste driver."
#			endif
#		elif defined(STM32L1)
#			if defined(STM32L151xC)
#				define STM32_TYPE (151)           // Nastaveni makra pro NUCLEO L151
#			elif defined(STM32L152xE)
#				define STM32_TYPE (152)           // Nastaveni makra pro NUCLEO L152
#			else
#				error "Vybrana deska rady L1 neni podporovana, zvolte manualni definici nebo dopiste driver."
#			endif
#		else
#			error "Neni vybrana zadna podporovana rada desek, zkontrolujte nastaveni!"
#		endif
#endif
//#=== Vyber "device header" pro pouzity pripravek - KONEC
//#============================================================================================================================================

//#============================================================================
//#=== Makra pro zvoleni typu clocku pripravku - ZACATEK
#if (STM32_TYPE == 71)
# define IO_ENABLE IOPENR
#elif (STM32_TYPE == 152)
# define IO_ENABLE AHBENR
#else
# define IO_ENABLE AHB1ENR
#endif
//#=== Makra pro zvoleni typu clocku pripravku- KONEC
//#============================================================================

#ifdef __cplusplus
}
#endif

#endif
