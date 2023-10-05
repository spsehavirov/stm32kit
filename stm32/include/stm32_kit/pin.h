#ifndef STM32_KIT_PIN
#define STM32_KIT_PIN

#include "config.h"   // Nastaveni projektu

#include "platform.h" // Podpora pro zjednodusene pinouty
#include "chrono.h"
#include "gpio.h"

INLINE_STM32 void pin_enable(enum pin pin) {
  SET_BIT(RCC->IO_ENABLE, (1UL << io_port_source(io_port(pin))));
}

INLINE_STM32 void pin_disable(enum pin pin) {
  CLEAR_BIT(RCC->IO_ENABLE, (1UL << io_port_source(io_port(pin))));
}

typedef enum  {
  PIN_MODE_DEFAULT = -1,
  PIN_MODE_INPUT  = 0x0,  // 0b00
  PIN_MODE_OUTPUT = 0x1,  // 0b01
  PIN_MODE_AF     = 0x2,  // 0b10
  PIN_MODE_ANALOG = 0x3,  // 0b11
  PIN_MODE_MASK   = PIN_MODE_ANALOG
} pin_mode_t;

typedef enum {
  PIN_PULL_DEFAULT = -1,
  PIN_PULL_NONE = 0UL, // 0b00
  PIN_PULL_UP   = 1UL, // 0b01
  PIN_PULL_DOWN = 2UL, // 0b10
  PIN_PULL_MASK = 3UL  // 0b11 - RESERVED: DO NOT USE!
} pin_pull_t;

typedef enum {
  PIN_SPEED_DEFAULT   = -1,
  PIN_SPEED_LOW       = 0UL, // 0b00
  PIN_SPEED_MID       = 1UL, // 0b01
  PIN_SPEED_HIGH      = 2UL, // 0b10
  PIN_SPEED_VERYHIGH  = 3UL, // 0b11
  PIN_SPEED_MASK      = PIN_SPEED_VERYHIGH
} pin_speed_t;

typedef enum {
  PIN_TYPE_DEFAULT   = -1,
  PIN_TYPE_PUSHPULL  = 0UL, // 0b0
  PIN_TYPE_OPENDRAIN = 1UL, // 0b1
  PIN_TYPE_MASK      = PIN_TYPE_OPENDRAIN
} pin_type_t;


typedef enum {
  PIN_AF_NONE = -1,
  PIN_AF0     =  0UL, // 0b0000
  PIN_AF1     =  1UL, // 0b0001
  PIN_AF2     =  2UL, // 0b0010
  PIN_AF3     =  3UL, // 0b0011
  PIN_AF4     =  4UL, // 0b0100
  PIN_AF5     =  5UL, // 0b0101
  PIN_AF6     =  6UL, // 0b0110
  PIN_AF7     =  7UL, // 0b0111
  PIN_AF8     =  8UL, // 0b1000
  PIN_AF9     =  9UL, // 0b1001
  PIN_AF10    = 10UL, // 0b1010
  PIN_AF11    = 11UL, // 0b1011
  PIN_AF12    = 12UL, // 0b1100
  PIN_AF13    = 13UL, // 0b1101
  PIN_AF14    = 14UL, // 0b1110
  PIN_AF15    = 15UL, // 0b1111
  PIN_AF_MASK = 15UL
} pin_af_t;

INLINE_STM32 void pin_mode(enum pin pin, pin_mode_t mode) {
  if (PIN_MODE_DEFAULT == mode) return;
  MODIFY_REG(io_port(pin)->MODER, (PIN_MODE_MASK << (2 * io_pin(pin))), (mode << 2 * io_pin(pin)));
}

INLINE_STM32 void pin_pull(enum pin pin, pin_pull_t pull) {
  if (PIN_PULL_DEFAULT == pull) return;
  MODIFY_REG(io_port(pin)->PUPDR, (PIN_PULL_MASK << (2 * io_pin(pin))), (pull << 2 * io_pin(pin)));
}

INLINE_STM32 void pin_output_speed(enum pin pin, pin_speed_t speed) {
  if (PIN_SPEED_DEFAULT == speed) return;
  MODIFY_REG(io_port(pin)->OSPEEDR, (PIN_SPEED_MASK << (2 * io_pin(pin))), (speed << 2 * io_pin(pin)));
}

INLINE_STM32 void pin_output_type(enum pin pin, pin_type_t type) {
  if (PIN_TYPE_DEFAULT == type) return;
  MODIFY_REG(io_port(pin)->OTYPER, (PIN_TYPE_MASK << (io_pin(pin))), (type << io_pin(pin)));
}

INLINE_STM32 void pin_af(enum pin pin, pin_af_t func) {
  if (PIN_AF_NONE == func) return;
  
  const int bank = io_pin(pin) > 7;
  const int offset_pin =  io_pin(pin) & ~(1 << 3);
  MODIFY_REG(io_port(pin)->AFR[bank],  (PIN_AF_MASK << (4 * offset_pin)),  (func << 4 * offset_pin));  // AF7 - UART
}

INLINE_STM32 void pin_setup(enum pin pin, pin_mode_t mode, pin_pull_t pull, pin_speed_t speed, pin_type_t type) {
  pin_enable(pin);
  pin_mode(pin, mode);
  pin_pull(pin, pull);
  pin_output_speed(pin, speed);
  pin_output_type(pin, type);
}

INLINE_STM32 void pin_setup_af(enum pin pin, pin_mode_t mode, pin_pull_t pull, pin_speed_t speed, pin_type_t type, pin_af_t func) {
  pin_setup(pin, mode, pull, speed, type);
  pin_af(pin, func);
}
  
#endif /* STM32_KIT_GPIO_SETUP */
