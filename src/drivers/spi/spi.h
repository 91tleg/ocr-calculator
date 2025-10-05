#ifndef SPI_H
#define SPI_H

#include "stm32h7xx.h"
#include <cstdint>

void spi_init(void);
uint8_t spi_write(uint8_t data);
uint8_t spi_write_buffer(const uint8_t *buf, uint32_t len);

#endif // SPI_H