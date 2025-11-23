#ifndef BSP_IWDG_H
#define BSP_IWDG_H 

#include <cstdint>

namespace bsp::wdt {

inline constexpr uint32_t timeout_ms = 1000;

} // namespace bsp::wdt

#endif // BSP_IWDG_H