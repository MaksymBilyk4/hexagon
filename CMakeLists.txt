cmake_minimum_required(VERSION 3.28)
project(hexagon)

set(CMAKE_CXX_STANDARD 20)

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

add_executable(hexagon main.cpp
        utils/EventHandler.cpp
        layout/figures/Circle.cpp
        utils/RandomGenerator.cpp
        layout/utils/LayoutController.cpp
        layout/components/Modal.cpp
        layout/components/Button.cpp
        layout/utils/LayoutConstructor.cpp
        utils/font/FontHolder.cpp
        layout/components/TextWrapper.cpp
)

target_link_libraries(hexagon sfml-graphics)
target_link_libraries(hexagon fmt)
