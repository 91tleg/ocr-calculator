#ifndef SPI_BASE_H
#define SPI_BASE_H

#include <cstdint>
#include "../../common/status/status.h"

namespace drv {

class spi_base
{
public: 
    using spi_status_t = status_t;
    virtual void init() = 0;
    virtual spi_status_t write(uint8_t data) = 0;
    virtual spi_status_t write_buffer(const uint8_t* buf, uint32_t len) = 0;
    virtual ~spi_base() = default;
};

} //namespace drv

#endif // SPI_BASE_H