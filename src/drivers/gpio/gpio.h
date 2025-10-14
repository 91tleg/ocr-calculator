#ifndef GPIO_H
#define GPIO_H

#include <cstdint>
#include "stm32h7xx.h"
#include "gpio_config.h"
#include "gpio_base.h"

namespace drv {

class gpio : public gpio_base
{
public:
    /**
     * @brief Constructor
     * 
     * @param config GPIO config struct
     */
    explicit gpio(gpio_config_t& config);

    /**
     * @brief Initialize the GPIO pin according to the config
     */
    void init() override;

    /**
     * @brief Set the GPIO pin high
     */
    void set() override;

    /**
     * @brief Set the GPIO pin low
     */
    void clear() override;

    /**
     * @brief Read the current state of the pin
     * 
     * @return true If pin is high, false if low
     */
    bool read() const override;

    /**
     * @brief Get the GPIO port of the pin
     * 
     * @return GPIO_TypeDef* to the port
     */
    GPIO_TypeDef* port() const;

    /**
     * @brief Get the pin number in the port
     * 
     * @return uint8_t Pin number
     */
    uint8_t pin() const;

private:
    gpio_config_t _config;
    static constexpr uint32_t pin_mask(uint8_t pin) { return 1UL << pin; }
    static constexpr uint32_t pin_reset_mask(uint8_t pin) { return ~(1UL << pin); }
    inline void write(bool high);
    inline void set_mode();
    inline void set_alternate_function();
    inline void set_output_type();
    inline void set_speed();
    inline void set_pupd();
    inline void enable_clock();
};

} // namespace drv

#endif // GPIO_H