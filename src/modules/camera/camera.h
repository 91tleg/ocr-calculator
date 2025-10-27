#ifndef CAMERA_H
#define CAMERA_H

#include <cstdint>
#include "../../drivers/camera/camera_base.h"

class camera
{
public:
    explicit camera(drv::camera_base& camera, uint16_t frame_size);
    void init();
    bool capture(uint8_t* buffer, uint16_t size);

private:
    drv::camera_base& _camera;
    uint16_t _frame_size;
};

#endif // CAEMRA_H