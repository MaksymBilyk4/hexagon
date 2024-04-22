#include <SFML/Graphics.hpp>
#include <iostream>

#include "layout/components/Button.hpp"
#include "layout/figures/LayoutCircle.hpp"
#include "layout/utils/LayoutController.hpp"
#include "utils/EventHandler.hpp"
#include "layout/components/Modal.hpp"

int main() {

    auto window = sf::RenderWindow(sf::VideoMode(1400, 1000), "Hexxagon", sf::Style::Default);
    window.setFramerateLimit(60);

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

        window.display();
    }

    return 0;
}
