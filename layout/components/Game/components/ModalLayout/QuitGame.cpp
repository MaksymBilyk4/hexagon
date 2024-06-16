#include "./QuitGame.hpp"
#include <iostream>

bool QuitGame::isOpened = false;
bool QuitGame::lockBackground = false;
bool QuitGame::isTextFieldDrawAble = false;

std::vector<std::unique_ptr<Component>> QuitGame::components;

std::unique_ptr<TextField> QuitGame::textField = std::make_unique<TextField>(sf::Vector2f(300, 40));
std::unique_ptr<Button> QuitGame::confirmSaveButton;
std::unique_ptr<Button> QuitGame::cancelSaveButton;

auto QuitGame::show() -> void {
    isOpened = true;
    lockBackground = true;
    for (auto &comp: components)
        if (comp != nullptr) comp->show();

}

auto QuitGame::hide() -> void {
    isOpened = false;
    for (auto &comp: components)
        if (comp != nullptr) comp->hide();
}

auto QuitGame::buildQuitGameLayout(sf::RenderWindow &renderWindow) -> void {
    auto modal = std::make_unique<Modal>(renderWindow, 850, 500);
    modal->setVerticalGradient(sf::Color(0, 0, 0, 200), sf::Color(0, 0, 0, 200));

    auto title = std::make_unique<TextWrapper>();
    title->setText("Really quit the game?");
    title->setPosition({400, 325});
    title->setFontSize(30);
    title->setFont(Fonts::SIXTY_FOUR_REGULAR_FONT);
    title->setColor(sf::Color::White);

    auto noBtn = std::make_unique<Button>(sf::Vector2f(400, 675), sf::Vector2f(650, 40), "No");
    auto yesNoSaveBtn = std::make_unique<Button>(sf::Vector2f(750, 550), sf::Vector2f(300, 40), "Yes. No save");
    auto yesSaveBtn = std::make_unique<Button>(sf::Vector2f(400, 550), sf::Vector2f(300, 40), "Yes. Save");

    auto disableFileSaving = []() -> void {
        if (isTextFieldDrawAble) {
            isTextFieldDrawAble = false;
            confirmSaveButton->hide();
            cancelSaveButton->hide();
            textField->resetContent();
        }
    };

    noBtn->bindOnClick([&disableFileSaving]() -> void {
        disableFileSaving();
        QuitGame::hide();
    });

    yesNoSaveBtn->bindOnClick([&disableFileSaving]() -> void {
        disableFileSaving();
        GameField::resetGameState();
        if (!GameField::currentLoadedGame.empty()) GameField::currentLoadedGame = "";
        QuitGame::hide();
        GameLayoutBuilder::unbuild();
        HomeLayoutBuilder::build();
        IllegalMove::lockBackground = false;
        QuitGame::lockBackground = false;
    });

    yesSaveBtn->bindOnClick([]() -> void {
        if (!GameField::currentLoadedGame.empty()) {
            GameFileStore::saveOldGame(GameField::currentLoadedGame);
            GameField::resetGameState();
            GameLayoutBuilder::unbuild();
            HomeLayoutBuilder::build();
            QuitGame::hide();
            IllegalMove::lockBackground = false;
            QuitGame::lockBackground = false;
        } else if (!isTextFieldDrawAble) {
            textField->setLimit(true, 30);
            textField->setPosition({400, 450});
            isTextFieldDrawAble = true;
            confirmSaveButton->show();
            cancelSaveButton->show();
        }
    });

    auto confirmButton = std::make_unique<Button>(sf::Vector2f(750, 450), sf::Vector2f(150, 40), "Save file");
    confirmButton->bindOnClick([&disableFileSaving]() -> void {
        GameFileStore::saveNewGame(textField->getContent());
        fmt::println("wrote content by user: {}", textField->getContent());
        disableFileSaving();
        GameField::resetGameState();
        GameLayoutBuilder::unbuild();
        HomeLayoutBuilder::build();
        QuitGame::hide();
        IllegalMove::lockBackground = false;
        QuitGame::lockBackground = false;
    });

    auto cancelButton = std::make_unique<Button>(sf::Vector2f(900, 450), sf::Vector2f(150, 40), "Cancel");
    cancelButton->bindOnClick([]() -> void {
        isTextFieldDrawAble = false;
        textField->resetContent();
        confirmSaveButton->hide();
        cancelSaveButton->hide();
    });


    components.push_back(std::move(modal));
    components.push_back(std::move(title));
    components.push_back(std::move(noBtn));
    components.push_back(std::move(yesNoSaveBtn));
    components.push_back(std::move(yesSaveBtn));

    confirmSaveButton = std::move(confirmButton);
    cancelSaveButton = std::move(cancelButton);
//    textField = std::move(fileTextField);
}