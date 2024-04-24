#pragma once

#include "SFML/Graphics.hpp"
#include "TextWrapper.hpp"
#include <vector>
#include <string>
#include <functional>

struct Button {

    Button(sf::Vector2f const& size, sf::Vector2f const& position, sf::Color const& innerColor, sf::Color const& borderColor, float borderWidth,
           std::string const& buttonText, sf::Color const& textColor);

    Button(sf::Vector2f const& size, sf::Color const& innerColor, sf::Color const& borderColor, float borderWidth, std::string const& buttonText,
           sf::Color const& textColor);

    Button(sf::Vector2f const& size, std::string const& buttonText);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    auto setSize(sf::Vector2f const& size) -> void;

    auto setPosition(sf::Vector2f const& position) -> void;

    auto setInnerColor(sf::Color const& color) -> void;

    auto setBorderColor(sf::Color const& color) -> void;

    auto setBorderWidth(float borderWidth) -> void;

    auto setHoverInnerColor(sf::Color const& color) -> void;

    auto setHoverBorderColor(sf::Color const& color) -> void;

    auto setTextColor(sf::Color const& color) -> void;

    auto setFontSize(int size) -> void;

    auto setFont(Fonts const& font) -> void;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    auto getWidth() -> float;

    auto getHeight() -> float;

    auto getInnerColor() -> sf::Color;

    auto getHoverInnerColor() -> sf::Color;

    auto getBorderColor() -> sf::Color;

    auto getBorderHoverColor() -> sf::Color;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static auto drawButtons(sf::RenderWindow &window) -> void;

    static auto catchOnMouseOver(sf::Window &window) -> void;

    static auto catchOnMouseClick(sf::Vector2i const &mousePos) -> void;

    auto isMouseOver(sf::Vector2i const &mousePos) -> bool;

    auto onClick(std::function<void()> const& handler) -> void;

    auto hover() -> void;

    auto unhover() -> void;

    auto show() -> void;

    auto hide() -> void;


private:
    static std::vector<Button> buttons;

    std::function<void()> onClickHandler;

    sf::RectangleShape buttonBase;
    TextWrapper buttonText;

    sf::Color hoverInnerColor;
    sf::Color hoverBorderColor;

    sf::Color innerColorCpy;
    sf::Color borderColorCpy;

    auto initButtonText(std::string const& t, sf::Color const& color, Fonts const& font, int fontSize) -> void;
    auto initButton(sf::Vector2f const& size, sf::Vector2f const& pos, sf::Color const& innerColor, sf::Color const& borderColor, float borderWidth) -> void;
};