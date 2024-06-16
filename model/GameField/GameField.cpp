#include "./GameField.hpp"

std::vector<std::vector<FieldState>> GameField::stateMatrix = std::vector<std::vector<FieldState>>(9, std::vector<FieldState>(9, FieldState::NOT_EXIST));

std::vector<std::vector<std::unique_ptr<Component>>> GameField::fieldMatrix; // Hexagon components
std::vector<std::vector<std::unique_ptr<Component>>> GameField::playerFigures; // Figures

std::unique_ptr<PlayerData> GameField::playerOne;
std::unique_ptr<PlayerData> GameField::playerTwo;

std::unique_ptr<TextWrapper> GameField::movePlayerLabel;
std::unique_ptr<TextWrapper> GameField::freeSpaceLabel;
std::unique_ptr<TextWrapper> GameField::gameModeLabel;

std::unique_ptr<CountBar> GameField::playerOneCountBar;
std::unique_ptr<CountBar> GameField::playerTwoCountBar;

Player GameField::currentMovePlayer;
Component *GameField::currentSelected = nullptr;

int GameField::gainedFields;
bool GameField::drawState = false;
bool GameField::playerFigureSelected = false;
std::string GameField::currentLoadedGame;
bool GameField::isLocked = true;
bool GameField::isGameFinished = false;

auto GameField::initGameItems() -> void {
    fieldMatrix.resize(9);
    playerFigures.resize(9);

    for (int row = 0; row < fieldMatrix.size(); ++row) {
        fieldMatrix[row].resize(9);
        playerFigures[row].resize(9);
    }

    playerOne = std::make_unique<PlayerData>(3, sf::Color::Red);
    playerTwo = std::make_unique<PlayerData>(3, sf::Color::Cyan);
    currentMovePlayer = Player::FIRST;
}

auto GameField::listenFieldClick(sf::Vector2i const &mousePosition) -> void {

//    if (isGameFinished) return;
    if (GameInfoLayoutBuilder::gameFinishedModalOpen) {
        GameInfoLayoutBuilder::gameFinishedModalOpen = true;
        return;
    }

    if (IllegalMove::lockBackground) {
        IllegalMove::lockBackground = false;
        return;
    } else if (QuitGame::lockBackground) {
        QuitGame::lockBackground = false;
        return;
    }

    if (isLocked) {
        isLocked = false;
        return;
    }


    for (auto i = 0; i < fieldMatrix.size(); ++i)
        for (auto j = 0; j < fieldMatrix[i].size(); ++j) {
            if (fieldMatrix[i][j] != nullptr && fieldMatrix[i][j]->isMouseOver(mousePosition)) {
                if (GameStatistic::gameMode == GameMode::PLAYER_VS_PLAYER || (GameStatistic::gameMode == GameMode::PLAYER_VS_COMPUTER && currentMovePlayer == Player::FIRST) || GameField::isGameFinished) {
                    if (static_cast<int>(stateMatrix[i][j]) == static_cast<int>(currentMovePlayer)) handleFieldClick(i, j, fieldMatrix[i][j].get());
                    else if (playerFigureSelected && stateMatrix[i][j] == FieldState::EMPTY) handlePlayerStep(i, j, fieldMatrix[i][j].get());
                    else if (isGameFinished) {
                        auto finishedMessage = std::string("You can't do any steps. Game is finished.\nWinner is ");
                        finishedMessage += (currentMovePlayer == Player::FIRST ? "Player two" : "Player one");
                        IllegalMove::setTitle("Game is finished");
                        IllegalMove::setMessage(finishedMessage);
                        IllegalMove::show();
                    }
                    else {
                        if (!IllegalMove::isOpened) {
                            auto currentPlayer = std::string(
                                    currentMovePlayer == Player::FIRST ? "Player One" : "Player two");
                            auto oppositePlayer = std::string(
                                    currentMovePlayer == Player::FIRST ? "Player Two" : "Player One");
                            if (currentSelected &&
                                static_cast<int>(stateMatrix[i][j]) != static_cast<int>(currentMovePlayer) &&
                                static_cast<int>(stateMatrix[i][j]) > 0) {
                                IllegalMove::setTitle("Illegal move!");
                                IllegalMove::setMessage(
                                        currentPlayer + ". You can't eat " + oppositePlayer + " like this!!!");
                                IllegalMove::show();
                            } else if (!currentSelected) {
                                if (stateMatrix[i][j] == FieldState::EMPTY) {
                                    IllegalMove::setTitle("Empty field");
                                    IllegalMove::setMessage(currentPlayer + ", please, choose your figure");
                                    IllegalMove::show();
                                } else if (playerFigures[i][j] != nullptr) {
                                    IllegalMove::setTitle("Choose your figure");
                                    IllegalMove::setMessage("It is figure of " + oppositePlayer +
                                                            "\nTo make a step choose your figure");
                                    IllegalMove::show();
                                }
                            }
                        }
                    }
                }
            }
        }
}

