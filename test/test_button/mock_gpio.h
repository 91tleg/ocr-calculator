#ifndef MOCK_GPIO_H
#define MOCK_GPIO_H

#include <gmock/gmock.h>
#include "../src/drivers/gpio/gpio_base.h"
#include "../src/drivers/gpio/gpio_types.h"

namespace test {

class mock_gpio : public drv::gpio_base
{
public:
    MOCK_METHOD(void, init, (), (override));
    MOCK_METHOD(void, set, (), (override));
    MOCK_METHOD(void, clear, (), (override));
    MOCK_METHOD(bool, read, (), (const, override));
};

} // namespace test

#endif // MOCK_GPIO_H