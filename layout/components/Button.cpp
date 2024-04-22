#include <SFML/Graphics.hpp>
#include <string>
#include <fmt/core.h>
#include <functional>

#include "../../utils/font/FontHolder.hpp"
#include "./Button.hpp"
#include "../../utils/Text.hpp"

std::vector<Button> Button::buttons;

Button::Button(sf::Vector2f size, sf::Vector2f position, sf::Color innerColor, sf::Color borderColor, float borderWidth,
               std::string buttonText, sf::Color textColor)
        : innerColorCpy(innerColor), borderColorCpy(borderColor) {


    Button::initButton(buttonBase, size, position, innerColor, borderColor, borderWidth);

    hoverInnerColor = sf::Color(128, 128, 128);
    hoverBorderColor = sf::Color(255, 255, 255);

    Button::initButtonText(text, buttonText, 20, textColor);
}

Button::Button(sf::Vector2f size, sf::Color innerColor, sf::Color borderColor, float borderWidth,
               std::string buttonText, sf::Color textColor) :
        innerColorCpy(innerColor), borderColorCpy(borderColor) {

    Button::initButton(buttonBase, size, {0,0}, innerColor, borderColor, borderWidth);

    hoverInnerColor = sf::Color(128, 128, 128);
    hoverBorderColor = sf::Color(255, 255, 255);

    Button::initButtonText(text, buttonText, 20, textColor);
}

Button::Button(sf::Vector2f size, std::string buttonText) {
    innerColorCpy = sf::Color::White;
    borderColorCpy = sf::Color::Black;

    Button::initButton(buttonBase, size, {0,0}, sf::Color::White, sf::Color::Black, 3);

    hoverInnerColor = sf::Color(128, 128, 128);
    hoverBorderColor = sf::Color(255, 255, 255);

    Button::initButtonText(text, buttonText, 20, sf::Color::Black);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
auto Button::setSize(sf::Vector2f size) -> void {
    buttonBase.setSize(size);
}

auto Button::setPosition(sf::Vector2f position) -> void {
    buttonBase.setPosition(position);
}

auto Button::setInnerColor(sf::Color color) -> void {
    buttonBase.setFillColor(color);
    innerColorCpy = color;
}

auto Button::setBorderColor(sf::Color color) -> void {
    buttonBase.setOutlineColor(color);
    borderColorCpy = color;
}

auto Button::setBorderWidth(float borderWidth) -> void {
    buttonBase.setOutlineThickness(borderWidth);
}

auto Button::setHoverInnerColor(sf::Color color) -> void {
    hoverInnerColor = color;
}

auto Button::setHoverBorderColor(sf::Color color) -> void {
    hoverBorderColor = color;
}

auto Button::setTextColor(sf::Color color) -> void {
    text.setFillColor(color);
}

auto Button::setFontSize(int size) -> void {
    text.setCharacterSize(size);
}

auto Button::setFont(sf::Font &font) -> void {
    text.setFont(font);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

auto Button::getWidth() -> float {
    return buttonBase.getSize().x;
}

auto Button::getHeight() -> float {
    return buttonBase.getSize().y;
}

auto Button::getHoverInnerColor() -> sf::Color {
    return hoverInnerColor;
}

auto Button::getInnerColor() -> sf::Color {
    return innerColorCpy;
}

auto Button::getBorderColor() -> sf::Color {
    return borderColorCpy;
}

auto Button::getBorderHoverColor() -> sf::Color {
    return hoverBorderColor;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

auto Button::drawButtons(sf::RenderWindow &window) -> void {
    for (Button &btn: buttons) {
        window.draw(btn.buttonBase);
        window.draw(btn.text);
    }
}

auto Button::catchOnMouseOver(sf::Vector2i &mousePos) -> void {
    for (Button &btn: buttons) {
        if (btn.isMouseOver(mousePos)) {
            btn.hover();
        } else btn.unhover();
    }
}

auto Button::catchOnMouseClick(sf::Vector2i &mousePos) -> void {
    for (Button &btn: buttons) {
        if (btn.isMouseOver(mousePos)) {
            if (btn.onClickHandler) btn.onClickHandler();
            else fmt::println("no click handler");
        }
    }
}

auto Button::isMouseOver(sf::Vector2i &mousePos) -> bool {
    if (
            (mousePos.x >= buttonBase.getPosition().x &&
             mousePos.x <= buttonBase.getPosition().x + buttonBase.getSize().x) &&
            (mousePos.y >= buttonBase.getPosition().y &&
             mousePos.y <= buttonBase.getPosition().y + buttonBase.getSize().y)) {
        return true;
    }

    return false;
}

auto Button::onClick(std::function<void()> handler) -> void {
    onClickHandler = handler;
}

auto Button::hover() -> void {
    buttonBase.setFillColor(hoverInnerColor);
    buttonBase.setOutlineColor(hoverBorderColor);
}

auto Button::unhover() -> void {
    buttonBase.setFillColor(getInnerColor());
    buttonBase.setOutlineColor(getBorderColor());
}

auto Button::show() -> void {

    auto buttonPos = buttonBase.getPosition();
    auto buttonSize = buttonBase.getSize();

    Text::center(buttonPos, buttonSize, text);

    buttons.push_back(*this);
}

auto Button::hide() -> void {
    auto buttonIterator = std::find_if(buttons.begin(), buttons.end(), [this](const Button &btn) {
        return &btn == this;
    });

    buttons.erase(buttonIterator);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
auto Button::initButtonText(sf::Text& text, std::string &buttonText, int characterSize, sf::Color color) -> void {
    text.setString(buttonText);
    text.setFont(FontHolder::getFont(Fonts::ROBOTO_MEDIUM_FONT));
    text.setCharacterSize(characterSize);
    text.setFillColor(color);
}

auto Button::initButton(sf::RectangleShape &buttonBase, sf::Vector2f &size, sf::Vector2f pos, sf::Color innerColor, sf::Color borderColor, float borderWidth) -> void {
    buttonBase.setSize(size);
    buttonBase.setPosition(pos);
    buttonBase.setFillColor(innerColor);
    buttonBase.setOutlineColor(borderColor);
    buttonBase.setOutlineThickness(borderWidth);
}