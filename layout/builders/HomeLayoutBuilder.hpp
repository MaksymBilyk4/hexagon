#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "../../utils/font/Fonts.hpp"
#include "../components/version2/ModalVer2.hpp"
#include "../components/version2/ButtonVer2.hpp"
#include "../components/version2/TextWrapperVer2.hpp"
#include "../components/version2/CheckBoxGroupVer2.hpp"

struct HomeLayoutBuilder {

    static auto build() -> void;

    static auto unbuild() -> void;

    static auto initHomeScreen(sf::RenderWindow &renderWindow) -> void;

private:

    static auto makeMainModal(sf::RenderWindow &renderWindow) -> void;
    static auto makeStartGameButton(sf::RenderWindow &renderWindow) -> void;
    static auto makeGameChoiceGroup() -> void;

    static std::unique_ptr<ModalVer2> modal;
    static std::unique_ptr<TextWrapperVer2> title;
    static std::unique_ptr<ButtonVer2> button;
    static std::unique_ptr<CheckBoxGroupVer2> checkBoxGroup;

};