/**
 * @file       uart.h
 * @brief      Ovladač pro rozhrani UART (RS-232).
 *
 * @author     SPŠE Havířov (https://github.com/spsehavir
 *
 * @date       2022-10-18
 * @copyright  Copyright SPSE Havirov (c) 2024
 */

#ifndef STM32_KIT_UART
#define STM32_KIT_UART

#include <stdlib.h>

#include "platform.h"
#include "chrono.h"
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "boards.h"
#define UART_TX_PIN    io_pin(UART_TX)
#define UART_TX_PORT   io_port(UART_TX)
#define UART_RX_PIN    io_pin(UART_RX)
#define UART_RX_PORT   io_port(UART_RX)

/**
 * @brief  Nastavení pinu pro TX.
 *
 * @param pin Pin, který se má nastavit.
 */
INLINE_STM32 void UART_TX_Setup(enum pin pin) {
    GPIO_clock_enable(pin);

    MODIFY_REG(io_port(pin)->MODER,   (3UL  << (2 * io_pin(pin))),  (2UL << 2 * io_pin(pin)));  // AF mode
     CLEAR_BIT(io_port(pin)->OTYPER,  (1UL  << (1 * io_pin(pin))));                             // Push-pull
    MODIFY_REG(io_port(pin)->OSPEEDR, (3UL  << (2 * io_pin(pin))),  (3UL << 2 * io_pin(pin)));  // Very high speed
    MODIFY_REG(io_port(pin)->AFR[0],  (15UL << (4 * io_pin(pin))),  (7UL << 4 * io_pin(pin)));  // AF7 - UART
}

/**
 * @brief  Nastavení pinu pro RX.
 *
 * @param pin Pin, který se má nastavit.
 */
INLINE_STM32 void UART_RX_Setup(enum pin pin) {
    GPIO_clock_enable(pin);

    MODIFY_REG(io_port(pin)->MODER,   (3UL << (2 * io_pin(pin))), (2UL << 2 * io_pin(pin)));   // AF mode
    MODIFY_REG(io_port(pin)->AFR[0], (15UL << (4 * io_pin(pin))), (7UL << 4 * io_pin(pin)));   // AF7 - UART
}

/**
 * @brief Vrátí výpočítanou hodnotu pro nastavení baudratu.
 *
 * @param pclk Frekvence hodin pro UART.
 * @param desired_rate Požadovaná rychlost přenosu.
 * @param over8 Přepínač pro 8/16 bitový přenos.
 */
INLINE_STM32 uint32_t UART_baudrate_calculate(int pclk, int desired_rate, int over8) {
    const uint32_t div_sampling = (pclk * 25) / ((2 + 2 * (!!!over8)) * desired_rate);
    const uint32_t mantissa = div_sampling / 100;
    const uint32_t fraction = ((div_sampling - mantissa * 100) * 16 + 50) / 100;

    return (mantissa << 4) | (fraction & 0x0F);
#if UART_EDU
    // if (over8 == 0):
    return (pclk + desired_rate / 2) / desired_rate;
#endif
}

/**
 * @brief  Počáteční inicializace UART.
 */
INLINE_STM32 void UART_setup(void) {
    UART_TX_Setup(UART_TX);
    UART_RX_Setup(UART_RX);

    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    USART2->BRR |= UART_baudrate_calculate(SystemCoreClock, 9600, 0);
    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE; // Enable Tx & Rx
    USART2->CR1 |= USART_CR1_UE; // USART Enable
}

/**
 * @brief  Odeslání znaku přes UART.
 *
 * @param znak Odesílaný znak (číslo, ANSI kód).
 */
INLINE_STM32 void UART_putc(uint8_t znak) {
    USART2->DR = znak;
    while (!(USART2->SR & USART_SR_TXE)) {
        // Počká na dokončení přenosu
    }
}

/**
 * @brief  Příjem znaku přes UART.
 *
 * @return Přijatý znak (číslo, ANSI kód).
 */
INLINE_STM32 uint8_t UART_getc(void) {
    while (!(USART2->SR & USART_SR_RXNE)) {
        // Počká na dokončení přenosu
    }
    return USART2->DR;
}

/**
 * @brief  Odeslání řetězce přes UART.
 *
 * @param buf Ukazatel na řetězec.
 * @param len Délka řetězce.
 *
 * @return Počet odeslaných znaků.
 */
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

/**
 * @brief  Příjem řetězce přes UART.
 *
 * @param buf Ukazatel na buffer, kam se má řetězec uložit.
 * @param len Délka bufferu.
 *
 * @return Počet přijatých znaků.
 */
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
