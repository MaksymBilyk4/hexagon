#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "../../util/font/Fonts.hpp"
#include "../components/Modal/Modal.hpp"
#include "../components/Button/Button.hpp"
#include "../components/TextWrapper/TextWrapper.hpp"
#include "../components/CheckBox/CheckBoxGroup.hpp"
#include "./GameInfo/GameInfoLayoutBuilder.hpp"
#include "../components/Game/constants/GameMode.hpp"
#include "../../model/GameStatistic/GameStatistic.hpp"

struct HomeLayoutBuilder {

    static auto build() -> void;

    static auto unbuild() -> void;

    static auto initHomeScreen(sf::RenderWindow &renderWindow) -> void;

    static std::unique_ptr<CheckBoxGroup> modeGroup;
private:

    static auto makeMainModal(sf::RenderWindow &renderWindow) -> void;
    static auto makeLinkButtons(sf::RenderWindow &renderWindow) -> void;
    static auto makeGameChoiceGroup() -> void;

    static std::vector<std::unique_ptr<Component>> components;


    static std::unique_ptr<Modal> modal;

};