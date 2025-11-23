#include "bsp_ili9341.h"
#include "bsp_gpio.h"

namespace bsp {

drv::ili9341_config_t ili9341_conf = {
    .cs = cs_pin,
    .dc = dc_pin,
    .rst = rst_pin
};

} // namespace bsp