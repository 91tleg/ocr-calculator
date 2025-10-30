#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>

class image
{
public:
    static constexpr uint8_t width  = 128U;
    static constexpr uint8_t height = 64U;

    image() { clear(); }

    void clear(uint8_t value = 0U)
    {
        for (uint8_t y = 0; y < height; ++y)
            for (uint8_t x = 0; x < width; ++x)
                _data[y][x] = value;
    }

    uint8_t pixel(uint8_t x, uint8_t y) const { return _data[y][x]; }

    void set_pixel(uint8_t x, uint8_t y, uint8_t value)
    {
        _data[y][x] = value;
    }

private:
    uint8_t _data[height][width];
};

#endif // IMAGE_H