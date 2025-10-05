#include "gpio.h"
#include "utils.h"

void gpio_init(GPIO_TypeDef* port, uint8_t pin)
{
    if (port == GPIOA) 
    {
        RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;
    }
    else if (port == GPIOB) 
    {
        RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN;
    }
    else if (port == GPIOC)
    {
        RCC->AHB4ENR |= RCC_AHB4ENR_GPIOCEN;
    }

    // Set pin as output
    port->MODER &= ~(0x3 << (pin * 2));
    port->MODER |=  (0x1 << (pin * 2));
}

void gpio_write(GPIO_TypeDef* port, uint16_t pin, uint8_t value)
{
    uint32_t pin_mask = PIN_MASK(pin);
    port->BSRR = (value) ? pin_mask : (pin_mask << 16U);
}

void gpio_clear(GPIO_TypeDef* port, uint16_t pin)
{
    port->BSRR = PIN_MASK(pin) << 16U;
}

uint8_t gpio_read(GPIO_TypeDef* port, uint16_t pin)
{
    return (port->IDR & PIN_MASK(pin)) ? 1 : 0;
}