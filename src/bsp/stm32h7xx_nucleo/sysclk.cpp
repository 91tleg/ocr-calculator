#include <cstdint>
#include "stm32h753xx.h"

namespace bsp {

uint32_t SystemCoreClock = 64000000;  // 64 MHz

void sysclk_config(void)
{
    RCC->CR |= RCC_CR_HSION; // Enable HSI
    while ((RCC->CR & RCC_CR_HSIRDY) == 0) {}

    RCC->CFGR &= ~RCC_CFGR_SW;           // Clear SW bits
    RCC->CFGR |= RCC_CFGR_SW_HSI;        // Select HSI

    // Wait until HSI is actually used as sysclk
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI) {}

    RCC->D1CFGR =
          RCC_D1CFGR_D1CPRE_DIV1    // CPU Clock = sysclk
        | RCC_D1CFGR_HPRE_DIV1      // AHB prescaler
        | RCC_D1CFGR_D1PPRE_DIV1;   // APB3

    RCC->D2CFGR =
          RCC_D2CFGR_D2PPRE1_DIV1   // APB1
        | RCC_D2CFGR_D2PPRE2_DIV1;  // APB2

    RCC->D3CFGR =
          RCC_D3CFGR_D3PPRE_DIV1;   // APB4

    SystemCoreClock = 400000000; // 400 MHz
}

} // namespace bsp