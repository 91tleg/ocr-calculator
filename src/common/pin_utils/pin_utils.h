#ifndef PIN_UTILS_H
#define PIN_UTILS_H 

#include <cstdint>
#include "stm32h7xx.h"

namespace pin_utils
{

enum class gpio_mode : uint8_t {
    input  = 0U,
    output = 1U,
    alt_fn = 2U,
    analog = 3U
};

constexpr uint32_t pin_mask(uint16_t pin) {
    return 1UL << pin;
}

constexpr uint32_t pin_reset_mask(uint16_t pin) {
    return 1UL << (pin + 16U);
}

inline void write(GPIO_TypeDef* port, uint8_t pin, bool high) {
    port->BSRR = high ? pin_mask(pin) : pin_reset_mask(pin);
}

inline void set_mode(GPIO_TypeDef* port, uint8_t pin, gpio_mode mode) {
    port->MODER = (port->MODER & ~(3UL << (pin * 2U))) |
                  ((static_cast<uint8_t>(mode) & 3U) << (pin * 2U));
}

inline void set_alternate_function(GPIO_TypeDef* port, uint8_t pin, uint8_t af) {
    const uint8_t index = pin >> 3U;
    const uint8_t shift = (pin & 7U) * 4U;
    port->AFR[index] = (port->AFR[index] & ~(0xFUL << shift)) |
                       ((af & 0xFUL) << shift);
}

inline void set_output_open_drain(GPIO_TypeDef* port, uint8_t pin) {
    port->OTYPER |= (1UL << pin);
}

inline void set_output_push_pull(GPIO_TypeDef* port, uint8_t pin) {
    port->OTYPER &= ~(1UL << pin);
}

inline void set_pupd_none(GPIO_TypeDef* port, uint8_t pin) {
    port->PUPDR &= ~(3UL << (pin * 2U));
}

inline void set_pupd_up(GPIO_TypeDef* port, uint8_t pin) {
    port->PUPDR = (port->PUPDR & ~(3UL << (pin * 2U))) |
                  (1UL << (pin * 2U));
}

inline void set_pupd_down(GPIO_TypeDef* port, uint8_t pin) {
    port->PUPDR = (port->PUPDR & ~(3UL << (pin * 2U))) |
                  (2UL << (pin * 2U));
}

inline void set_speed_high(GPIO_TypeDef* port, uint8_t pin) {
    port->OSPEEDR |= (3UL << (pin * 2U));
}

inline void enable_clock(GPIO_TypeDef* port) {
    if (port == GPIOA) RCC->AHB4ENR |= RCC_AHB4ENR_GPIOAEN;
    else if (port == GPIOB) RCC->AHB4ENR |= RCC_AHB4ENR_GPIOBEN;
    else if (port == GPIOC) RCC->AHB4ENR |= RCC_AHB4ENR_GPIOCEN;
    __DSB();
}

} // namespace pin_utils

#endif // PIN_UTILS_H