#ifndef BOARD_H
#define BOARD_H

#if defined(STM32H7XX)
#include "stm32h753/ili9341.h"
#include "stm32h753/ov7670.h"
#include "common/systick/systick.h"
#else
#error "board no found"
#endif

namespace board {

void board_init()
{
    sys::systick::init(1000);
    lcd.init();
    cam.init();
}

} // namespace board

#endif // BOARD_H