auto GameField::handlePlayerStep(int clickedRow, int clickedCol, Component *hexagon) -> void {
    auto clickedHex = dynamic_cast<Hexagon *>(hexagon); // where user clicked
    auto selectedHex = dynamic_cast<Hexagon *>(currentSelected); // current selected player's hex

    auto selectedRow = selectedHex->getFieldRow();
    auto selectedCol = selectedHex->getFieldCol();


    if (clickedHex->getBorderColor() == sf::Color::Green || clickedHex->getBotShortStep()) {
        auto playerFigure = std::make_unique<PlayerFigure>(currentMovePlayer == Player::FIRST ? playerOne->getPlayerColor() : playerTwo->getPlayerColor());
        GameLayoutBuilder::setPlayerFigurePosition(playerFigure.get(), clickedHex->getPosition());
        playerFigures[clickedRow][clickedCol] = std::move(playerFigure);
        stateMatrix[clickedRow][clickedCol] = currentMovePlayer == Player::FIRST ? FieldState::PLAYER_ONE : FieldState::PLAYER_TWO;
        gainedFields++;
        eatEnemy(clickedHex);
        GameStatistic::updateGameStatistic(true);
        clearBorders();
        if (clickedHex->getIsSelectedByBot()) {
            clickedHex->setIsSelectedByBot(false);
            clickedHex->setBotShortStep(false);
        }
        changePlayer();
        GameStatistic::printStatistic();
    } else if (clickedHex->getBorderColor() == sf::Color::Yellow || clickedHex->getBotLongStep()) {
        auto playerFigure = playerFigures[selectedRow][selectedCol].get();
        GameLayoutBuilder::setPlayerFigurePosition(dynamic_cast<PlayerFigure *>(playerFigure),
                                                   clickedHex->getPosition());
        playerFigures[clickedRow][clickedCol] = std::move(playerFigures[selectedRow][selectedCol]);
        stateMatrix[clickedRow][clickedCol] =
                currentMovePlayer == Player::FIRST ? FieldState::PLAYER_ONE : FieldState::PLAYER_TWO;
        stateMatrix[selectedRow][selectedCol] = FieldState::EMPTY;
        eatEnemy(clickedHex);
        GameStatistic::updateGameStatistic(false);
        clearBorders();
        if (clickedHex->getIsSelectedByBot()) {
            clickedHex->setIsSelectedByBot(false);
            clickedHex->setBotLongStep(false);
        }
        changePlayer();
        GameStatistic::printStatistic();
    } else {
        if (!IllegalMove::isOpened) {
            auto currentPlayer = std::string(currentMovePlayer == Player::FIRST ? "Player One" : "Player two");
            IllegalMove::setTitle("Illegal Move!");
            IllegalMove::setMessage(currentPlayer + ". Too far, sorry. Not today...\nGo to green or yellow area");
            IllegalMove::show();
        }
    }

}

auto GameField::handleFieldClick(int row, int col, Component *hexagon) -> void {
    auto clickedHexagon = dynamic_cast<Hexagon *>(hexagon);

    if (!playerFigureSelected) {
        clickedHexagon->drawYellowBorder();

        currentSelected = hexagon;
        playerFigureSelected = true;

        drawBorders(row, col, false);
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

        drawBorders(row, col, false);
    }
}

