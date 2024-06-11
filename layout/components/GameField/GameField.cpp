#include "./GameField.hpp"

std::vector<std::vector<FieldState>> GameField::stateMatrix = std::vector<std::vector<FieldState>>(9,std::vector<FieldState>(9,FieldState::NOT_EXIST));

std::vector<std::vector<std::unique_ptr<Component>>> GameField::fieldMatrix; // Hexagon components
std::vector<std::vector<std::unique_ptr<Component>>> GameField::playerFigures; // Figures

std::unique_ptr<Player> GameField::playerOne;
std::unique_ptr<Player> GameField::playerTwo;

std::unique_ptr<TextWrapper> GameField::movePlayerLabel;

std::unique_ptr<CountBar> GameField::playerOneCountBar;
std::unique_ptr<CountBar> GameField::playerTwoCountBar;

CurrentMovePlayer GameField::currentMovePlayer;
Component *GameField::currentSelected = nullptr;

int GameField::gainedFields;
bool GameField::drawState;
bool GameField::playerFigureSelected = false;
std::string GameField::currentLoadedGame;

auto GameField::initGameItems() -> void {
    fieldMatrix.resize(9);
    playerFigures.resize(9);

    for (int row = 0; row < fieldMatrix.size(); ++row) {
        fieldMatrix[row].resize(9);
        playerFigures[row].resize(9);
    }

    playerOne = std::make_unique<Player>(3, sf::Color::Red);
    playerTwo = std::make_unique<Player>(3, sf::Color::Cyan);
    currentMovePlayer = CurrentMovePlayer::FIRST;
}

auto GameField::listenFieldClick(sf::Vector2i const &mousePosition) -> void {
    for (auto i = 0; i < fieldMatrix.size(); ++i)
        for (auto j = 0; j < fieldMatrix[i].size(); ++j)
            if (fieldMatrix[i][j] != nullptr && fieldMatrix[i][j]->isMouseOver(mousePosition)) {
                if (HomeLayoutBuilder::getGameMode() == GameMode::PLAYER_VS_PLAYER || (HomeLayoutBuilder::getGameMode() == GameMode::PLAYER_VS_COMPUTER && currentMovePlayer == CurrentMovePlayer::FIRST)) {
                    if (static_cast<int>(stateMatrix[i][j]) == static_cast<int>(currentMovePlayer))
                        handleFieldClick(i, j, fieldMatrix[i][j].get());
                    else if (playerFigureSelected && stateMatrix[i][j] == FieldState::EMPTY)
                        handlePlayerStep(i, j, fieldMatrix[i][j].get());
                }
            }
}

auto GameField::handlePlayerStep(int clickedRow, int clickedCol, Component *hexagon) -> void {
    auto clickedHex = dynamic_cast<Hexagon *>(hexagon); // where user clicked
    auto selectedHex = dynamic_cast<Hexagon *>(currentSelected); // current selected players hex

    auto selectedRow = selectedHex->getFieldRow();
    auto selectedCol = selectedHex->getFieldCol();
//    fmt::println("clicked: {} {} ", clickedRow, clickedCol);
//    fmt::println("selected:  {} {} ", selectedHex->getFieldRow(), selectedHex->getFieldCol());


    if (clickedHex->getBorderColor() == sf::Color::Green || clickedHex->getIsSelectedByBot()) {
        auto playerFigure = std::make_unique<PlayerFigure>(currentMovePlayer == CurrentMovePlayer::FIRST ? playerOne->getPlayerColor() : playerTwo->getPlayerColor());
        GameLayoutBuilder::setPlayerFigurePosition(playerFigure.get(), clickedHex->getPosition());
        playerFigures[clickedRow][clickedCol] = std::move(playerFigure);
        stateMatrix[clickedRow][clickedCol] = currentMovePlayer == CurrentMovePlayer::FIRST ? FieldState::PLAYER_ONE : FieldState::PLAYER_TWO;
        gainedFields++;
        eatEnemy(clickedHex);
        updateCountBar(true);
        clearBorders();
        if (clickedHex->getIsSelectedByBot()) clickedHex->setIsSelectedByBot(false);
        changePlayer();
    } else if (clickedHex->getBorderColor() == sf::Color::Yellow || clickedHex->getIsSelectedByBot()) {
        auto playerFigure = playerFigures[selectedRow][selectedCol].get();
        GameLayoutBuilder::setPlayerFigurePosition(dynamic_cast<PlayerFigure *>(playerFigure),clickedHex->getPosition());
        playerFigures[clickedRow][clickedCol] = std::move(playerFigures[selectedRow][selectedCol]);
        stateMatrix[clickedRow][clickedCol] = currentMovePlayer == CurrentMovePlayer::FIRST ? FieldState::PLAYER_ONE : FieldState::PLAYER_TWO;
        stateMatrix[selectedRow][selectedCol] = FieldState::EMPTY;
        eatEnemy(clickedHex);
        updateCountBar(false);
        clearBorders();
        if (clickedHex->getIsSelectedByBot()) clickedHex->setIsSelectedByBot(false);
        changePlayer();
    } else {
        fmt::println("TODO ERROR");
    }

}

