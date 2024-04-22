#pragma once

#include <SFML/Graphics.hpp>

struct Text {

    static auto center(sf::Vector2f& parentPosition, sf::Vector2f& parentSize, sf::Text& text) -> void;

};