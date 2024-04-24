#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../../utils/font/Fonts.hpp"

struct TextWrapper {

    TextWrapper(std::string const& t, sf::Color const& color, Fonts const& font, int fontSize);

    TextWrapper(std::string const& t);

    TextWrapper();

    auto setFontSize(int fontSize) -> void;

    auto setPosition(sf::Vector2f const& position) -> void;

    auto setColor(sf::Color color) -> void;

    auto setLetterSpacing(float letterSpacing) -> void;

    auto setFont(Fonts const& font) -> void;

    auto centerBothAxis(sf::Vector2f const& parentPosition, sf::Vector2f const& parentSize) -> void;

    auto centerHorizontalAxis(float parentX, float parentWidth, float posY) -> void;

    auto show() -> void;

    auto hide() -> void;

    static auto drawTextWrappers(sf::RenderWindow &window) -> void;

private:

    sf::Text text;
    static std::vector<TextWrapper> textWrappers;


    auto initTextProperties(std::string const &t, sf::Color const &color, Fonts const &font, int fontSize) -> void;

};