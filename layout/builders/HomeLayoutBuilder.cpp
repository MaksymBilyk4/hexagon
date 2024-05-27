#include "./HomeLayoutBuilder.hpp"

std::unique_ptr<Modal> HomeLayoutBuilder::modal;
std::unique_ptr<TextWrapper> HomeLayoutBuilder::rubies;
std::unique_ptr<TextWrapper> HomeLayoutBuilder::pearls;
std::unique_ptr<TextWrapper> HomeLayoutBuilder::title;
std::unique_ptr<Button> HomeLayoutBuilder::button;
std::unique_ptr<CheckBoxGroup> HomeLayoutBuilder::checkBoxGroup;

auto HomeLayoutBuilder::build() -> void {
    modal->show();
//    title->show();
//    rubies->show();
//    pearls->show();
    button->show();
    checkBoxGroup->show();
}

auto HomeLayoutBuilder::unbuild() -> void {
    modal->hide();
//    title->hide();
//    rubies->hide();
//    pearls->hide();
    button->hide();
    checkBoxGroup->hide();
}

auto HomeLayoutBuilder::initHomeScreen(sf::RenderWindow &renderWindow) -> void {
    makeMainModal(renderWindow);
    makeStartGameButton(renderWindow);
    makeGameChoiceGroup();
}

auto HomeLayoutBuilder::makeMainModal(sf::RenderWindow &renderWindow) -> void {
    auto mainModal = std::make_unique<Modal>(renderWindow, 950, 750);

    auto topGradient = sf::Color(191, 64, 191, 150);
    auto bottomGradient = sf::Color(75, 0, 130, 150);
    mainModal->setVerticalGradient(topGradient, bottomGradient);

    auto headerText = std::make_unique<TextWrapper>();
    headerText->setText("Hexxagon");
    headerText->setColor(sf::Color::White);
    headerText->setFont(Fonts::SIXTY_FOUR_REGULAR_FONT);
    headerText->setFontSize(60);
    headerText->centerHorizontalAxis(mainModal->getPosition().x, mainModal->getSize().x,
                                     mainModal->getPosition().y + 50);

    auto rubiesText = std::make_unique<TextWrapper>(sf::Vector2f (525, 400), "Rubies");
    rubiesText->setColor(sf::Color::Red);
    rubiesText->setFont(Fonts::ROBOTO_MEDIUM_FONT);
    rubiesText->setFontSize(34);


    auto pearlsText = std::make_unique<TextWrapper>(sf::Vector2f (725, 400), "Pearls");
    pearlsText->setText("Pearls");
    pearlsText->setColor(sf::Color(66, 149, 245));
    pearlsText->setFont(Fonts::ROBOTO_MEDIUM_FONT);
    pearlsText->setFontSize(34);

    modal = std::move(mainModal);
    title = std::move(headerText);
    rubies = std::move(rubiesText);
    pearls = std::move(pearlsText);
}

auto HomeLayoutBuilder::makeStartGameButton(sf::RenderWindow &renderWindow) -> void {
    auto startGameButton = std::make_unique<Button>(sf::Vector2f(0, 0), sf::Vector2f(500, 50), "START GAME");
    startGameButton->setBorderColor({194, 31, 188});
    startGameButton->setHoverBorderColor({255, 0, 229});
    startGameButton->setBorderWidth(3);
    startGameButton->setButtonTextFontSize(40);
    startGameButton->setColor({190, 190, 190});
    startGameButton->setHoverColor({255, 255, 255});
    startGameButton->setPosition({static_cast<float>(renderWindow.getSize().x / 2 - startGameButton->getSize().x / 2), 725});
    startGameButton->bindOnClick([]() -> void {
        HomeLayoutBuilder::unbuild();
        GameLayoutBuilder::build();
    });

    button = std::move(startGameButton);
}

auto HomeLayoutBuilder::makeGameChoiceGroup() -> void {
    auto group = std::make_unique<CheckBoxGroup>();
    auto cb1 = new CheckBox({390, 530}, {30, 30}, "PLAYER     vs.    COMPUTER");
    auto cb2 = new CheckBox({390, 600}, {30, 30}, "PLAYER     vs.     PLAYER ");

    cb1->setActionContext("Check Box 1");
    cb2->setActionContext("Check Box 2");

    group->addCheckBox(*cb1);
    group->addCheckBox(*cb2);

    checkBoxGroup = std::move(group);
}