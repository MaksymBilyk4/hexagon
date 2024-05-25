#include "SFML/Graphics.hpp"
#include <vector>
#include <algorithm>
#include "fmt/core.h"

#include "./TextWrapper.hpp"
#include "../../../utils/font/FontHolder.hpp"
#include "../../../utils/ComponentUtil.hpp"


std::vector<TextWrapper> TextWrapper::textWrappers;

TextWrapper::TextWrapper(std::string const& t, sf::Color const& color, Fonts const& font, int fontSize) {
    initTextProperties(t, color, font, fontSize);
}

TextWrapper::TextWrapper(std::string const& t) {
    initTextProperties(t, sf::Color::Black, Fonts::ROBOTO_REGULAR_FONT, 20);
}

TextWrapper::TextWrapper() {};

auto TextWrapper::isMouseOver(const sf::Vector2i &mousePosition) const -> bool {
    return ComponentUtil::isMouseOver(text.getPosition(), text.getGlobalBounds().getSize(), mousePosition);
}

auto TextWrapper::getSize() const -> sf::Vector2f {
    return text.getGlobalBounds().getSize();
}

auto TextWrapper::setPosition(sf::Vector2f const& position) -> void {
    text.setPosition(position);
}

auto TextWrapper::setText(std::string const& t) -> void {
    text.setString(t);
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

auto TextWrapper::setFont(Fonts const& font) -> void {
    text.setFont(FontHolder::getFont(font));
}

auto TextWrapper::centerBothAxis(sf::Vector2f const& parentPosition, sf::Vector2f const& parentSize) -> void {
    text.setPosition({
        parentPosition.x + (parentSize.x / 2) - text.getGlobalBounds().width  / 2,
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
    textWrappers.push_back(*this);
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

auto TextWrapper::initTextProperties(std::string const &t, sf::Color const &color, Fonts const &font, int fontSize) -> void {
    text.setFont(FontHolder::getFont(font));
    text.setFillColor(color);
    text.setCharacterSize(fontSize);
    text.setString(t);
}

auto TextWrapper::getPosition() const -> sf::Vector2f {
    return sf::Vector2f();
}
