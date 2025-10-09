#include "gpio.h"
#include "../../common/pin_utils/pin_utils.h"

namespace drv {

gpio::gpio(GPIO_TypeDef* port, uint8_t pin)
    : _port(port), _pin(pin)
{
    pin_utils::enable_clock(_port);
}

void gpio::init(pin_utils::gpio_mode mode) const
{
    pin_utils::set_mode(_port, _pin, mode);
}

void gpio::set() const
{
    pin_utils::write(_port, _pin, true);
}

void gpio::clear() const
{
    pin_utils::write(_port, _pin, false);
}

bool gpio::read() const
{
    return (_port->IDR & pin_utils::pin_mask(_pin)) != 0U;
}

GPIO_TypeDef* gpio::port() const
{
    return _port;
}

uint8_t gpio::pin() const
{
    return _pin;
}

} // namespace drv