#!/bin/bash

set -euf -o pipefail

BUILD_DIR="cmake-build"
INSTALL_DIR=$(pwd)/output
rm -rf "${BUILD_DIR}"

# Configure
BUILD_TYPE=Debug
cmake -B "${BUILD_DIR}" \
    -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR}" \
    -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
    -DCPACK_OUTPUT_FILE_PREFIX="${INSTALL_DIR}"

# Build
cmake --build "${BUILD_DIR}"

cd "${BUILD_DIR}"
# Test
make test CTEST_OUTPUT_ON_FAILURE=TRUE GTEST_COLOR=TRUE
# GTEST_COLOR=TRUE ctest --output-on-failure

# Install
# cmake --build . --target install
# cmake --install . --prefix "../output" # After cmake 3.15
make install

# Package
# cmake --build . --target package
make package

cd -
