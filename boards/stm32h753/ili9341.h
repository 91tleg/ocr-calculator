#ifndef STM32H753_ILI9341_H
#define STM32H753_ILI9341_H

#include "gpio.h"
#include "drivers/display/ili9341/ili9341_config.h"
#include "drivers/display/ili9341/ili9341.h"
#include "spi.h"

namespace board {

drv::ili9341_config_t ili9341_conf = {
    .cs = cs_pin,
    .dc = dc_pin,
    .rst = rst_pin
};

drv::ili9341 lcd(spi1, ili9341_conf);

} // namespace board

#endif // STM32H753_ILI9341_H