#include "./GameLayoutBuilder.hpp"

std::unique_ptr<TextWrapper> GameLayoutBuilder::test;

auto GameLayoutBuilder::build() -> void {
    test->show();
}

auto GameLayoutBuilder::unbuild() -> void {
    test->hide();
}

auto GameLayoutBuilder::initGameField() -> void {

    auto testText = std::make_unique<TextWrapper>(sf::Vector2f(500,500), "Test Text For Game");

    testText->setFontSize(40);
    testText->setColor(sf::Color::Red);
    testText->setFont(Fonts::ROBOTO_MEDIUM_FONT);
    test = std::move(testText);
}

