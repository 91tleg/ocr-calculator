#include "button.h"

button::button(drv::gpio_base& gpio)
    : _gpio(gpio), _state(state::released), _pressed_event(false) {}

void button::init()
{
    _gpio.init();
}

void button::update()
{
    const bool pressed_now = !_gpio.read();

    if (pressed_now && _state == state::released) {
        _pressed_event = true;
        _state = state::pressed;
    } 
    else if (!pressed_now && _state == state::pressed) {
        _state = state::released;
    }
}

bool button::is_pressed() const
{
    return _state == state::pressed;
}
