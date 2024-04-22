#pragma once

#include "SFML/Graphics.hpp"
#include <vector>
#include <string>
#include <functional>

struct Button {

    Button(sf::Vector2f size, sf::Vector2f position, sf::Color innerColor, sf::Color borderColor, float borderWidth,
           std::string buttonText, sf::Color textColor);

    Button(sf::Vector2f size, sf::Color innerColor, sf::Color borderColor, float borderWidth, std::string buttonText,
           sf::Color textColor);

    Button(sf::Vector2f size, std::string buttonText);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    auto setSize(sf::Vector2f size) -> void;

    auto setPosition(sf::Vector2f position) -> void;

    auto setInnerColor(sf::Color color) -> void;

    auto setBorderColor(sf::Color color) -> void;

    auto setBorderWidth(float borderWidth) -> void;

    auto setHoverInnerColor(sf::Color color) -> void;

    auto setHoverBorderColor(sf::Color color) -> void;

    auto setTextColor(sf::Color color) -> void;

    auto setFontSize(int size) -> void;

    auto setFont(sf::Font &font) -> void;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    auto getWidth() -> float;

    auto getHeight() -> float;

    auto getInnerColor() -> sf::Color;

    auto getHoverInnerColor() -> sf::Color;

    auto getBorderColor() -> sf::Color;

    auto getBorderHoverColor() -> sf::Color;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static auto drawButtons(sf::RenderWindow &window) -> void;

    static auto catchOnMouseOver(sf::Vector2i &mousePos) -> void;

    static auto catchOnMouseClick(sf::Vector2i &mousePos) -> void;

    auto isMouseOver(sf::Vector2i &mousePos) -> bool;

    auto onClick(std::function<void()> handler) -> void;

    auto hover() -> void;

    auto unhover() -> void;

    auto show() -> void;

    auto hide() -> void;


private:
    static std::vector<Button> buttons;

    std::function<void()> onClickHandler;

    sf::RectangleShape buttonBase;
    sf::Text text;

    sf::Color hoverInnerColor;
    sf::Color hoverBorderColor;

    sf::Color innerColorCpy;
    sf::Color borderColorCpy;

    static auto initButton(sf::RectangleShape& buttonBase, sf::Vector2f& size, sf::Vector2f pos, sf::Color innerColor, sf::Color borderColor, float borderWidth) -> void;
    static auto initButtonText(sf::Text& text, std::string& buttonText, int characterSize, sf::Color color) -> void;
};