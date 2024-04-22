#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../figures/LayoutCircle.hpp"
#include "../../utils/RandomGenerator.hpp"


struct LayoutController {

    LayoutController(sf::RenderWindow &window, int figureCount, sf::Color figureColor);

    LayoutController(sf::RenderWindow &window, int figureCount);

    LayoutController(sf::RenderWindow &window);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static auto drawBackground(sf::RenderWindow &window) -> void;

    auto init() -> void;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    auto setFigureColor(sf::Color color) -> void;

    auto setFigureCount(int figureCount) -> void;

private:
    int figureCount;
    sf::Color figureColor;
    static RandomGenerator random;
    static std::vector<LayoutCircle> figures;
    sf::RenderWindow &globalWindow;

    auto generateFigures() -> void;

};