#ifndef SPI_H
#define SPI_H

#include <cstdint>
#include "stm32h7xx.h"

namespace drv {

class spi {
public:
    spi(GPIO_TypeDef* sck_port, uint8_t sck_pin,
        GPIO_TypeDef* mosi_port, uint8_t mosi_pin,
        GPIO_TypeDef* miso_port, uint8_t miso_pin,
        SPI_TypeDef* instance, uint8_t af);
    void init();
    int8_t write(uint8_t data);
    int8_t write_buffer(const uint8_t* buf, uint32_t len);

private:
    GPIO_TypeDef* const _sck_port;
    const uint8_t _sck_pin;
    GPIO_TypeDef* const _mosi_port;
    const uint8_t _mosi_pin;
    GPIO_TypeDef* const _miso_port;
    const uint8_t _miso_pin;
    SPI_TypeDef* const _instance;
    const uint8_t _af;
    static constexpr uint16_t _timeout = 1000U;

    void init_gpio() const;
    int8_t wait_flag(uint32_t flag, uint32_t value) const;
};

} // namespace drv

#endif // SPI_H