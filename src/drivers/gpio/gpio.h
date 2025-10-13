#ifndef GPIO_H
#define GPIO_H

#include <cstdint>
#include "stm32h7xx.h"
#include "../../common/gpio_types/gpio_types.h"
#include "gpio_config.h"

namespace drv {

class gpio {
public:
    explicit gpio(gpio_config_t& config);
    void init(gpio_mode mode);
    void set();
    void clear();
    bool read()  const;
    GPIO_TypeDef* port() const;
    uint8_t pin() const;

private:
    gpio_config_t _config;
};

} // namespace drv

#endif // GPIO_H