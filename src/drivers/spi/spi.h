#ifndef SPI_H
#define SPI_H

#include <cstdint>
#include "stm32h7xx.h"
#include "spi_config.h"
#include "../../common/status/status.h"

namespace drv {

class spi {
public:
    using spi_status_t = drv::status_t;
    explicit spi(spi_config_t& config);
    void init();
    spi_status_t write(uint8_t data);
    spi_status_t write_buffer(const uint8_t* buf, uint32_t len);

private:
    spi_config_t _config;
    static constexpr uint16_t _timeout = 1000U;

    void init_gpio();
    spi_status_t wait_flag(uint32_t flag, uint32_t value) const;
};

} // namespace drv

#endif // SPI_H