#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "../layout/components/Component.hpp"

struct Drawer {

    static auto draw(std::vector<std::unique_ptr<Component>> &components, sf::RenderWindow &renderWindow) -> void;

};