#include "bsp_gpio.h"
#include "drivers/gpio/gpio_config.h"
#include "drivers/gpio/gpio_types.h"

using namespace drv;

namespace bsp {

gpio_config_t i2c1_scl_conf = {
    .port = GPIOB,
    .pin = 6,
    .mode = gpio_mode::alt_fn,
    .speed = gpio_speed::very_high,
    .pupd = gpio_pupd::pull_up,
    .output_type = gpio_output_type::open_drain,
    .alternate_function = 4
};

gpio_config_t i2c1_sda_conf = {
    .port = GPIOB,
    .pin = 7,
    .mode = gpio_mode::alt_fn,
    .speed = gpio_speed::very_high,
    .pupd = gpio_pupd::pull_up,
    .output_type = gpio_output_type::open_drain,
    .alternate_function = 4
};

gpio_config_t spi1_sck_conf = {
    .port = GPIOA,
    .pin = 5,
    .mode = gpio_mode::alt_fn,
    .speed = gpio_speed::very_high,
    .pupd = gpio_pupd::none,
    .output_type = gpio_output_type::push_pull,
    .alternate_function = 5
};

gpio_config_t spi1_mosi_conf = {
    .port = GPIOA,
    .pin = 7,
    .mode = gpio_mode::alt_fn,
    .speed = gpio_speed::very_high,
    .pupd = gpio_pupd::none,
    .output_type = gpio_output_type::push_pull,
    .alternate_function = 5
};

gpio_config_t ili9341_cs_conf = {
    .port = GPIOB,
    .pin = 6,
    .mode = gpio_mode::output,
    .speed = gpio_speed::very_high,
    .pupd = gpio_pupd::none,
    .output_type = gpio_output_type::push_pull,
    .alternate_function = 0
};

gpio_config_t ili9341_dc_conf = {
    .port = GPIOB,
    .pin = 7,
    .mode = gpio_mode::output,
    .speed = gpio_speed::very_high,
    .pupd = gpio_pupd::none,
    .output_type = gpio_output_type::push_pull,
    .alternate_function = 0
};

gpio_config_t ili9341_rst_conf = {
    .port = GPIOB,
    .pin = 8,
    .mode = gpio_mode::output,
    .speed = gpio_speed::very_high,
    .pupd = gpio_pupd::none,
    .output_type = gpio_output_type::push_pull,
    .alternate_function = 0
};


gpio_config_t ov7670_reset_conf = {
    .port = GPIOB,
    .pin = 8,
    .mode = gpio_mode::output,
    .speed = gpio_speed::very_high,
    .pupd = gpio_pupd::none,
    .output_type = gpio_output_type::push_pull,
    .alternate_function = 0
};

gpio_config_t ov7670_vsync_conf = {
    .port = GPIOC,
    .pin = 7,
    .mode = gpio_mode::input,
    .speed = gpio_speed::very_high,
    .pupd = gpio_pupd::none,
    .output_type = gpio_output_type::push_pull,
    .alternate_function = 0
};

gpio_config_t ov7670_href_conf = {
    .port = GPIOC,
    .pin = 6,
    .mode = gpio_mode::input,
    .speed = gpio_speed::very_high,
    .pupd = gpio_pupd::none,
    .output_type = gpio_output_type::push_pull,
    .alternate_function = 0
};

gpio_config_t ov7670_pclk_conf = {
    .port = GPIOB,
    .pin = 6,
    .mode = gpio_mode::input,
    .speed = gpio_speed::very_high,
    .pupd = gpio_pupd::none,
    .output_type = gpio_output_type::push_pull,
    .alternate_function = 0
};

gpio_config_t ov7670_d0_conf = {
    .port = GPIOC,
    .pin = 9,
    .mode = gpio_mode::input,
    .speed = gpio_speed::very_high,
    .pupd = gpio_pupd::none,
    .output_type = gpio_output_type::push_pull,
    .alternate_function = 0
};

gpio_config_t ov7670_d1_conf = {
    .port = GPIOC,
    .pin = 8, 
    .mode = gpio_mode::input,
    .speed = gpio_speed::very_high,
    .pupd = gpio_pupd::none,
    .output_type = gpio_output_type::push_pull,
    .alternate_function = 0
};

gpio_config_t ov7670_d2_conf = {
    .port = GPIOE,
    .pin = 0,
    .mode = gpio_mode::input,
    .speed = gpio_speed::very_high,
    .pupd = gpio_pupd::none,
    .output_type = gpio_output_type::push_pull,
    .alternate_function = 0
};

gpio_config_t ov7670_d3_conf = {
    .port = GPIOE,
    .pin = 1,
    .mode = gpio_mode::input,
    .speed = gpio_speed::very_high,
    .pupd = gpio_pupd::none,
    .output_type = gpio_output_type::push_pull,
    .alternate_function = 0
};

gpio_config_t ov7670_d4_conf = {
    .port = GPIOE,
    .pin = 4,
    .mode = gpio_mode::input,
    .speed = gpio_speed::very_high,
    .pupd = gpio_pupd::none,
    .output_type = gpio_output_type::push_pull,
    .alternate_function = 0
};

gpio_config_t ov7670_d5_conf = {
    .port = GPIOB,
    .pin = 6,
    .mode = gpio_mode::input,
    .speed = gpio_speed::very_high,
    .pupd = gpio_pupd::none,
    .output_type = gpio_output_type::push_pull,
    .alternate_function = 0
};

gpio_config_t ov7670_d6_conf = {
    .port = GPIOB,
    .pin = 7,
    .mode = gpio_mode::input,
    .speed = gpio_speed::very_high,
    .pupd = gpio_pupd::none,
    .output_type = gpio_output_type::push_pull,
    .alternate_function = 0
};

gpio_config_t ov7670_d7_conf = {
    .port = GPIOB,
    .pin = 9,
    .mode = gpio_mode::input,
    .speed = gpio_speed::very_high,
    .pupd = gpio_pupd::none,
    .output_type = gpio_output_type::push_pull,
    .alternate_function = 0
};

gpio_config_t button_conf = {
    .port = GPIOA,
    .pin = 6,
    .mode = gpio_mode::input,
    .speed = gpio_speed::medium,
    .pupd = gpio_pupd::pull_up,
    .output_type = gpio_output_type::none,
    .alternate_function = 0
};

gpio scl_pin(i2c1_scl_conf);
gpio sda_pin(i2c1_sda_conf);

gpio sck_pin(spi1_sck_conf);
gpio mosi_pin(spi1_mosi_conf);

gpio cs_pin(ili9341_cs_conf);
gpio dc_pin(ili9341_dc_conf);
gpio rst_pin(ili9341_rst_conf);

gpio ov7670_reset(ov7670_reset_conf);
gpio ov7670_vsync(ov7670_vsync_conf);
gpio ov7670_href(ov7670_href_conf);
gpio ov7670_pclk(ov7670_pclk_conf);
gpio ov7670_d0(ov7670_d0_conf);
gpio ov7670_d1(ov7670_d1_conf);
gpio ov7670_d2(ov7670_d2_conf);
gpio ov7670_d3(ov7670_d3_conf);
gpio ov7670_d4(ov7670_d4_conf);
gpio ov7670_d5(ov7670_d5_conf);
gpio ov7670_d6(ov7670_d6_conf);
gpio ov7670_d7(ov7670_d7_conf);

gpio button_pin(button_conf);

} // namespace bsp