auto GameField::changePlayer() -> void {
    currentMovePlayer == Player::FIRST ? currentMovePlayer = Player::SECOND : currentMovePlayer = Player::FIRST;
    playerFigureSelected = false;

    if (currentSelected != nullptr) {
        auto hex = dynamic_cast<Hexagon *>(currentSelected);
        hex->setBorderColor(Hexagon::defaultBorderColor);
        currentSelected = nullptr;
    }

    movePlayerLabel->setText(currentMovePlayer == Player::FIRST ? "Current player: 1" : "Current player: 2");
    movePlayerLabel->setColor(
            currentMovePlayer == Player::FIRST ? playerOne->getPlayerColor() : playerTwo->getPlayerColor());
    gainedFields = 0;
    printStateMatrix();

    auto availableSteps = getAllAvailableSteps();
    auto movePlayer = currentMovePlayer == Player::FIRST ? "First player" : "Second plyaer";
    fmt::println("{}: all available steps {}",movePlayer, availableSteps);

    if (availableSteps == 0) finishGame(true);


    if (GameStatistic::gameMode == GameMode::PLAYER_VS_COMPUTER && currentMovePlayer == Player::SECOND) botStep();
}

auto GameField::botStep() -> void {
    fmt::println("BOT STEP");

    auto figureStepsMap = std::map<std::pair<int, int>, std::vector<BotMoveData>>();
    auto playerTwoColor = playerTwo->getPlayerColor();

    for (auto i = 0; i < stateMatrix.size(); ++i)
        for (auto j = 0; j < stateMatrix.size(); ++j) {
            if (stateMatrix[i][j] == FieldState::PLAYER_TWO) {
                auto coordinates = std::pair<int, int>(i, j);
                drawBorders(i, j, true);

                auto stepsAvailable = getClickedHexAvailableSteps();
                if (stepsAvailable == 0) {
                    clearBorders();
                    continue;
                }

                figureStepsMap[coordinates] = getPossibleMoves();
                clearBorders();
            }
        }

    auto selectedStep = std::pair<std::pair<int, int>, BotMoveData>({0, 0}, BotMoveData());

    for (auto const& entry : figureStepsMap) {
        fmt::println("----------\n{}", entry.first);
        for (auto const& move : entry.second) {
            if (move.greenStep && move.gain >= selectedStep.second.gain) {
                selectedStep.second = move;
                selectedStep.first = entry.first;
            }
            else if (move.gain >= selectedStep.second.gain) {
                selectedStep.second = move;
                selectedStep.first = entry.first;
            }
        }
    }

    fmt::println("Bot chosen figure: {}. Move data: {}", selectedStep.first, selectedStep.second.getDataString());

    currentSelected = fieldMatrix[selectedStep.first.first][selectedStep.first.second].get();
    playerFigureSelected = true;

    auto chosenBotHex = dynamic_cast<Hexagon *>(fieldMatrix[selectedStep.second.goRow][selectedStep.second.goCol].get());
    chosenBotHex->setIsSelectedByBot(true);
    selectedStep.second.greenStep ? chosenBotHex->setBotShortStep(true) : chosenBotHex->setBotLongStep(true);
    handlePlayerStep(selectedStep.second.goRow, selectedStep.second.goCol, fieldMatrix[selectedStep.second.goRow][selectedStep.second.goCol].get());
}

auto GameField::getPossibleMoves() -> std::vector<BotMoveData> {
    auto moveDataVec = std::vector<BotMoveData>();

    for (auto & row : fieldMatrix) {
        for (const auto & col : row) {
            if (col != nullptr) {
                auto hex = dynamic_cast<Hexagon*>(col.get());
                if (hex->getBotShortStep()) {
                    auto data = getMoveData(hex->getFieldRow(), hex->getFieldCol(), true);
                    moveDataVec.push_back(data);
                } else if (hex->getBotLongStep()) {
                    auto data = getMoveData(hex->getFieldRow(), hex->getFieldCol(), false);
                    moveDataVec.push_back(data);
                }
            }
        }
    }

    return moveDataVec;
}

auto GameField::getMoveData(int row, int col, bool isGreenStep) -> BotMoveData {

    auto data = BotMoveData();
    data.goRow = row;
    data.goCol = col;

    auto enemies = getEatEnemies(row, col);

    data.enemiesAround = enemies;
    data.gain = enemies;
    data.greenStep = isGreenStep;

    return data;
}

