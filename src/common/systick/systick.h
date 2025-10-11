#ifndef SYSTICK_H
#define SYSTICK_H

#include <cstdint>

namespace sys {

class systick
{
public:
    static void init(uint32_t tick_hz);
    static uint32_t millis();
    static void handler();
    static void wait_for_tick();
    static void delay_ms(uint32_t ms);

private:
    static volatile uint32_t _tick_count;
};

} // namespace sys

#endif // SYSTICK_H