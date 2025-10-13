#ifndef STATUS_H
#define STATUS_H

#include <cstdint>

namespace drv {

enum class status_t : int8_t {
    ok = 0,
    timeout = -1,
    error = -2,
};

} // namespace drv

#endif // STATUS_H