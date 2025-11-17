#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include <cstring>

/**
 * @class image
 * @brief Simple bit-packed black-and-white image.
 * Each pixel is stored as a single bit.
 */
class image
{
public:
    static constexpr uint16_t width  = 160;
    static constexpr uint16_t height = 120;
    static constexpr uint8_t max_symbols = 20;

    image() { clear(); }

    /** Clear all pixels to 0 or 1 */
    void clear(bool value = false)
    {
        std::memset(_data, value ? 0xFF : 0x00, sizeof(_data));
    }

    /** Get pixel value at (x, y) */
    bool pixel(uint16_t x, uint16_t y) const
    {
        uint32_t idx = y * width + x;
        return (_data[idx >> 3U] >> (idx & 7U)) & 1U;
    }

    /** Set pixel value at (x, y) */
    void set_pixel(uint16_t x, uint16_t y, bool value)
    {
        uint32_t idx = y * width + x;
        if(value) {
            _data[idx >> 3U] |= (1U << (idx & 7U));
        } else {
            _data[idx >> 3U] &= ~(1U << (idx & 7U));
        }
    }

    uint8_t* data() { return _data; }
    const uint8_t* data() const { return _data; }

private:
    uint8_t _data[(width * height + 7) / 8] = {0};
};

#endif // IMAGE_H
