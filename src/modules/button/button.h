#ifndef BUTTON_H
#define BUTTON_H

#include <cstdint>
#include "../../drivers/gpio/gpio_base.h"

class button
{
public:
    enum class state : uint8_t {
        released = 0U,
        pressed  = 1U
    };

    explicit button(drv::gpio_base& gpio);

    void init();
    void update();
    bool is_pressed() const;

private:
    drv::gpio_base& _gpio;
    state _state;
    bool _pressed_event;
    
};

#endif // BUTTON_H