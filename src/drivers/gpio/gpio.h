#ifndef GPIO_H
#define GPIO_H

#include <cstdint>
#include "stm32h7xx.h"

enum gpio_mode : uint8_t
{
    GPIO_MODE_IN = 0U,
    GPIO_MODE_OUT = 1U,
    GPIO_MODE_AF = 2U,
    GPIO_MODE_ANA = 3U
};

void gpio_init(GPIO_TypeDef *port, uint8_t pin, gpio_mode mode);
void gpio_write(GPIO_TypeDef *port, uint16_t pin, uint8_t value);
void gpio_clear(GPIO_TypeDef *port, uint16_t pin);
uint8_t gpio_read(GPIO_TypeDef *port, uint16_t pin);

#endif // GPIO_H