#ifndef OV7670_H
#define OV7670_h

#include <cstdint>
#include "../../i2c/i2c_base.h"
#include "../camera_base.h"
#include "../../../common/systick/systick_base.h"
#include "ov7670_config.h"

namespace drv {

class ov7670 : public camera_base
{
public:
    explicit ov7670(i2c_base& bus, ov7670_config_t& config, sys::systick_base& time);
    void init() override;
    bool capture(uint8_t* buffer, uint32_t buf_size) override;

private:
    i2c_base& _bus;
    ov7670_config_t& _config;
    sys::systick_base& _time;
    void write_reg(uint8_t reg, uint8_t value);
    void read_reg(uint8_t reg, uint8_t& value);
    uint8_t read_data_pins() const;
};

} //namespace drv

#endif // OV7670_H