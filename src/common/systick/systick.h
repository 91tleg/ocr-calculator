#ifndef SYSTICK_H
#define SYSTICK_H

#include <cstdint>
#include "systick_base.h"

namespace sys {

class systick : public systick_base
{
public:
    void init(uint32_t tick_hz);
    uint32_t millis() const override;
    static void handler();
    void delay_ms(uint32_t ms) const override;

private:
    static volatile uint32_t _tick_count;
    static inline void wait_for_tick();
};

} // namespace sys

#endif // SYSTICK_H