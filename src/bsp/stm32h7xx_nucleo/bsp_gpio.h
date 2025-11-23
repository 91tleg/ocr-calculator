#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include "drivers/gpio/gpio.h"

namespace bsp {

extern drv::gpio scl_pin;
extern drv::gpio sda_pin;

extern drv::gpio sck_pin;
extern drv::gpio mosi_pin;

extern drv::gpio cs_pin;
extern drv::gpio dc_pin;
extern drv::gpio rst_pin;

extern drv::gpio ov7670_reset;
extern drv::gpio ov7670_vsync;
extern drv::gpio ov7670_href;
extern drv::gpio ov7670_pclk;
extern drv::gpio ov7670_d0;
extern drv::gpio ov7670_d1;
extern drv::gpio ov7670_d2;
extern drv::gpio ov7670_d3;
extern drv::gpio ov7670_d4;
extern drv::gpio ov7670_d5;
extern drv::gpio ov7670_d6;
extern drv::gpio ov7670_d7;

extern drv::gpio button_pin;

} // namespace bsp

#endif // BSP_GPIO_H