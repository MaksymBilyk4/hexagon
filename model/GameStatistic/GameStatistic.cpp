#include "./GameStatistic.hpp"

auto GameStatistic::resetGameStatistic() -> void {

    GameField::currentSelected = nullptr;
    GameField::playerFigureSelected = false;

    GameField::playerOne->setFieldCount(3);
    GameField::playerTwo->setFieldCount(3);
    GameField::currentMovePlayer = Player::FIRST;
    GameField::movePlayerLabel->setText("Current Player: 1");
    GameField::freeSpaceLabel->setText("Free Space Left: 52");

    GameField::playerOneCountBar->setCountedItems(3);
    GameField::playerTwoCountBar->setCountedItems(3);

    gameMode = GameMode::PLAYER_VS_COMPUTER;

    stepsDone = 0;

    allFiguresEaten = 0;

    firstPlayerAte = 0;

    secondPlayerAte = 0;

    spaceLeft = 52;

    winner = Player::FIRST;

    GameStatistic::printStatistic();

}

auto GameStatistic::updateGameStatistic(bool isGreenStep) -> void {
    auto currentPlayerBar = GameField::currentMovePlayer == Player::FIRST ? GameField::playerOneCountBar.get() : GameField::playerTwoCountBar.get();
    auto oppositePlayerBar = GameField::currentMovePlayer == Player::FIRST ? GameField::playerTwoCountBar.get() : GameField::playerOneCountBar.get();

    currentPlayerBar->increaseCounter(GameField::gainedFields);
    oppositePlayerBar->decreaseCounter(isGreenStep ? GameField::gainedFields - 1 : GameField::gainedFields);
    allFiguresEaten += GameField::gainedFields;

    auto left = 0;
    for (auto &row : GameField::stateMatrix)
        left += std::count_if(
                row.begin(),
                row.end(),
                [](FieldState &state) -> bool {
                    return state == FieldState::EMPTY;
                }
        );

    spaceLeft = left;
    auto leftSpace = std::string("Free Space Left: ");
    leftSpace += std::to_string(spaceLeft);

    GameField::freeSpaceLabel->setText(leftSpace);

    if (GameField::currentMovePlayer == Player::FIRST) GameStatistic::firstPlayerAte += GameField::gainedFields;
    else GameStatistic::secondPlayerAte += GameField::gainedFields;

    GameStatistic::stepsDone++;

    GameField::playerOne->setFieldCount(GameField::playerOneCountBar->getCountedItems());
    GameField::playerTwo->setFieldCount(GameField::playerTwoCountBar->getCountedItems());
}

auto GameStatistic::printStatistic() -> void {

    fmt::println("--------------------------");
    fmt::println("Current move player: {}\nPlayer one figures: {}\nPlayer two figures: {}\nSteps done: {}\nFigures eaten: {}\nFirst player ate: {}\nSecond player ate: {}\nFree space: {}\nGame mode: {}",
                 static_cast<int>(GameField::currentMovePlayer),
                 GameField::playerOneCountBar->getCountedItems(),
                 GameField::playerTwoCountBar->getCountedItems(),
                 stepsDone,
                 allFiguresEaten,
                 firstPlayerAte,
                 secondPlayerAte,
                 spaceLeft,
                 static_cast<int>(gameMode) == 1 ? "PLAYER_VS_COMPUTER" : "PLAYER_VS_PLAYER"
                 );

}