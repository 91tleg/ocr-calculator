#include <gtest/gtest.h>
#include "../src/modules/button/button.h"
#include "mock_gpio.h"

using namespace test;

TEST(ButtonTest, InitCallsGpioInit) {
    mock_gpio gpio;
    button btn(gpio);

    EXPECT_CALL(gpio, init())
        .Times(1);

    btn.init();
}

TEST(ButtonTest, PressAndRelease) {
    mock_gpio gpio;
    button btn(gpio);

    EXPECT_CALL(gpio, init());
    btn.init();

    EXPECT_CALL(gpio, read())
        .WillOnce(::testing::Return(false));
    btn.update();
    EXPECT_TRUE(btn.is_pressed());

    // Still pressed
    EXPECT_CALL(gpio, read())
        .WillOnce(::testing::Return(false));
    btn.update();
    EXPECT_TRUE(btn.is_pressed());

    // Released
    EXPECT_CALL(gpio, read())
        .WillOnce(::testing::Return(true));
    btn.update();
    EXPECT_FALSE(btn.is_pressed());
}

TEST(ButtonTest, PressEventTriggersOnce) {
    mock_gpio gpio;
    button btn(gpio);
    btn.init();

    // First press
    EXPECT_CALL(gpio, read())
        .WillOnce(::testing::Return(false));
    btn.update();
    EXPECT_TRUE(btn.is_pressed());

    EXPECT_CALL(gpio, read())
        .WillOnce(::testing::Return(false));
    btn.update();
    EXPECT_TRUE(btn.is_pressed());

    // Release
    EXPECT_CALL(gpio, read())
        .WillOnce(::testing::Return(true));
    btn.update();
    EXPECT_FALSE(btn.is_pressed());
}