/**
  * @file       gpio.h
  * @brief      Definice a funkce pro práci s GPIO
  *
  * @author     SPŠE Havířov (https://github.com/spsehavirov)
  * @date       2023-04-10
  *
  * @copyright  Copyright SPSE Havirov (c) 2024
  */

#ifndef STM32_KIT_GPIO
#define STM32_KIT_GPIO

#include "platform.h"
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 *  @brief Definice portů, jejiž piny jsou použity ke configu
 *
 *  Definice portů, jejiž piny jsou použity ke configu. Pokud je definováno
 *
 *  Enumerace je specifikována jako kombinace horní části (port) a dolní části
 *  (pin). Jako takové můžeme maskovat a posunout, abychom získali požadovaný port / pin.
 *  To zjednodušuje konfigurace, protože potřebujeme jen jednu hodnotu, abychom
 *  specifikovali pin i port.
 *
 *  @code
 *      #define BTN_1 (PA0)
 *      io_port(BTN_1)->BSRR = 1UL << io_pin(BTN_1);
 *  @endcode
 */
enum pin {
    // Základní porty
    PA0 = 0x00, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8, PA9, PA10, PA11, PA12, PA13, PA14, PA15,
    PB0 = 0x10, PB1, PB2, PB3, PB4, PB5, PB6, PB7, PB8, PB9, PB10, PB11, PB12, PB13, PB14, PB15,
    PC0 = 0x20, PC1, PC2, PC3, PC4, PC5, PC6, PC7, PC8, PC9, PC10, PC11, PC12, PC13, PC14, PC15,
    PD0 = 0x30, PD1, PD2, PD3, PD4, PD5, PD6, PD7, PD8, PD9, PD10, PD11, PD12, PD13, PD14, PD15,
    PE0 = 0x40, PE1, PE2, PE3, PE4, PE5, PE6, PE7, PE8, PE9, PE10, PE11, PE12, PE13, PE14, PE15,
    PF0 = 0x50, PF1, PF2, PF3, PF4, PF5, PF6, PF7, PF8, PF9, PF10, PF11, PF12, PF13, PF14, PF15,
#ifdef EXTRA_PINS
    // Rozšířené porty, dostupné na některých deskách
    PG0 = 0x60, PG1, PG2, PG3, PG4, PG5, PG6, PG7, PG8, PG9, PG10, PG11, PG12, PG13, PG14, PG15,
    PH0 = 0x70, PH1, PH2, PH3, PH4, PH5, PH6, PH7, PH8, PH9, PH10, PH11, PH12, PH13, PH14, PH15,
    PI0 = 0x80, PI1, PI2, PI3, PI4, PI5, PI6, PI7, PI8, PI9, PI10, PI11, PI12, PI13, PI14, PI15,
    PJ0 = 0x90, PJ1, PJ2, PJ3, PJ4, PJ5, PJ6, PJ7, PJ8, PJ9, PJ10, PJ11, PJ12, PJ13, PJ14, PJ15,
    PK0 = 0xA0, PK1, PK2, PK3, PK4, PK5, PK6, PK7, PK8, PK9, PK10, PK11, PK12, PK13, PK14, PK15,
    PL0 = 0xB0, PL1, PL2, PL3, PL4, PL5, PL6, PL7, PL8, PL9, PL10, PL11, PL12, PL13, PL14, PL15,
    PM0 = 0xC0, PM1, PM2, PM3, PM4, PM5, PM6, PM7, PM8, PM9, PM10, PM11, PM12, PM13, PM14, PM15,
#endif
    P_INVALID = 0xFF,
    NC = 0xFE
};
typedef enum pin pin_t;

/**
 *  @defgroup pin_bsrr 8.4.7 GPIO port bit set/reset register
 *  8.4.7 GPIO port bit set/reset register (GPIOx_BSRR) (x = A..I/J/K)
 *  @{
 */
#define IO_PIN_SET(x)   (0x1UL << ((x)))  ///< SET pin in Bitwise set/reset register.
#define IO_PIN_RESET(x) (0x1UL << ((x) + 16)) ///< RESET pin in Bitwise set/reset register.
#define IO_PIN_BSRR(__PIN__,__BOOL_VALUE__) ((__BOOL_VALUE__)? IO_PIN_SET((__PIN__)):IO_PIN_RESET((__PIN__))) ///< Helper to (RE)SET bit on pin
/** @} */ // end of pin_bsrr

/**
 *  @brief Vrátí index portu
 *
 *  Získá index portu, aby bylo možné povolit hodinový signál pro tento port.
 *
 *  @code
 *      RCC->AHB1ENR |= io_port_source(GPIOA);
 *  @endcode
 *
 *  @param [in] port Port pro zjištění indexu
 */
