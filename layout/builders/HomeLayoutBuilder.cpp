#include "./HomeLayoutBuilder.hpp"
#include "./GameLayoutBuilder.hpp"


std::vector<std::unique_ptr<Component>> HomeLayoutBuilder::components;
std::unique_ptr<CheckBoxGroup> HomeLayoutBuilder::modeGroup;
std::unique_ptr<Modal> HomeLayoutBuilder::modal;

auto HomeLayoutBuilder::build() -> void {
    for (auto const &comp: components)
        comp->show();

    modeGroup->show();
    modal->show();
}

auto HomeLayoutBuilder::unbuild() -> void {
    for (auto const &comp: components)
        comp->hide();

    modeGroup->hide();
    modal->hide();
}

auto HomeLayoutBuilder::initHomeScreen(sf::RenderWindow &renderWindow) -> void {
    makeMainModal(renderWindow);
    makeGameChoiceGroup();
    makeLinkButtons(renderWindow);
}

auto HomeLayoutBuilder::makeMainModal(sf::RenderWindow &renderWindow) -> void {
    auto mainModal = std::make_unique<Modal>(renderWindow, 950, 750);

    auto headerText = std::make_unique<TextWrapper>();
    headerText->setText("Hexxagon");
    headerText->setColor(sf::Color::White);
    headerText->setFont(Fonts::SIXTY_FOUR_REGULAR_FONT);
    headerText->setFontSize(60);
    headerText->centerHorizontalAxis(mainModal->getPosition().x, mainModal->getSize().x,
                                     mainModal->getPosition().y + 15);

    auto pearls = std::make_unique<TextWrapper>();
    pearls->setText("Pearls");
    pearls->setColor(sf::Color(56, 119, 235));
    pearls->setFont(Fonts::ROBOTO_MEDIUM_FONT);
    pearls->setFontSize(40);
    pearls->setPosition({775, mainModal.get()->getPosition().y + 125});


    auto rubies = std::make_unique<TextWrapper>();
    rubies->setText("Rubies");
    rubies->setColor(sf::Color(247, 62, 62));
    rubies->setFont(Fonts::ROBOTO_MEDIUM_FONT);
    rubies->setFontSize(40);
    rubies->setPosition({500, mainModal.get()->getPosition().y + 125});

    modal = std::move(mainModal);
    components.push_back(std::move(headerText));
    components.push_back(std::move(rubies));
    components.push_back(std::move(pearls));
}

auto HomeLayoutBuilder::makeLinkButtons(sf::RenderWindow &renderWindow) -> void {
    auto startGameButton = std::make_unique<Button>(sf::Vector2f(0, 0), sf::Vector2f(500, 50), "START GAME");
    startGameButton->setButtonTextFontSize(40);
    startGameButton->setPosition({(renderWindow.getSize().x / 2 - startGameButton->getSize().x / 2), 725});

    startGameButton->bindOnClick([]() -> void {
        HomeLayoutBuilder::unbuild();
        GameLayoutBuilder::build();
    });

    auto bestGamesButton = std::make_unique<Button>(sf::Vector2f(250, 450), sf::Vector2f(200, 50), "Best games");
    auto savedGamesButton = std::make_unique<Button>(sf::Vector2f(920, 450), sf::Vector2f(230, 50), "Saved games");

    bestGamesButton->setButtonTextFontSize(35);
    savedGamesButton->setButtonTextFontSize(35);

    bestGamesButton->setButtonTextPosition({260, 450});
    savedGamesButton->setButtonTextPosition({930, 450});

    bestGamesButton->bindOnClick([]() -> void {
        GameInfoLayoutBuilder::buildBestGames();
        GameInfoLayoutBuilder::build();
        HomeLayoutBuilder::unbuild();
    });

    savedGamesButton->bindOnClick([]() -> void {
        GameInfoLayoutBuilder::buildSavedGames();
        GameInfoLayoutBuilder::build();
        HomeLayoutBuilder::unbuild();
    });

    components.push_back(std::move(startGameButton));
    components.push_back(std::move(bestGamesButton));
    components.push_back(std::move(savedGamesButton));
}

auto HomeLayoutBuilder::makeGameChoiceGroup() -> void {
    auto group = std::make_unique<CheckBoxGroup>();

    auto cb1YPos = static_cast<float>(modal->getPosition().y + modal->getSize().y / 1.70);
    auto cb2YPos = static_cast<float>(modal->getPosition().y + modal->getSize().y / 1.45);

    auto cb1 = new CheckBox({450, cb1YPos}, {30, 30}, "PLAYER     vs.    COMPUTER");
    auto cb2 = new CheckBox({450, cb2YPos}, {30, 30}, "PLAYER     vs.     PLAYER ");

    cb1->setActionContext(std::to_string(GameMode::PLAYER_VS_COMPUTER));
    cb2->setActionContext(std::to_string(GameMode::PLAYER_VS_PLAYER));
    cb1->setLabelGap({50, -10});
    cb2->setLabelGap({75, -10});

    group->addCheckBox(*cb1);
    group->addCheckBox(*cb2);

    modeGroup = std::move(group);
}