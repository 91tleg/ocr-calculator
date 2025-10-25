#ifndef STM32H753_OV7670_H
#define STM32H753_OV7670_H 

#include "i2c.h"
#include "drivers/camera/ov7670/ov7670.h"
#include "drivers/camera/ov7670/ov7670_config.h"

namespace board {

drv::ov7670_config_t ov7670_conf = {
    .reset = ov7670_reset,
    .vsync = ov7670_vsync,
    .href  = ov7670_href,
    .pclk  = ov7670_pclk,
    .d0 = ov7670_d0,
    .d1 = ov7670_d1,
    .d2 = ov7670_d2,
    .d3 = ov7670_d3,
    .d4 = ov7670_d4,
    .d5 = ov7670_d5,
    .d6 = ov7670_d6,
    .d7 = ov7670_d7
};

drv::ov7670 cam(i2c1, ov7670_conf);

} // namespace board

#endif // STM32H753_OV7670_H