#include "./GameLayoutBuilder.hpp"

std::unique_ptr<Button> GameLayoutBuilder::stats;
std::unique_ptr<Button> GameLayoutBuilder::quitButton;


auto GameLayoutBuilder::build(bool isFileBuild) -> void {
    GameField::drawState = true;
    auto currentMode = std::string("Game mode: ");
    if (!isFileBuild) {
        currentMode += HomeLayoutBuilder::modeGroup->getActiveCheckBoxActionContext() ==
                       std::to_string(GameMode::PLAYER_VS_PLAYER) ? "PLAYER VS PLAYER" : "PLAYER VS COMPUTER";
        GameStatistic::gameMode = HomeLayoutBuilder::modeGroup->getActiveCheckBoxActionContext() ==
                                  std::to_string(GameMode::PLAYER_VS_PLAYER) ? GameMode::PLAYER_VS_PLAYER
                                                                             : GameMode::PLAYER_VS_COMPUTER;
    } else
        currentMode += GameStatistic::gameMode == GameMode::PLAYER_VS_PLAYER ? "PLAYER VS PLAYER" : "PLAYER VS COMPUTER";
    GameField::gameModeLabel->setText(currentMode);

    if (GameField::isGameFinished) {
        stats->show();
    }
    quitButton->show();
}

auto GameLayoutBuilder::unbuild() -> void {
    GameField::drawState = false;
    stats->hide();
    quitButton->hide();
}

auto GameLayoutBuilder::prepareGameField(sf::RenderWindow &renderWindow) -> void {

    GameField::initGameItems();
    QuitGame::buildQuitGameLayout(renderWindow);
    IllegalMove::buildIllegalMoveLayout(renderWindow);
    GameLayoutBuilder::buildGameLayoutItems();

    auto hexHeight = 105.f;
    auto hexHeightHalf = hexHeight / 2;
    auto puzzleGap = 90.f;

    auto startXPos = 325.f;
    auto startYPos = 200.f;

    auto iterationYPos = startYPos;
    auto reduceHexCount = 1;

    auto updateCoordinates =
            [&iterationYPos, &startXPos, hexHeightHalf, puzzleGap]
                    (int currentCol) -> void {
                iterationYPos = currentCol < 4 ? iterationYPos - hexHeightHalf : iterationYPos + hexHeightHalf;
                startXPos += puzzleGap;
            };

    for (int row = 0; row <= 9; ++row) {
        startXPos = 325.f;
        startYPos += hexHeight;
        for (int col = 0; col <= 9; ++col) {
            if (row == 3 && col == 4 || (row == 4 && (col == 3 || col == 5))) {
                updateCoordinates(col);
                continue;
            } else if (row > 4 && (col < reduceHexCount || col >= 9 - reduceHexCount)) {
                updateCoordinates(col);
                continue;
            }

            auto hex = std::make_unique<Hexagon>();
            hex->setPosition({startXPos, iterationYPos});
            hex->setFieldRow(row);
            hex->setFieldCol(col);
            GameField::fieldMatrix[row][col] = std::move(hex);
            GameField::stateMatrix[row][col] = FieldState::EMPTY;
            updateCoordinates(col);
        }
        iterationYPos = startYPos;
        if (row > 4) reduceHexCount++;
    }

    initDefaultPlayersPositions();
}

