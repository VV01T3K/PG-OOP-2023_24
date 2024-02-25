cmake_minimum_required(VERSION 3.27)
project(test)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        "*.h"
        "*.cpp"
)

add_executable(test ${SOURCES})