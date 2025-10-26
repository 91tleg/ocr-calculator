#ifndef MOCK_CAMERA_H
#define MOCK_CAMERA_H

#include <gmock/gmock.h>
#include "../src/drivers/camera/camera_base.h"

namespace test {

class mock_camera : public drv::camera_base {
public:
    MOCK_METHOD(void, init, (), (override));
    MOCK_METHOD(bool, capture, (uint8_t* buffer, uint32_t size), (override));
};

} // namespace test

#endif // MOCK_CAMERA_H