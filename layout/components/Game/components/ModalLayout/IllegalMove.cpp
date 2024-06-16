#include "./IllegalMove.hpp"

bool IllegalMove::isOpened = false;
bool IllegalMove::lockBackground = false;

std::unique_ptr<Modal> IllegalMove::modal;
std::unique_ptr<TextWrapper> IllegalMove::title;
std::unique_ptr<TextWrapper> IllegalMove::message;
std::unique_ptr<Component> IllegalMove::closeButton;

auto IllegalMove::show() -> void {
    isOpened = true;
    lockBackground = true;
    modal->show();
    title->show();
    message->show();
    closeButton->show();
}

auto IllegalMove::hide() -> void {
    isOpened = false;
    modal->hide();
    title->hide();
    message->hide();
    closeButton->hide();
}

auto IllegalMove::setTitle(const std::string &t) -> void {
    title->setText(t);
}

auto IllegalMove::setMessage(const std::string &msg) -> void {
    message->setText(msg);
}

auto IllegalMove::buildIllegalMoveLayout(sf::RenderWindow &renderWindow) -> void {
    auto layoutModal = std::make_unique<Modal>(renderWindow, 850, 500);
    layoutModal->setVerticalGradient(sf::Color(0,0,0,200), sf::Color(0,0,0,200));

    auto layoutTitle = std::make_unique<TextWrapper>();
    layoutTitle->setPosition({400, 325});
    layoutTitle->setFontSize(40);
    layoutTitle->setFont(Fonts::SIXTY_FOUR_REGULAR_FONT);
    layoutTitle->setColor(sf::Color::White);

    auto layoutMessage = std::make_unique<TextWrapper>();
    layoutMessage->setColor(sf::Color::White);
    layoutMessage->setFontSize(25);
    layoutMessage->setPosition({400, 425});
    layoutMessage->setFont(Fonts::ROBOTO_MEDIUM_FONT);

    auto closeLayoutButton = std::make_unique<Button>(sf::Vector2f(400, 550), sf::Vector2f(200, 50), "OK. Close!");
    closeLayoutButton->setButtonTextColor(sf::Color::White);
    closeLayoutButton->setBorderColor(sf::Color::Green);
    closeLayoutButton->setColor(sf::Color::Black);
    closeLayoutButton->bindOnClick([]() -> void {
        IllegalMove::hide();
    });
    closeLayoutButton->setHoverColor(sf::Color::Black);
    closeLayoutButton->setBorderColor(sf::Color::Green);
    closeLayoutButton->setButtonTextColor(sf::Color::Green);

    modal = std::move(layoutModal);
    title = std::move(layoutTitle);
    message = std::move(layoutMessage);
    closeButton = std::move(closeLayoutButton);
}