auto GameField::getEatEnemies(int row, int col) -> int {
    auto currentPlayerState = currentMovePlayer == Player::FIRST ? FieldState::PLAYER_ONE : FieldState::PLAYER_TWO;

    auto enemies = 0;
    auto startRow = row - 1;
    auto startCol = col - 1;

    auto endRow = startRow + 2;
    auto endCol = startCol + 2;
    for (auto i = startRow; i <= endRow; ++i) {
        if (i < 0 || i >= fieldMatrix.size()) continue;
        for (auto j = startCol; j <= endCol; ++j) {
            if (j < 0 || j >= fieldMatrix.size()) continue;
            if (stateMatrix[i][j] == FieldState::NOT_EXIST || stateMatrix[i][j] == FieldState::EMPTY || stateMatrix[i][j] == currentPlayerState) continue;
            if (i == row && j == col) continue;

            if (col < 4) {
                if (j == endCol && i == startRow || j == startCol && i == endRow) continue;
                enemies++;
            } else if (col == 4) {
                if (i == endRow && j != col) continue;
                enemies++;
            } else if (col > 4) {
                if (j == startCol && i == startRow || j == endCol && i == endRow) continue;
                enemies++;
            }
        }
    }

    return enemies;
}

auto GameField::canMoveTo(int fromRow, int toRow, int fromCol, int toCol) -> bool {
    auto absRowDifference = std::abs(fromRow - toRow);
    auto absColDifference = std::abs(fromCol - toCol);

    if (absRowDifference > 2 || absColDifference > 2) return false;

    auto rowDifference = fromRow - toRow;
    auto colDifference = fromCol - toCol;


    if (fromCol == 3 ) {
        if (rowDifference == 2 && colDifference < 0) return false;
        if (rowDifference == -1 && colDifference > 1) return false;
        if (rowDifference == -2 && (colDifference > 0 || colDifference < -1)) return false;
    }

    if (fromCol == 5) {
        if (rowDifference == 2 && colDifference > 0) return false;
        if (rowDifference == -1 && colDifference < -1) return false;
        if (rowDifference == -2 && (colDifference < 0 || colDifference > 1)) return false;
    }

    if (fromCol < 4) {
        if (rowDifference == 2 && colDifference < 0) return false;
        if (rowDifference == 1 && colDifference < -1) return false;
        if (rowDifference == -1 &&colDifference > 1) return false;
        if (rowDifference == -2 && colDifference > 0) return false;
    }

    if (fromCol > 5) {
        if (rowDifference == 2 && colDifference > 0) return false;
        if (rowDifference == 1 && colDifference > 1) return false;
        if (rowDifference == -1 && colDifference < -1) return false;
        if (rowDifference == 02 && colDifference < 0) return false;
    }


    if (fromCol == 4) {
        if (rowDifference == -1 && absColDifference > 1) return false;
        if (rowDifference == -2 && colDifference != 0) return false;
    }

    return true;
}

auto GameField::eatEnemy(Hexagon *clickedHex) -> void {
    auto clickedRow = clickedHex->getFieldRow();
    auto clickedCol = clickedHex->getFieldCol();

    auto eatColor = currentMovePlayer == Player::FIRST ? playerOne->getPlayerColor() : playerTwo->getPlayerColor();
    auto replacementState = currentMovePlayer == Player::FIRST ? FieldState::PLAYER_ONE : FieldState::PLAYER_TWO;

    auto eat = [eatColor, replacementState](auto row, auto col) -> void {
        if (stateMatrix[row][col] > 0 &&
            static_cast<int>(currentMovePlayer) != static_cast<int>(stateMatrix[row][col])) {
            auto figureToEat = dynamic_cast<PlayerFigure *>(playerFigures[row][col].get());
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
                    )
                eat(i, j);


            if (clickedCol < 4)
                if (
                        (rowDifference == 1 && colDifference == 1) ||
                        (rowDifference == -1 && colDifference == -1)
                        )
                    eat(i, j);


            if (clickedCol == 4 && rowDifference == 1 && (std::abs(colDifference)) <= 1) eat(i, j);

            if (clickedCol > 4)
                if (
                        (rowDifference == 1 && colDifference == -1) ||
                        (rowDifference == -1 && colDifference == 1)
                        )
                    eat(i, j);


        }
}

