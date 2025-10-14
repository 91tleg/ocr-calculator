#ifndef I2C_BASE_H
#define II2C_BASE_H

#include <cstdint>
#include "../../common/status/status.h"

namespace drv {

class i2c_base
{
public:
    using i2c_status_t = status_t;
    virtual void init() = 0;
    virtual i2c_status_t write_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t data) = 0;
    virtual i2c_status_t read_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t* data) = 0;
    virtual ~i2c_base() = default;
};

} //namespace drv

#endif // II2C_H