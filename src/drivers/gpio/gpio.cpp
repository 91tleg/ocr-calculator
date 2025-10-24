#include "gpio.h"
#include "gpio_types.h"

namespace drv {

gpio::gpio(gpio_config_t& config) : _config(config) {}

void gpio::init()
{
    enable_clock();
    set_mode();
    set_output_type();
    set_speed();
    set_pupd();
    if (_config.mode == gpio_mode::alt_fn) {
        set_alternate_function();
    }
}

void gpio::set()
{
    write(true);
}

void gpio::clear()
{
    write(false);
}

bool gpio::read() const
{
    return (_config.port->IDR & pin_mask(_config.pin)) != 0UL;
}

GPIO_TypeDef* gpio::port() const
{
    return _config.port;
}

uint8_t gpio::pin() const
{
    return _config.pin;
}

void gpio::write(bool high)
{
    _config.port->BSRR = high
        ? pin_mask(_config.pin)
        : pin_reset_mask(_config.pin);
}

void gpio::set_mode()
{
    _config.port->MODER =
        (_config.port->MODER & ~(3UL << (_config.pin * 2U))) |
        ((static_cast<uint8_t>(_config.mode) & 3U) << (_config.pin * 2U));
}
    
void gpio::set_alternate_function()
{
    const uint8_t index = _config.pin >> 3U;
    const uint8_t shift = (_config.pin & 7U) * 4U;
    _config.port->AFR[index] = 
        (_config.port->AFR[index] & ~(0xFUL << shift)) |
        ((_config.alternate_function & 0xFUL) << shift);
}

void gpio::set_output_type()
{
    switch (_config.output_type) {
        case gpio_output_type::open_drain:
            _config.port->OTYPER |= (1UL << _config.pin);
            break;

        case gpio_output_type::push_pull:
            _config.port->OTYPER &= ~(1UL << _config.pin);
            break;

        case gpio_output_type::none:
        default:
            // Pin not configured as output
            break;
    }
}

void gpio::set_speed()
{
    _config.port->OSPEEDR =
        (_config.port->OSPEEDR & ~(3UL << (_config.pin * 2U))) |
        ((static_cast<uint8_t>(_config.speed) & 3U) << (_config.pin * 2U));
}
    
void gpio::set_pupd()
{
    _config.port->PUPDR =
        (_config.port->PUPDR & ~(3UL << (_config.pin * 2U))) |
        ((static_cast<uint8_t>(_config.pupd) & 3U) << (_config.pin * 2U));
}
    
void gpio::enable_clock()
{
    if (_config.port == GPIOA)      { RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN; }
    else if (_config.port == GPIOB) { RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN; }
    else if (_config.port == GPIOC) { RCC->AHB4ENR |= RCC_AHB4ENR_GPIOCEN; }
    else if (_config.port == GPIOD) { RCC->AHB4ENR |= RCC_AHB4ENR_GPIODEN; }
    else if (_config.port == GPIOE) { RCC->AHB4ENR |= RCC_AHB4ENR_GPIOEEN; }
    else { return; }
    __DSB();
}

} // namespace drv