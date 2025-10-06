#include "gpio.h"
#include "../../common/gpio/gpio_utils.h"

static inline void gpio_enable_clk(GPIO_TypeDef* port)
{
    if (port == GPIOA) { RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN; }
    else if (port == GPIOB) { RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN; }
    else if (port == GPIOC) { RCC->AHB4ENR |= RCC_AHB4ENR_GPIOCEN; }
}

void gpio_init(GPIO_TypeDef* port, uint8_t pin, gpio_mode mode)
{
    gpio_enable_clk(port);
    GPIO_SET_MODE(port, pin, mode);
}

void gpio_write(GPIO_TypeDef* port, uint16_t pin, uint8_t value)
{
    port->BSRR = (value) ? PIN_MASK(pin) : PIN_RESET_MASK(pin);
}

void gpio_clear(GPIO_TypeDef* port, uint16_t pin)
{
    port->BSRR = PIN_RESET_MASK(pin);
}

uint8_t gpio_read(GPIO_TypeDef* port, uint16_t pin)
{
    return (port->IDR & PIN_MASK(pin)) ? 1 : 0;
}