#ifndef I2C_CONFIG_H
#define I2C_CONFIG_H

#include <cstdint>
#include "stm32h7xx.h"

namespace drv {

struct i2c_config_t
{
    GPIO_TypeDef* scl_port;
    uint8_t scl_pin;
    GPIO_TypeDef* sda_port;
    uint8_t sda_pin;
    I2C_TypeDef* instance;
    uint8_t af;
};

} // namespace drv

#endif // I2C_CONFIG_H