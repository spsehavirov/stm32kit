/**
  * @file       adc.h
  * @brief      Konfiguracni soubor pro pouzivane LED diody a tlacitko.
  *
  * @author     Petr Madecki (petr.madecki@spsehavirov.cz)
  * @author     Tomas Michalek (tomas.michalek@spsehavirov.cz)
  *
  * @date       10-April-2022
  * @copyright  Copyright SPSE Havirov (c) 2022
  */
#ifndef STM32_KIT_ADC
#define STM32_KIT_ADC

#include "platform.h" /* Podpora pro desky */
#include "chrono.h"   /* Podpora pro casovani a delay smycky */
#include "gpio.h"     /* Podpora pro zjednodusene pinovani */
#include "pin.h"

#include "boards.h"
#define ADC_1_PIN    io_pin(ADC_1)
#define ADC_1_PORT   io_port(ADC_1)

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
  pin_enable(ADC_1);
  pin_mode(ADC_1, PIN_MODE_ANALOG); // Analog mode
  
  RCC->APB2ENR |= 0x00000100; // Enable ADC clock
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
