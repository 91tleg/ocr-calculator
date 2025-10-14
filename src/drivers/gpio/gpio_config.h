#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H

#include <cstdint>
#include "stm32h7xx.h"
#include "gpio_types.h"

namespace drv {

struct gpio_config_t
{
    GPIO_TypeDef* port;
    uint8_t pin;
    gpio_mode mode;
    gpio_speed speed;
    gpio_pupd pupd;
    gpio_output_type output_type;
    uint8_t alternate_function;
};

} // namespace drv

#endif // GPIO_CONIFG_H