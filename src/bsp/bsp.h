#ifndef BSP_H
#define BSP_H

#if defined(STM32H753xx)
#include "stm32h7xx_nucleo/stm32h7xx_nucleo.h"
#else 
#error "board no found"
#endif

#endif // BSP_H