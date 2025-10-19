#ifndef STM32H753_SPI_H
#define STM32H753_SPI_H

#include "gpio.h"
#include "drivers/spi/spi_config.h"
#include "drivers/spi/spi.h"

namespace board {

drv::spi_config_t spi1_config = {
    .sck = sck_pin,
    .mosi = mosi_pin,
    .instance = SPI1,
    .af = 5
};

drv::spi spi1(spi1_config);

} // namespace board

#endif // STM32H753_SPI_H