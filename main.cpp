#include <SFML/Graphics.hpp>
#include <iostream>

#include "layout/models/LayoutCircle.hpp"
#include "layout/utils/LayoutBackgroundGenerator.hpp"
#include "utils/EventHandler.hpp"

int main() {

    auto window = sf::RenderWindow(sf::VideoMode(1200, 800), "Hexxagon", sf::Style::Default);
    window.setFramerateLimit(60);

    auto eventHandler = EventHandler();

    auto layoutBackgroundGenerator = LayoutBackgroundGenerator();
    layoutBackgroundGenerator.generate(window);

    while (window.isOpen()) {

        auto event = sf::Event();
        while (window.pollEvent(event))
            eventHandler.handle_event(event, window);

        window.clear(sf::Color::Black);

        layoutBackgroundGenerator.drawBackground(window);

        window.display();
    }

    return 0;
}
