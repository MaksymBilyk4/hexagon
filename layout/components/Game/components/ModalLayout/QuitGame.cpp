#include "./QuitGame.hpp"
#include <iostream>

bool QuitGame::isOpened = false;
bool QuitGame::lockBackground = false;
std::vector<std::unique_ptr<Component>> QuitGame::components;

auto QuitGame::show() -> void {
    isOpened = true;
    lockBackground = true;
    for (auto &comp : components)
        if (comp != nullptr) comp->show();

}

auto QuitGame::hide() -> void {
    isOpened = false;
    for (auto &comp : components)
        if (comp != nullptr) comp -> hide();
}

auto QuitGame::buildQuitGameLayout(sf::RenderWindow &renderWindow) -> void {
    auto modal = std::make_unique<Modal>(renderWindow, 850, 500);
    modal->setVerticalGradient(sf::Color(0,0,0,200), sf::Color(0,0,0,200));

    auto title = std::make_unique<TextWrapper>();
    title->setText("Really quit the game?");
    title->setPosition({400, 325});
    title->setFontSize(30);
    title->setFont(Fonts::SIXTY_FOUR_REGULAR_FONT);
    title->setColor(sf::Color::White);

    auto noBtn = std::make_unique<Button>(sf::Vector2f(400, 675), sf::Vector2f(650, 40), "No");
    auto yesNoSaveBtn = std::make_unique<Button>(sf::Vector2f(750, 550), sf::Vector2f(300, 40), "Yes. No save");
//    auto empty = std::make_unique<Button>(sf::Vector2f(0, 0), sf::Vector2f(0, 0), "");
    auto yesSaveBtn = std::make_unique<Button>(sf::Vector2f(400, 550), sf::Vector2f(300, 40), "Yes. Save");


    noBtn->bindOnClick([]() -> void {
        QuitGame::hide();
    });

    yesNoSaveBtn->bindOnClick([]() -> void {
        GameField::resetGameState();
        if (!GameField::currentLoadedGame.empty()) GameField::currentLoadedGame = "";
        QuitGame::hide();
        GameLayoutBuilder::unbuild();
        HomeLayoutBuilder::build();
        IllegalMove::lockBackground = false;
        QuitGame::lockBackground = false;
    });

    yesSaveBtn->bindOnClick([]() -> void {
        if (!GameField::currentLoadedGame.empty()) GameFileStore::saveOldGame(GameField::currentLoadedGame);
        else GameFileStore::saveNewGame();
        GameField::resetGameState();
        GameLayoutBuilder::unbuild();
        HomeLayoutBuilder::build();
        QuitGame::hide();
        IllegalMove::lockBackground = false;
        QuitGame::lockBackground = false;
    });

    components.push_back(std::move(modal));
    components.push_back(std::move(title));
    components.push_back(std::move(noBtn));
    components.push_back(std::move(yesNoSaveBtn));
    components.push_back(std::move(yesSaveBtn));
//    components.push_back(std::move(empty));

}