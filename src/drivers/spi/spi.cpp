#include "spi.h"
#include "../../common/pin_utils/pin_utils.h"

namespace drv {

spi::spi(GPIO_TypeDef* sck_port, uint8_t sck_pin,
         GPIO_TypeDef* mosi_port, uint8_t mosi_pin,
         GPIO_TypeDef* miso_port, uint8_t miso_pin,
         SPI_TypeDef* instance, uint8_t af)
    : _sck_port(sck_port), _sck_pin(sck_pin),
      _mosi_port(mosi_port), _mosi_pin(mosi_pin),
      _miso_port(miso_port), _miso_pin(miso_pin),
      _instance(instance), _af(af)
{}

void spi::init_gpio() const
{
    pin_utils::enable_clock(_sck_port);
    pin_utils::enable_clock(_mosi_port);
    pin_utils::enable_clock(_miso_port);

    // SCK
    pin_utils::set_mode(_sck_port, _sck_pin, pin_utils::gpio_mode::alt_fn);
    pin_utils::set_alternate_function(_sck_port, _sck_pin, _af);
    pin_utils::set_output_push_pull(_sck_port, _sck_pin);
    pin_utils::set_speed_high(_sck_port, _sck_pin);
    pin_utils::set_pupd_none(_sck_port, _sck_pin);

    // MOSI
    pin_utils::set_mode(_mosi_port, _mosi_pin, pin_utils::gpio_mode::alt_fn);
    pin_utils::set_alternate_function(_mosi_port, _mosi_pin, _af);
    pin_utils::set_output_push_pull(_mosi_port, _mosi_pin);
    pin_utils::set_speed_high(_mosi_port, _mosi_pin);
    pin_utils::set_pupd_none(_mosi_port, _mosi_pin);

    // MISO
    pin_utils::set_mode(_miso_port, _miso_pin, pin_utils::gpio_mode::alt_fn);
    pin_utils::set_alternate_function(_miso_port, _miso_pin, _af);
    pin_utils::set_pupd_none(_miso_port, _miso_pin);
}

void spi::init()
{
    init_gpio();

    // Enable SPI1 clock
    if (_instance == SPI1) { RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; }
    else if (_instance == SPI2) { RCC->APB1LENR |= RCC_APB1LENR_SPI2EN; }
    // Add more SPI instances if needed

    // Reset SPI
    if (_instance == SPI1) {
        RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;
        RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST;
    }

    // Disable SPI
    _instance->CR1 &= ~SPI_CR1_SPE;

    _instance->CFG1 =
        (3U << SPI_CFG1_MBR_Pos) |   // Baud / 8
        (7U << SPI_CFG1_DSIZE_Pos);  // 8-bit

    _instance->CFG2 =
        SPI_CFG2_MASTER |
        SPI_CFG2_COMM_0 |            // Full duplex
        SPI_CFG2_MSSI;               // Internal SS

    // Enable SPI
    _instance->CR1 |= SPI_CR1_SPE;
}

int8_t spi::wait_flag(uint32_t flag, uint32_t value) const
{
    uint16_t timeout = _timeout;
    while (((_instance->SR & flag) ? 1U : 0U) != value) {
        if (--timeout == 0) { return -1; }
    }
    return 0;
}

int8_t spi::write(uint8_t data)
{
    if (wait_flag(SPI_SR_TXP, 1) < 0) { return -1; }
    *reinterpret_cast<volatile uint8_t*>(&_instance->TXDR) = data;

    if (wait_flag(SPI_SR_EOT, 1) < 0) { return -1; }
    _instance->IFCR = SPI_IFCR_EOTC;
    return 0;
}

int8_t spi::write_buffer(const uint8_t* buf, uint32_t len)
{
    if (!buf) { return -1; }
    for (uint32_t i = 0; i < len; ++i) {
        if (write(buf[i]) < 0) { return -1; }
    }
    return 0;
}

} // namespace drv