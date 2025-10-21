#include "ov7670.h"
#include "../../../common/log/log.h"

namespace drv {

namespace config {
    constexpr uint8_t width           = 160U;
    constexpr uint8_t height          = 120U;
    constexpr uint16_t frame_size     = width * height;
    constexpr uint8_t device_addr     = 0x42U >> 1U;
    constexpr uint32_t i2c_timeout_ms = 100UL;
    constexpr uint32_t reset_delay_ms = 50UL;
} // namespace config

namespace reg {
    constexpr uint8_t COM7   = 0x12U;
    constexpr uint8_t CLKRC  = 0x11U;
    constexpr uint8_t TSLB   = 0x3AU;
    constexpr uint8_t COM15  = 0x40U;
    constexpr uint8_t HSTART = 0x17U;
    constexpr uint8_t HSTOP  = 0x18U;
    constexpr uint8_t VSTART = 0x19U;
    constexpr uint8_t VSTOP  = 0x1AU;
    constexpr uint8_t VREF   = 0x03U;
    constexpr uint8_t PID    = 0x0AU;
    constexpr uint8_t COM13  = 0x3DU;
} // namespace reg

namespace ctrl {
    constexpr uint8_t COM7_RESET        = 0x80U;
    constexpr uint8_t COM7_QVGA         = 0x10U;
    constexpr uint8_t COM7_YUV          = 0x00U;
    constexpr uint8_t COM7_Y8           = 0x10U;
    constexpr uint8_t COM15_Y8          = 0x00U;
    constexpr uint8_t COM15_RGB565      = 0x10U;
    constexpr uint8_t TSLB_NORMAL       = 0x04U;
    constexpr uint8_t AGC_AEC_AWB_EN    = 0xE0U;
    constexpr uint8_t PLL_4X            = 0x4AU;
    constexpr uint8_t CLK_PRESCALE_DIV2 = 0x01U;
    constexpr uint8_t HSTART_DEFAULT    = 0x16U;
    constexpr uint8_t HSTOP_DEFAULT     = 0x04U;
    constexpr uint8_t VSTART_DEFAULT    = 0x02U;
    constexpr uint8_t VSTOP_DEFAULT     = 0x7AU;
    constexpr uint8_t VREF_DEFAULT      = 0x0AU;
    constexpr uint8_t PID_EXPECTED      = 0x76U;
} // namespace ctrl

ov7670::ov7670(i2c_base& bus, ov7670_config_t& config, sys::systick_base& time)
    : _bus(bus), _config(config), _time(time) {}

void ov7670::init()
{
    _config.reset.clear();
    _time.delay_ms(config::reset_delay_ms);
    _config.reset.set();
    _time.delay_ms(config::reset_delay_ms);

    uint8_t pid = 0;
    read_reg(reg::PID, pid);
    if (pid != ctrl::PID_EXPECTED) {
        sys::log::error("Incorect pid: %d", pid);
        return;
    }

    write_reg(reg::COM7, ctrl::COM7_RESET);
    _time.delay_ms(config::reset_delay_ms);
    write_reg(reg::COM7, ctrl::COM7_QVGA | ctrl::COM7_Y8);
    write_reg(reg::CLKRC, ctrl::CLK_PRESCALE_DIV2);
}

void ov7670::write_reg(uint8_t reg, uint8_t value)
{
    _bus.write_byte(config::device_addr, reg, value);
}

void ov7670::read_reg(uint8_t reg, uint8_t& value)
{
    _bus.read_byte(config::device_addr, reg, &value);
}

bool ov7670::capture(uint8_t* buffer, uint32_t buf_size)
{
    if (!buffer || buf_size < config::frame_size) {
        return false;
    }

    // Frame start
    while (!_config.vsync.read());
    while (_config.vsync.read());


    for (uint16_t y = 0; y < config::height; ++y) {
        // Line start
        while (!_config.href.read());

        for (uint16_t x = 0; x < config::width; ++x) {
            while (!_config.pclk.read());  // Rising edge
            buffer[y * config::width + x] = read_data_pins();
            while (_config.pclk.read());  // Falling edge
        }

        // Line end
        while (_config.href.read());
    }

    return true;
}

uint8_t ov7670::read_data_pins() const
{
    uint8_t value = 0;
    value |= (_config.d0.read() ? 1U << 0U : 0U);
    value |= (_config.d1.read() ? 1U << 1U : 0U);
    value |= (_config.d2.read() ? 1U << 2U : 0U);
    value |= (_config.d3.read() ? 1U << 3U : 0U);
    value |= (_config.d4.read() ? 1U << 4U : 0U);
    value |= (_config.d5.read() ? 1U << 5U : 0U);
    value |= (_config.d6.read() ? 1U << 6U : 0U);
    value |= (_config.d7.read() ? 1U << 7U : 0U);
    return value;
}

} // namespace drv