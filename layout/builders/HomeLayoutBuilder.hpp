#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "../../utils/font/Fonts.hpp"
#include "../components/Modal/Modal.hpp"
#include "../components/Button/Button.hpp"
#include "../components/TextWrapper/TextWrapper.hpp"
#include "../components/CheckBox/CheckBoxGroup.hpp"

struct HomeLayoutBuilder {

    static auto build() -> void;

    static auto unbuild() -> void;

    static auto initHomeScreen(sf::RenderWindow &renderWindow) -> void;

private:

    static auto makeMainModal(sf::RenderWindow &renderWindow) -> void;
    static auto makeStartGameButton(sf::RenderWindow &renderWindow) -> void;
    static auto makeGameChoiceGroup() -> void;

    static std::unique_ptr<Modal> modal;
    static std::unique_ptr<TextWrapper> title;
    static std::unique_ptr<Button> button;
    static std::unique_ptr<CheckBoxGroup> checkBoxGroup;

};