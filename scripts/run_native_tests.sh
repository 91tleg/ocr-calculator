#!/bin/bash
set -e

cd test
mkdir -p build
cd build
cmake ..
make

ctest --output-on-failure