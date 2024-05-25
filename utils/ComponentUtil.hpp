#pragma once
#include <SFML/Graphics.hpp>

#include <algorithm>
#include <memory>
#include <vector>
#include <fmt/core.h>
#include <fmt/format.h>
#include "../layout/components/Component.hpp"

struct ComponentUtil {

    static auto listenOnMouseClick(std::vector<std::unique_ptr<Component>> const& components, sf::Vector2i const& mousePosition) -> void;

    static auto listenOnMouseMove(std::vector<std::unique_ptr<Component>> const& components, sf::Vector2i const& mousePosition) -> void;

    template<typename C>
    static auto hide(std::vector<C> &componentCollection, C &component) -> void;

    template<typename C>
    static auto show(std::vector<C> &componentCollection, C &component) -> void;

    template<typename T>
    static auto isMouseOver(T const &element, sf::Vector2i const &mousePosition) -> bool;

    // reloaded method for elements
    static auto isMouseOver(sf::Vector2f const &elementPosition, sf::Vector2f const &elementSize,
                            sf::Vector2i const &mousePosition) -> bool;

};

template<typename T>
auto ComponentUtil::isMouseOver(const T &element, const sf::Vector2i &mousePosition) -> bool {
    if (
            (mousePosition.x >= element.getPosition().x &&
             mousePosition.x <= element.getPosition().x + element.getSize().x) &&
            (mousePosition.y >= element.getPosition().y &&
             mousePosition.y <= element.getPosition().y + element.getSize().y)) {
        return true;
    }
    return false;
}

template<typename C>
auto ComponentUtil::show(std::vector<C> &componentCollection, C &component) -> void {
    auto existenceIterator = std::ranges::find_if(
            componentCollection.begin(),
            componentCollection.end(),
            [&component](C const& otherComponent) -> bool {return &component == &otherComponent;});

    if (existenceIterator == componentCollection.end()) {
        component.show();
        componentCollection.push_back(component);
    } else fmt::println("Unable to show: Component already rendered!");

}

template<typename C>
auto ComponentUtil::hide(std::vector<C> &componentCollection, C &component) -> void {
    auto existenceIterator = std::ranges::find_if(
            componentCollection.begin(),
            componentCollection.end(),
            [&component](C const& otherComponent) -> bool {return &component == &otherComponent;});

    if (existenceIterator != componentCollection.end()) {
        component.hide();
        componentCollection.erase(existenceIterator);
    } else fmt::println("Unable to hide: Component not found!");

}

//auto ComponentUtil::listenOnMouseClick(std::vector<std::unique_ptr<Component>> const& components, sf::Vector2i const& mousePosition) -> void {
//    for (auto const& comp : components) {
//        if (comp->isMouseOver(mousePosition))
//            comp->onClick();
//    }
//}
//
//auto ComponentUtil::listenOnMouseMove(const std::vector<std::unique_ptr<Component>> &components, const sf::Vector2i &mousePosition) -> void {
//    for (auto const& comp : components) {
//        if (comp->isMouseOver(mousePosition)) comp->onMouseOver();
//        else comp -> onMouseLeave();
//    }
//}