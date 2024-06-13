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
#include "../../util/Game/GameFileStore.hpp"
#include "./HomeLayoutBuilder.hpp"

struct GameLayoutBuilder {

    static auto build(bool isFileBuild = false) -> void;

    static auto unbuild() -> void;

    static auto prepareGameField(sf::RenderWindow& renderWindow) -> void;

    static auto setPlayerFigurePosition(PlayerFigure* figure, sf::Vector2f const& hexPosition) -> void;

    static auto makeIllegalMoveModal(sf::RenderWindow &renderWindow) -> void;

    static auto initDefaultPlayersPositions() -> void;

private:


    static auto makeLeaveGameButton() -> void;

    static auto makeExitModal(sf::RenderWindow& renderWindow) -> void;

    static auto makeCurrentPlayerMoveLabel() -> void;

    static auto makePlayersCountBar() -> void;

    static std::vector<std::unique_ptr<Component>> components;

    static std::vector<std::unique_ptr<Component>> exitLayoutComponents;
};