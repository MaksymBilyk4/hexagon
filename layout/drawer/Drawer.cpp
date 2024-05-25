#include "./Drawer.hpp"

auto Drawer::draw(std::vector<std::unique_ptr<Component>> &components, sf::RenderWindow &renderWindow) -> void {
    for (auto &componentToDraw: components)
        componentToDraw->draw(renderWindow);
}