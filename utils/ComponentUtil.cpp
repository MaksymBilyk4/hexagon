#include "ComponentUtil.hpp"

auto ComponentUtil::isMouseOver(sf::Vector2f const &elementPosition,
                                sf::Vector2f const &elementSize,
                                sf::Vector2i const &mousePosition) -> bool {
    if (
            (mousePosition.x >= elementPosition.x &&
             mousePosition.x <= elementPosition.x + elementSize.x) &&
            (mousePosition.y >= elementPosition.y &&
             mousePosition.y <= elementPosition.y + elementSize.y)) {
        return true;
    }
    return false;
}

auto ComponentUtil::listenOnMouseClick(const std::vector<std::unique_ptr<Component>> &components, const sf::Vector2i &mousePosition) -> void {
    for (auto const &comp: components) {
        if (comp->isMouseOver(mousePosition)) comp->onClick();
    }
}

auto ComponentUtil::listenOnMouseMove(const std::vector<std::unique_ptr<Component>> &components, const sf::Vector2i &mousePosition) -> void {
    for (auto const& comp : components) {
        if (comp->isMouseOver(mousePosition)) comp->onMouseOver();
        else comp -> onMouseLeave();
    }
}