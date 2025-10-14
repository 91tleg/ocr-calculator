#include "spi.h"
#include "../../common/log/log.h"

namespace drv {

spi::spi(spi_config_t& config) : _config(config) {}

void spi::init_gpio()
{
    _config.sck.init();
    _config.mosi.init();
}

void spi::init()
{
    init_gpio();

    if (_config.instance == SPI1) {
        RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; 
        RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;
        RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST;
    }
    else if (_config.instance == SPI2) {
        RCC->APB1LENR |= RCC_APB1LENR_SPI2EN; 
        RCC->APB1LRSTR |= RCC_APB1LRSTR_SPI2RST;
        RCC->APB1LRSTR &= ~RCC_APB1LRSTR_SPI2RST;
    }

    // Disable SPI
    _config.instance->CR1 &= ~SPI_CR1_SPE;

    _config.instance->CFG1 =
        (3U << SPI_CFG1_MBR_Pos) |   // Baud / 8
        (7U << SPI_CFG1_DSIZE_Pos);  // 8-bit

    _config.instance->CFG2 =
        SPI_CFG2_MASTER |
        SPI_CFG2_COMM_0 |            // Full duplex
        SPI_CFG2_MSSI;               // Internal SS

    // Enable SPI
    _config.instance->CR1 |= SPI_CR1_SPE;
}

spi::spi_status_t spi::wait_flag(uint32_t flag, uint32_t value) const
{
    uint16_t timeout = _timeout;
    while (((_config.instance->SR & flag) ? 1UL : 0UL) != value) {
        if (--timeout == 0U) { return spi_status_t::timeout; }
    }
    return spi_status_t::ok;
}

spi::spi_status_t spi::write(uint8_t data)
{
    if (static_cast<int8_t>(wait_flag(SPI_SR_TXP, 1UL)) < 0) { goto timeout; }
    *reinterpret_cast<volatile uint8_t*>(&_config.instance->TXDR) = data;

    if (static_cast<int8_t>(wait_flag(SPI_SR_EOT, 1UL)) < 0) { goto timeout; }
    _config.instance->IFCR = SPI_IFCR_EOTC;
    return spi_status_t::ok;

timeout:
    sys::log::error("SPI timeout");
    return spi_status_t::timeout;
}

spi::spi_status_t spi::write_buffer(const uint8_t* buf, uint32_t len)
{
    if (!buf) {
        sys::log::error("SPI error: no buffer");
        return spi_status_t::error; 
    }
    for (uint32_t i = 0UL; i < len; ++i) {
        if (static_cast<int8_t>(write(buf[i])) < 0) {
            return  spi_status_t::timeout;
        }
    }
    return spi_status_t::ok;
}

} // namespace drv