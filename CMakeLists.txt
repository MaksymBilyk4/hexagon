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
        layout/builders/BackgroundBuilder.cpp

        layout/drawer/Drawer.cpp
        layout/components/Component.cpp
        layout/components/GameField/constants/FieldState.hpp
        layout/components/GameField/GameField.cpp
        layout/components/GameField/components/Hexagon.cpp
        layout/builders/GameLayoutBuilder.cpp
        layout/components/Player/Player.cpp
        layout/components/GameField/constants/CurrentMovePlayer.hpp
        layout/components/GameField/components/PlayerFigure.cpp
        layout/components/GameField/components/CountBar.cpp
        layout/builders/GameInfo/GameInfoLayoutBuilder.cpp
        layout/builders/GameInfo/GameInfo.hpp
        layout/builders/GameInfo/GameMode.hpp
        layout/components/TextField/TextField.cpp
        utils/Game/GameFileStore.cpp
)

target_link_libraries(hexagon sfml-graphics)
target_link_libraries(hexagon fmt)
