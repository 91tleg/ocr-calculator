#ifndef ILI9341_CONFIG_H
#define ILI9341_CONFIG_H

#include "../../gpio/gpio_base.h"

namespace drv {

struct ili9341_config_t
{
    gpio_base& cs;
    gpio_base& dc;
    gpio_base& rst;
};

} // namespace drv

#endif // ILI9341_CONFIG_H