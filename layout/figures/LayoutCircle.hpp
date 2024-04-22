#pragma once

#include "SFML/Graphics.hpp"

struct LayoutCircle {

    sf::Vector2f position; // position
    sf::Vector2f velocity; // movement speed
    float radius; // radius of circle
    float depth; // for '3d'
    sf::Color circleColor;

    LayoutCircle(sf::Vector2f position, sf::Vector2f velocity, float radius, float depth);
    LayoutCircle(sf::Vector2f position, sf::Vector2f velocity, float radius, float depth, sf::Color color);

};