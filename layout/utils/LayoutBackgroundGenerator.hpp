#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../models/LayoutCircle.hpp"
#include "../../utils/RandomGenerator.hpp"


struct LayoutBackgroundGenerator {


    LayoutBackgroundGenerator(int figureCount, sf::Color figureColor);
    LayoutBackgroundGenerator();

    auto generate(sf::RenderWindow& window) -> void;

    auto drawBackground(sf::RenderWindow& window) -> void;

    auto setFigureColor(sf::Color color) -> void;

    auto setFigureCount(int figureCount) -> void;

private:
    int figureCount;
    sf::Color figureColor;
    RandomGenerator random;
    std::vector<LayoutCircle> figures;

};