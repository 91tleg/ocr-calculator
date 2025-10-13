#include "gpio.h"
#include "../../common/pin_utils/pin_utils.h"

namespace drv {

gpio::gpio(gpio_config_t& config) : _config(config) {}

void gpio::init(gpio_mode mode)
{
    pin_utils::enable_clock(_config.port);
    pin_utils::set_mode(_config.port, _config.pin, mode);
}

void gpio::set()
{
    pin_utils::write(_config.port, _config.pin, true);
}

void gpio::clear()
{
    pin_utils::write(_config.port, _config.pin, false);
}

bool gpio::read() const
{
    return (_config.port->IDR & pin_utils::pin_mask(_config.pin)) != 0UL;
}

GPIO_TypeDef* gpio::port() const
{
    return _config.port;
}

uint8_t gpio::pin() const
{
    return _config.pin;
}

} // namespace drv