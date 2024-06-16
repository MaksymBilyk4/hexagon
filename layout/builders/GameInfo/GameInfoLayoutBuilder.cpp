#include "./GameInfoLayoutBuilder.hpp"


std::unique_ptr<Modal> GameInfoLayoutBuilder::infoModal;
std::unique_ptr<TextWrapper> GameInfoLayoutBuilder::infoTitle;
std::unique_ptr<Button> GameInfoLayoutBuilder::infoLeaveButton;
std::vector<std::unique_ptr<Component>> GameInfoLayoutBuilder::buttons;

std::vector<std::unique_ptr<Component>> GameInfoLayoutBuilder::components;

bool GameInfoLayoutBuilder::gameFinishedModalOpen = false;
sf::Vector2f GameInfoLayoutBuilder::middlePos;

auto GameInfoLayoutBuilder::build() -> void {
    for (auto &comp : components)
        if (comp != nullptr) comp->show();

    infoModal->show();
    infoTitle->show();
    infoLeaveButton->show();
}

auto GameInfoLayoutBuilder::unbuild() -> void {
    for (auto &btn : buttons)
        btn->hide();

    buttons.clear();

    for (auto &comp : components)
        if (comp != nullptr) comp->hide();
    components.clear();

    infoTitle->hide();
    infoModal->hide();
    infoLeaveButton->hide();
}

auto GameInfoLayoutBuilder::buildBestGames() -> void {
    infoModal->setSize(sf::Vector2f(1100, 900));
    infoModal->setPosition({middlePos.x - infoModal->getSize().x / 2, 20});
    infoModal->setVerticalGradient(sf::Color(191, 64, 191, 150), sf::Color(75, 0, 130, 150));


    infoTitle->setText("Your best games");
    infoTitle->setFontSize(60);
    infoTitle->centerHorizontalAxis(infoModal->getPosition().x, infoModal->getSize().x, infoModal->getPosition().y + 15);

    infoLeaveButton->setText("Leave to main menu");
    infoLeaveButton->setPosition({(middlePos.x - infoLeaveButton->getSize().x / 2), 825});

    infoLeaveButton->bindOnClick([]() -> void {
        GameInfoLayoutBuilder::unbuild();
        HomeLayoutBuilder::build();
    });

}

auto GameInfoLayoutBuilder::buildSavedGames() -> void {
    infoModal->setSize(sf::Vector2f(1100, 900));
    infoModal->setPosition({middlePos.x - infoModal->getSize().x / 2, 20});
    infoModal->setVerticalGradient(sf::Color(191, 64, 191, 150), sf::Color(75, 0, 130, 150));

    infoTitle->setFontSize(60);
    infoTitle->setText("Your saved games");
    infoTitle->centerHorizontalAxis(infoModal->getPosition().x, infoModal->getSize().x, infoModal->getPosition().y + 15);
    infoLeaveButton->setText("Leave to main menu");
    infoLeaveButton->setPosition({(middlePos.x - infoLeaveButton->getSize().x / 2), 825});

    infoLeaveButton->bindOnClick([]() -> void {
        GameInfoLayoutBuilder::unbuild();
        HomeLayoutBuilder::build();
    });

    auto path = std::filesystem::path(Path::GAME_SAVE_PATH);

    auto games = std::vector<std::filesystem::path>();

    for (auto const& entry : std::filesystem::directory_iterator(path)) {
        games.push_back(entry.path());
    }

    auto left = 250.f;
    auto mid = 600.f;
    auto right = 950.f;
    auto y = 100.f;

    auto step = 0;

    for (auto  i = 0 ; i < games.size(); i++) {
        if (i % 3 == 0) {
            y += 60;
            step = 0;
        }

        auto position = sf::Vector2f(left, y);

        if (step == 1) position.x = mid;
        else if (step == 2) position.x = right;

        auto fileButton = std::make_unique<Button>(position, sf::Vector2f(200, 40), games[i].filename().string());
        fileButton->setButtonTextColor(sf::Color::White);
        fileButton->setBorderColor(sf::Color::Green);
        fileButton->setColor(sf::Color::Black);
        fileButton->setHoverColor(sf::Color::Black);
        fileButton->setBorderWidth(4);
        fileButton->setButtonTextPosition({position.x + 10, position.y + 5});
        fileButton->bindOnClick([games, i]() -> void {
            GameFileStore::uploadGame(games[i].string());
            GameInfoLayoutBuilder::unbuild();
            GameLayoutBuilder::build(true);
        });


        buttons.push_back(std::move(fileButton));
        step++;
    }

    for (auto &btn : buttons)
        btn->show();
}

