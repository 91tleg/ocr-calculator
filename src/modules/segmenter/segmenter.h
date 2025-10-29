#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <cstdint>
#include "../../common/include/image.h"
#include "../../common/include/bounding_box.h"

class segmenter
{
public:
    segmenter(const image& img);
    uint8_t segment();
    const bounding_box* get_characters() const;

private:
    const image& _img;
    static constexpr uint8_t max_symbols = 15U;
    static constexpr uint16_t stack_size = 512U;
    bounding_box _boxes[max_symbols];
    bool _visited[image::height][image::width];
    void flood_fill(int16_t start_x, int16_t start_y, bounding_box& box);
};

#endif // SEGMENTATION_H