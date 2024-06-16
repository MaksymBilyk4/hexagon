#pragma once

#include <vector>
#include <memory>
#include <map>
#include <fmt/core.h>

#include "../../layout/components/Game/components/ModalLayout/IllegalMove.hpp"
#include "../../layout/components/Player/PlayerData.hpp"
#include "../../layout/components/Game/constants/FieldState.hpp"
#include "../../layout/components/Game/constants/Player.hpp"
#include "../../layout/components/Game/components/PlayerFigure.hpp"
#include "../../layout/components/Game/components/Hexagon.hpp"
#include "../../layout/components/Game/components/CountBar.hpp"
#include "../../layout/builders/GameLayoutBuilder.hpp"
#include "../GameStatistic/GameStatistic.hpp"
#include "../../util/game/GameFileStore.hpp"
#include "../../layout/components/Game/components/ModalLayout/IllegalMove.hpp"
#include "./BotMoveData.hpp"

struct GameField {

    static auto initGameItems() -> void;

    static auto listenFieldClick(sf::Vector2i const& mousePosition) -> void;

    static auto botStep() -> void;

    static auto getPossibleMoves() -> std::vector<BotMoveData>;

    static auto getMoveData(int row, int col, bool isGreenStep) -> BotMoveData;

    static auto getEatEnemies(int row, int col) -> int;

    static auto getAllAvailableSteps() -> int;

    static auto getClickedHexAvailableSteps() -> int;

    static auto finishGame(bool buildDialog) -> void;

    static auto resetGameState() -> void;

    static auto printFieldMatrix() -> void;

    static auto printStateMatrix() -> void;

    static auto printFigureMatrix() -> void;


    static std::vector<std::vector<FieldState>> stateMatrix; // numbers
    static std::vector<std::vector<std::unique_ptr<Component>>> fieldMatrix; // hex
    static std::vector<std::vector<std::unique_ptr<Component>>> playerFigures; // player figures

    static std::unique_ptr<TextWrapper> movePlayerLabel;
    static std::unique_ptr<CountBar> playerOneCountBar;
    static std::unique_ptr<CountBar> playerTwoCountBar;

    static std::unique_ptr<PlayerData> playerOne;
    static std::unique_ptr<PlayerData> playerTwo;

    static std::unique_ptr<TextWrapper> freeSpaceLabel;
    static std::unique_ptr<TextWrapper> gameModeLabel;

    static Player currentMovePlayer;
    static std::string currentLoadedGame;

    static int gainedFields;
    static bool playerFigureSelected;
    static bool drawState;
    static Component* currentSelected;

    static bool isLocked;
    static bool isGameFinished;

private:
    static auto handleFieldClick(int row, int col, Component* hexagon) -> void;
    static auto handlePlayerStep(int row, int col, Component* hexagon) -> void;
    static auto eatEnemy(Hexagon* clickedHex) -> void;

    static auto clearBorders() -> void;
    static auto drawBorders(int clickedRow, int clickedCol, bool isBot) -> void;

    static auto changePlayer() -> void;
};