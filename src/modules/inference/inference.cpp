#include "inference.h"
#include "model.h"
#include "common/log/log.h"

inference::inference() { setup_interpreter(); }

int8_t inference::predict(const uint8_t *input_image)
{
    for (uint16_t i = 0; i < _input_size; ++i) {
        _input->data.uint8[i] = input_image[i];
    }

    TfLiteStatus status = _interpreter->Invoke(); 
    if (status != kTfLiteOk) {
        sys::log::error("Invoke failed: %d", status);
        return -1;
    }

    int8_t max_index = 0;
    float max_score = 0.f;
    for (int8_t i = 0; i < _num_classes; ++i) {
        float score = _output->data.f[i];
        if (score > max_score) {
            max_score = score;
            max_index = i;
        }
    }
    return max_index;
}

void inference::setup_interpreter()
{
    const tflite::Model *model = tflite::GetModel(ocr_model);

    _resolver.AddFullyConnected();
    _resolver.AddRelu();
    _resolver.AddSoftmax();

    static tflite::MicroInterpreter static_interpreter(
        model, _resolver, _tensor_arena, _tensor_arena_size);
    _interpreter = &static_interpreter;

    TfLiteStatus status = _interpreter->AllocateTensors(); 
    if (status != kTfLiteOk) {
        sys::log::error("Tensor allocation failed: %d", status);
        return;
    }

    _input = _interpreter->input(0);
    _output = _interpreter->output(0);
}