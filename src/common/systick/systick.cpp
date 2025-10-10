#include "systick.h"
#include "stm32h7xx.h"

namespace sys {

volatile uint32_t sys::systick::_tick_count = 0U;

void systick::init(uint32_t tick_hz)
{
    uint32_t reload = SystemCoreClock / tick_hz;

    SysTick->LOAD = reload - 1U;
    SysTick->VAL = 0U;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk |
                    SysTick_CTRL_ENABLE_Msk;
}

uint32_t systick::millis()
{
    return _tick_count;
}

void systick::handler()
{
    ++_tick_count;
}

void systick::wait_for_tick()
{
    __asm__ volatile("wfi");
}

void systick::delay_ms(uint32_t ms)
{
    const uint32_t start = millis();
    while ((millis() - start) < ms) {
        wait_for_tick();
    }
}

} // namespace sys

extern "C" void SysTick_Handler(void)
{
    sys::systick::handler();
}