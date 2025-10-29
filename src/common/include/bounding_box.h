#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <cstdint>

struct bounding_box
{
    int16_t x0;
    int16_t y0;
    int16_t x1;
    int16_t y1;
    bool valid = false;
};

#endif // BOUNDING_BOX_H 