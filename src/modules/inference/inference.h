#ifndef INFERENCE_H
#define INFERENCE_H

#include <cstdint>
#include "tensorflow/lite/micro/micro_log.h"
#include "tensorflow/lite/micro/system_setup.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"

class inference
{
public:
    inference();
    int8_t predict(const uint8_t *input_image);

private:
    static constexpr uint16_t _input_size = 28 * 28;
    static constexpr int8_t _num_classes = 14;
    static constexpr uint16_t _tensor_arena_size = 10 * 1024;

    tflite::MicroInterpreter *_interpreter;
    TfLiteTensor *_input;
    TfLiteTensor *_output;
    uint8_t _tensor_arena[_tensor_arena_size];

    tflite::MicroMutableOpResolver<10> _resolver;

    void setup_interpreter();
};

#endif // INFERENCE_H