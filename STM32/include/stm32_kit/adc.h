/**
  *********************************************************************************
  * @file     adc.h
  * @author   SPSE Havirov
  * @version  1.5.8
  * @date     10-April-2022
  * @brief    Konfiguracni soubor pro pouzivane LED diody a tlacitko.
  *
  *           Podporovane desky:
  *             STM32F4-DISCOVERY (STM32F407VGTx)   -   skolni pripravek
  *               Kod pro makro STM32_TYPE:
  *                                               407
  *               CLK:
  *                                               16MHz		HSI
  *               ADC1 pin                        PA1
  *
  *
  *********************************************************************************
  * @attention
  *
  *   Otestovano na: F407
  *
  *   Netestovano: F411, L152, F401, G071
  *
  **********************************************************************************
  */
#ifndef STM32_KIT_ADC
#define STM32_KIT_ADC

#include "platform.h" /* Podpora pro desky */
#include "chrono.h"   /* Podpora pro casovani a delay smycky */
#include "gpio.h"     /* Podpora pro zjednodusene pinovani */

#ifndef CUSTOM_ADC
# if ((STM32_TYPE == 71) || (STM32_TYPE == 152) || (STM32_TYPE == 401) || (STM32_TYPE == 411))
#   define ADC      (PA1)  // ADC on F401, F411, G071, L152
# else
#   define ADC      (PA1)  // ADC on F407
# endif
# define ADC_PIN    io_pin(ADC)
# define ADC_PORT   io_port(ADC)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief Initialize Analog-To-Digital converter to single shot mode
 *
 *  Setup the ADC1 to work with ADC pin in analog mode in order to read
 *  values from <0-4096> (12b mode). ADC is setup as single-shot on channel 1
 *  with sampling set to 480 cycles (better accuracy).
 *
 *  @returns None
 */
void ADC_setup(void) {
  __disable_irq();
  GPIO_clock_enable(ADC);
  RCC->APB2ENR |= 0x00000100; // Enable ADC clock
  MODIFY_REG(ADC_PORT->MODER, 3UL << (2 * ADC_PIN), 3UL << (2 * ADC_PIN)); // Analog mode
  
  MODIFY_REG(ADC1->SMPR2, 7UL << (3 * 1), 7UL << (3 * 1)); // Set sampling to 111 - 480 cycles
  ADC1->CR2  = 0;
  ADC1->SQR3 = 1; // Convert on channel 1
  ADC1->CR2  = 1;
  __enable_irq();
}
  
/**
 *  @brief Read single value from ADC
 *
 *  Do single pass on AD conversion and return the result. The conversion
 *. ends when the SOC sets Status Register to EOC (end-of-conversion).
 *
 *  @return Read value from ADC
 */
uint16_t ADC_read(void) {
  ADC1->CR2 |= ADC_CR2_SWSTART;
  
  while (!((ADC1->SR) & ADC_SR_EOC)) {
    /* Busy-wait for the conversion to happen */
  }
  
  return ADC1->DR;
}

#ifdef __cplusplus
}
#endif

#endif /* STM32_KIT_ADC */
