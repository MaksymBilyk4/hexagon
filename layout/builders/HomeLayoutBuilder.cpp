#include "./HomeLayoutBuilder.hpp"

std::vector<std::unique_ptr<Component>> HomeLayoutBuilder::components;
std::unique_ptr<Modal> HomeLayoutBuilder::modal;

auto HomeLayoutBuilder::build() -> void {
    for (auto const &comp: components)
        comp->show();

    modal->show();
}

auto HomeLayoutBuilder::unbuild() -> void {
    for (auto const &comp: components)
        comp->hide();

    modal->hide();
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

    auto pearls = std::make_unique<TextWrapper>();
    pearls->setText("Pears");
    pearls->setColor(sf::Color(56, 119, 235));
    pearls->setFont(Fonts::ROBOTO_MEDIUM_FONT);
    pearls->setFontSize(40);
    auto pearlsPosition = sf::Vector2f(
            mainModal->getPosition().x +
            (mainModal->getSize().x / 2 - pearls->getSize().x + mainModal->getSize().x * 0.1),
            mainModal->getPosition().y + mainModal->getSize().y * 0.25);
    pearls->setPosition(pearlsPosition);


    auto rubies = std::make_unique<TextWrapper>();
    rubies->setText("Rubies");
    rubies->setColor(sf::Color(247, 62, 62));
    rubies->setFont(Fonts::ROBOTO_MEDIUM_FONT);
    rubies->setFontSize(40);
    auto rubiesPosition = sf::Vector2f(
            mainModal->getPosition().x +
            (mainModal->getSize().x / 2 - pearls->getSize().x - mainModal->getSize().x * 0.1),
            mainModal->getPosition().y + mainModal->getSize().y * 0.25);
    rubies->setPosition(rubiesPosition);

    modal = std::move(mainModal);
    components.push_back(std::move(headerText));
    components.push_back(std::move(rubies));
    components.push_back(std::move(pearls));
}

auto HomeLayoutBuilder::makeStartGameButton(sf::RenderWindow &renderWindow) -> void {
    auto startGameButton = std::make_unique<Button>(sf::Vector2f(0, 0), sf::Vector2f(500, 50), "START GAME");
    startGameButton->setBorderColor({194, 31, 188});
    startGameButton->setHoverBorderColor({255, 0, 229});
    startGameButton->setBorderWidth(3);
    startGameButton->setButtonTextFontSize(40);
    startGameButton->setColor({190, 190, 190});
    startGameButton->setHoverColor({255, 255, 255});
    startGameButton->setPosition(
            {static_cast<float>(renderWindow.getSize().x / 2 - startGameButton->getSize().x / 2), 725});
    startGameButton->setButtonTextColor(sf::Color(sf::Color::Black));
    startGameButton->bindOnClick([]() -> void {
        HomeLayoutBuilder::unbuild();
        fmt::println("unbuild");
        fmt::println("{}", Button::buttons.size());
        fmt::println("{}", Modal::modals.size());
        fmt::println("{}", CheckBoxGroup::groups.size());
        fmt::println("{}", TextWrapper::textWrappers.size());
    });

    components.push_back(std::move(startGameButton));
}

auto HomeLayoutBuilder::makeGameChoiceGroup() -> void {
    auto group = std::make_unique<CheckBoxGroup>();

    auto cb1YPos = static_cast<float>( modal->getPosition().y + modal->getSize().y / 1.70);
    auto cb2YPos = static_cast<float>(modal->getPosition().y + modal->getSize().y / 1.45);

    auto cb1 = new CheckBox({390, cb1YPos}, {30, 30}, "PLAYER     vs.    COMPUTER");
    auto cb2 = new CheckBox({390, cb2YPos}, {30, 30}, "PLAYER     vs.     PLAYER ");

    cb1->setActionContext("Check Box 1");
    cb2->setActionContext("Check Box 2");
    cb1->centerLabel(modal->getPosition().x, modal->getSize().x, cb1YPos - 10);
    cb2->centerLabel(modal->getPosition().x, modal->getSize().x, cb2YPos - 10);

    group->addCheckBox(*cb1);
    group->addCheckBox(*cb2);

    components.push_back(std::move(group));
}