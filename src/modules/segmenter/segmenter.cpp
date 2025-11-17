#include "segmenter.h"
#include <cstring>

segmenter::segmenter(const image& img) : _img(img) {}

uint8_t segmenter::segment()
{
    std::memset(_visited, 0, sizeof(_visited));
    uint8_t symbol_count = 0;

    for(uint8_t y = 0; y < image::height; ++y) {
        for(uint8_t x = 0; x < image::width; ++x) {
            if (!_img.pixel(x, y) || get_bit(x, y)) {
                continue;
            }

            if (symbol_count >= image::max_symbols) {
                return symbol_count;
            }

            bounding_box box {
                .x0 = x,
                .y0 = y,
                .x1 = x,
                .y1 = y,
                .valid = true
            };

            flood_fill(x, y, box);

            _boxes[symbol_count++] = box;
        }
    }

    return symbol_count;
}

const bounding_box* segmenter::get_characters() const
{
    return _boxes;
}

void segmenter::flood_fill(int16_t start_x, int16_t start_y, bounding_box& box)
{
    struct point { int16_t x; int16_t y; };

    point stack[_stack_size];
    int16_t sp = 0;

    stack[sp++] = { start_x, start_y };

    while (sp > 0) {
        point p = stack[--sp];

        if(p.x < 0 || p.x >= image::width || p.y < 0 || p.y >= image::height) {
            continue;
        }

        if(get_bit(p.x, p.y) || !_img.pixel(p.x, p.y)) {
            continue;
        }

        set_bit(p.x, p.y);

        if (p.x < box.x0) { box.x0 = p.x; }
        if (p.y < box.y0) { box.y0 = p.y; }
        if (p.x > box.x1) { box.x1 = p.x; }
        if (p.y > box.y1) { box.y1 = p.y; }

        if (sp + 4 < _stack_size) {
            stack[sp++] = {static_cast<int16_t>(p.x + 1), p.y};
            stack[sp++] = {static_cast<int16_t>(p.x - 1), p.y};
            stack[sp++] = {p.x, static_cast<int16_t>(p.y + 1)};
            stack[sp++] = {p.x, static_cast<int16_t>(p.y - 1)};
        }
    }
}

bool segmenter::get_bit(uint16_t x, uint16_t y) const
{
    uint32_t idx = y * image::width + x;
    return (_visited[idx >> 3U] >> (idx & 7U)) & 1U;
}

void segmenter::set_bit(uint16_t x, uint16_t y)
{
    uint32_t idx = y * image::width + x;
    _visited[idx >> 3U] |= (1U << (idx & 7U));
}