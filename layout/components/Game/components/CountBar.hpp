#pragma once

#include <SFML/Graphics.hpp>

#include "../../Box.hpp"
#include "../../TextWrapper/TextWrapper.hpp"

struct CountBar : Box{

    CountBar(sf::Vector2f const& position, sf::Color const& barColor, int initCountedNumbers);

    ~CountBar() override = default;

    auto getColor() const -> sf::Color override;

    auto getBorderColor() const -> sf::Color override;

    auto getBorderWidth() const -> float override;

    auto setColor(const sf::Color &color) -> void override;

    auto setBorderColor(const sf::Color &color) -> void override;

    auto setBorderWidth(float borderWidth) -> void override;

    auto getPosition() const -> sf::Vector2f override;

    auto getSize() const -> sf::Vector2f override;

    auto setPosition(const sf::Vector2f &position) -> void override;

    auto setSize(const sf::Vector2f &size) -> void override;

    auto isMouseOver(const sf::Vector2i &mousePosition) const -> bool override;

    auto onClick() -> void override;

    auto onMouseOver() -> void override;

    auto onMouseLeave() -> void override;

    auto show() -> void override;

    auto hide() -> void override;

    auto draw(sf::RenderWindow &renderWindow) -> void override;

    auto getCountedItems() const -> int;

    auto reset(float xPos) -> void;

    auto setCountedItems(int items) -> void;

    auto increaseCounter(int number) -> void;

    auto decreaseCounter(int number) -> void;

private:
    int countedItems;
    sf::Color barColor;

    sf::RectangleShape barBase;
    TextWrapper barText;

};