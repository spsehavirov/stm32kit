/**
  * @file       adc.h
  * @brief      Konfiguračni soubor pro používané LED diody a tlacitko.
  *
  * @author     SPŠE Havířov (https://github.com/spsehavirov)
  * @date       2022-04-25
  *
  * @copyright  Copyright SPSE Havirov (c) 2024
  */

#ifndef STM32_KIT_ADC
#define STM32_KIT_ADC

#include "platform.h"
#include "chrono.h"
#include "gpio.h"
#include "pin.h"

#include "boards.h"
#define ADC_1_PIN    io_pin(ADC_1)
#define ADC_1_PORT   io_port(ADC_1)

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief Inicializace ADC převodníku
 *
 *  Nastaví ADC převodník do analogového módu, aby bylo možné číst hodnoty
 *  z rozsahu <0-4096> (12b mód). ADC je nastaven jako single-shot na kanál 1
 *  s vzorkováním 480 cyklů (pro lepší přesnost).
 *
 */
INLINE_STM32 void ADC_setup(void) {
  __disable_irq();
  pin_enable(ADC_1);
  pin_mode(ADC_1, PIN_MODE_ANALOG); // Analofový mód
  
  RCC->APB2ENR |= 0x00000100; // Nastaví ADC clock
  MODIFY_REG(ADC1->SMPR2, 7UL << (3 * 1), 7UL << (3 * 1)); // Nastaví vzorkování na 111 - 480 cyklů
  
  ADC1->CR2  = 0;
  ADC1->SQR3 = 1; // Kanál 1
  ADC1->CR2  = 1;
  __enable_irq();
}

/**
 *  @brief Přečte hodnotu z ADC převodníku
 *
 *  Udělá jedno měření a vrátí výsledek. Převodník končí, když SOC nastaví
 *  Status Register na EOC (end-of-conversion). Výsledek je uložen v ADC_DR.
 *
 *  @return Hodnota z ADC převodníku
 */
INLINE_STM32 uint16_t ADC_read(void) {
  ADC1->CR2 |= ADC_CR2_SWSTART;

  while (!((ADC1->SR) & ADC_SR_EOC)) {
    // Čeká na dokončení převodu
  }

  return ADC1->DR;
}

#ifdef __cplusplus
}
#endif

#endif /* STM32_KIT_ADC */
