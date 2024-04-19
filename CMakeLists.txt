cmake_minimum_required(VERSION 3.28)
project(hexagon)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.2.1
)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML
        GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(fmt)
FetchContent_MakeAvailable(SFML)

add_executable(hexagon main.cpp)

target_link_libraries(hexagon sfml-graphics)
target_link_libraries(hexagon fmt)