auto GameField::changePlayer() -> void {
    currentMovePlayer == CurrentMovePlayer::FIRST ? currentMovePlayer = CurrentMovePlayer::SECOND : currentMovePlayer = CurrentMovePlayer::FIRST;
    playerFigureSelected = false;

    if (currentSelected != nullptr) {
        auto hex = dynamic_cast<Hexagon *>(currentSelected);
        hex->setBorderColor(Hexagon::defaultBorderColor);
        currentSelected = nullptr;
    }

    movePlayerLabel->setText(currentMovePlayer == CurrentMovePlayer::FIRST ? "Current player: 1" : "Current player: 2");
    movePlayerLabel->setColor(currentMovePlayer == CurrentMovePlayer::FIRST ? playerOne->getPlayerColor() : playerTwo->getPlayerColor());
    gainedFields = 0;
    printStateMatrix();

    if (HomeLayoutBuilder::getGameMode() == GameMode::PLAYER_VS_COMPUTER && currentMovePlayer == CurrentMovePlayer::SECOND) botStep();
}

auto GameField::botStep() -> void {
    fmt::println("BOT STEP");

    bool found = false;

    auto selectedRow = int();
    auto selectedCol = int();
    for (auto row = 0; row < playerFigures.size(); ++row) {
        for (auto col = 0; col < playerFigures[row].size(); ++col) {
            if (playerFigures[row][col] != nullptr) {
                auto fig = dynamic_cast<PlayerFigure*>(playerFigures[row][col].get());
                if (fig->getColor() == playerTwo->getPlayerColor()) {
                    currentSelected = fieldMatrix[row][col].get();
                    playerFigureSelected = true;
                    selectedRow = row;
                    selectedCol = col;
                    found = true;
                    break;
                }
            }
        }
        if (found) break;
    }

    auto stepRow = int();
    auto stepCol = int();
    found = false;

    auto rowDifference = int();
    auto colDifference = int();

    for (auto row = 0; row < stateMatrix.size(); ++row) {
        for (auto col = 0; col < stateMatrix[row].size(); ++col) {
            rowDifference = selectedRow - row;
            colDifference = selectedCol - col;

            if (rowDifference == 0 && (std::abs(colDifference) == 1 || std::abs(colDifference) == 2) && stateMatrix[row][col] == FieldState::EMPTY) {
                found = true;
                stepRow = row;
                stepCol = col;
                break;
            }

        }
        if (found) break;
    }
    
    fmt::println("bot row selected, col selected {} {}", selectedRow, selectedCol);
    fmt::println("bot selected step to move {} {}", stepCol, stepRow);

    auto clickedHex = dynamic_cast<Hexagon*>(fieldMatrix[stepRow][stepCol].get());
    clickedHex->setIsSelectedByBot(true);
    handlePlayerStep(0, 3, fieldMatrix[stepRow][stepCol].get());
}

auto GameField::handleFieldClick(int row, int col, Component *hexagon) -> void {
    auto clickedHexagon = dynamic_cast<Hexagon *>(hexagon);

    if (!playerFigureSelected) {
        clickedHexagon->drawYellowBorder();

        currentSelected = hexagon;
        playerFigureSelected = true;

        drawBorders(row, col);
    } else if (currentSelected != nullptr && hexagon == currentSelected) {
        clickedHexagon->drawDefaultBorder();

        currentSelected = nullptr;
        playerFigureSelected = false;

        clearBorders();
    } else if (currentSelected != nullptr && hexagon != currentSelected) {

        auto oldSelected = dynamic_cast<Hexagon *>(currentSelected);
        oldSelected->drawDefaultBorder();

        currentSelected = hexagon;
        playerFigureSelected = true;

        clearBorders();
        clickedHexagon->drawYellowBorder();

        drawBorders(row, col);
    }
}

