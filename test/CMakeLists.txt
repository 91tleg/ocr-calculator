cmake_minimum_required(VERSION 3.16.0)
project(NativeTests LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(googletest)

include_directories(
    ${CMAKE_SOURCE_DIR}/../include
    ${CMAKE_SOURCE_DIR}/../src
    ${CMAKE_SOURCE_DIR}/../src/modules

    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/third_party/flatbuffers/include
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/third_party/gemmlowp
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/third_party/kissfft
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/third_party/ruy
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/tensorflow/lite
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/tensorflow/lite/c
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/tensorflow/lite/core/api
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/tensorflow/lite/core/kernels
)
add_definitions(-DTF_LITE_STATIC_MEMORY)

file(GLOB_RECURSE TFLM_SOURCES
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/tensorflow/lite/c/*.cc
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/tensorflow/lite/micro/*.cc
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/tensorflow/lite/kernels/*.cc
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/tensorflow/lite/schema/*.cc
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/tensorflow/lite/core/kernels/*.cc
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/tensorflow/lite/core/api/*.cc
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/tensorflow/lite/core/c/*.cc
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/tensorflow/compiler/mlir/lite/core/api/error_reporter.cc
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/tensorflow/lite/micro/tflite_bridge/micro_error_reporter.cc
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/tensorflow/compiler/mlir/lite/schema/schema_utils.cc
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/third_party/kissfft/*.cc
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/third_party/gemmlowp/*.cc
    ${CMAKE_SOURCE_DIR}/../lib/tflm_tree/third_party/ruy/*.cc
)

add_library(tflm STATIC ${TFLM_SOURCES})

function(add_native_test TEST_NAME MODULE_PATH)
    add_executable(${TEST_NAME}
        ${CMAKE_SOURCE_DIR}/../src/modules/${MODULE_PATH}/${MODULE_PATH}.cpp
        ${CMAKE_SOURCE_DIR}/${TEST_NAME}/${TEST_NAME}.cpp
    )

    # Address sanitizer
    #target_compile_options(${TEST_NAME} PRIVATE -fsanitize=address -fno-omit-frame-pointer)
    #target_link_options(${TEST_NAME} PRIVATE -fsanitize=address -fno-omit-frame-pointer)

    target_link_libraries(${TEST_NAME}
        PRIVATE
        gtest
        gmock
        gtest_main
        pthread
        tflm
    )

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

file(GLOB TEST_DIRS "${CMAKE_SOURCE_DIR}/test_*")

foreach(TEST_DIR ${TEST_DIRS})
    get_filename_component(TEST_NAME ${TEST_DIR} NAME)
    string(REPLACE "test_" "" MODULE_NAME ${TEST_NAME})
    add_native_test(${TEST_NAME} ${MODULE_NAME})
endforeach()