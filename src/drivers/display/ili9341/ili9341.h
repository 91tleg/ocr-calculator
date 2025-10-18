#ifndef ILI9341_H
#define ILI9341_H

#include "ili9341_config.h"
#include "../display_base.h"
#include "../../spi/spi_base.h"
#include "../../../common/systick/systick_base.h"

namespace drv {

class ili9341 : public display_base
{
public:
    explicit ili9341(spi_base& spi, ili9341_config_t& config, sys::systick_base& time);
    void init() override;
    void fill_screen(uint16_t color) override;
    void draw_pixel(uint16_t x, uint16_t y, uint16_t color) override;
    void draw_image(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* pixels);

private:
    spi_base& _spi;
    ili9341_config_t& _config;
    sys::systick_base& _time;

    void gpio_init();
    inline void cs_low();
    inline void cs_high();
    inline void dc_low();
    inline void dc_high();
    inline void rst_low();
    inline void rst_high();
    inline void send_command(uint8_t cmd);
    inline void send_data(uint8_t data);
    inline void write_word(uint16_t value);
    void set_address_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
    void write_color_buffer(const uint16_t* colors, uint16_t count);
};

} // namespace drv

#endif // ILI9341_H