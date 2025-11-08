#ifndef BUTTON_CONTROLLER_H
#define BUTTON_CONTROLLER_H

#include "modules/button/button.h"

class button_controller
{
public:
    button_controller(button& capture_btn, button& cancel_btn);
    void tick();
    bool capture_requested();
    bool cancel_requested();

private:
    button& _capture_btn;
    button& _cancel_btn;
    bool _capture_requested;
    bool _cancel_requested;
};

#endif // BUTTON_CONTROLLER_H