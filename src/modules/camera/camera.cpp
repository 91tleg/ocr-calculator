#include "camera.h"

camera::camera(drv::camera_base& camera, uint16_t frame_size) 
    : _camera(camera), _frame_size(frame_size) {}

void camera::init()
{
    _camera.init();
}

bool camera::capture(uint8_t* buffer, uint16_t size)
{
    if (!buffer || size < _frame_size) {
        return false;
    }
    return _camera.capture(buffer, sizeof(buffer));
}