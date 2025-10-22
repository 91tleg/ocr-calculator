#ifndef STM32H753_GPIO_H
#define STM32H753_GPIO_H

#include "drivers/gpio/gpio_config.h"
#include "drivers/gpio/gpio_types.h"
#include "drivers/gpio/gpio.h"

namespace board {

drv::gpio_config_t i2c1_scl_conf = {
    .port = GPIOB,
    .pin = 6,
    .mode = drv::gpio_mode::alt_fn,
    .speed = drv::gpio_speed::very_high,
    .pupd = drv::gpio_pupd::pull_up,
    .output_type = drv::gpio_output_type::open_drain,
    .alternate_function = 4
};

drv::gpio_config_t i2c1_sda_conf = {
    .port = GPIOB,
    .pin = 7,
    .mode = drv::gpio_mode::alt_fn,
    .speed = drv::gpio_speed::very_high,
    .pupd = drv::gpio_pupd::pull_up,
    .output_type = drv::gpio_output_type::open_drain,
    .alternate_function = 4
};

drv::gpio_config_t spi1_sck_conf = {
    .port = GPIOA,
    .pin = 5,
    .mode = drv::gpio_mode::alt_fn,
    .speed = drv::gpio_speed::very_high,
    .pupd = drv::gpio_pupd::none,
    .output_type = drv::gpio_output_type::push_pull,
    .alternate_function = 5
};

drv::gpio_config_t spi1_mosi_conf = {
    .port = GPIOA,
    .pin = 7,
    .mode = drv::gpio_mode::alt_fn,
    .speed = drv::gpio_speed::very_high,
    .pupd = drv::gpio_pupd::none,
    .output_type = drv::gpio_output_type::push_pull,
    .alternate_function = 5
};

drv::gpio_config_t ili9341_cs_conf = {
    .port = GPIOB,
    .pin = 6,
    .mode = drv::gpio_mode::output,
    .speed = drv::gpio_speed::very_high,
    .pupd = drv::gpio_pupd::none,
    .output_type = drv::gpio_output_type::push_pull,
    .alternate_function = 0
};

drv::gpio_config_t ili9341_dc_conf = {
    .port = GPIOB,
    .pin = 7,
    .mode = drv::gpio_mode::output,
    .speed = drv::gpio_speed::very_high,
    .pupd = drv::gpio_pupd::none,
    .output_type = drv::gpio_output_type::push_pull,
    .alternate_function = 0
};

drv::gpio_config_t ili9341_rst_conf = {
    .port = GPIOB,
    .pin = 8,
    .mode = drv::gpio_mode::output,
    .speed = drv::gpio_speed::very_high,
    .pupd = drv::gpio_pupd::none,
    .output_type = drv::gpio_output_type::push_pull,
    .alternate_function = 0
};


drv::gpio_config_t ov7670_reset_conf = {
    .port = GPIOB,
    .pin = 8,
    .mode = drv::gpio_mode::output,
    .speed = drv::gpio_speed::very_high,
    .pupd = drv::gpio_pupd::none,
    .output_type = drv::gpio_output_type::push_pull,
    .alternate_function = 0
};

drv::gpio_config_t ov7670_vsync_conf = {
    .port = GPIOC,
    .pin = 7,
    .mode = drv::gpio_mode::input,
    .speed = drv::gpio_speed::very_high,
    .pupd = drv::gpio_pupd::none,
    .output_type = drv::gpio_output_type::push_pull,
    .alternate_function = 0
};

drv::gpio_config_t ov7670_href_conf = {
    .port = GPIOC,
    .pin = 6,
    .mode = drv::gpio_mode::input,
    .speed = drv::gpio_speed::very_high,
    .pupd = drv::gpio_pupd::none,
    .output_type = drv::gpio_output_type::push_pull,
    .alternate_function = 0
};

drv::gpio_config_t ov7670_pclk_conf = {
    .port = GPIOB,
    .pin = 6,
    .mode = drv::gpio_mode::input,
    .speed = drv::gpio_speed::very_high,
    .pupd = drv::gpio_pupd::none,
    .output_type = drv::gpio_output_type::push_pull,
    .alternate_function = 0
};

drv::gpio_config_t ov7670_d0_conf = {
    .port = GPIOC,
    .pin = 9,
    .mode = drv::gpio_mode::input,
    .speed = drv::gpio_speed::very_high,
    .pupd = drv::gpio_pupd::none,
    .output_type = drv::gpio_output_type::push_pull,
    .alternate_function = 0
};

drv::gpio_config_t ov7670_d1_conf = {
    .port = GPIOC,
    .pin = 8, 
    .mode = drv::gpio_mode::input,
    .speed = drv::gpio_speed::very_high,
    .pupd = drv::gpio_pupd::none,
    .output_type = drv::gpio_output_type::push_pull,
    .alternate_function = 0
};

drv::gpio_config_t ov7670_d2_conf = {
    .port = GPIOE,
    .pin = 0,
    .mode = drv::gpio_mode::input,
    .speed = drv::gpio_speed::very_high,
    .pupd = drv::gpio_pupd::none,
    .output_type = drv::gpio_output_type::push_pull,
    .alternate_function = 0
};

drv::gpio_config_t ov7670_d3_conf = {
    .port = GPIOE,
    .pin = 1,
    .mode = drv::gpio_mode::input,
    .speed = drv::gpio_speed::very_high,
    .pupd = drv::gpio_pupd::none,
    .output_type = drv::gpio_output_type::push_pull,
    .alternate_function = 0
};

drv::gpio_config_t ov7670_d4_conf = {
    .port = GPIOE,
    .pin = 4,
    .mode = drv::gpio_mode::input,
    .speed = drv::gpio_speed::very_high,
    .pupd = drv::gpio_pupd::none,
    .output_type = drv::gpio_output_type::push_pull,
    .alternate_function = 0
};

drv::gpio_config_t ov7670_d5_conf = {
    .port = GPIOB,
    .pin = 6,
    .mode = drv::gpio_mode::input,
    .speed = drv::gpio_speed::very_high,
    .pupd = drv::gpio_pupd::none,
    .output_type = drv::gpio_output_type::push_pull,
    .alternate_function = 0
};

drv::gpio_config_t ov7670_d6_conf = {
    .port = GPIOB,
    .pin = 7,
    .mode = drv::gpio_mode::input,
    .speed = drv::gpio_speed::very_high,
    .pupd = drv::gpio_pupd::none,
    .output_type = drv::gpio_output_type::push_pull,
    .alternate_function = 0
};

drv::gpio_config_t ov7670_d7_conf = {
    .port = GPIOB,
    .pin = 9,
    .mode = drv::gpio_mode::input,
    .speed = drv::gpio_speed::very_high,
    .pupd = drv::gpio_pupd::none,
    .output_type = drv::gpio_output_type::push_pull,
    .alternate_function = 0
};

drv::gpio scl_pin(i2c1_scl_conf);
drv::gpio sda_pin(i2c1_sda_conf);

drv::gpio sck_pin(spi1_sck_conf);
drv::gpio mosi_pin(spi1_mosi_conf);

drv::gpio cs_pin(ili9341_cs_conf);
drv::gpio dc_pin(ili9341_dc_conf);
drv::gpio rst_pin(ili9341_rst_conf);

drv::gpio ov7670_reset(ov7670_reset_conf);
drv::gpio ov7670_vsync(ov7670_vsync_conf);
drv::gpio ov7670_href(ov7670_href_conf);
drv::gpio ov7670_pclk(ov7670_pclk_conf);
drv::gpio ov7670_d0(ov7670_d0_conf);
drv::gpio ov7670_d1(ov7670_d1_conf);
drv::gpio ov7670_d2(ov7670_d2_conf);
drv::gpio ov7670_d3(ov7670_d3_conf);
drv::gpio ov7670_d4(ov7670_d4_conf);
drv::gpio ov7670_d5(ov7670_d5_conf);
drv::gpio ov7670_d6(ov7670_d6_conf);
drv::gpio ov7670_d7(ov7670_d7_conf);

} // namespace board

#endif // STM32H753_GPIO_H