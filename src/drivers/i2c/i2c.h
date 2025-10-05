#ifndef I2C_H
#define I2C_H

#include <cstdint>

void i2c_init(void);
int8_t i2c_write_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t data);
int8_t i2c_read_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data);

#endif // I2C_H