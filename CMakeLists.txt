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
        utils/RandomGenerator.cpp
        utils/ComponentUtil.hpp
        utils/font/FontHolder.cpp
        utils/cursor/Cursor.cpp

        layout/figures/Circle.cpp

        layout/components/Modal/Modal.cpp
        layout/components/Button/Button.cpp
        layout/components/TextWrapper/TextWrapper.cpp
        layout/components/CheckBox/CheckBox.cpp
        layout/components/CheckBox/CheckBoxGroup.cpp
        utils/ComponentUtil.cpp
        utils/cursor/CursorHolder.hpp
        layout/components/Box.hpp
        layout/builders/HomeLayoutBuilder.cpp
        layout/builders/LayoutBuilder.cpp

        layout/drawer/Drawer.cpp
        layout/components/Component.cpp
)

add_executable(debug debug.cpp)

target_link_libraries(hexagon sfml-graphics)
target_link_libraries(hexagon fmt)
target_link_libraries(debug fmt)