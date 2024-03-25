cmake_minimum_required(VERSION 3.28)
project(OOP)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR})
endif()

file(GLOB_RECURSE  SOURCES
"Project/*.hpp"
"Project/*.cpp"
)

add_executable(OOP ${SOURCES})

target_link_libraries(OOP PRIVATE nlohmann_json::nlohmann_json)