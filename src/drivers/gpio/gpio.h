#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include "stm32h7xx.h"

void gpio_init(GPIO_TypeDef* port, uint8_t pin);
void gpio_write(GPIO_TypeDef* port, uint16_t pin, uint8_t value);
void gpio_clear(GPIO_TypeDef* port, uint16_t pin);
uint8_t gpio_read(GPIO_TypeDef* port, uint16_t pin);

#endif // GPIO_H