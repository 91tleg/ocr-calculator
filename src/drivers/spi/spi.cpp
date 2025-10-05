#include "spi.h"
#include "../gpio/gpio.h"
#include "stm32h7xx.h"
#include "../boards/board.h"

static void spi_gpio_init(void)
{
    // Enable GPIOA clock
    gpio_init(SPI_SCK_PORT, SPI_SCK_PIN);
    gpio_init(SPI_MOSI_PORT, SPI_MOSI_PIN);
    gpio_init(SPI_MISO_PORT, SPI_MISO_PIN);

    // SCK
    SPI_SCK_PORT->MODER   &= ~(3U << (SPI_SCK_PIN * 2));
    SPI_SCK_PORT->MODER   |=  (2U << (SPI_SCK_PIN * 2)); // AF
    SPI_SCK_PORT->OSPEEDR |=  (3U << (SPI_SCK_PIN * 2));
    SPI_SCK_PORT->OTYPER  &= ~(1U << SPI_SCK_PIN);
    SPI_SCK_PORT->PUPDR   &= ~(3U << (SPI_SCK_PIN * 2));
    SPI_SCK_PORT->AFR[0]  &= ~(0xFU << (SPI_SCK_PIN * 4));
    SPI_SCK_PORT->AFR[0]  |=  (SPI_AF << (SPI_SCK_PIN * 4));

    // MOSI
    SPI_MOSI_PORT->MODER   &= ~(3U << (SPI_MOSI_PIN * 2));
    SPI_MOSI_PORT->MODER   |=  (2U << (SPI_MOSI_PIN * 2)); 
    SPI_MOSI_PORT->OSPEEDR |=  (3U << (SPI_MOSI_PIN * 2));
    SPI_MOSI_PORT->OTYPER  &= ~(1U << SPI_MOSI_PIN);
    SPI_MOSI_PORT->PUPDR   &= ~(3U << (SPI_MOSI_PIN * 2));
    SPI_MOSI_PORT->AFR[0]  &= ~(0xFU << (SPI_MOSI_PIN * 4));
    SPI_MOSI_PORT->AFR[0]  |=  (SPI_AF << (SPI_MOSI_PIN * 4));

    // MISO (optional, if needed)
    SPI_MISO_PORT->MODER   &= ~(3U << (SPI_MISO_PIN * 2));
    SPI_MISO_PORT->MODER   |=  (2U << (SPI_MISO_PIN * 2));
    SPI_MISO_PORT->PUPDR   &= ~(3U << (SPI_MISO_PIN * 2));
    SPI_MISO_PORT->AFR[0]  &= ~(0xFU << (SPI_MISO_PIN * 4));
    SPI_MISO_PORT->AFR[0]  |=  (SPI_AF << (SPI_MISO_PIN * 4));
}

static int spi_wait_flag(uint32_t flag, uint32_t value)
{
    int timeout = SPI_TIMEOUT;
    while (((SPI_INSTANCE->SR & flag) ? 1U : 0U) != value)
    {
        if (--timeout == 0) { return -1; }
    }
    return 0;
}

void spi_init(void)
{
    spi_gpio_init();

    // Enable SPI1 clock
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    // Reset SPI1
    RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;
    RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST;

    // Disable SPI before config
    SPI_INSTANCE->CR1 &= ~SPI_CR1_SPE;

    // Configure SPI
    SPI_INSTANCE->CFG1 =
        (3U << SPI_CFG1_MBR_Pos) |        // Baud prescaler /8
        (7U << SPI_CFG1_DSIZE_Pos);       // 8-bit data

    SPI_INSTANCE->CFG2 =
        SPI_CFG2_MASTER |                 // Master
        SPI_CFG2_COMM_0 |                 // Full duplex
        SPI_CFG2_MSSI;                    // Internal SS input

    // Enable SPI
    SPI_INSTANCE->CR1 |= SPI_CR1_SPE;
}

uint8_t spi_write(uint8_t data)
{
    if (spi_wait_flag(SPI_SR_TXP, 1) < 0) { return -1; }
    *((__IO uint8_t *)&SPI_INSTANCE->TXDR) = data;

    if (spi_wait_flag(SPI_SR_EOT, 1) < 0) { return -1; }
    SPI_INSTANCE->IFCR = SPI_IFCR_EOTC;
    return 0;
}

uint8_t spi_write_buffer(const uint8_t *buf, uint32_t len)
{
    if (!buf) { return -1; }

    for (uint32_t i = 0; i < len; i++)
    {
        if (spi_write(buf[i]) < 0) { return -1; }
    }
    return 0;
}