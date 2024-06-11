#include "./GameInfoLayoutBuilder.hpp"


std::vector<std::unique_ptr<Component>> GameInfoLayoutBuilder::components;
GameInfo GameInfoLayoutBuilder::infoRenderType;
std::unique_ptr<TextWrapper> GameInfoLayoutBuilder::infoTitle;
std::vector<std::unique_ptr<Component>> GameInfoLayoutBuilder::buttons;


auto GameInfoLayoutBuilder::build() -> void {
    for (auto &comp : components)
        if (comp != nullptr) comp->show();

    infoTitle->show();
}

auto GameInfoLayoutBuilder::unbuild() -> void {
    for (auto &btn : buttons)
        btn->hide();

    for (auto &comp : components)
        if (comp != nullptr) comp->hide();

    infoTitle->hide();
}

auto GameInfoLayoutBuilder::buildBestGames() -> void {
    infoTitle->setText("Your best games");
}

auto GameInfoLayoutBuilder::buildSavedGames() -> void {
    infoTitle->setText("Your saved games");
    auto path = std::filesystem::path("/Users/maksymbilyk/Desktop/programming/PJAIT/hexagon/assets/saved_game_data");

    auto games = std::vector<std::filesystem::path>();

    for (auto const& entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().filename().string().starts_with("game_")) games.push_back(entry.path());
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

        auto btn = std::make_unique<Button>(position, sf::Vector2f(200, 40), games[i].filename().string());
        btn->setButtonTextColor(sf::Color::White);
        btn->setBorderColor(sf::Color::Green);
        btn->setColor(sf::Color::Black);
        btn->setBorderWidth(4);
        btn->setButtonTextPosition({position.x + 10, position.y + 5});
        btn->bindOnClick([games, i]() -> void {
            GameFileStore::uploadGame(games[i].string());
            GameInfoLayoutBuilder::unbuild();
            GameLayoutBuilder::build();
        });


        buttons.push_back(std::move(btn));
        step++;
    }

    for (auto &btn : buttons)
        btn->show();
}

auto GameInfoLayoutBuilder::initInfoScreen(sf::RenderWindow& renderWindow) -> void {
    auto modal = std::make_unique<Modal>(renderWindow, 1100, 900);
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

    components.push_back(std::move(modal));
    components.push_back(std::move(leaveButton));
    infoTitle = std::move(title);
}