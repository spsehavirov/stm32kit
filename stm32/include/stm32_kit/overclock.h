#ifndef STM32_KIT_OVERCLOCK
#define STM32_KIT_OVERCLOCK

#include "stm32_kit.h"
#define HSE_VALUE = 8000000

void clock168Mhz(){
	
	// zapnuti ext osc.
	RCC->CR |= RCC_CR_HSEON;
	// cekani na nej
	while(!(RCC->CR & RCC_CR_HSERDY));
	
	// zapnuti clocku na power interface
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	// power scale 1 (> 144Mhz)
	PWR->CR |= PWR_CR_VOS;
	
	// ahb prescaler 1
	RCC->CFGR &= ~RCC_CFGR_HPRE;
	// apb low prescaler 4
	RCC->CFGR |= RCC_CFGR_PPRE1_2 | RCC_CFGR_PPRE1_0;
	// apb high prescaler 2
	RCC->CFGR |= RCC_CFGR_PPRE2_2;

  // nastaveni parametru pll
	RCC->PLLCFGR =  8 										// PLLM = 8
								| (336 << 6)						// PLLN = 336
								| (((2 >> 1) -1) << 16)	// PLLP = 2
								| (7 << 24)							// PLLQ = 7
								| RCC_PLLCFGR_PLLSRC_HSE;
	
	// zapnuti pll
	RCC->CR |= RCC_CR_PLLON;
	// cekani na nej
	while(!(RCC->CR & RCC_CR_PLLRDY));

  // nastaveni parametru flash radice
	FLASH->ACR =  FLASH_ACR_PRFTEN
							| FLASH_ACR_ICEN
							| FLASH_ACR_DCEN
							| 5;							// 5 wait states
	
	// nastaveni pll jako zdroje clocku
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	// cekani na nej
	while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));
	
	SystemCoreClockUpdate();
}

#endif
