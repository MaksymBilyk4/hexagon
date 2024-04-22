#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <fmt/core.h>

#include "./TextWrapper.hpp"
#include "../../utils/font/FontHolder.hpp"


std::vector<TextWrapper> TextWrapper::textWrappers;

TextWrapper::TextWrapper(std::string t, sf::Color color, Fonts font, int fontSize) {
    initTextProperties(t, color, font, fontSize);
}

auto TextWrapper::setPosition(sf::Vector2f position) -> void {
    text.setPosition(position);
}

auto TextWrapper::setFontSize(int fontSize) -> void {
    text.setCharacterSize(fontSize);
}

auto TextWrapper::setColor(sf::Color color) -> void {
    text.setFillColor(color);
}

auto TextWrapper::setLetterSpacing(float letterSpacing) -> void {
    text.setLetterSpacing(letterSpacing);
}

auto TextWrapper::centerBothAxis(sf::Vector2f parentPosition, sf::Vector2f parentSize) -> void {
    text.setPosition({
        parentPosition.x + (parentSize.x / 2) - (text.getGlobalBounds().width + text.getLetterSpacing() * static_cast<float >(text.getString().getSize() * text.getCharacterSize())) / 2,
        parentPosition.y + (parentSize.y / 3) - text.getGlobalBounds().height / 2
    });
}

// TODO Centering with Letter Spacings
auto TextWrapper::centerHorizontalAxis(float parentX, float parentWidth, float posY) -> void {
    text.setPosition({
        parentX + (parentWidth / 2) - (text.getGlobalBounds().width / 2),
        posY
    });
}

auto TextWrapper::show() -> void {
    textWrappers.emplace_back(*this);
}

auto TextWrapper::hide() -> void {
    auto tw = std::ranges::find_if(textWrappers.begin(), textWrappers.end(), [this](TextWrapper &tw) -> bool {
        return &tw == this;
    });

    textWrappers.erase(tw);
}

auto TextWrapper::drawTextWrappers(sf::RenderWindow &window) -> void {
    for (TextWrapper &tw: textWrappers) {
        window.draw(tw.text);
    }
}

auto TextWrapper::initTextProperties(std::string &t, sf::Color &color, Fonts &font, int fontSize) -> void {
    text.setFont(FontHolder::getFont(font));
    text.setFillColor(color);
    text.setCharacterSize(fontSize);
    text.setString(t);
}