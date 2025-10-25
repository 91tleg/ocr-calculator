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

enum class gpio_pupd : uint8_t {
    none      = 0U,
    pull_up   = 1U,
    pull_down = 2U
};

enum class gpio_output_type : uint8_t {
    push_pull  = 0U,
    open_drain = 1U,
    none       = 2U
};

enum class gpio_speed : uint8_t {
    low       = 0U,
    medium    = 1U,
    high      = 2U,
    very_high = 3U
};

enum class gpio_state : uint8_t {
    low  = 0U,
    high = 1U
};

} // namespace drv

#endif // GPIO_TYPES_H