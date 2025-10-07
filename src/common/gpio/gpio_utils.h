#ifndef GPIO_UTILS_H
#define GPIO_UTILS_H

#include <cstdint>

constexpr uint32_t PIN_MASK(uint16_t pin)
{
    return static_cast<uint32_t>(1U << pin);
}

constexpr uint32_t PIN_RESET_MASK(uint16_t pin)
{
    return PIN_MASK(pin) << 16U;
}

#define GPIO_SET_MODE(port, pin, mode)              \
    do {                                            \
        (port)->MODER &= ~(3U << ((pin) * 2));      \
        (port)->MODER |=  ((mode) << ((pin) * 2));  \
    } while (0)

#define GPIO_SET_AF(port, pin, af)                                  \
    do {                                                            \
        (port)->AFR[((pin) >> 3)] &= ~(0xFU << (((pin) & 7U) * 4)); \
        (port)->AFR[((pin) >> 3)] |=  ((af) << (((pin) & 7U) * 4)); \
    } while (0)

#define GPIO_SET_OTYPE_OD(port, pin)  \
    ((port)->OTYPER |= (1U << (pin)))

#define GPIO_SET_OTYPE_PP(port, pin)      \
    ( (port)->OTYPER &= ~(1U << (pin)) )

#define GPIO_SET_PUPD_NONE(port, pin)           \
    ( (port)->PUPDR  &= ~(3U << ((pin) * 2)) )

#define GPIO_SET_PUPD_UP(port, pin)             \
    do {                                        \
        (port)->PUPDR &= ~(3U << ((pin) * 2));  \
        (port)->PUPDR |=  (1U << ((pin) * 2));  \
    } while (0)

#define GPIO_SET_PUPD_DOWN(port, pin)           \
    do {                                        \
        (port)->PUPDR &= ~(3U << ((pin) * 2));  \
        (port)->PUPDR |=  (2U << ((pin) * 2));  \
    } while (0)

#define GPIO_SET_SPEED_HIGH(port, pin)          \
    ( (port)->OSPEEDR |= (3U << ((pin) * 2)) )

#endif // GPIO_UTILS_H