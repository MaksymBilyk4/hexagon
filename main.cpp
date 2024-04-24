#include <SFML/Graphics.hpp>
#include <iostream>

#include "layout/components/Modal.hpp"
#include "layout/components/Button.hpp"
#include "layout/components/TextWrapper.hpp"
#include "layout/figures/Circle.hpp"
#include "layout/utils/LayoutController.hpp"
#include "utils/EventHandler.hpp"
#include "utils/font/FontHolder.hpp"

int main() {

    auto window = sf::RenderWindow(sf::VideoMode(1400, 1000), "Hexxagon", sf::Style::Default);
    window.setFramerateLimit(60);

    auto fontHolder = FontHolder();
    auto eventHandler = EventHandler();

    auto layoutController = LayoutController(window, 50);
    layoutController.init();

    while (window.isOpen()) {

        auto event = sf::Event();
        while (window.pollEvent(event))
            eventHandler.handle_event(event, window);

        window.clear(sf::Color::Black);

        LayoutController::drawBackground(window);

        Modal::drawModals(window);
        Button::drawButtons(window);
        TextWrapper::drawTextWrappers(window);

        window.display();
    }

    return 0;
}