auto GameField::finishGame(bool buildDialog) -> void {
    auto winner = currentMovePlayer == Player::FIRST ? FieldState::PLAYER_TWO : FieldState::PLAYER_ONE;
    auto winnerString = winner == FieldState::PLAYER_ONE ? "Winner: Player One" : "Winner: Player Two";
    auto playerOneColor = playerOne->getPlayerColor();
    auto playerTwoColor = playerTwo->getPlayerColor();

    for (auto row = 0; row < fieldMatrix.size(); ++row) {
        for (auto col = 0; col < fieldMatrix[row].size(); ++col) {
            if (fieldMatrix[row][col] != nullptr) {
                if (stateMatrix[row][col] != winner) {
                    auto figure = std::make_unique<PlayerFigure>(
                        winner == FieldState::PLAYER_ONE ? playerOneColor : playerTwoColor
                    );
                    GameLayoutBuilder::setPlayerFigurePosition(figure.get(), fieldMatrix[row][col]->getPosition());
                    stateMatrix[row][col] = winner;
                    playerFigures[row][col] = std::move(figure);
                }
            }
        }
    }



    if (winner == FieldState::PLAYER_ONE) {
        playerOneCountBar->setCountedItems(58);
        movePlayerLabel->setColor(playerOneColor);
    } else {
        playerTwoCountBar->setCountedItems(58);
        movePlayerLabel->setColor(playerTwoColor);
    }

    freeSpaceLabel->setText("Free space left: 0");
    movePlayerLabel->setText(winnerString);
    isGameFinished = true;

    if (buildDialog) {
        GameInfoLayoutBuilder::buildFinishedGameInfo();
        GameInfoLayoutBuilder::build();
    }
}

auto GameField::getAllAvailableSteps() -> int {
    auto currentPlayerState = currentMovePlayer == Player::FIRST ? FieldState::PLAYER_ONE : FieldState::PLAYER_TWO;
    auto allAvailableSteps = 0;
    for (auto row = 0; row < stateMatrix.size(); ++row)
        for (auto col = 0; col < stateMatrix[row].size(); ++col) {
            if (stateMatrix[row][col] == currentPlayerState) {
                drawBorders(row, col, true);
                auto availableSteps = getClickedHexAvailableSteps();
                if (availableSteps > 0) allAvailableSteps++;
                clearBorders();
            }
        }

    return allAvailableSteps;
}

auto GameField::getClickedHexAvailableSteps() -> int {
    int availableSteps = -1;

    for (auto const& fieldRow : fieldMatrix)
        for (auto const &field : fieldRow)
            if (field != nullptr) {
                auto hex = dynamic_cast<Hexagon*>(field.get());
                if (
                        hex->getBotLongStep() ||
                        hex->getBotShortStep() ||
                        hex->getBorderColor() == sf::Color::Green ||
                        hex->getBorderColor() == sf::Color::Yellow
                ) availableSteps++;
            }

    return availableSteps;
}

