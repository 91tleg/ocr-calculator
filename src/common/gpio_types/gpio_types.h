#ifndef GPIO_TYPES_H
#define GPIO_TYPES_H

#include <cstdint>

namespace drv {

enum class gpio_mode : uint8_t {
    input  = 0U,
    output = 1U,
    alt_fn = 2U,
    analog = 3U
};

} //namespace drv

#endif // GPIO_TYPES_H