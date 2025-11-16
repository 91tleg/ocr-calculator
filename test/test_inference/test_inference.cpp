#include <gtest/gtest.h>
#include "sample_image.h"
#include "../src/modules/inference/inference.h"
#include "tensorflow/lite/micro/system_setup.h"

TEST(InferenceTest, PredictsCorrectDigit)
{
    tflite::InitializeTarget();

    static inference infer{};

    int8_t prediction = infer.predict(image);

    EXPECT_EQ(prediction, 5) << "Model did not predict the expected digit 5.";
}