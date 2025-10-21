#ifndef CAMERA_BASE_H
#define CAMERA_BASE_H

#include <cstdint>

namespace drv {

class camera_base
{
public:
    virtual void init() = 0;
    virtual bool capture(uint8_t* buffer, uint32_t buf_size) = 0;
    virtual ~camera_base() = default;
};

} // namespace drv

#endif // CAMERA_BASE_H