auto GameField::drawBorders(int clickedRow, int clickedCol, bool isBot) -> void {

    auto rowDifference = int();
    auto colDifference = int();
    auto drawCondition = bool();

    auto drawBorder = [isBot](Hexagon* hex, sf::Color const& drawColor) -> void {
        if (drawColor == sf::Color::Yellow) isBot ? hex->setBotLongStep(true) : hex->drawYellowBorder();
        else if (drawColor == sf::Color::Green) isBot ? hex->setBotShortStep(true) : hex->drawGreenBorder();
    };

    for (int i = 0; i < fieldMatrix.size(); ++i)
        for (int j = 0; j < fieldMatrix[i].size(); ++j) {
            if (fieldMatrix[i][j] != nullptr) {
                auto hex = dynamic_cast<Hexagon *>(fieldMatrix[i][j].get());

                drawCondition = stateMatrix[i][j] == FieldState::EMPTY;
                rowDifference = clickedRow - i;
                colDifference = clickedCol - j;

                if (drawCondition) {

                    // YELLOW BORDERS ===========================================================================
                    if ((rowDifference == 0 && (std::abs(colDifference) == 2))) drawBorder(hex, sf::Color::Yellow);

                    if (clickedCol == 4) {
                        if (rowDifference == -1 && (std::abs(colDifference)) == 1) drawBorder(hex, sf::Color::Yellow);
                        if (rowDifference == -2 && colDifference == 0) drawBorder(hex, sf::Color::Yellow);
                        if (rowDifference == 2 && (std::abs(colDifference) <= 2)) drawBorder(hex, sf::Color::Yellow);
                        if (rowDifference == 1 && (std::abs(colDifference) == 2)) drawBorder(hex, sf::Color::Yellow);
                    }

                    if (clickedCol > 4) {
                        if (rowDifference == -2 && colDifference == 2 && clickedCol != 5) drawBorder(hex, sf::Color::Yellow);
                        if (rowDifference == 2 && (colDifference == -1 || colDifference == -2 || colDifference == 0))
                            drawBorder(hex, sf::Color::Yellow);
                        if (rowDifference == 1 && colDifference == 1) drawBorder(hex, sf::Color::Yellow);
                        if (rowDifference == -1 && colDifference == 2) drawBorder(hex, sf::Color::Yellow);
                        if (rowDifference == 1 && colDifference == -2) drawBorder(hex, sf::Color::Yellow);
                        if (rowDifference == -2 && (colDifference == 1 || colDifference == 0)) drawBorder(hex, sf::Color::Yellow);
                        if (rowDifference == -1 && (colDifference == -1)) drawBorder(hex, sf::Color::Yellow);
                    }

                    if (clickedCol < 4) {
                        if (rowDifference == 2 && (colDifference == 1 || colDifference == 2 || colDifference == 0))
                            drawBorder(hex, sf::Color::Yellow);
                        if (rowDifference == 1 && colDifference == -1) drawBorder(hex, sf::Color::Yellow);
                        if (rowDifference == -1 && colDifference == -2) drawBorder(hex, sf::Color::Yellow);
                        if (rowDifference == 1 && colDifference == 2) drawBorder(hex, sf::Color::Yellow);
                        if (rowDifference == -2 && (colDifference == -1 || colDifference == 0)) drawBorder(hex, sf::Color::Yellow);
                        if (rowDifference == -2 && colDifference == -2 && clickedCol != 3) drawBorder(hex, sf::Color::Yellow);
                        if (rowDifference == -1 && (colDifference == 1)) drawBorder(hex, sf::Color::Yellow);
                    }

                    if (clickedCol == 3) {
                        if (rowDifference == 1 && colDifference == -2) drawBorder(hex, sf::Color::Yellow);
                        if (rowDifference == -1 && colDifference == -2) drawBorder(hex, sf::Color::Yellow);
                    }

                    if (clickedCol == 5) {
                        if (rowDifference == -1 && colDifference == 2) drawBorder(hex, sf::Color::Yellow);
                        if (rowDifference == 1 && colDifference == 2) drawBorder(hex, sf::Color::Yellow);
                    }

                    // GREEN BORDERS ===========================================================================
                    if ((rowDifference == 0 && (std::abs(colDifference) == 1)) ||
                        (std::abs(rowDifference) == 1 && colDifference == 0))
                        drawBorder(hex, sf::Color::Green);

                    if (clickedCol < 4) if (rowDifference == -1 && colDifference == -1) drawBorder(hex, sf::Color::Green);

                    if (clickedCol <= 4) if (rowDifference == 1 && colDifference == 1) drawBorder(hex, sf::Color::Green);

                    if (clickedCol >= 4) if (rowDifference == 1 && colDifference == -1) drawBorder(hex, sf::Color::Green);

                    if (clickedCol > 4) if (rowDifference == -1 && colDifference == 1) drawBorder(hex, sf::Color::Green);


                }
            }
        }
}

auto GameField::clearBorders() -> void {
    for (auto const &row: fieldMatrix)
        for (auto const &hex: row)
            if (hex != nullptr) {
                auto hexField =dynamic_cast<Hexagon *>(hex.get());
                hexField->setBorderColor(Hexagon::defaultBorderColor);
                hexField->setBotShortStep(false);
                hexField->setBotLongStep(false);
            }

}

auto GameField::resetGameState() -> void {

    GameField::clearBorders();
    isLocked = true;
    isGameFinished = false;


    for (auto &stateRow: stateMatrix)
        for (auto &fieldState: stateRow)
            if (static_cast<int>(fieldState) > 0)
                fieldState = FieldState::EMPTY;

    for (auto &figRow: playerFigures)
        for (auto &figure: figRow)
            figure = nullptr;

    GameStatistic::resetGameStatistic();
    GameLayoutBuilder::initDefaultPlayersPositions();
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