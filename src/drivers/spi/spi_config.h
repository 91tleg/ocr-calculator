#ifndef SPI_CONFIG_H
#define SPI_CONFIG_H

#include <cstdint>
#include "stm32h7xx.h"

namespace drv {

struct spi_config_t {
    GPIO_TypeDef* sck_port;
    uint8_t sck_pin;
    GPIO_TypeDef* mosi_port;
    uint8_t mosi_pin;
    SPI_TypeDef* instance;
    uint8_t af;
};

} //namespace drv

#endif // SPI_CONFIG_H