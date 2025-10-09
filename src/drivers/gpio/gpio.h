#ifndef GPIO_H
#define GPIO_H

#include <cstdint>
#include "stm32h7xx.h"

namespace drv {

class gpio {
public:
    gpio(GPIO_TypeDef* port, uint8_t pin);
    void init(pin_utils::gpio_mode mode) const;
    void set()   const;
    void clear() const;
    bool read()  const;
    GPIO_TypeDef* port() const;
    uint8_t pin() const;

private:
    GPIO_TypeDef* const _port;
    const uint8_t _pin;
};

} // namespace drv

#endif // GPIO_H