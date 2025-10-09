#include "i2c.h"
#include "../../common/pin_utils/pin_utils.h"

namespace drv {

i2c::i2c(GPIO_TypeDef* scl_port, uint8_t scl_pin,
         GPIO_TypeDef* sda_port, uint8_t sda_pin,
         I2C_TypeDef* instance, uint8_t af)
    : _scl_port(scl_port), _scl_pin(scl_pin),
      _sda_port(sda_port), _sda_pin(sda_pin),
      _instance(instance), _af(af)
{}

void i2c::init_gpio()
{
    pin_utils::enable_clock(_scl_port);
    pin_utils::enable_clock(_sda_port);

    // SCL
    pin_utils::set_mode(_scl_port, _scl_pin, pin_utils::gpio_mode::alt_fn);
    pin_utils::set_alternate_function(_scl_port, _scl_pin, _af);
    pin_utils::set_output_open_drain(_scl_port, _scl_pin);
    pin_utils::set_speed_high(_scl_port, _scl_pin);
    pin_utils::set_pupd_none(_scl_port, _scl_pin);

    // SDA
    pin_utils::set_mode(_sda_port, _sda_pin, pin_utils::gpio_mode::alt_fn);
    pin_utils::set_alternate_function(_sda_port, _sda_pin, _af);
    pin_utils::set_output_open_drain(_sda_port, _sda_pin);
    pin_utils::set_speed_high(_sda_port, _sda_pin);
    pin_utils::set_pupd_none(_sda_port, _sda_pin);
}

void i2c::init()
{
    init_gpio();

    // Enable I2C clock
    if (_instance == I2C1) { RCC->APB1LENR |= RCC_APB1LENR_I2C1EN; }
    else if (_instance == I2C2) { RCC->APB1LENR |= RCC_APB1LENR_I2C2EN; }

    // Reset I2C
    if (_instance == I2C1) {
        RCC->APB1LRSTR |= RCC_APB1LRSTR_I2C1RST;
        RCC->APB1LRSTR &= ~RCC_APB1LRSTR_I2C1RST;
    }

    _instance->TIMINGR = 0x10C0ECFF;

    // Enable I2C
    _instance->CR1 |= I2C_CR1_PE;
}

int8_t i2c::wait_flag(uint32_t flag, uint32_t value)
{
    uint16_t timeout = _timeout;
    while (((_instance->ISR & flag) ? 1U : 0U) != value) {
        if (--timeout == 0) { return -1; }
    }
    return 0;
}

int8_t i2c::write_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t data)
{
    // Configure transfer: 2 bytes (reg + data)
    _instance->CR2 = (dev_addr << 1) | (2 << I2C_CR2_NBYTES_Pos) | I2C_CR2_START;

    if (wait_flag(I2C_ISR_TXIS, 1) < 0) { return -1; }
    _instance->TXDR = reg_addr;

    if (wait_flag(I2C_ISR_TXIS, 1) < 0) { return -1; }
    _instance->TXDR = data;

    if (wait_flag(I2C_ISR_TC, 1) < 0) { return -1; }
    _instance->CR2 |= I2C_CR2_STOP;

    if (wait_flag(I2C_ISR_STOPF, 1) < 0) { return -1; }
    _instance->ICR |= I2C_ICR_STOPCF;

    return 0;
}

int8_t i2c::read_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t* data)
{
    if (!data) { return -1; }

    // Write register address
    _instance->CR2 = (dev_addr << 1) | (1 << I2C_CR2_NBYTES_Pos) | I2C_CR2_START;
    if (wait_flag(I2C_ISR_TXIS, 1) < 0) { return -1; }
    _instance->TXDR = reg_addr;
    if (wait_flag(I2C_ISR_TC, 1) < 0) { return -1; }

    // Read one byte
    _instance->CR2 = (dev_addr << 1) | I2C_CR2_RD_WRN | (1 << I2C_CR2_NBYTES_Pos) | I2C_CR2_START;
    if (wait_flag(I2C_ISR_RXNE, 1) < 0) { return -1; }
    *data = static_cast<uint8_t>(_instance->RXDR);

    if (wait_flag(I2C_ISR_TC, 1) < 0) { return -1; }
    _instance->CR2 |= I2C_CR2_STOP;
    if (wait_flag(I2C_ISR_STOPF, 1) < 0) { return -1; }
    _instance->ICR |= I2C_ICR_STOPCF;

    return 0;
}

} // namespace drv