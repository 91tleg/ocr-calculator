#ifndef INFERENCE_H
#define INFERENCE_H

#include <cstdint>
#include "tensorflow/lite/micro/micro_log.h"
#include "tensorflow/lite/micro/system_setup.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"

/**
 * @class inference
 * @brief A class for running inference using TensorFlow Lite Micro.
 *
 * This class handles the setup and execution of a TensorFlow Lite Micro model
 * for image classification.
 */
class inference
{
public:
    /**
     * @brief Constructor.
     *
     * Initializes the tflm interpreter and sets up the model for inference.
     */
    inference();

    /**
     * @brief Runs inference on the given input image.
     *
     * @param input_image Pointer to the input image data (grayscale, 28x28 pixels).
     * @return int8_t The predicted class index (-1 if error).
     */
    int8_t predict(const uint8_t *input_image);

private:
    static constexpr uint16_t _input_size = 28 * 28;
    static constexpr int8_t _num_classes = 10;
    static constexpr uint16_t _tensor_arena_size = 10 * 1024;
    uint8_t _tensor_arena[_tensor_arena_size];

    tflite::MicroInterpreter *_interpreter;
    TfLiteTensor *_input = nullptr;
    TfLiteTensor *_output = nullptr;
    tflite::MicroMutableOpResolver<5> _resolver;

    /**
     * @brief Sets up the tflm interpreter.
     *
     * Initializes the tflm interpreter and sets up the model for inference.
     */
    void setup_interpreter();
};

#endif // INFERENCE_H