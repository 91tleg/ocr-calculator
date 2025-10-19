#include "iwdg.h"
#include "stm32h7xx.h"

namespace drv {

iwdg::iwdg(uint32_t timeout_ms) : _timeout_ms(timeout_ms) {}

void iwdg::init()
{
    constexpr uint32_t lsi_freq_hz = 32000UL;
    constexpr uint8_t prescaler_div = 32U;
    uint32_t reload = (_timeout_ms * lsi_freq_hz) /
                      (static_cast<uint32_t>(prescaler_div) * 1000UL);

    if (reload > IWDG_RLR_RL) {
        reload = IWDG_RLR_RL;
    }

    IWDG1->KR = IWDG_KEY_WRITE_ACCESS_ENABLE;
    IWDG1->PR = IWDG_PRESCALER_32;
    IWDG1->RLR = reload;
    IWDG1->KR = IWDG_KEY_RELOAD;
    IWDG1->KR = IWDG_KEY_ENABLE;
}

void iwdg::reset()
{
    IWDG1->KR = IWDG_KEY_RELOAD;
}

} // namespace drv