auto GameLayoutBuilder::initDefaultPlayersPositions() -> void {
    GameField::stateMatrix[0][0] = FieldState::PLAYER_ONE;
    GameField::stateMatrix[0][4] = FieldState::PLAYER_TWO;
    GameField::stateMatrix[0][8] = FieldState::PLAYER_ONE;

    GameField::stateMatrix[4][0] = FieldState::PLAYER_TWO;
    GameField::stateMatrix[8][4] = FieldState::PLAYER_ONE;
    GameField::stateMatrix[4][8] = FieldState::PLAYER_TWO;

    auto playerOneColor = GameField::playerOne->getPlayerColor();
    auto playerTwoColor = GameField::playerTwo->getPlayerColor();

    for (auto i = 0; i < GameField::stateMatrix.size(); ++i)
        for (auto j = 0; j < GameField::stateMatrix[i].size(); ++j) {
            if (GameField::stateMatrix[i][j] != FieldState::EMPTY &&
                GameField::stateMatrix[i][j] != FieldState::NOT_EXIST) {
                auto playerFigure = std::make_unique<PlayerFigure>(
                        GameField::stateMatrix[i][j] == FieldState::PLAYER_ONE ? playerOneColor : playerTwoColor
                );

                auto hexPosition = GameField::fieldMatrix[i][j]->getPosition();
                setPlayerFigurePosition(playerFigure.get(), hexPosition);
                GameField::playerFigures[i][j] = std::move(playerFigure);
            }
        }

}

auto GameLayoutBuilder::setPlayerFigurePosition(PlayerFigure *figure, sf::Vector2f const &hexPosition) -> void {
    figure->setPosition({
                                hexPosition.x - 15,
                                hexPosition.y + 30
                        });
}

auto GameLayoutBuilder::buildGameLayoutItems() -> void {
    auto statsButton = std::make_unique<Button>(sf::Vector2f(1050, 850), sf::Vector2f(320, 50), "SHOW STATISTICS");
    statsButton->bindOnClick([]() -> void {
        if (!QuitGame::isOpened && !IllegalMove::isOpened && !GameInfoLayoutBuilder::gameFinishedModalOpen) {
            GameInfoLayoutBuilder::buildFinishedGameInfo();
            GameInfoLayoutBuilder::build();
        }
    });
    statsButton->setButtonTextFontSize(30);
    statsButton->setButtonTextPosition({statsButton->getButtonTextPosition().x - 30, statsButton->getButtonTextPosition().y});
    stats = std::move(statsButton);


    auto leaveGameButton = std::make_unique<Button>(sf::Vector2f(150, 850), sf::Vector2f(140, 50), "QUIT");

    leaveGameButton->setButtonTextFontSize(30);
    leaveGameButton->setButtonTextPosition(
            {leaveGameButton->getButtonTextPosition().x - 10, leaveGameButton->getButtonTextPosition().y});

    leaveGameButton->bindOnClick([]() -> void {
        if (!QuitGame::isOpened && !IllegalMove::isOpened && !GameInfoLayoutBuilder::gameFinishedModalOpen) {
            QuitGame::show();
        }
    });

    auto currentMoveLabel = std::make_unique<TextWrapper>(sf::Vector2f(1100, 750), "Current player: 1");
    currentMoveLabel->setColor(GameField::playerOne->getPlayerColor());
    currentMoveLabel->setFontSize(30);

    auto freeSpace = std::make_unique<TextWrapper>(sf::Vector2f(1100, 800), "Free Space Left: 58");
    freeSpace->setColor(sf::Color::White);
    freeSpace->setFontSize(30);

    auto mode = std::string("Game mode: ");
    auto gameModeL = std::make_unique<TextWrapper>(sf::Vector2f(960, 920), "Game mode: ");
    gameModeL->setColor(sf::Color::White);
    gameModeL->setFontSize(26);

    auto playerOneBar = std::make_unique<CountBar>(sf::Vector2f(1270, 600), GameField::playerOne->getPlayerColor(),
                                                   GameField::playerOne->getFieldCount());
    auto playerTwoBar = std::make_unique<CountBar>(sf::Vector2f(1270, 675), GameField::playerTwo->getPlayerColor(),
                                                   GameField::playerTwo->getFieldCount());

    GameField::playerOneCountBar = std::move(playerOneBar);
    GameField::playerTwoCountBar = std::move(playerTwoBar);

    GameField::gameModeLabel = std::move(gameModeL);
    GameField::freeSpaceLabel = std::move(freeSpace);
    GameField::movePlayerLabel = std::move(currentMoveLabel);

    quitButton = std::move(leaveGameButton);
}
