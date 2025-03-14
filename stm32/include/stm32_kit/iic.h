/**
 * @file       iic.h
 * @brief      I2C (Inter-Integrated Circuit) driver with universal timing configuration
 *
 * @attention  This is an alternative experimental driver with to goal to make the
 *             timing calculations universal instead of pedetermined magic numbers.
 */


#ifndef STM32_KIT_IIC
#define STM32_KIT_IIC

#include <stdint.h>
#include "stm32_kit/pin.h"
#include "stm32_kit/platform.h"

/**
 * @brief Duty cycle constants for fast mode
 */
#define I2C_DUTY_2_1  1  ///< Fast mode with 2:1 duty cycle
#define I2C_DUTY_16_9 2  ///< Fast mode with 16:9 duty cycle

/**
 * @brief I2C configuration structure
 */
typedef struct {
    uint32_t frequency;     ///< I2C frequency in Hz (e.g., 100000 for 100 kHz)
    uint32_t duty;          ///< Duty cycle: IIC_DUTY_2_1 or IIC_DUTY_16_9
    uint32_t rise_time_ns;  ///< Maximum rise time in nanoseconds
} IIC_Config_t;

/**
 * @brief Configure I2C timing directly on the peripheral
 * @param dev I2C peripheral (e.g., I2C1, I2C2, I2C3)
 * @param peripheral_clock Peripheral clock frequency in Hz
 * @param frequency I2C frequency in Hz (e.g., 100000 for 100 kHz)
 * @param duty Duty cycle: I2C_DUTY_2_1 or I2C_DUTY_16_9
 * @param rise Maximum rise time in nanoseconds
 */
static inline void i2c_calculate_timing(I2C_TypeDef *__restrict dev, uint32_t peripheral_clock, uint32_t frequency, uint32_t duty, uint32_t rise) {
    // Configure CCR (Clock Control Register)
    if (frequency <= 100000) {
        // Standard mode (100 kHz)
        dev->CCR = (peripheral_clock / (frequency * 2)) & I2C_CCR_CCR_Msk;
    } else {
        // Fast mode (400 kHz or above)
        if (duty == I2C_DUTY_16_9) {
            dev->CCR = (peripheral_clock / (frequency * 25)) & I2C_CCR_CCR_Msk;
            dev->CCR |= I2C_CCR_DUTY;  // Set duty cycle to 16:9
        } else {
            dev->CCR = (peripheral_clock / (frequency * 3)) & I2C_CCR_CCR_Msk;  // Default 2:1 duty cycle
        }
    }

    // Configure TRISE (Rise Time Register)
    dev->TRISE = ((peripheral_clock / 1_000_000) * rise / 1000) + 1;

    // Configure CR2 (Peripheral Clock Frequency)
    dev->CR2 = (peripheral_clock / 1_000_000) & I2C_CR2_FREQ_Msk;
}

/**
 * @brief Helper to enable the I2C peripheral
 * @param dev Pointer to the I2C peripheral (e.g., I2C1, I2C2, I2C3)
 */
static inline void IIC_enable(I2C_TypeDef *__restrict dev) {
    if (dev == I2C1) RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    if (dev == I2C2) RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
    if (dev == I2C3) RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;
}

/**
 * @brief Helper to reset the I2C peripheral
 * @param dev Pointer to the I2C peripheral (e.g., I2C1, I2C2, I2C3)
 */
static inline void IIC_reset(I2C_TypeDef *__restrict dev) {
    SET_BIT(dev->CR1, I2C_CR1_SWRST);
    CLEAR_BIT(dev->CR1, I2C_CR1_SWRST);
}

/**
 * @brief Clears the I2C software flags by reading SR1 and SR2
 * @param dev Pointer to the I2C peripheral
 */
static inline void IIC_sw_clear(const I2C_TypeDef *__restrict dev) {
    uint16_t reg;
    reg = dev->SR1;
    reg = dev->SR2;
    (void)reg;
}

/**
 * @brief Wait for a specific flag in SR1
 * @param dev Pointer to the I2C peripheral
 * @param flag The flag to wait for
 */
