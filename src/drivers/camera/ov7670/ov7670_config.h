#ifndef OV7670_CONFIG_H
#define OV7670_CONFIG_H

#include "../../gpio/gpio_base.h"

namespace drv {

struct ov7670_config_t
{
    // Control pins
    gpio_base& reset;
    gpio_base& vsync;
    gpio_base& href;
    gpio_base& pclk;

    // Data pins
    gpio_base& d0;
    gpio_base& d1;
    gpio_base& d2;
    gpio_base& d3;
    gpio_base& d4;
    gpio_base& d5;
    gpio_base& d6;
    gpio_base& d7;
};

} // namespace drv

#endif // OV7670_CONFIG_H