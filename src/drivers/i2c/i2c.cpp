#include "i2c.h"
#include "../../common/pin_utils/pin_utils.h"
#include "../../common/gpio_types/gpio_types.h"
#include "../../common/log/log.h"

namespace drv {

i2c::i2c(i2c_config_t& config) : _config(config) {}

void i2c::init_gpio()
{
    pin_utils::enable_clock(_config.scl_port);
    pin_utils::enable_clock(_config.sda_port);

    // SCL
    pin_utils::set_mode(_config.scl_port, _config.scl_pin, gpio_mode::alt_fn);
    pin_utils::set_alternate_function(_config.scl_port, _config.scl_pin, _config.af);
    pin_utils::set_output_open_drain(_config.scl_port, _config.scl_pin);
    pin_utils::set_speed_high(_config.scl_port, _config.scl_pin);
    pin_utils::set_pupd_none(_config.scl_port, _config.scl_pin);

    // SDA
    pin_utils::set_mode(_config.sda_port, _config.sda_pin, gpio_mode::alt_fn);
    pin_utils::set_alternate_function(_config.sda_port, _config.sda_pin, _config.af);
    pin_utils::set_output_open_drain(_config.sda_port, _config.sda_pin);
    pin_utils::set_speed_high(_config.sda_port, _config.sda_pin);
    pin_utils::set_pupd_none(_config.sda_port, _config.sda_pin);
}

void i2c::init()
{
    init_gpio();

    if (_config.instance == I2C1) {
        RCC->APB1LENR |= RCC_APB1LENR_I2C1EN;
        RCC->APB1LRSTR |= RCC_APB1LRSTR_I2C1RST;
        RCC->APB1LRSTR &= ~RCC_APB1LRSTR_I2C1RST;
    }
    else if (_config.instance == I2C2) {
        RCC->APB1LENR |= RCC_APB1LENR_I2C2EN;
        RCC->APB1LRSTR |= RCC_APB1LRSTR_I2C2RST;
        RCC->APB1LRSTR &= ~RCC_APB1LRSTR_I2C2RST;
    }

    _config.instance->TIMINGR = 0x10C0ECFFUL;

    // Enable I2C
    _config.instance->CR1 |= I2C_CR1_PE;
}

i2c::i2c_status_t i2c::wait_flag(uint32_t flag, uint32_t value)
{
    uint16_t timeout = _timeout;
    while (((_config.instance->ISR & flag) ? 1U : 0U) != value) {
        if (--timeout == 0U) { return i2c_status_t::timeout; }
    }
    return i2c_status_t::ok;
}

i2c::i2c_status_t i2c::write_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t data)
{
    // Configure transfer: 2 bytes (reg + data)
    _config.instance->CR2 = (dev_addr << 1U) | (2U << I2C_CR2_NBYTES_Pos) | I2C_CR2_START;

    if (static_cast<int8_t>(wait_flag(I2C_ISR_TXIS, 1UL)) < 0) { goto timeout; }
    _config.instance->TXDR = reg_addr;

    if (static_cast<int8_t>(wait_flag(I2C_ISR_TXIS, 1UL)) < 0) { goto timeout; }
    _config.instance->TXDR = data;

    if (static_cast<int8_t>(wait_flag(I2C_ISR_TC, 1UL)) < 0) { goto timeout; }
    _config.instance->CR2 |= I2C_CR2_STOP;

    if (static_cast<int8_t>(wait_flag(I2C_ISR_STOPF, 1UL)) < 0) { goto timeout; }
    _config.instance->ICR |= I2C_ICR_STOPCF;

    return i2c_status_t::ok;

timeout:
    sys::log::error("I2C write timeout");
    return i2c_status_t::timeout;
}

i2c::i2c_status_t i2c::read_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t* data)
{
    if (!data) { goto error; }

    // Write register address
    _config.instance->CR2 = (dev_addr << 1U) | (1U << I2C_CR2_NBYTES_Pos) | I2C_CR2_START;
    if (static_cast<int8_t>(wait_flag(I2C_ISR_TXIS, 1UL)) < 0) { goto timeout; }
    _config.instance->TXDR = reg_addr;
    if (static_cast<int8_t>(wait_flag(I2C_ISR_TC, 1UL)) < 0) { goto timeout; }

    // Read one byte
    _config.instance->CR2 = (dev_addr << 1U) | I2C_CR2_RD_WRN | 
                            (1U << I2C_CR2_NBYTES_Pos) | I2C_CR2_START;
    if (static_cast<int8_t>(wait_flag(I2C_ISR_RXNE, 1UL)) < 0) { goto timeout; }
    *data = static_cast<uint8_t>(_config.instance->RXDR);

    if (static_cast<int8_t>(wait_flag(I2C_ISR_TC, 1UL)) < 0) { goto timeout; }
    _config.instance->CR2 |= I2C_CR2_STOP;
    if (static_cast<int8_t>(wait_flag(I2C_ISR_STOPF, 1UL)) < 0) { goto timeout; }
    _config.instance->ICR |= I2C_ICR_STOPCF;

    return i2c_status_t::ok;

timeout:
    sys::log::error("I2C read timemout");
    return i2c_status_t::timeout;

error:
    sys::log::error("I2C read error: no buffer");
    return i2c_status_t::error;
}

} // namespace drv