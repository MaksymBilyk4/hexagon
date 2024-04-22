#pragma once

#include "SFML/Graphics.hpp"
#include <vector>

struct Modal {


    Modal(sf::Window &window, int width, int height);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    auto getIsOpen() -> bool;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    auto setIsOpen(bool state) -> void;

    auto setVerticalGradient(sf::Color& upperColor, sf::Color& bottomColor) -> void;

    auto setHorizontalGradient(sf::Color& leftColor, sf::Color& rightColor) -> void;

    auto setColor(sf::Color& color) -> void;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static auto drawModals(sf::RenderWindow& window) -> void;

    auto show() -> void;

    auto hide() -> void;

private:

    static std::vector<Modal> modals;

    sf::VertexArray modalBase;
    bool isOpen;
};