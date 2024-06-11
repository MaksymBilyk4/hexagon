#include "./GameLayoutBuilder.hpp"

std::vector<std::unique_ptr<Component>> GameLayoutBuilder::components;
std::vector<std::unique_ptr<Component>> GameLayoutBuilder::exitLayoutComponents;

auto GameLayoutBuilder::build() -> void {
    GameField::drawState = true;

    for (auto const& comp : components)
        comp->show();

}

auto GameLayoutBuilder::unbuild() -> void {
    GameField::drawState = false;

    for (auto const& comp : components)
        comp->hide();
}

auto GameLayoutBuilder::prepareGameField(sf::RenderWindow &renderWindow) -> void {

    GameField::initGameItems();
    GameLayoutBuilder::makeExitModal(renderWindow);
    GameLayoutBuilder::makeLeaveGameButton();
    GameLayoutBuilder::makeCurrentPlayerMoveLabel();
    GameLayoutBuilder::makePlayersCountBar();

    auto leftXPosition = static_cast<float>(renderWindow.getSize().x / 4 - Hexagon::defaultRadius / 4);
    auto rightXPosition = static_cast<float>(renderWindow.getSize().x - 28 * Hexagon::defaultRadius / 4);
    auto yPosition = (renderWindow.getSize().y / 4.96);
    auto counter = 1;
    int reversed = 8;

    for (int i = 5; i < 10; i++) {

        for (auto j = 0; j < i; j++) {
            if (i == 8 && j == 4 || i == 9 && j == 3) {
                yPosition += Hexagon::defaultRadius * 2;
                continue;
            }

            auto leftFieldItem = std::make_unique<Hexagon>();
            leftFieldItem->setPosition({leftXPosition, static_cast<float>(yPosition)});

            if (i != 9) {
                auto rightFieldItem = std::make_unique<Hexagon>();
                rightFieldItem->setPosition({rightXPosition, static_cast<float >(yPosition)});
                rightFieldItem->setFieldRow(j);
                rightFieldItem->setFieldCol(reversed);
                GameField::fieldMatrix[j][reversed] = std::move(rightFieldItem);
                GameField::stateMatrix[j][reversed] = FieldState::EMPTY;
            }

            leftFieldItem->setFieldRow(j);
            leftFieldItem->setFieldCol(i - 5);
            GameField::fieldMatrix[j][i - 5] = std::move(leftFieldItem);
            GameField::stateMatrix[j][i - 5] = FieldState::EMPTY;

            yPosition += Hexagon::defaultRadius * 2;
        }

        counter = counter + 2;
        leftXPosition = leftXPosition + Hexagon::defaultRadius * 2 - 11;
        rightXPosition = rightXPosition - Hexagon::defaultRadius * 2 + 11;
        yPosition = (renderWindow.getSize().y / 4.5) - counter * Hexagon::defaultRadius / 2;
        reversed--;
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
            if (GameField::stateMatrix[i][j] != FieldState::EMPTY && GameField::stateMatrix[i][j] != FieldState::NOT_EXIST) {
                auto playerFigure = std::make_unique<PlayerFigure>(
                    GameField::stateMatrix[i][j] == FieldState::PLAYER_ONE ? playerOneColor : playerTwoColor
                );

                auto hexPosition = GameField::fieldMatrix[i][j]->getPosition();
                setPlayerFigurePosition(playerFigure.get(), hexPosition);
                GameField::playerFigures[i][j] = std::move(playerFigure);
            }
        }

}

auto GameLayoutBuilder::setPlayerFigurePosition(PlayerFigure* figure, sf::Vector2f const& hexPosition) -> void {
    figure->setPosition({
        hexPosition.x - 15,
        hexPosition.y + 30
    });
}

// DRAWING COMPONENTS =================================================================================================

auto GameLayoutBuilder::makeLeaveGameButton() -> void {
    auto leaveGameButton = std::make_unique<Button>(sf::Vector2f(150, 850), sf::Vector2f(140, 50), "QUIT");

    leaveGameButton->setButtonTextFontSize(30);
    leaveGameButton->setButtonTextPosition({leaveGameButton->getButtonTextPosition().x - 10, leaveGameButton->getButtonTextPosition().y});

    leaveGameButton->bindOnClick([]() -> void {
        for (auto &comp : exitLayoutComponents)
            comp->show();
    });

    components.push_back(std::move(leaveGameButton));
}

auto GameLayoutBuilder::makeExitModal(sf::RenderWindow& renderWindow) -> void {
    auto modal = std::make_unique<Modal>(renderWindow, 850, 500);

    modal->setVerticalGradient(sf::Color(0,0,0,200), sf::Color(0,0,0,200));

    auto title = std::make_unique<TextWrapper>();
    title->setText("Really quit the game?");
    title->setPosition({400, 325});
    title->setFontSize(30);
    title->setFont(Fonts::SIXTY_FOUR_REGULAR_FONT);
    title->setColor(sf::Color::White);

    auto yesSaveBtn = std::make_unique<Button>(sf::Vector2f(400, 550), sf::Vector2f(300, 40), "Yes. Save");
    auto yesNoSaveBtn = std::make_unique<Button>(sf::Vector2f(750, 550), sf::Vector2f(300, 40), "Yes. No save");

    auto noBtn = std::make_unique<Button>(sf::Vector2f(400, 675), sf::Vector2f(650, 40), "No");

    noBtn->bindOnClick([]() -> void {
        for (auto &comp : exitLayoutComponents)
            comp->hide();
    });

    yesNoSaveBtn->bindOnClick([]() -> void {
        GameField::resetGameState();
        for (auto &comp : exitLayoutComponents)
            comp->hide();
        GameLayoutBuilder::unbuild();
        HomeLayoutBuilder::build();
    });

    yesSaveBtn->bindOnClick([]() -> void {
        if (!GameField::currentLoadedGame.empty()) GameFileStore::saveOldGame(GameField::currentLoadedGame);
        else GameFileStore::saveNewGame();

        GameField::resetGameState();
        for (auto &comp : exitLayoutComponents)
            comp->hide();
        GameLayoutBuilder::unbuild();
        HomeLayoutBuilder::build();
    });


    exitLayoutComponents.push_back(std::move(yesSaveBtn));
    exitLayoutComponents.push_back(std::move(yesNoSaveBtn));
    exitLayoutComponents.push_back(std::move(noBtn));
    exitLayoutComponents.push_back(std::move(modal));
    exitLayoutComponents.push_back(std::move(title));
}

auto GameLayoutBuilder::makeCurrentPlayerMoveLabel() -> void {
    auto currentMoveLabel = std::make_unique<TextWrapper>(sf::Vector2f(1100, 850), "Current player: 1");
    currentMoveLabel->setColor(GameField::playerOne->getPlayerColor());
    currentMoveLabel->setFontSize(30);
    GameField::movePlayerLabel = std::move(currentMoveLabel);
}

auto GameLayoutBuilder::makePlayersCountBar() -> void {
    auto playerOneBar = std::make_unique<CountBar>(sf::Vector2f(1270, 700), GameField::playerOne->getPlayerColor(), GameField::playerOne->getFieldCount());
    auto playerTwoBar = std::make_unique<CountBar>(sf::Vector2f(1270, 775), GameField::playerTwo->getPlayerColor(), GameField::playerTwo->getFieldCount());

    GameField::playerOneCountBar = std::move(playerOneBar);
    GameField::playerTwoCountBar = std::move(playerTwoBar);
}