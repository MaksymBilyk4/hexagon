#include "./Text.hpp"

auto Text::center(sf::Vector2f& parentPosition, sf::Vector2f& parentSize, sf::Text& text) -> void {

    auto parentX = parentPosition.x;
    auto parentY = parentPosition.y;

    auto parentWidth = parentSize.x;
    auto parentHeight = parentSize.y;

    text.setPosition({
        parentX + (parentWidth / 2) - text.getGlobalBounds().width / 2,
        parentY + (parentHeight / 3) - text.getGlobalBounds().height / 2
    });
}