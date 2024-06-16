#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "../components/TextWrapper/TextWrapper.hpp"
#include "../../util/font/Fonts.hpp"
#include "../components/Game/components/Hexagon.hpp"
#include "../components/Modal/Modal.hpp"
#include "../../model/GameField/GameField.hpp"
#include "../components/Game/components/PlayerFigure.hpp"
#include "../components/Game/components/CountBar.hpp"
#include "../components/Button/Button.hpp"
#include "../components/Game/constants/GameMode.hpp"
#include "./HomeLayoutBuilder.hpp"
#include "../components/Game/components/ModalLayout/QuitGame.hpp"
#include "../components/Game/components/ModalLayout/IllegalMove.hpp"

struct GameLayoutBuilder {

    static auto build(bool isFileBuild = false) -> void;

    static auto unbuild() -> void;

    static auto prepareGameField(sf::RenderWindow& renderWindow) -> void;

    static auto setPlayerFigurePosition(PlayerFigure* figure, sf::Vector2f const& hexPosition) -> void;

    static auto initDefaultPlayersPositions() -> void;

    static auto build2() -> void;

    static std::unique_ptr<Button> quitButton;
    static std::unique_ptr<Button> stats;

private:

    static auto buildGameLayoutItems() -> void;

};