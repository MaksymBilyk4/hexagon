#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "../components/TextWrapper/TextWrapper.hpp"
#include "../../utils/font/Fonts.hpp"
#include "../components/GameField/components/Hexagon.hpp"
#include "../components/GameField/GameField.hpp"
#include "../components/GameField/components/PlayerFigure.hpp"
#include "../components/GameField/components/CountBar.hpp"
#include "../components/Button/Button.hpp"
#include "./HomeLayoutBuilder.hpp"
#include "./GameInfo/GameMode.hpp"
#include "../../utils/Game/GameFileStore.hpp"

struct GameLayoutBuilder {

    static auto build() -> void;

    static auto unbuild() -> void;

    static auto prepareGameField(sf::RenderWindow& renderWindow) -> void;

    static auto setPlayerFigurePosition(PlayerFigure* figure, sf::Vector2f const& hexPosition) -> void;

    static auto initDefaultPlayersPositions() -> void;

private:


    static auto makeLeaveGameButton() -> void;

    static auto makeExitModal(sf::RenderWindow& renderWindow) -> void;

    static auto makeCurrentPlayerMoveLabel() -> void;

    static auto makePlayersCountBar() -> void;

    static std::vector<std::unique_ptr<Component>> components;

    static std::vector<std::unique_ptr<Component>> exitLayoutComponents;

    static GameMode gameMode;

};