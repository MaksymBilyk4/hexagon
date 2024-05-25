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
        utils/cursor/CursorHolder.cpp

        layout/utils/LayoutController.cpp
        layout/utils/LayoutConstructor.cpp

        layout/figures/Circle.cpp

        layout/components/Modal/Modal.cpp
        layout/components/Button/Button.cpp
        layout/components/TextWrapper/TextWrapper.cpp
        layout/components/CheckBox/CheckBox.cpp
        layout/components/CheckBox/CheckBoxGroup.cpp
        utils/ComponentUtil.cpp
        utils/cursor/CurrentHolder.hpp
        layout/components/Component.hpp
        layout/components/Box.hpp
        layout/components/version2/ButtonVer2.cpp
        layout/components/version2/TextWrapperVer2.cpp
        layout/components/version2/ModalVer2.cpp
        layout/components/version2/CheckBoxVer2.cpp
        layout/components/version2/CheckBoxGroupVer2.cpp
        layout/builders/HomeLayoutBuilder.cpp
        layout/builders/LayoutBuilder.cpp

        utils/Drawer.cpp
)

add_executable(debug debug.cpp)

target_link_libraries(hexagon sfml-graphics)
target_link_libraries(hexagon fmt)
target_link_libraries(debug fmt)