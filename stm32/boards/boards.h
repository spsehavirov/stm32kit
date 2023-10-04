/**
 *
 *
 */

#ifndef STM32_KIT_BOARDS_AUTODETECT
#define STM32_KIT_BOARDS_AUTODETECT

#include "stm32_kit/platform.h"

#ifndef CUSTOM_BOARD
# if (STM32_TYPE == 407)
#	include "disc/f407.h"
# elif (STM32_TYPE == 401)
#	include "nucleo/f401.h"
# elif (STM32_TYPE == 411)
#	include "nucleo/f411.h"
# elif (STM32_TYPE == 71)
#	include "nucleo/g071.h"
# elif (STM32_TYPE == 152)
# 	include "nucleo/l152.h"
# else
#	error "Board definition not found. Try defining CUSTOM_BOARD!"
# endif
#endif


#endif /* STM32_KIT_BOARDS_AUTODETECT */
