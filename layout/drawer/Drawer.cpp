#include "./Drawer.hpp"

auto Drawer::draw(std::vector<std::unique_ptr<Component>> &components, sf::RenderWindow &renderWindow) -> void {
    for (auto &componentToDraw: components)
        if (componentToDraw != nullptr)
            componentToDraw->draw(renderWindow);
}

auto Drawer::draw(std::vector<std::vector<std::unique_ptr<Component>>> &components, sf::RenderWindow& renderWindow) -> void {
    for (auto &row : components)
        for (auto &entry : row)
            if (entry != nullptr)
                entry->draw(renderWindow);
}
