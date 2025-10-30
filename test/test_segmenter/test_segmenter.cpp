#include <gtest/gtest.h>
#include "../src/modules/segmenter/segmenter.h"
#include "../src/common/include/image.h"

TEST(SegmenterTest, FindsSingleComponent)
{
    image img;
    img.clear();

    img.set_pixel(2, 2, 1);
    img.set_pixel(2, 3, 1);
    img.set_pixel(3, 3, 1);

    segmenter seg(img);
    uint8_t count = seg.segment();

    EXPECT_EQ(count, 1);
    const bounding_box* boxes = seg.get_characters();
    EXPECT_TRUE(boxes[0].valid);
    EXPECT_EQ(boxes[0].x0, 2);
    EXPECT_EQ(boxes[0].y0, 2);
    EXPECT_EQ(boxes[0].x1, 3);
    EXPECT_EQ(boxes[0].y1, 3);
}

TEST(SegmenterTest, FindsTwoSeparateBlobs)
{
    image img;
    img.clear();

    // First blob
    img.set_pixel(1, 1, 1);
    img.set_pixel(1, 2, 1);

    // Second blob
    img.set_pixel(6, 4, 1);
    img.set_pixel(7, 4, 1);

    segmenter seg(img);
    uint8_t count = seg.segment();

    EXPECT_EQ(count, 2);
    const bounding_box* boxes = seg.get_characters();
    EXPECT_TRUE(boxes[0].valid);
    EXPECT_TRUE(boxes[1].valid);
}

TEST(SegmenterTest, HandlesEmptyImage)
{
    image img;
    img.clear();

    segmenter seg(img);
    uint8_t count = seg.segment();
    EXPECT_EQ(count, 0);
}

TEST(SegmenterTest, BoundingBoxesStayWithinBounds)
{
    image img;
    img.clear();

    img.set_pixel(0, 0, 1);
    img.set_pixel(image::width - 1, image::height - 1, 1);

    segmenter seg(img);
    uint8_t count = seg.segment();

    EXPECT_GE(count, 1);
    const bounding_box* boxes = seg.get_characters();
    for (int i = 0; i < count; ++i) {
        EXPECT_GE(boxes[i].x0, 0);
        EXPECT_GE(boxes[i].y0, 0);
        EXPECT_LT(boxes[i].x1, image::width);
        EXPECT_LT(boxes[i].y1, image::height);
    }
}