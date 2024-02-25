cmake_minimum_required(VERSION 3.27)
project(test)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        "Project/*.h"
        "Project/*.cpp"
)

add_executable(test ${SOURCES})