cmake_minimum_required(VERSION 3.16.0)
project(NativeTests LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(googletest)

include_directories(
    ${CMAKE_SOURCE_DIR}/../include
    ${CMAKE_SOURCE_DIR}/../src
    ${CMAKE_SOURCE_DIR}/../src/modules
)

function(add_native_test TEST_NAME MODULE_PATH)
    add_executable(${TEST_NAME}
        ${CMAKE_SOURCE_DIR}/../src/modules/${MODULE_PATH}/${MODULE_PATH}.cpp
        ${CMAKE_SOURCE_DIR}/${TEST_NAME}/${TEST_NAME}.cpp
    )

    target_link_libraries(${TEST_NAME}
        PRIVATE
        gtest
        gmock
        gtest_main
        pthread
    )

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

file(GLOB TEST_DIRS "${CMAKE_SOURCE_DIR}/test_*")

foreach(TEST_DIR ${TEST_DIRS})
    get_filename_component(TEST_NAME ${TEST_DIR} NAME)
    string(REPLACE "test_" "" MODULE_NAME ${TEST_NAME})
    add_native_test(${TEST_NAME} ${MODULE_NAME})
endforeach()