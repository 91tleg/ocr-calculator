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

add_executable(test_button
    ${BUTTON_SOURCES}
    ${GTEST_SOURCES}
    ${CMAKE_SOURCE_DIR}/test_button/test_button.cpp
)

target_link_libraries(test_button
    gtest
    gmock
    gtest_main
    gmock_main
    pthread
)

add_test(NAME test_button COMMAND test_button)