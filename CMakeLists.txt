cmake_minimum_required(VERSION 3.28)
project(OOP)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v5.0.0
)
FetchContent_MakeAvailable(ftxui)

file(GLOB_RECURSE  SOURCES
        "Project/*.hpp"
        "Project/*.cpp"
)

add_executable(OOP ${SOURCES})

target_link_libraries(OOP
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)