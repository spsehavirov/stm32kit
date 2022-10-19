/**
 * @file       uart.h
 * @author     Petr Madecki (petr.madecki@spsehavirov.cz)
 * @author     Tomas Michalek (tomas.michalek@spsehavirov.cz)
 *
 * @date       2022-10-18
 * @copyright  Copyright SPSE Havirov (c) 2022
 */

#ifndef STM32_KIT_UART
#define STM32_KIT_UART

#include "platform.h" // Podpora pro zjednodusene pinouty
#include "chrono.h"
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif
  
#ifndef CUSTOM_KBD
# if (STM32_TYPE == 407)
#   define UART_RX    (PA2)
#   define UART_TX    (PA3)
# else
#   error "Zatim neexistuje podpora pro danou desku!"
# endif
# define UART_RX_PIN      io_pin(UART_RX)
# define UART_RX_PORT     io_port(UART_RX)
# define UART_TX_PIN      io_pin(UART_TX)
# define UART_TX_PORT     io_port(UART_TX)
#endif
  
INLINE_STM32 void UART_setup(void) {
}
  
INLINE_STM32 uint8_t UART_get(void) {
}
  
INLINE_STM32 void UART_put(uin8_t chr) {
}
  
INLINE_STM32 int UART_read(void *buf, size_t len) {
  uint8_t *str = (uint8_t *)buf;
  int alen = 0;
  for (int i = len; i; i--) {
    if (*str == '\0') break;
    
    UART_put(*str);
    str++;
    alen++;
  }
  return alen;
}

INLINE_STM32 int UART_write(void *buf, size_t len) {
  uint8_t *str = (uint8_t *)buf;
  int i = 0;
  for (; i < len; i++) {
    str[i] = UART_get();
  }
  
  return i;
}
  
#ifdef __cplusplus
}
#endif

#endif /* STM32_KIT_UART */
