#pragma once

#include "./Component.hpp"

struct Box : Component {

    virtual auto getColor() const -> sf::Color = 0;

    virtual auto getBorderColor() const -> sf::Color = 0;

    virtual auto getBorderWidth() const -> float = 0;

    virtual auto setColor(sf::Color const& color) -> void = 0;

    virtual auto setBorderColor(sf::Color const& color) -> void = 0;

    virtual auto setBorderWidth(float borderWidth) -> void = 0;

    ~Box() override = default;

};