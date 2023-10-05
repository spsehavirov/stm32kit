/**
 * @file       uart.h
 * @brief      Ovladac pro rozhrani UART (RS-232).
 *
 * @author     Petr Madecki (petr.madecki@spsehavirov.cz)
 * @author     Tomas Michalek (tomas.michalek@spsehavirov.cz)
 *
 * @date       2022-10-18
 * @copyright  Copyright SPSE Havirov (c) 2022
 */

#ifndef STM32_KIT_UART
#define STM32_KIT_UART

#include <stdlib.h> // Podpora pro size_t

#include "platform.h" // Podpora pro zjednodusene pinouty
#include "chrono.h"
#include "gpio.h"
#include "pin.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"   // Nastaveni projektu
#include "boards.h"

INLINE_STM32 void UART_TX_Setup(enum pin pin) {
    pin_enable(pin);
    pin_setup_af(pin, PIN_MODE_AF, PIN_PULL_DEFAULT, PIN_SPEED_VERYHIGH, PIN_TYPE_PUSHPULL, PIN_AF7); // AF7 - UART
}

INLINE_STM32 void UART_RX_Setup(enum pin pin) {
    pin_enable(pin);
    pin_mode(pin, PIN_MODE_AF);
    pin_af(pin, PIN_AF7); // AF7 - UART
}

CONSTEXPR uint32_t UART_baudrate_calculate(int pclk, int desired_rate, int over8) {
    const uint32_t div_sampling = (pclk * 25) / ((2 + 2 * (!!!over8)) * desired_rate);
    const uint32_t mantissa = div_sampling / 100;
    const uint32_t fraction = ((div_sampling - mantissa * 100) * 16 + 50) / 100;

    return (mantissa << 4) | (fraction & 0x0F);
#if UART_EDU
    // if (over8 == 0):
    return (pclk + desired_rate / 2) / desired_rate;
#endif
}

INLINE_STM32 void UART_setup(void) {
    UART_TX_Setup(UART_TX);
    UART_RX_Setup(UART_RX);

    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    USART2->BRR |= UART_baudrate_calculate(SystemCoreClock, UART_BAUDRATE, 0);
    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE; // Enable Tx & Rx
    USART2->CR1 |= USART_CR1_UE; // USART Enable
}


INLINE_STM32 void UART_putc(uint8_t znak) {
    USART2->DR = znak;
    while (!(USART2->SR & USART_SR_TXE)) {
        // Wait for transmision to complete
    }
}

INLINE_STM32 uint8_t UART_getc(void) {
    while (!(USART2->SR & USART_SR_RXNE)) {
        // Wait for transmision to complete
    }
    return USART2->DR;
}

INLINE_STM32 size_t UART_write(const void *__restrict buf, size_t len) {
    uint8_t *str = (uint8_t *)buf;
    int count = 0;
    for (int i = len; i; --i) {
        UART_putc(*str);
        str++;
        count++;
    }
    return count;
}

INLINE_STM32 int UART_read(void *__restrict buf, size_t len) {
    uint8_t *str = (uint8_t *)buf;
    int alen = 0;
    uint8_t chr;
    for (int i = len; i; i--) {
        chr = UART_getc();
        *str = chr;
        if (*str == '\0') break;
        if (*str == '\r') break;
        str++;
        alen++;
    }
	*str = '\0';
    return alen;
}

#ifdef __cplusplus
}
#endif

#endif /* STM32_KIT_UART */
