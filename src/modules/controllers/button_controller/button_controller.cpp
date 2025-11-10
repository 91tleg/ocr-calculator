#include "button_controller.h"

button_controller::button_controller(button &capture_btn, button &cancel_btn)
    : _capture_btn(capture_btn), _cancel_btn(cancel_btn),
      _capture_requested(false), _cancel_requested(false) {}

void button_controller::tick()
{
    _capture_btn.update();
    _cancel_btn.update();

    // Capture event: pressed and released
    if (_capture_btn.is_pressed() && !_capture_requested) {
        _capture_requested = true;
    }

    // Cancel event
    if (_cancel_btn.is_pressed() && !_cancel_requested) {
        _cancel_requested = true;
    }
}

bool button_controller::capture_requested()
{
    if (_capture_requested) {
        _capture_requested = false;
        return true;
    }
    return false;
}

bool button_controller::cancel_requested()
{
    if (_cancel_requested) {
        _cancel_requested = false;
        return true;
    }
    return false;
}