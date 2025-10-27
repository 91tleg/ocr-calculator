#include "mock_camera.h"
#include "../src/modules/camera/camera.h"
#include <gtest/gtest.h>

using namespace test;

TEST(CameraTest, Init_DelegatesToUnderlyingCamera)
{
    mock_camera mock_cam;
    camera cam(mock_cam, 160);

    EXPECT_CALL(mock_cam, init()).Times(1);
    cam.init();
}

TEST(CameraTest, Capture_ReturnsFalse_WhenBufferIsNull)
{
    mock_camera mock_cam;
    camera cam(mock_cam, 160);
    EXPECT_FALSE(cam.capture(nullptr, 160));
}

TEST(CameraTest, Capture_ReturnsFalse_WhenBufferTooSmall)
{
    mock_camera mock_cam;
    camera cam(mock_cam, 160);
    uint8_t buf[100];
    EXPECT_FALSE(cam.capture(buf, 100));
}

TEST(CameraTest, Capture_CallsUnderlyingDriver)
{
    mock_camera mock_cam;
    camera cam(mock_cam, 160);

    uint8_t buf[160];
    EXPECT_CALL(mock_cam, capture(testing::_, testing::_))
         .WillOnce(::testing::Return(true));

    EXPECT_TRUE(cam.capture(buf, sizeof(buf)));
}