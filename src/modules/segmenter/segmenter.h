#ifndef SEGMENTER_H
#define SEGMENTER_H

#include <cstdint>
#include "../../common/include/image.h"
#include "../../common/include/bounding_box.h"

/**
 * @class segmenter
 * @brief A class for splitting an image into symbols.
 * 
 * This class performs a flood-fill based segmentation on a binary image
 * and stores bounding boxes for each detected symbol.
 */
class segmenter
{
public:
    /**
     * @brief Constructor.
     * 
     * @param img The image to segment (binary image expected).
     */
    segmenter(const image& img);

    /**
     * @brief Perform segmentation on the image.
     * 
     * Iterates over all pixels, performs flood-fill, and fills
     * bounding boxes for each detected symbol.
     * 
     * @return uint8_t Number of symbols detected.
     */
    uint8_t segment();

    /**
     * @brief Get the array of detected symbols' bounding boxes.
     * 
     * @return const bounding_box* Pointer to the first bounding box.
     */
    const bounding_box* get_characters() const;

private:
    const image& _img;
    bounding_box _boxes[image::max_symbols];
    uint8_t _visited[(image::width * image::height + 7) / 8] = {0};
    static constexpr uint8_t _stack_size = 64;

    void flood_fill(int16_t start_x, int16_t start_y, bounding_box& box);

    /**
     * @brief Get the value of a bit in the _visited map.
     * 
     * @param x X-coordinate of the pixel.
     * @param y Y-coordinate of the pixel.
     * @return true Pixel has been visited.
     * @return false Pixel has not been visited.
     */
    inline bool get_bit(uint16_t x, uint16_t y) const;

    /**
     * @brief Set a pixel as visited in the _visited map.
     * 
     * @param x X-coordinate of the pixel.
     * @param y Y-coordinate of the pixel.
     */
    inline void set_bit(uint16_t x, uint16_t y);
};

#endif // SEGMENTER_H