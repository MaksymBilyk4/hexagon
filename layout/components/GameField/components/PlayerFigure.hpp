#pragma once

#include "SFML/Graphics.hpp"
#include <memory>
#include <vector>
#include "../../../../utils/ComponentUtil.hpp"
#include "./Hexagon.hpp"
#include "../../Component.hpp"
#include "../../Box.hpp"

struct PlayerFigure : Box {

    auto getPosition() const -> sf::Vector2f override;

    auto getSize() const -> sf::Vector2f override;

    auto setPosition(const sf::Vector2f &position) -> void override;

    auto setSize(const sf::Vector2f &size) -> void override;

    auto isMouseOver(const sf::Vector2i &mousePosition) const -> bool override;

    auto show() -> void override;

    auto hide() -> void override;

    auto draw(sf::RenderWindow &renderWindow) -> void override;

    auto getColor() const -> sf::Color override;

    auto getBorderColor() const -> sf::Color override;

    auto getBorderWidth() const -> float override;

    auto setColor(const sf::Color &color) -> void override;

    auto setBorderColor(const sf::Color &color) -> void override;

    auto setBorderWidth(float borderWidth) -> void override;

    auto setRadius(float radius) -> void;

    PlayerFigure(sf::Color const& color);

    static std::vector<std::unique_ptr<Component>> playerFigures;

private:
    sf::CircleShape figure;

};