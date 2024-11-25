#!/bin/sh

cmake -S . -B cmake-build-debug -DCMAKE_BUILD_TYPE=Release
cmake --build cmake-build-debug