auto GameInfoLayoutBuilder::buildFinishedGameInfo() -> void {
    gameFinishedModalOpen = true;
    IllegalMove::lockBackground = true;

    auto text = std::string();
    if (GameField::isGameFinished) text = GameStatistic::winner == Player::FIRST ? "Winner: Player one" : "Winner: Player Two";
    else text = "Winner: game is on";


    infoModal->setSize(sf::Vector2f(800, 500));
    infoModal->setPosition({middlePos.x - infoModal->getSize().x / 2, 200});
    infoModal->setVerticalGradient(sf::Color(0,0,0,200), sf::Color(0,0,0,200));


    infoTitle->setText(text);
    infoTitle->setFontSize(40);
    infoTitle->centerHorizontalAxis(infoModal->getPosition().x, infoModal->getSize().x, infoModal->getPosition().y + 15);

    infoLeaveButton->setText("Close statistics");
    infoLeaveButton->setPosition({(middlePos.x - infoLeaveButton->getSize().x / 2), 570});

    infoLeaveButton->bindOnClick([]() -> void {
        GameInfoLayoutBuilder::unbuild();
        gameFinishedModalOpen = false;
    });

    text = "Steps done: " + std::to_string(GameStatistic::stepsDone);
    auto stepsDone = std::make_unique<TextWrapper>(sf::Vector2f (400, 300), text);

    text = "All figures eaten: " + std::to_string(GameStatistic::allFiguresEaten);
    auto allFiguresEaten = std::make_unique<TextWrapper>(sf::Vector2f(400, 350), text);

    text = "Player one all figures eaten: " + std::to_string(GameStatistic::firstPlayerAte);
    auto playerOneAte = std::make_unique<TextWrapper>(sf::Vector2f(400, 400), text);

    text = "Player two all figures eaten: " + std::to_string(GameStatistic::secondPlayerAte);
    auto playerTwoAte = std::make_unique<TextWrapper>(sf::Vector2f(400, 450), text);

    text = "Game mode: " + std::string(GameStatistic::gameMode == GameMode::PLAYER_VS_PLAYER ? "PLAYER VS PLAYER" : "PLAYER VS COMPUTER");
    auto gameMode = std::make_unique<TextWrapper>(sf::Vector2f(400, 500), text);

    stepsDone->setColor(sf::Color::White);
    allFiguresEaten->setColor(sf::Color::White);
    playerOneAte->setColor(sf::Color::White);
    playerTwoAte->setColor(sf::Color::White);
    gameMode->setColor(sf::Color::White);

    stepsDone->setFontSize(30);
    allFiguresEaten->setFontSize(30);
    playerOneAte->setFontSize(30);
    playerTwoAte->setFontSize(30);
    gameMode->setFontSize(30);

    components.push_back(std::move(stepsDone));
    components.push_back(std::move(allFiguresEaten));
    components.push_back(std::move(playerOneAte));
    components.push_back(std::move(playerTwoAte));
    components.push_back(std::move(gameMode));

}

auto GameInfoLayoutBuilder::initGameInfoComponents(sf::RenderWindow& renderWindow) -> void {
    auto modal = std::make_unique<Modal>(renderWindow, 1100, 900);
    middlePos = sf::Vector2f(renderWindow.getSize().x / 2, renderWindow.getSize().y / 2);

    auto leaveButton = std::make_unique<Button>(sf::Vector2f(0, 0), sf::Vector2f(500, 50), "Leave to main menu");
    leaveButton->setPosition({(renderWindow.getSize().x / 2 - leaveButton->getSize().x / 2), 825});
    leaveButton->setButtonTextFontSize(40);
    leaveButton->setButtonTextPosition({(renderWindow.getSize().x / 2 - leaveButton->getSize().x / 2) + 75, 825});

    leaveButton->bindOnClick([]() -> void {
        GameInfoLayoutBuilder::unbuild();
        HomeLayoutBuilder::build();
    });

    auto title = std::make_unique<TextWrapper>();
    title->setText("Your saved games");
    title->setColor(sf::Color::White);
    title->setFont(Fonts::SIXTY_FOUR_REGULAR_FONT);
    title->setFontSize(60);
    title->centerHorizontalAxis(modal->getPosition().x, modal->getSize().x, modal->getPosition().y + 15);

    infoModal = std::move(modal);
    infoTitle = std::move(title);
    infoLeaveButton = std::move(leaveButton);
}
