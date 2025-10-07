#include "spi.h"
#include "../gpio/gpio.h"
#include "stm32h7xx.h"
#include "../boards/board.h"
#include "../../common/gpio/gpio_utils.h"

static void spi_gpio_init(void)
{
    // Enable GPIOA clock
    gpio_init(SPI_SCK_PORT, SPI_SCK_PIN, GPIO_MODE_AF);
    gpio_init(SPI_MOSI_PORT, SPI_MOSI_PIN, GPIO_MODE_AF);
    gpio_init(SPI_MISO_PORT, SPI_MISO_PIN, GPIO_MODE_AF);

    // SCK
    GPIO_SET_SPEED_HIGH(SPI_SCK_PORT, SPI_SCK_PIN);
    GPIO_SET_OTYPE_PP(SPI_SCK_PORT, SPI_SCK_PIN);
    GPIO_SET_PUPD_NONE(SPI_SCK_PORT, SPI_SCK_PIN);
    GPIO_SET_AF(SPI_SCK_PORT, SPI_SCK_PIN, SPI_AF);

    // MOSI
    GPIO_SET_SPEED_HIGH(SPI_MOSI_PORT, SPI_MOSI_PIN);
    GPIO_SET_OTYPE_PP(SPI_MOSI_PORT, SPI_MOSI_PIN);
    GPIO_SET_PUPD_NONE(SPI_MOSI_PORT, SPI_MOSI_PIN);
    GPIO_SET_AF(SPI_MOSI_PORT, SPI_MOSI_PIN, SPI_AF);

    // MISO
    GPIO_SET_PUPD_NONE(SPI_MISO_PORT, SPI_MISO_PIN);
    GPIO_SET_AF(SPI_MISO_PORT, SPI_MISO_PIN, SPI_AF);
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

int8_t spi_write(uint8_t data)
{
    if (spi_wait_flag(SPI_SR_TXP, 1) < 0) { return -1; }
    *((__IO uint8_t *)&SPI_INSTANCE->TXDR) = data;

    if (spi_wait_flag(SPI_SR_EOT, 1) < 0) { return -1; }
    SPI_INSTANCE->IFCR = SPI_IFCR_EOTC;
    return 0;
}

int8_t spi_write_buffer(const uint8_t *buf, uint32_t len)
{
    if (!buf) { return -1; }

    for (uint32_t i = 0; i < len; i++)
    {
        if (spi_write(buf[i]) < 0) { return -1; }
    }
    return 0;
}