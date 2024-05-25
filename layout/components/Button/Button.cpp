#include "SFML/Graphics.hpp"
#include <string>
#include "fmt/core.h"
#include <functional>

#include "../../../utils/font/FontHolder.hpp"
#include "./Button.hpp"
#include "../../../utils/cursor/CursorHolder.hpp"
#include "../../../utils/ComponentUtil.hpp"


std::vector<Button> Button::buttons;

Button::Button(sf::Vector2f const &size, sf::Vector2f const &position, sf::Color const &innerColor,
               sf::Color const &borderColor, float borderWidth,
               std::string const &buttonText, sf::Color const &textColor)
        : innerColorCpy(innerColor), borderColorCpy(borderColor) {

    Button::initButton(size, position, innerColor, borderColor, borderWidth);

    hoverInnerColor = sf::Color(128, 128, 128);
    hoverBorderColor = sf::Color(255, 255, 255);

    initButtonText(buttonText, textColor, Fonts::ROBOTO_REGULAR_FONT, 20);
}

Button::Button(sf::Vector2f const &size, sf::Color const &innerColor, sf::Color const &borderColor, float borderWidth,
               std::string const &buttonText,
               sf::Color const &textColor) :
        innerColorCpy(innerColor), borderColorCpy(borderColor) {

    Button::initButton(size, {0, 0}, innerColor, borderColor, borderWidth);

    hoverInnerColor = sf::Color(128, 128, 128);
    hoverBorderColor = sf::Color(255, 255, 255);

    initButtonText(buttonText, textColor, Fonts::ROBOTO_REGULAR_FONT, 20);
}

Button::Button(sf::Vector2f const &size, std::string const &buttonText) {
    innerColorCpy = sf::Color::White;
    borderColorCpy = sf::Color::Black;

    Button::initButton(size, {0, 0}, sf::Color::White, sf::Color::Black, 3);

    hoverInnerColor = sf::Color(128, 128, 128);
    hoverBorderColor = sf::Color(255, 255, 255);

    initButtonText(buttonText, sf::Color::Black, Fonts::ROBOTO_REGULAR_FONT, 20);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
auto Button::setSize(sf::Vector2f const &size) -> void {
    buttonBase.setSize(size);
}

auto Button::setPosition(sf::Vector2f const &position) -> void {
    buttonBase.setPosition(position);
}

auto Button::setInnerColor(sf::Color const &color) -> void {
    buttonBase.setFillColor(color);
    innerColorCpy = color;
}

auto Button::setBorderColor(sf::Color const &color) -> void {
    buttonBase.setOutlineColor(color);
    borderColorCpy = color;
}

auto Button::setBorderWidth(float borderWidth) -> void {
    buttonBase.setOutlineThickness(borderWidth);
}

auto Button::setHoverInnerColor(sf::Color const &color) -> void {
    hoverInnerColor = color;
}

auto Button::setHoverBorderColor(sf::Color const &color) -> void {
    hoverBorderColor = color;
}

auto Button::setTextColor(sf::Color const &color) -> void {
    buttonText.setColor(color);
}

auto Button::setFontSize(int size) -> void {
    buttonText.setFontSize(size);
}

auto Button::setFont(Fonts const &font) -> void {
    buttonText.setFont(font);
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
    }
}

auto Button::catchOnMouseOver(sf::Window &window) -> void {

    auto mousePos = sf::Mouse::getPosition(window);
    bool cursorSet = false;

    for (Button &btn : buttons) {
        if (btn.isMouseOver(mousePos) &&
            (CursorHolder::getCurrentHolder() == CurrentHolder::NO_ONE ||
             CursorHolder::getCurrentHolder() == CurrentHolder::BUTTON)) {
            btn.hover();
            CursorHolder::setHandCursor(window);
            CursorHolder::setCurrentHolder(CurrentHolder::BUTTON);
            cursorSet = true;
        } else {
            btn.unhover();
        }
    }

    if (!cursorSet && CursorHolder::getCurrentHolder() == CurrentHolder::BUTTON) {
        CursorHolder::setSimpleCursor(window);
        CursorHolder::setCurrentHolder(CurrentHolder::NO_ONE);
    }

}

auto Button::catchOnMouseClick(sf::Vector2i const &mousePos) -> void {
    for (Button &btn: buttons) {
        if (btn.isMouseOver(mousePos)) {
            if (btn.onClickHandler) btn.onClickHandler();
            else fmt::println("no click handler");
        }
    }
}

auto Button::isMouseOver(sf::Vector2i const &mousePos) -> bool {
    return ComponentUtil::isMouseOver(buttonBase, mousePos);
}

auto Button::onClick(std::function<void()> const &handler) -> void {
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
    buttonText.centerBothAxis(buttonBase.getPosition(), buttonBase.getSize());
    buttonText.show();
    buttons.push_back(*this);
//    ComponentUtil::show(Button::buttons, *this);
}

auto Button::hide() -> void {
    auto buttonIterator = std::find_if(buttons.begin(), buttons.end(), [this](const Button &btn) {
        return &btn == this;
    });

    buttonText.hide();
    buttons.erase(buttonIterator);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
auto Button::initButtonText(std::string const &t, sf::Color const &color, Fonts const &font, int fontSize) -> void {
    buttonText = TextWrapper(t, color, font, fontSize);
}

auto Button::initButton(sf::Vector2f const &size, sf::Vector2f const &pos, sf::Color const &innerColor,
                        sf::Color const &borderColor, float borderWidth) -> void {
    buttonBase.setSize(size);
    buttonBase.setPosition(pos);
    buttonBase.setFillColor(innerColor);
    buttonBase.setOutlineColor(borderColor);
    buttonBase.setOutlineThickness(borderWidth);
}