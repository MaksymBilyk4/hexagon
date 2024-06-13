#pragma once

#include <memory>
#include "../Box.hpp"
#include "../../../util/component/ComponentUtil.hpp"

struct Modal : Component {

    Modal(sf::RenderWindow const &renderWindow, int width, int height);

    auto getPosition() const -> sf::Vector2f override;

    auto getSize() const -> sf::Vector2f override;

    auto setPosition(sf::Vector2f const &position) -> void override;

    auto setSize(sf::Vector2f const &size) -> void override;

    auto isMouseOver(const sf::Vector2i &mousePosition) const -> bool override;

    auto show() -> void override;

    auto hide() -> void override;

    auto draw(sf::RenderWindow &renderWindow) -> void override;

    auto setVerticalGradient(sf::Color const &upperColor, sf::Color const &bottomColor) -> void;

    auto setHorizontalGradient(sf::Color const &leftColor, sf::Color const &rightColor) -> void;

    auto setInlineColor(sf::Color const& color) -> void;

    static std::vector<std::unique_ptr<Component>> modals;

private:

    sf::VertexArray modalBase;

    static inline int vertexCount = 4;

};