auto GameField::eatEnemy(Hexagon *clickedHex) -> void {
    auto clickedRow = clickedHex->getFieldRow();
    auto clickedCol = clickedHex->getFieldCol();

    auto eatColor = currentMovePlayer == CurrentMovePlayer::FIRST ? playerOne->getPlayerColor() : playerTwo->getPlayerColor();
    auto replacementState = currentMovePlayer == CurrentMovePlayer::FIRST ? FieldState::PLAYER_ONE : FieldState::PLAYER_TWO;

    auto eat = [eatColor, replacementState](auto row, auto col) -> void {
        if (stateMatrix[row][col] > 0 && static_cast<int>(currentMovePlayer) != static_cast<int>(stateMatrix[row][col])) {
            auto figureToEat = dynamic_cast<PlayerFigure*>(playerFigures[row][col].get());
            figureToEat->setColor(eatColor);
            stateMatrix[row][col] = replacementState;
            gainedFields++;
        }
    };

    for (auto i = 0; i < stateMatrix.size(); ++i)
        for (auto j = 0; j < stateMatrix[i].size(); ++j) {
            auto rowDifference = clickedRow - i;
            auto colDifference = clickedCol - j;

            if (
                    (rowDifference == 0 && std::abs(colDifference) == 1) ||
                    (std::abs(rowDifference) == 1 && colDifference == 0)
                    ) eat(i, j);


            if (clickedCol < 4)
                if (
                        (rowDifference == 1 && colDifference == 1) ||
                        (rowDifference == -1 && colDifference == -1)
                        ) eat(i, j);


            if (clickedCol == 4 && rowDifference == 1 && (std::abs(colDifference)) <= 1) eat(i, j);

            if (clickedCol > 4)
                if (
                        (rowDifference == 1 && colDifference == -1) ||
                        (rowDifference == -1 && colDifference == 1)
                        ) eat(i, j);


        }
}

auto GameField::updateCountBar(bool greenStep) -> void {
    auto currentPlayerBar = currentMovePlayer == CurrentMovePlayer::FIRST ? playerOneCountBar.get() : playerTwoCountBar.get();
    auto oppositePlayerBar = currentMovePlayer == CurrentMovePlayer::FIRST ? playerTwoCountBar.get() : playerOneCountBar.get();

    currentPlayerBar->increaseCounter(gainedFields);
    oppositePlayerBar->decreaseCounter(greenStep ? gainedFields - 1 : gainedFields);

    playerOne->setFieldCount(playerOneCountBar->getCountedItems());
    playerTwo->setFieldCount(playerTwoCountBar->getCountedItems());
}

