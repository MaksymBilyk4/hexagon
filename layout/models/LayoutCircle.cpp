#include "SFML/Graphics.hpp"
#include "fmt/format.h"
#include "LayoutCircle.hpp"

LayoutCircle::LayoutCircle(
        sf::Vector2f position,
        sf::Vector2f velocity,
        float radius,
        float depth
) :
        position(position),
        velocity(velocity),
        radius(radius),
        depth(depth) {}

LayoutCircle::LayoutCircle(
        sf::Vector2f position,
        sf::Vector2f velocity,
        float radius,
        float depth,
        sf::Color color
) :
        position(position),
        velocity(velocity),
        radius(radius),
        depth(depth),
        circleColor(color) {}

auto LayoutCircle::format_as(LayoutCircle c) -> std::string {
    return fmt::format("position: {} {}, velocity: {} {}, radius: {}, depth: {}", c.position.x, c.position.y, c.velocity.x, c.velocity.y, c.radius, c.depth);
}

