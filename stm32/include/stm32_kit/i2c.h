/**
 * @file       i2c.h
 * @brief      Minimal I2C driver using only CMSIS
 */
#ifndef STM32_KIT_I2C
#define STM32_KIT_I2C

#include "platform.h"
#include "gpio.h"
#include "pin.h"
#include "boards.h"

typedef struct {
    uint32_t speed;
    uint16_t own_address;
    uint16_t own_address2;
    uint8_t master;
    uint8_t addr10;
    uint8_t dual;
    uint8_t general_call;
    uint8_t duty;
    uint8_t nostretch;
    uint8_t pinpack;
} I2C_Config;

static inline void I2C_load_config(I2C_TypeDef *i2c, I2C_Config *cfg) {
    cfg->speed = I2C_SPEED;
    cfg->own_address = 0;
    cfg->own_address2 = 0;
    cfg->master = 1;
    cfg->addr10 = 0;
    cfg->dual = 0;
    cfg->general_call = 0;
    cfg->duty = 0;
    cfg->nostretch = 0;
    cfg->pinpack = 0;

#define I2C_OPT(bus, name) I2C##bus##_##name
#define I2C_LOAD(bus)                            \
    do {                                        \
        cfg->speed       = I2C_OPT(bus, SPEED);  \
        cfg->master      = I2C_OPT(bus, MASTER); \
        cfg->addr10      = I2C_OPT(bus, ADDR10); \
        cfg->dual        = I2C_OPT(bus, DUAL);   \
        cfg->general_call= I2C_OPT(bus, GEN_CALL);\
        cfg->duty        = I2C_OPT(bus, DUTY);   \
        cfg->nostretch   = I2C_OPT(bus, NOSTRETCH);\
        cfg->own_address = I2C_OPT(bus, OWN_ADDRESS);\
        cfg->own_address2= I2C_OPT(bus, SECOND_ADDRESS);\
        cfg->pinpack     = I2C_OPT(bus, PINPACK);\
    } while (0)

    if (i2c == I2C1) {
        I2C_LOAD(1);
    } else if (i2c == I2C2) {
        I2C_LOAD(2);
    } else if (i2c == I2C3) {
        I2C_LOAD(3);
    }

#undef I2C_LOAD
#undef I2C_OPT
}