auto GameField::drawBorders(int clickedRow, int clickedCol) -> void {

    auto rowDifference = int();
    auto colDifference = int();
    auto drawCondition = bool();

    for (int i = 0; i < fieldMatrix.size(); ++i)
        for (int j = 0; j < fieldMatrix[i].size(); ++j) {
            if (fieldMatrix[i][j] != nullptr) {
                auto hex = dynamic_cast<Hexagon*>(fieldMatrix[i][j].get());

                drawCondition = stateMatrix[i][j] == FieldState::EMPTY;
                rowDifference = clickedRow - i;
                colDifference = clickedCol - j;

                if (drawCondition) {

                    // YELLOW BORDERS ===========================================================================
                    if ((rowDifference == 0 && (std::abs(colDifference) == 2))) hex->drawYellowBorder();

                    if (clickedCol == 4) {
                        if (rowDifference == -1 && (std::abs(colDifference)) == 1) hex->drawYellowBorder();
                        if (rowDifference == -2 && colDifference == 0) hex->drawYellowBorder();
                        if (rowDifference == 2 && (std::abs(colDifference) <= 2)) hex->drawYellowBorder();
                        if (rowDifference == 1 && (std::abs(colDifference) == 2)) hex->drawYellowBorder();
                    }

                    if (clickedCol > 4) {
                        if (rowDifference == -2 && colDifference == 2 && clickedCol != 5) hex->drawYellowBorder();
                        if (rowDifference == 2 && (colDifference == -1 || colDifference == -2 || colDifference == 0)) hex->drawYellowBorder();
                        if (rowDifference == 1 && colDifference == 1) hex->drawYellowBorder();
                        if (rowDifference == -1 && colDifference == 2) hex->drawYellowBorder();
                        if (rowDifference == 1 && colDifference == -2) hex->drawYellowBorder();
                        if (rowDifference == -2 && (colDifference == 1 || colDifference == 0)) hex->drawYellowBorder();
                        if (rowDifference == -1 && (colDifference == -1)) hex->drawYellowBorder();
                    }

                    if (clickedCol < 4) {
                        if (rowDifference == 2 && (colDifference == 1 || colDifference == 2 || colDifference == 0)) hex->drawYellowBorder();
                        if (rowDifference == 1 && colDifference == -1) hex->drawYellowBorder();
                        if (rowDifference == -1 && colDifference == -2) hex->drawYellowBorder();
                        if (rowDifference == 1 && colDifference == 2) hex->drawYellowBorder();
                        if (rowDifference == -2 && (colDifference == -1 || colDifference == 0)) hex->drawYellowBorder();
                        if (rowDifference == -2 && colDifference == -2 && clickedCol != 3) hex->drawYellowBorder();
                        if (rowDifference == -1 && (colDifference == 1)) hex->drawYellowBorder();
                    }

                    if (clickedCol == 3) {
                        if (rowDifference == 1 && colDifference == -2) hex->drawYellowBorder();
                        if (rowDifference == -1 && colDifference == -2) hex->drawYellowBorder();
                    }

                    if (clickedCol == 5) {
                        if (rowDifference == -1 && colDifference == 2) hex->drawYellowBorder();
                        if (rowDifference == 1 && colDifference == 2) hex->drawYellowBorder();
                    }

                    // GREEN BORDERS ===========================================================================
                    if ((rowDifference == 0 && (std::abs(colDifference) == 1)) || (std::abs(rowDifference) == 1 && colDifference == 0)) hex->drawGreenBorder();

                    if (clickedCol < 4) if (rowDifference == -1 && colDifference == -1) hex->drawGreenBorder();

                    if (clickedCol <= 4) if (rowDifference == 1 && colDifference == 1) hex->drawGreenBorder();

                    if (clickedCol >= 4) if (rowDifference == 1 && colDifference == -1) hex->drawGreenBorder();

                    if (clickedCol > 4 ) if  (rowDifference == -1 && colDifference == 1) hex->drawGreenBorder();


                }
            }
        }
}

auto GameField::clearBorders() -> void {
    for (auto const &row: fieldMatrix)
        for (auto const &hex: row)
            if (hex != nullptr)
                dynamic_cast<Hexagon *>(hex.get())->setBorderColor(Hexagon::defaultBorderColor);

}

auto GameField::resetGameState() -> void {
    currentSelected = nullptr;
    playerFigureSelected = false;

    clearBorders();

    playerOne->setFieldCount(3);
    playerTwo->setFieldCount(3);
    currentMovePlayer = CurrentMovePlayer::FIRST;

    movePlayerLabel->setText("Current player: 1");
    movePlayerLabel->setColor(currentMovePlayer == CurrentMovePlayer::FIRST ? playerOne->getPlayerColor() : playerTwo->getPlayerColor());

    playerOneCountBar->setCountedItems(3);
    playerOneCountBar->setCountedItems(3);

    for (auto &stateRow : stateMatrix)
        for (auto &fieldState : stateRow)
            if (static_cast<int>(fieldState) > 0)
                fieldState = FieldState::EMPTY;

    for (auto &figRow : playerFigures)
        for (auto &figure : figRow)
            figure = nullptr;

    GameLayoutBuilder::initDefaultPlayersPositions();
//    printStateMatrix();
//    printFigureMatrix();
}

auto GameField::printFieldMatrix() -> void {
    const int columnWidth = 8;

    for (auto &inner: GameField::fieldMatrix) {
        for (auto &hex: inner) {
            if (hex != nullptr) {
                fmt::print("{:<{}}", hex->getComponentId(), columnWidth);
            } else {
                fmt::print("{:<{}}", "null", columnWidth);
            }
        }
        fmt::print("\n");
    }
}

auto GameField::printStateMatrix() -> void {
    const int columnWidth = 8;
    for (auto &inner: GameField::stateMatrix) {
        for (auto &hex: inner) {
            fmt::print("{:<{}} ", static_cast<int>(hex), columnWidth);
        }
        fmt::print("\n");
    }
}

auto GameField::printFigureMatrix() -> void {
    const int columnWidth = 8;

    for (auto &inner: GameField::playerFigures) {
        for (auto &hex: inner) {
            if (hex != nullptr) {
                fmt::print("{:<{}}", hex->getComponentId(), columnWidth);
            } else {
                fmt::print("{:<{}}", "null", columnWidth);
            }
        }
        fmt::print("\n");
    }
}