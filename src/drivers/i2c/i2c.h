#ifndef I2C_H
#define I2C_H

#include <cstdint>
#include "stm32h7xx.h"
#include "i2c_config.h"
#include "../../common/status/status.h"

namespace drv {

class i2c {
public:
    using i2c_status_t = drv::status_t;
    explicit i2c(i2c_config_t& config);
    void init();
    i2c_status_t write_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t data);
    i2c_status_t read_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t* data);

private:
    i2c_config_t _config;
    static constexpr uint16_t _timeout = 1000U;

    void init_gpio();
    i2c_status_t wait_flag(uint32_t flag, uint32_t value);
};

} // namespace drv

#endif // I2C_H