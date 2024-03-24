#!/bin/bash

cd build

sudo apt-get install ccache -y

export PATH="/usr/lib/ccache:$PATH"

cmake -DCMAKE_C_COMPILER_LAUNCHER=ccache -DCMAKE_CXX_COMPILER_LAUNCHER=ccache ..

ccache -c
