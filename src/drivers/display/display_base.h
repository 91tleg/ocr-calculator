#ifndef DISPLAY_BASE_H
#define DISPLAY_BASE_H

#include <cstdint>

namespace drv {

class display_base
{
public:
    virtual void init() = 0;
    virtual void fill_screen(uint16_t color) = 0;
    virtual void draw_pixel(uint16_t x, uint16_t y, uint16_t color) = 0;
    virtual ~display_base() = default;
};

} //namespace drv

#endif // DISPLAY_BASE_H