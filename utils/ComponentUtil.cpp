#include "ComponentUtil.hpp"

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

auto ComponentUtil::hide(std::vector<std::unique_ptr<Component>> &components, Component &component) -> void {
//    auto existenceIterator = std::ranges::find_if(
//            components.begin(),
//            components.end(),
//            [&component](std::unique_ptr<Component> const& compPtr) -> bool {
//                return &component == compPtr.get();
//            }
//    );
//
//    if (existenceIterator != components.end())
//        components.erase(existenceIterator);
}

auto ComponentUtil::show(std::vector<std::unique_ptr<Component>> &components, Component &component) -> void {
//    components.push_back(std::make_unique<Component>(component));
//    component.show();
}


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

auto ComponentUtil::isMouseOver(const Component &component, const sf::Vector2i &mousePosition) -> bool {
    if (
            (mousePosition.x >= component.getPosition().x &&
             mousePosition.x <= component.getPosition().x + component.getSize().x) &&
            (mousePosition.y >= component.getPosition().y &&
             mousePosition.y <= component.getPosition().y + component.getSize().y)) {
        return true;
    }
    return false;

}