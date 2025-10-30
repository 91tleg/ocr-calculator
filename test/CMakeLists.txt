cmake_minimum_required(VERSION 3.16.0)
project(NativeTests LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(googletest)
include_directories(
    ${CMAKE_SOURCE_DIR}/../include
    ${CMAKE_SOURCE_DIR}/../src
    ${CMAKE_SOURCE_DIR}/modules
)

set(BUTTON_SOURCES ${CMAKE_SOURCE_DIR}/../src/modules/button/button.cpp)
set(CAMERA_SOURCES ${CMAKE_SOURCE_DIR}/../src/modules/camera/camera.cpp)
set(SEGMENTER_SOURCES ${CMAKE_SOURCE_DIR}/../src/modules/segmenter/segmenter.cpp)

add_executable(test_button
    ${BUTTON_SOURCES}
    ${GTEST_SOURCES}
    ${CMAKE_SOURCE_DIR}/test_button/test_button.cpp
)

add_executable(test_camera
    ${CAMERA_SOURCES}
    ${GTEST_SOURCES}
    ${CMAKE_SOURCE_DIR}/test_camera/test_camera.cpp
)

add_executable(test_segmenter
    ${SEGMENTER_SOURCES}
    ${GTEST_SOURCES}
    ${CMAKE_SOURCE_DIR}/test_segmenter/test_segmenter.cpp
)

target_link_libraries(test_button
    gtest
    gmock
    gtest_main
    gmock_main
    pthread
)

target_link_libraries(test_camera
    gtest
    gmock
    gtest_main
    gmock_main
    pthread
)

target_link_libraries(test_segmenter
    gtest
    gmock
    gtest_main
    gmock_main
    pthread
)

add_test(NAME test_button COMMAND test_button)
add_test(NAME test_camera COMMAND test_camera)
add_test(NAME test_segmenter COMMAND test_segmenter)