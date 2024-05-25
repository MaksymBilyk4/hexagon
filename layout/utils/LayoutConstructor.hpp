#pragma once

#include <SFML/Graphics.hpp>
#include "../components/Modal/Modal.hpp"
#include "../components/Button/Button.hpp"
#include "../components/CheckBox/CheckBoxGroup.hpp"

struct LayoutConstructor {

    static auto buildHomeScreen(sf::RenderWindow &window) -> void;
    static auto buildGameField() -> void;

private:
    static auto makeMainModal(sf::RenderWindow &window) -> Modal;

    static auto makeStartGameButton(sf::RenderWindow &window) -> Button;

    static auto makeCheckBoxGameModeChoiceGroup() -> CheckBoxGroup;


};