INLINE_STM32 CONSTEXPR uint32_t io_port_source(GPIO_TypeDef *port) {
    return ((uint32_t)port - (GPIOA_BASE)) / ((GPIOB_BASE) - (GPIOA_BASE));
}

/**
 *  @brief Vrátí index pinu
 *
 *  Získá pozici pinu, relativně k začátku portu.
 *
 *  @param pin Pin enumerace pro zjištění indexu
 */
INLINE_STM32 CONSTEXPR int io_pin(enum pin pin) {
    return pin & (0x0F); // Získá dolní část
}

/**
 *  @brief Vrátí pozici pinu
 *
 *  Hlavní použití této pomocné funkce je nastavení nebo posunutí pozice pinu
 *  v IO konfiguraci a/nebo funkcí read(), write().
 *
 *  @param pin Pin enumerace pro zjištění pozice
 */
INLINE_STM32 CONSTEXPR uint32_t io_pin_pos(enum pin pin) {
    return 1UL << io_pin(pin);
}

/**
 *  @brief Vrátí offset portu
 *
 *  Získá index protu pro specifikovaný pin. Používá se pro výpočet pozic
 *  a umístění ve struktuře.
 *
 *  @param pin Pin enumerace pro zjištění offsetu
 */
INLINE_STM32 CONSTEXPR uint32_t io_port_offset(enum pin pin) {
    return (pin & (0xF0)) >> 4; // Získá horní část
}

/**
 *  @brief Vrátí port pro specifikovaný pin
 *
 *  @param pin Pin enumerace pro zjištění portu
 */
INLINE_STM32 CONSTEXPR GPIO_TypeDef* io_port(enum pin pin) {
    uint32_t port = io_port_offset(pin) - io_port_offset(PA0);
    uint32_t offest = port * ((GPIOB_BASE) - (GPIOA_BASE));
    return (GPIO_TypeDef *) (GPIOA_BASE + offest);
}

/**
 * @brief Nastaví hodnotu pinu na specifikovanou hodnotu
 *
 * Nastaví hodnotu výstupu pinu pomocí registru BSRR
 *
 * @param pin Pin enumerace pro nastavení
 * @param value Hodnota, která má být nastavena (0 nebo 1)
 */
INLINE_STM32 void io_set(enum pin pin, int value) {
    WRITE_REG(io_port(pin)->BSRR, IO_PIN_BSRR(io_pin(pin), value));
}

/**
 * @brief Vrátí výstupní hodnotu pinu
 *
 * Přečte hodnotu pinu z registru ODR
 *
 * @param pin Pin enumerace pro čtení
 */
INLINE_STM32 int io_get(enum pin pin) {
    return READ_BIT(io_port(pin)->ODR, (1UL << io_pin(pin))) >> io_pin(pin);
}

/**
 * @brief Vrátí vsupní hodnotu pinu
 *
 * Přečte hodnotu pinu z registru IDR
 *
 * @param pin Pin enumerace pro čtení
 */
INLINE_STM32 int io_read(enum pin pin) {
    return READ_BIT(io_port(pin)->IDR, (1UL << io_pin(pin))) >> io_pin(pin);
}

/**
 * @brief Neguje hodnotu pinu v zadaném registru
 */
#define TOGGLE_BIT(REG, BIT)    ((REG) ^= (1UL << (BIT)))


/**
 * Makra pro nastavení funkce pinu
 */
#define SET_PIN_MODE(GPIOx, PIN, MODE)    ((GPIOx)->MODER |= ((MODE) << (PIN)))
#define CLR_PIN_MODE(GPIOx, PIN)          ((GPIOx)->MODER &= ~(3UL << (PIN)))

/**
 * Globální proměnné
 */
static uint8_t STM32_port_name[] = {
   'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'
};

/**
 * @brief  Aktivace CLK na portu.
 *
 * @param  pin Pin pro aktivaci hodinového signálu
 *
 */
INLINE_STM32 void GPIO_clock_enable(enum pin pin) {
  const uint32_t source = 1UL << io_port_source(io_port(pin));
  SET_BIT(RCC->IO_ENABLE, source);
}

/**
 * @brief  Deaktivace CLK na portu.
 *
 * @param  pin Pin pro deaktivaci hodinového signálu
 *
 */
INLINE_STM32 void GPIO_clock_disable(enum pin pin) {
  const uint32_t source = 1UL << io_port_source(io_port(pin));
  CLEAR_BIT(RCC->IO_ENABLE, source);
}

#ifdef __cplusplus
}
#endif

#endif /* STM32_KIT_CHRONO */
