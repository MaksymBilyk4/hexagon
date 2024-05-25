#pragma once

#include <vector>
#include "../components/Component.hpp"
#include "../figures/Circle.hpp"
#include "../../utils/RandomGenerator.hpp"

struct LayoutBuilder {

    static auto drawBackground(sf::RenderWindow &renderWindow) -> void;

    static auto generateFigures(sf::RenderWindow &renderWindow) -> void;

private:

    static RandomGenerator random;
    static std::vector<Circle> figures;


};