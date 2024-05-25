#include "SFML/Graphics.hpp"
#include "Circle.hpp"

Circle::Circle(
        sf::Vector2f position,
        sf::Vector2f velocity,
        float radius
) :
        position(position),
        velocity(velocity),
        radius(radius) {}

Circle::Circle(
        sf::Vector2f position,
        sf::Vector2f velocity,
        float radius,
        sf::Color color
) :
        position(position),
        velocity(velocity),
        radius(radius),
        circleColor(color) {}

