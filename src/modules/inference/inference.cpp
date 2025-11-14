#include "inference.h"
#include "model.h"

inference::inference() { setup_interpreter(); }

int8_t inference::predict(const uint8_t *input_image)
{
    for (uint16_t i = 0; i < _input_size; ++i) {
        _input->data.uint8[i] = input_image[i];
    }

    TfLiteStatus status = _interpreter->Invoke(); 
    if (status != kTfLiteOk) {
        return -1;
    }

    int8_t max_index = 0;
    float max_score = 0.f;
    for (int8_t i = 0; i < _num_classes; ++i) {
        float score =
            static_cast<float>(_output->data.int8[i] - _output->params.zero_point) * _output->params.scale;
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
    _resolver.AddQuantize();
    _resolver.AddDequantize();

    static tflite::MicroInterpreter static_interpreter(
        model, _resolver, _tensor_arena, _tensor_arena_size);
    _interpreter = &static_interpreter;

    TfLiteStatus allocate_status = _interpreter->AllocateTensors();
    if (allocate_status != kTfLiteOk) {
        return;
    }

    _input = _interpreter->input(0);
    _output = _interpreter->output(0);
}