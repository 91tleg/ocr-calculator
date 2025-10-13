#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H

#include <cstdint>
#include "stm32h7xx.h"

namespace drv {

struct gpio_config_t {
    GPIO_TypeDef* port;
    uint8_t pin;
};

} // namespace drv

#endif // GPIO_CONIFG_H