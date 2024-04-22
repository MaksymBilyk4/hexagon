#include <SFML/Graphics.hpp>
#include <iostream>

#include "layout/components/Button.hpp"
#include "layout/figures/LayoutCircle.hpp"
#include "layout/utils/LayoutController.hpp"
#include "utils/EventHandler.hpp"
#include "layout/components/Modal.hpp"
#include "layout/utils/LayoutConstructor.hpp"
#include "utils/font/FontHolder.hpp"

int main() {

    auto window = sf::RenderWindow(sf::VideoMode(1400, 1000), "Hexxagon", sf::Style::Default);
    window.setFramerateLimit(60);

    auto fontHolder = FontHolder();
    auto eventHandler = EventHandler();

    auto layoutController = LayoutController(window, 50);
    layoutController.init();


    auto t = LayoutConstructor::mainText();
//    t.setFont(FontHolder::getFont(Fonts::SIXTY_FOUR_REGULAR_FONT));
//    t.setPosition({200, 200});
//    t.setFillColor(sf::Color::Red);

    while (window.isOpen()) {

        auto event = sf::Event();
        while (window.pollEvent(event))
            eventHandler.handle_event(event, window);

        window.clear(sf::Color::Black);

        LayoutController::drawBackground(window);
        Modal::drawModals(window);
        Button::drawButtons(window);

//        window.draw(t);

        window.display();
    }

    return 0;
}
