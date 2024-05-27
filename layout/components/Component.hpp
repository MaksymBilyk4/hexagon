#pragma once

#include <SFML/Graphics.hpp>
#include <fmt/core.h>

struct Component {

    Component();

    virtual auto getPosition() const -> sf::Vector2f = 0;

    virtual auto getSize() const -> sf::Vector2f = 0;

    virtual auto setPosition(sf::Vector2f const &position) -> void = 0;

    virtual auto setSize(sf::Vector2f const &size) -> void = 0;

    virtual auto isMouseOver(const sf::Vector2i &mousePosition) const -> bool = 0;

    virtual auto onClick() -> void {
        fmt::println("On click event");
    };

    virtual auto onMouseOver() -> void {
        fmt::println("On mouse over event");
    }

    virtual auto onMouseLeave() -> void {
        fmt::println("On mouse leave event");
    }

    virtual auto show() -> void = 0;

    virtual auto hide() -> void = 0;

    virtual auto draw(sf::RenderWindow &renderWindow) -> void = 0;

    virtual ~Component() = default;

    auto getComponentId() const -> int;

    static int idCounter;

private:
    int componentId;
};