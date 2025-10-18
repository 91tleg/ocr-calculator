#ifndef SYSTICK_BASE_H
#define SYSTICK_BASE_H

#include <cstdint>

namespace sys {

class systick_base
{
public:
    virtual uint32_t millis() const = 0;
    virtual void delay_ms(uint32_t ms) const = 0;
    virtual ~systick_base() = default;
};

} // namespace sys

#endif // SYSTICK_BASE_H