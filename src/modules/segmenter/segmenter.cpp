#include "segmenter.h"

segmenter::segmenter(const image& img) : _img(img) {}

uint8_t segmenter::segment()
{
    uint8_t count = 0;

    for (int16_t y = 0; y < image::height; ++y) {
        for (int16_t x = 0; x < image::width; ++x) {
            if (_img.pixel(x, y) == 1 && !_visited[y][x] && count < max_symbols) {
                bounding_box box;
                box.x0 = box.x1 = x;
                box.y0 = box.y1 = y;
                box.valid = true;

                flood_fill(x, y, box);
                _boxes[count++] = box;
            }
        }
    }

    return count;
}

const bounding_box* segmenter::get_characters() const
{
    return _boxes;
}

void segmenter::flood_fill(int16_t start_x, int16_t start_y, bounding_box& box)
{
    struct point {
        int16_t x;
        int16_t y;
    };
    point stack[stack_size];
    int16_t sp = 0;

    stack[sp++] = {start_x, start_y};

    while (sp > 0) {
        point p = stack[--sp];

        if (p.x < 0 || p.x >= image::width || p.y < 0 || p.y >= image::height) {
            continue;
        }
        if (_visited[p.y][p.x] || _img.pixel(p.x, p.y) == 0) {
            continue;
        }

        _visited[p.y][p.x] = true;

        if (p.x < box.x0) { box.x0 = p.x; }
        if (p.y < box.y0) { box.y0 = p.y; }
        if (p.x > box.x1) { box.x1 = p.x; }
        if (p.y > box.y1) { box.y1 = p.y; }

        if (sp + 4 < stack_size) {
            stack[sp++] = {static_cast<int16_t>(p.x + 1), p.y};
            stack[sp++] = {static_cast<int16_t>(p.x - 1), p.y};
            stack[sp++] = {p.x, static_cast<int16_t>(p.y + 1)};
            stack[sp++] = {p.x, static_cast<int16_t>(p.y - 1)};
        }
    }
}