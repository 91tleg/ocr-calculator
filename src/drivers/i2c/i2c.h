#ifndef I2C_H
#define I2C_H

#include <cstdint>
#include "i2c_config.h"
#include "i2c_base.h"

namespace drv {

class i2c : public i2c_base
{
public:
    /**
     * @brief Constructor
     * 
     * @param config I2C config struct
     */
    explicit i2c(i2c_config_t& config);

    /**
     * @brief Initialize the I2C according to the config
     */
    void init() override;

    /**
     * @brief Write a single byte to a register of a device on the I2C bus
     * 
     * @param dev_addr 7-bit I2C address of the target device
     * @param reg_addr Register address to write to
     * @param data     Byte of data to write
     * @return i2c_status_t Status of the operation (ok, timeout, error)
     */
    i2c_status_t write_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t data) override;

    /**
     * @brief Read a single byte from a register of a device on the I2C bus
     * 
     * @param dev_addr 7-bit I2C address of the target device
     * @param reg_addr Register address to read from
     * @param data     Pointer to store the read byte
     * @return i2c_status_t Status of the operation (ok, timeout, error)
     */
    i2c_status_t read_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t* data) override;

private:
    i2c_config_t _config;
    static constexpr uint16_t _timeout = 1000U;

    void init_gpio();
    i2c_status_t wait_flag(uint32_t flag, uint32_t value);
};

} // namespace drv

#endif // I2C_H