#ifndef I2C_H
#define I2C_H

#include <cstdint>
#include "stm32h7xx.h"

namespace drv {

class i2c {
public:
    i2c(GPIO_TypeDef* scl_port, uint8_t scl_pin,
        GPIO_TypeDef* sda_port, uint8_t sda_pin,
        I2C_TypeDef* instance, uint8_t af);
    void init();
    int8_t write_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t data);
    int8_t read_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t* data);

private:
    GPIO_TypeDef* const _scl_port;
    const uint8_t _scl_pin;
    GPIO_TypeDef* const _sda_port;
    const uint8_t _sda_pin;
    I2C_TypeDef* const _instance;
    uint8_t _af;
    static constexpr uint16_t _timeout = 1000U;

    void init_gpio();
    int8_t wait_flag(uint32_t flag, uint32_t value);
};

} // namespace drv

#endif // I2C_H