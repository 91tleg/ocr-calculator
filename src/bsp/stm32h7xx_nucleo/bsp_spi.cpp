#include "bsp_spi.h"
#include "bsp_gpio.h"

namespace bsp {

drv::spi_config_t spi1_conf = {
    .sck = sck_pin,
    .mosi = mosi_pin,
    .instance = SPI1,
    .af = 5
};

} // namespace bsp
