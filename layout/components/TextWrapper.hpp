#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../../utils/font/Fonts.hpp"

struct TextWrapper {

    TextWrapper(std::string t, sf::Color color, Fonts font, int fontSize);

    auto setFontSize(int fontSize) -> void;

    auto setPosition(sf::Vector2f position) -> void;

    auto setColor(sf::Color color) -> void;

    auto setLetterSpacing(float letterSpacing) -> void;

    auto centerBothAxis(sf::Vector2f parentPosition, sf::Vector2f parentSize) -> void;

    auto centerHorizontalAxis(float parentX, float parentWidth, float posY) -> void;

    auto show() -> void;

    auto hide() -> void;

    static auto drawTextWrappers(sf::RenderWindow &window) -> void;

private:

    sf::Text text;
    static std::vector<TextWrapper> textWrappers;


    auto initTextProperties(std::string &t, sf::Color &color, Fonts &font, int fontSize) -> void;

};