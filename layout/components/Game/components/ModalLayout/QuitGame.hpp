#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "../../../Component.hpp"
#include "../../../Modal/Modal.hpp"
#include "../../../Button/Button.hpp"
#include "../../../TextWrapper/TextWrapper.hpp"
#include "../../../../model/GameField/GameField.hpp"
#include "../../../../util/game/GameFileStore.hpp"
#include "../../../../builders/HomeLayoutBuilder.hpp"
#include "../../../../builders/GameLayoutBuilder.hpp"

struct QuitGame {

    static auto show() -> void;

    static auto hide() -> void;

    static auto buildQuitGameLayout(sf::RenderWindow &renderWindow) -> void;

    static bool isOpened;

    static bool lockBackground;

    static std::vector<std::unique_ptr<Component>> components;

};