#include "SFML/Graphics.hpp"
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

