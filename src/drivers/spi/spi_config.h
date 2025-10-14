#ifndef SPI_CONFIG_H
#define SPI_CONFIG_H

#include <cstdint>
#include "stm32h7xx.h"
#include "../gpio/gpio_base.h"

namespace drv {

struct spi_config_t
{
    gpio_base& sck;
    gpio_base& mosi;
    SPI_TypeDef* instance;
    uint8_t af;
};

} //namespace drv

#endif // SPI_CONFIG_H