#ifdef __cplusplus
extern "C" {
#endif

/* Default speed for I2C bus */
#ifndef I2C_SPEED
# define I2C_SPEED 100000U
#endif

/** Wait for selected flag in SR1 register */
static inline void I2C_wait_flag(I2C_TypeDef *i2c, uint32_t flag) {
    while (!(i2c->SR1 & flag)) {
        /* busy wait */
    }
}

/*----------------------------------------------------------------------------*/
/* Peripheral selection based on pins                                         */
/*----------------------------------------------------------------------------*/
static inline I2C_TypeDef *I2C_autoselect(enum pin scl, enum pin sda) {
#if (STM32_TYPE == 407)
    if ((scl == PB6 && sda == PB7) || (scl == PB8 && sda == PB9))
        return I2C1;
    if ((scl == PB10 && sda == PB11) || (scl == PF1 && sda == PF0) ||
        (scl == PH4 && sda == PH5))
        return I2C2;
    if ((scl == PA8 && sda == PC9) || (scl == PH7 && sda == PH8))
        return I2C3;
    return 0;
#elif (STM32_TYPE == 401)
    if ((scl == PB6 && sda == PB7) || (scl == PB8 && sda == PB9))
        return I2C1;
    return 0;
#elif (STM32_TYPE == 71)
    if (scl == PB8 && sda == PB9)
        return I2C1;
    return 0;
#else
# error "I2C_autoselect not implemented for this MCU"
#endif
}

static inline void I2C_pinpack_pins(I2C_TypeDef *i2c, uint8_t pack, enum pin *scl, enum pin *sda) {
#if (STM32_TYPE == 407)
    if (i2c == I2C1) {
        *scl = (pack ? I2C1_SCL_PP1 : I2C1_SCL_PP0);
        *sda = (pack ? I2C1_SDA_PP1 : I2C1_SDA_PP0);
    } else if (i2c == I2C2) {
        switch (pack) {
        case 1: *scl = I2C2_SCL_PP1; *sda = I2C2_SDA_PP1; break;
        case 2: *scl = I2C2_SCL_PP2; *sda = I2C2_SDA_PP2; break;
        default: *scl = I2C2_SCL_PP0; *sda = I2C2_SDA_PP0; break;
        }
    } else if (i2c == I2C3) {
        *scl = (pack ? I2C3_SCL_PP1 : I2C3_SCL_PP0);
        *sda = (pack ? I2C3_SDA_PP1 : I2C3_SDA_PP0);
    } else {
        *scl = NC; *sda = NC;
    }
#else
#error "I2C pin packs not defined for this MCU"
#endif
}

/*----------------------------------------------------------------------------*/
/* Clock configuration                                                         */
/*----------------------------------------------------------------------------*/
static inline void I2C_clock(I2C_TypeDef *i2c, uint32_t pclk, const I2C_Config *c) {
    uint32_t freq = pclk / 1000000U;
    uint32_t speed = c->speed;
    i2c->CR2 = freq;
    if (speed > 100000U) {
        uint32_t ccr;
        if (c->duty) {
            ccr = pclk / (speed * 25U);
            i2c->CCR = ccr | I2C_CCR_FS | I2C_CCR_DUTY;
        } else {
            ccr = pclk / (speed * 3U);
            i2c->CCR = ccr | I2C_CCR_FS;
        }
        i2c->TRISE = (freq * 300U) / 1000U + 1U;
    } else {
        uint32_t ccr = pclk / (speed << 1);
        if (ccr < 4U) ccr = 4U;
        i2c->CCR = ccr;
        i2c->TRISE = freq + 1U;
    }
}

/*----------------------------------------------------------------------------*/
/* Basic setup                                                                 */
/*----------------------------------------------------------------------------*/
static inline I2C_TypeDef *I2C_setup(I2C_TypeDef *i2c) {
    enum pin scl, sda;
    I2C_Config c;
    I2C_load_config(i2c, &c);
#if (STM32_TYPE == 407)
    if (i2c == I2C1 && !I2C1_ENABLE) return 0;
    if (i2c == I2C2 && !I2C2_ENABLE) return 0;
    if (i2c == I2C3 && !I2C3_ENABLE) return 0;
#elif (STM32_TYPE == 401)
    if (i2c == I2C1 && !I2C1_ENABLE) return 0;
#elif (STM32_TYPE == 71)
    if (i2c == I2C1 && !I2C1_ENABLE) return 0;
#endif
    I2C_pinpack_pins(i2c, c.pinpack, &scl, &sda);
    if (scl == NC || sda == NC)
        return 0;

    pin_setup_af(scl, PIN_MODE_AF, PIN_PULL_UP, PIN_SPEED_HIGH, PIN_TYPE_OPENDRAIN, PIN_AF4);
    pin_setup_af(sda, PIN_MODE_AF, PIN_PULL_UP, PIN_SPEED_HIGH, PIN_TYPE_OPENDRAIN, PIN_AF4);

#if (STM32_TYPE == 407)
    if (i2c == I2C1) RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    if (i2c == I2C2) RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
    if (i2c == I2C3) RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;
#elif (STM32_TYPE == 401) || (STM32_TYPE == 411)
    if (i2c == I2C1) RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
#elif (STM32_TYPE == 71)
    if (i2c == I2C1) RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
#endif

    i2c->CR1 = c.nostretch ? I2C_CR1_NOSTRETCH : 0;
    if (c.general_call)
        i2c->CR1 |= I2C_CR1_ENGC;
    I2C_clock(i2c, SystemCoreClock, &c);
    if (!c.master) {
        i2c->OAR1 = (c.addr10 ? I2C_OAR1_ADDMODE : 0) |
                    (c.own_address & (c.addr10 ? 0x03FF : 0x7F));
        if (c.dual)
            i2c->OAR2 = I2C_OAR2_ENDUAL | (c.own_address2 & 0x7F);
    }
    i2c->CR1 |= I2C_CR1_PE;
    return i2c;
}

/*----------------------------------------------------------------------------*/
/* Utility commands                                                            */
/*----------------------------------------------------------------------------*/
static inline void I2C_start(I2C_TypeDef *i2c) {
    i2c->CR1 |= I2C_CR1_START;
    I2C_wait_flag(i2c, I2C_SR1_SB);
}

static inline void I2C_stop(I2C_TypeDef *i2c) {
    i2c->CR1 |= I2C_CR1_STOP;
}

static inline void I2C_opt_send_addr(I2C_TypeDef *i2c, uint16_t addr, int read, int addr10) {
    if (!addr10) {
        i2c->DR = (addr << 1) | (read ? 1 : 0);
        I2C_wait_flag(i2c, I2C_SR1_ADDR);
        (void)i2c->SR1; (void)i2c->SR2;
    } else {
        uint8_t header = 0xF0 | ((addr >> 7) & 0x06);
        i2c->DR = header | 0;
        I2C_wait_flag(i2c, I2C_SR1_ADD10);
        I2C_wait_flag(i2c, I2C_SR1_TXE);
        i2c->DR = addr & 0xFF;
        I2C_wait_flag(i2c, I2C_SR1_BTF);
        I2C_start(i2c);
        i2c->DR = header | (read ? 1 : 0);
        I2C_wait_flag(i2c, I2C_SR1_ADDR);
        (void)i2c->SR1; (void)i2c->SR2;
    }
}

static inline void I2C_opt_send_data(I2C_TypeDef *i2c, const uint8_t *buf, size_t len) {
    for (size_t i = 0; i < len; i++) {
        I2C_wait_flag(i2c, I2C_SR1_TXE);
        i2c->DR = buf[i];
    }
    I2C_wait_flag(i2c, I2C_SR1_BTF);
}

static inline void I2C_opt_recv_data(I2C_TypeDef *i2c, uint8_t *buf, size_t len) {
    while (len--) {
        if (len == 0)
            i2c->CR1 &= ~I2C_CR1_ACK;
        I2C_wait_flag(i2c, I2C_SR1_RXNE);
        *buf++ = i2c->DR;
    }
    i2c->CR1 |= I2C_CR1_ACK;
}

static inline int I2C_slave_read(I2C_TypeDef *i2c, uint8_t *buf, size_t max_len) {
    size_t len = 0;
    I2C_wait_flag(i2c, I2C_SR1_ADDR);
    (void)i2c->SR1; (void)i2c->SR2;
    while (1) {
        if (i2c->SR1 & I2C_SR1_RXNE) {
            if (len < max_len)
                buf[len++] = i2c->DR;
            else
                (void)i2c->DR;
        }
        if (i2c->SR1 & I2C_SR1_STOPF) {
            (void)i2c->SR1;
            i2c->CR1 |= I2C_CR1_PE;
            break;
        }
    }
    return len;
}

static inline void I2C_slave_write(I2C_TypeDef *i2c, const uint8_t *buf, size_t len) {
    I2C_wait_flag(i2c, I2C_SR1_ADDR);
    (void)i2c->SR1; (void)i2c->SR2;
    while (len) {
        I2C_wait_flag(i2c, I2C_SR1_TXE);
        i2c->DR = *buf++;
        len--;
        if (i2c->SR1 & I2C_SR1_AF) {
            (void)i2c->SR1;
            i2c->CR1 |= I2C_CR1_PE;
            return;
        }
        if (i2c->SR1 & I2C_SR1_STOPF) {
            (void)i2c->SR1;
            i2c->CR1 |= I2C_CR1_PE;
            return;
        }
    }
    I2C_wait_flag(i2c, I2C_SR1_BTF);
}

/*----------------------------------------------------------------------------*/
/* High level helpers                                                          */
/*----------------------------------------------------------------------------*/
static inline void I2C_write(I2C_TypeDef *i2c, uint16_t addr, const void *buf, size_t len) {
    I2C_Config c;
    I2C_load_config(i2c, &c);
    I2C_start(i2c);
    I2C_opt_send_addr(i2c, addr, 0, c.addr10);
    I2C_opt_send_data(i2c, (const uint8_t *)buf, len);
    I2C_stop(i2c);
}

static inline void I2C_read(I2C_TypeDef *i2c, uint16_t addr, void *buf, size_t len) {
    I2C_Config c;
    I2C_load_config(i2c, &c);
    I2C_start(i2c);
    I2C_opt_send_addr(i2c, addr, 1, c.addr10);
    I2C_opt_recv_data(i2c, (uint8_t *)buf, len);
    I2C_stop(i2c);
}

#ifdef __cplusplus
}
#endif

#endif /* STM32_KIT_I2C */
