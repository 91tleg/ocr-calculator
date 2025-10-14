#ifndef I2C_CONFIG_H
#define I2C_CONFIG_H

#include <cstdint>
#include "stm32h7xx.h"
#include "../gpio/gpio_base.h"

namespace drv {

struct i2c_config_t
{
    gpio_base& scl;
    gpio_base& sda;
    I2C_TypeDef* instance;
    uint8_t af;
};

} // namespace drv

#endif // I2C_CONFIG_H