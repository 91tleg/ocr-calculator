#ifndef SPI_H
#define SPI_H

#include <cstdint>
#include "spi_config.h"
#include "spi_base.h"

namespace drv {

class spi : public spi_base
{
public:
    /**
     * @brief Constructor
     * 
     * @param config SPI config struct
     */
    explicit spi(spi_config_t& config);

    /**
     * @brief Initializes the SPI according to the config
     */
    void init() override;

    /**
     * @brief Writes a single byte over SPI
     */
    spi_status_t write(uint8_t data) override;

    /**
     * @brief Writes a buffer of bytes over SPI
     */
    spi_status_t write_buffer(const uint8_t* buf, uint32_t len) override;

private:
    spi_config_t _config;
    static constexpr uint16_t _timeout = 1000U;

    void init_gpio();
    spi_status_t wait_flag(uint32_t flag, uint32_t value) const;
};

} // namespace drv

#endif // SPI_H