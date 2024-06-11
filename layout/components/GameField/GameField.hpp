#pragma once

#include <vector>
#include <memory>
#include <fmt/core.h>
#include "../Player/Player.hpp"
#include "constants/FieldState.hpp"
#include "constants/CurrentMovePlayer.hpp"
#include "components/PlayerFigure.hpp"
#include "components/Hexagon.hpp"
#include "components/CountBar.hpp"
#include "../../builders/GameLayoutBuilder.hpp"

struct GameField {

    static auto initGameItems() -> void;

    static auto printFieldMatrix() -> void;
    static auto printStateMatrix() -> void;
    static auto printFigureMatrix() -> void;

    static auto listenFieldClick(sf::Vector2i const& mousePosition) -> void;

    static auto resetGameState() -> void;

    static std::vector<std::vector<FieldState>> stateMatrix; // numbers
    static std::vector<std::vector<std::unique_ptr<Component>>> fieldMatrix; // hex
    static std::vector<std::vector<std::unique_ptr<Component>>> playerFigures; // player figures

    static std::unique_ptr<TextWrapper> movePlayerLabel;
    static std::unique_ptr<CountBar> playerOneCountBar;
    static std::unique_ptr<CountBar> playerTwoCountBar;

    static std::unique_ptr<Player> playerOne;
    static std::unique_ptr<Player> playerTwo;

    static CurrentMovePlayer currentMovePlayer;

    static bool drawState;
    static std::string currentLoadedGame;
    static auto botStep() -> void;

private:
    static auto handleFieldClick(int row, int col, Component* hexagon) -> void;
    static auto handlePlayerStep(int row, int col, Component* hexagon) -> void;
    static auto eatEnemy(Hexagon* clickedHex) -> void;
    static auto updateCountBar(bool greenStep) -> void;

    static auto clearBorders() -> void;
    static auto drawBorders(int clickedRow, int clickedCol) -> void;

    static auto changePlayer() -> void;

    static bool playerFigureSelected;
    static int gainedFields;
    static Component* currentSelected;

};