#include "bsp_i2c.h"
#include "bsp_gpio.h"

namespace bsp {

drv::i2c_config_t i2c1_conf = {
    .scl = scl_pin,
    .sda = sda_pin,
    .instance = I2C1,
    .af = 4
};

} // namespace bsp