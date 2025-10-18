#include "ili9341.h"

namespace drv {

namespace config {
    constexpr uint16_t width          = 240U;
    constexpr uint16_t height         = 320U;
    constexpr uint32_t frame_size     = width * height;
    constexpr uint32_t reset_delay_ms = 100UL;
    constexpr uint32_t init_delay_ms  = 100UL;
} // namespace config

namespace cmd {
    constexpr uint8_t SWRESET  = 0x01U;
    constexpr uint8_t COLMOD   = 0x3AU;
    constexpr uint8_t MADCTL   = 0x36U;
    constexpr uint8_t DISP_ON  = 0x29U;
    constexpr uint8_t CASET    = 0x2AU;
    constexpr uint8_t RASET    = 0x2BU;
    constexpr uint8_t RAMWR    = 0x2CU;
} // namespace cmd

namespace color_mode {
    constexpr uint8_t RGB_16BIT = 0x55U;
} // namespace color_mode

namespace madctl {
    constexpr uint8_t MX  = 0x40U;
    constexpr uint8_t MY  = 0x80U;
    constexpr uint8_t MV  = 0x20U;
    constexpr uint8_t BGR = 0x08U;
    constexpr uint8_t ROTATION_0   = MX | BGR;
    constexpr uint8_t ROTATION_90  = MV | BGR;
    constexpr uint8_t ROTATION_180 = MY | BGR;
    constexpr uint8_t ROTATION_270 = MX | MY | MV | BGR;
} //namespace madctl

ili9341::ili9341(spi_base& spi, ili9341_config_t& config, sys::systick_base& time)
    : _spi(spi), _config(config), _time(time) {}

void ili9341::init()
{
    gpio_init();
    _spi.init();

    // Reset
    rst_low();
    _time.delay_ms(config::init_delay_ms);
    rst_high();
    _time.delay_ms(config::init_delay_ms);

    send_command(cmd::SWRESET);
    _time.delay_ms(config::reset_delay_ms);

    send_command(cmd::COLMOD);
    send_data(color_mode::RGB_16BIT);

    send_command(cmd::MADCTL);
    send_data(madctl::ROTATION_0);

    send_command(cmd::DISP_ON);
}

void ili9341::set_address_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    send_command(cmd::CASET);
    write_word(x0);
    write_word(x1);

    send_command(cmd::RASET);
    write_word(y0);
    write_word(y1);

    send_command(cmd::RAMWR);
}

void ili9341::fill_screen(uint16_t color)
{
    set_address_window(0, 0, config::width - 1, config::height - 1);

    static uint16_t line[config::width];
    for (uint16_t x = 0; x < config::width; ++x) {
        line[x] = color;
    }

    cs_low();
    dc_high();

    for (uint16_t y = 0; y < config::height; ++y) {
        write_color_buffer(line, config::width);
    }

    cs_high();
}

void ili9341::draw_pixel(uint16_t x, uint16_t y, uint16_t color)
{
    if (x >= config::width || y >= config::height) { return; }

    set_address_window(x, y, x, y);
    cs_low();
    dc_high();
    write_word(color);
    cs_high();
}

void ili9341::draw_image(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* pixels)
{
    if (x >= config::width || y >= config::height) { return; }
    if (x + w > config::width)  { w = config::width - x; }
    if (y + h > config::height) { h = config::height - y; }

    set_address_window(x, y, x + w - 1, y + h - 1);
    
    cs_low();
    dc_high();
    write_color_buffer(pixels, w * h);
    cs_high();
}

void ili9341::gpio_init()
{
    _config.cs.init();
    _config.dc.init();
    _config.rst.init();
    cs_high();
}

void ili9341::cs_low()
{ 
    _config.cs.clear();
}

void ili9341::cs_high()
{ 
    _config.cs.set();
}

void ili9341::dc_low() 
{ 
    _config.dc.clear();
}

void ili9341::dc_high()
{ 
    _config.dc.set();
}

void ili9341::rst_low()
{ 
    _config.rst.clear();
}

void ili9341::rst_high()
{ 
    _config.rst.set();
}

void ili9341::send_command(uint8_t cmd)
{
    cs_low();
    dc_low();
    _spi.write(cmd);
    cs_high();
}

void ili9341::send_data(uint8_t data)
{
    cs_low();
    dc_high();
    _spi.write(data);
    cs_high();
}

void ili9341::write_word(uint16_t value)
{
    _spi.write(static_cast<uint8_t>(value >> 8U));
    _spi.write(static_cast<uint8_t>(value & 0xFFU));
}

void ili9341::write_color_buffer(const uint16_t* colors, uint16_t count)
{
    uint8_t buffer[config::width * 2U];
    const uint8_t* src = reinterpret_cast<const uint8_t*>(colors);

    uint32_t total_bytes = static_cast<uint32_t>(count) * 2UL;
    uint32_t bytes_per_chunk = sizeof(buffer);
    uint32_t remaining = total_bytes;

    while (remaining > 0UL) {
        uint32_t chunk = (remaining > bytes_per_chunk) ? bytes_per_chunk : remaining;
        _spi.write_buffer(src, static_cast<uint16_t>(chunk));
        src += chunk;
        remaining -= chunk;
    }
}

} // namespace drv