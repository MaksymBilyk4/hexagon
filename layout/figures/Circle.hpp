#pragma once

#include "SFML/Graphics.hpp"

struct Circle {

    sf::Vector2f position;
    sf::Vector2f velocity;
    float radius;
    sf::Color circleColor;

    Circle(sf::Vector2f position, sf::Vector2f velocity, float radius);
    Circle(sf::Vector2f position, sf::Vector2f velocity, float radius, sf::Color color);

};