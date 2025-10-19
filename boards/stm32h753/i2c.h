#ifndef STM32H753_I2C_H
#define STM32H753_I2C_H

#include "drivers/i2c/i2c.h"
#include "gpio.h"

namespace board {

drv::i2c_config_t i2c1_conf = {
    .scl = scl_pin,
    .sda = sda_pin,
    .instance = I2C1,
    .af = 4
};

drv::i2c i2c1(i2c1_conf);

} // namespace board

#endif // STM32H753_I2C_H