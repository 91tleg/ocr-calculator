#include "i2c.h"
#include "../gpio/gpio.h"
#include "stm32h7xx.h"
#include "../boards/board.h"
#include "../../common/gpio/gpio_utils.h"

static void i2c_gpio_init(void)
{
    gpio_init(I2C_SCL_PORT, I2C_SCL_PIN, GPIO_MODE_AF);
    gpio_init(I2C_SDA_PORT, I2C_SDA_PIN, GPIO_MODE_AF);

    // SCL
    GPIO_SET_OTYPE_OD(I2C_SCL_PORT, I2C_SCL_PIN);
    GPIO_SET_SPEED_HIGH(I2C_SCL_PORT, I2C_SCL_PIN);
    GPIO_SET_PUPD_NONE(I2C_SCL_PORT, I2C_SCL_PIN);
    GPIO_SET_AF(I2C_SCL_PORT, I2C_SCL_PIN, I2C_AF);

    // SDA
    GPIO_SET_OTYPE_OD(I2C_SDA_PORT, I2C_SDA_PIN);
    GPIO_SET_SPEED_HIGH(I2C_SDA_PORT, I2C_SDA_PIN);
    GPIO_SET_PUPD_NONE(I2C_SDA_PORT, I2C_SDA_PIN);
    GPIO_SET_AF(I2C_SDA_PORT, I2C_SDA_PIN, I2C_AF);
}

static int8_t i2c_wait_flag(uint32_t flag, uint32_t value)
{
    uint16_t timeout = I2C_TIMEOUT;
    while (((I2C_INSTANCE->ISR & flag) ? 1U : 0U) != value)
    {
        if (--timeout == 0) { return -1; }
    }
    return 0;
}

void i2c_init(void)
{
    i2c_gpio_init();

    // Enable I2C1 clock
    RCC->APB1LENR |= RCC_APB1LENR_I2C1EN;

    // Reset I2C
    RCC->APB1LRSTR |= RCC_APB1LRSTR_I2C1RST;
    RCC->APB1LRSTR &= ~RCC_APB1LRSTR_I2C1RST;

    // Configure timing
    I2C_INSTANCE->TIMINGR = 0x10C0ECFF;

    // Enable I2C peripheral
    I2C_INSTANCE->CR1 |= I2C_CR1_PE;
}

int8_t i2c_write_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t data)
{
    // Configure transfer: 2 bytes (reg + data)
    I2C_INSTANCE->CR2 = (dev_addr << 1) | (2 << I2C_CR2_NBYTES_Pos) | I2C_CR2_START;

    if (i2c_wait_flag(I2C_ISR_TXIS, 1) < 0) { return -1; }
    I2C_INSTANCE->TXDR = reg_addr;

    if (i2c_wait_flag(I2C_ISR_TXIS, 1) < 0) { return -1; }
    I2C_INSTANCE->TXDR = data;

    if (i2c_wait_flag(I2C_ISR_TC, 1) < 0) { return -1; }
    I2C_INSTANCE->CR2 |= I2C_CR2_STOP;

    if (i2c_wait_flag(I2C_ISR_STOPF, 1) < 0) { return -1; }
    I2C_INSTANCE->ICR |= I2C_ICR_STOPCF;

    return 0;
}

int8_t i2c_read_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data)
{
    if (!data) { return -1; }

    // Write register address
    I2C_INSTANCE->CR2 = (dev_addr << 1) | (1 << I2C_CR2_NBYTES_Pos) | I2C_CR2_START;
    if (i2c_wait_flag(I2C_ISR_TXIS, 1) < 0) { return -1; }
    I2C_INSTANCE->TXDR = reg_addr;
    if (i2c_wait_flag(I2C_ISR_TC, 1) < 0) { return -1; }

    // Read one byte
    I2C_INSTANCE->CR2 = (dev_addr << 1) | I2C_CR2_RD_WRN | (1 << I2C_CR2_NBYTES_Pos) | I2C_CR2_START;
    if (i2c_wait_flag(I2C_ISR_RXNE, 1) < 0) { return -1; }
    *data = (uint8_t)I2C_INSTANCE->RXDR;

    if (i2c_wait_flag(I2C_ISR_TC, 1) < 0) { return -1; }
    I2C_INSTANCE->CR2 |= I2C_CR2_STOP;
    if (i2c_wait_flag(I2C_ISR_STOPF, 1) < 0) { return -1; }
    I2C_INSTANCE->ICR |= I2C_ICR_STOPCF;

    return 0;
}