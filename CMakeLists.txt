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

        util/event/EventHandler.cpp
        util/random/RandomGenerator.cpp
        util/component/ComponentUtil.hpp
        util/font/FontHolder.cpp
        util/cursor/Cursor.cpp

        layout/figures/Circle.cpp

        layout/components/Modal/Modal.cpp
        layout/components/Button/Button.cpp
        layout/components/TextWrapper/TextWrapper.cpp
        layout/components/CheckBox/CheckBox.cpp
        layout/components/CheckBox/CheckBoxGroup.cpp
        util/component/ComponentUtil.cpp
        util/cursor/CursorHolder.hpp
        layout/components/Box.hpp
        layout/builders/HomeLayoutBuilder.cpp
        layout/builders/BackgroundBuilder.cpp

        layout/drawer/Drawer.cpp
        layout/components/Component.cpp
        layout/components/Game/constants/FieldState.hpp
        model/GameField/GameField.cpp
        layout/components/Game/components/Hexagon.cpp
        layout/builders/GameLayoutBuilder.cpp
        layout/components/Player/Player.cpp
        layout/components/Game/constants/Player.hpp
        layout/components/Game/components/PlayerFigure.cpp
        layout/components/Game/components/CountBar.cpp
        layout/builders/GameInfo/GameInfoLayoutBuilder.cpp
        layout/components/Game/constants/GameMode.hpp
        util/game/GameFileStore.cpp
        util/game/Path.hpp
        model/GameStatistic/GameStatistic.cpp
        layout/components/Game/components/ModalLayout/IllegalMove.cpp
        model/GameField/BotMoveData.cpp
        layout/components/Game/components/ModalLayout/QuitGame.cpp
        layout/components/TextField/TextField.cpp
)
add_executable(deb debug.cpp)
target_link_libraries(hexagon sfml-graphics)
target_link_libraries(hexagon fmt)
target_link_libraries(deb fmt)