static inline void IIC_wait_for_flag(const I2C_TypeDef *__restrict dev, uint16_t flag) {
    while (!(dev->SR1 & flag)) {
        // Wait for the flag to be set
    }
}

/**
 * @brief Configure the I2C peripheral
 * @param dev Pointer to the I2C peripheral (e.g., I2C1, I2C2, I2C3)
 * @param config Pointer to the I2C configuration structure
 */
static inline void IIC_setup(I2C_TypeDef *__restrict dev, const IIC_Config_t *config) {
    __disable_irq();

    // Configure SDA and SCL pins
    pin_setup_af(i2c_pin_sda(dev), PIN_MODE_AF, PIN_PULL_UP, PIN_SPEED_VERYHIGH, PIN_TYPE_OPENDRAIN, PIN_AF4);
    pin_setup_af(i2c_pin_scl(dev), PIN_MODE_AF, PIN_PULL_UP, PIN_SPEED_VERYHIGH, PIN_TYPE_OPENDRAIN, PIN_AF4);

    // Enable the I2C peripheral and reset it
    IIC_enable(dev);
    IIC_reset(dev);

    // Apply timing configuration
    IIC_calculate_timing(dev, SystemCoreClock, config->frequency, config->duty, config->rise_time_ns);

    // Enable the I2C peripheral
    dev->CR1 |= I2C_CR1_PE;

    __enable_irq();
}

/**
 * @brief Write a single byte to the I2C peripheral
 * @param dev Pointer to the I2C peripheral
 * @param data Byte to write
 */
static inline void IIC_write_byte(I2C_TypeDef *__restrict dev, uint8_t data) {
    IIC_wait_for_flag(dev, I2C_SR1_TXE);  // Wait until TX buffer is empty
    dev->DR = data;
}

/**
 * @brief Read a single byte from the I2C peripheral
 * @param dev Pointer to the I2C peripheral
 * @return The byte read from the I2C peripheral
 */
static inline uint8_t IIC_read_byte(I2C_TypeDef *__restrict dev) {
    IIC_wait_for_flag(dev, I2C_SR1_RXNE);  // Wait until RX buffer has data
    return dev->DR;
}

/**
 * @brief Write multiple bytes to the I2C peripheral
 * @param dev Pointer to the I2C peripheral
 * @param data Pointer to the data buffer
 * @param len Number of bytes to write
 */
static inline void IIC_write(I2C_TypeDef *__restrict dev, const uint8_t *data, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        IIC_write_byte(dev, data[i]);
    }
}

/**
 * @brief Read multiple bytes from the I2C peripheral
 * @param dev Pointer to the I2C peripheral
 * @param data Pointer to the buffer to store received data
 * @param len Number of bytes to read
 */
static inline void IIC_read(I2C_TypeDef *__restrict dev, uint8_t *data, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        data[i] = IIC_read_byte(dev);
    }
}

/**
 * @brief Write the address to the I2C peripheral
 * @param dev Pointer to the I2C peripheral
 * @param addr Address to write
 */
static inline void IIC_write_addr(I2C_TypeDef *__restrict dev, uint8_t addr) {
    dev->DR = addr;
    IIC_wait_for_flag(dev, I2C_SR1_ADDR);
    IIC_sw_clear(dev);
}

/**
 * @brief Scan for devices on the I2C bus
 * @param dev Pointer to the I2C peripheral
 * @return Address of the first found device, or 0 if none found
 */
static inline uint8_t IIC_scan(I2C_TypeDef *__restrict dev) {
    uint8_t addr = 2;
    uint8_t found = 0;

    while (!found) {
        if (!addr) break;

        // Start condition
        dev->CR1 |= I2C_CR1_START;
        IIC_wait_for_flag(dev, I2C_SR1_SB);

        // Send address
        dev->DR = addr;
        delay_us(100);

        if (!(dev->SR1 & I2C_SR1_ADDR)) {
            addr += 2;
            IIC_sw_clear(dev);
            continue;
        }

        found = addr;
        IIC_sw_clear(dev);
        dev->CR1 |= I2C_CR1_STOP;  // Stop condition
    }

    return found;
}


#endif /* STM32_KIT_IIC */
