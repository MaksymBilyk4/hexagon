#include <SFML/Graphics.hpp>
#include "utils/EventHandler.h"

int main() {

    auto window = sf::RenderWindow(sf::VideoMode(1000, 800), "Hexagon", sf::Style::Default);

    auto eventHandler = EventHandler();

    while (window.isOpen()) {

        auto event = sf::Event();
        while (window.pollEvent(event))
            eventHandler.handle_event(event, window);

        window.clear();
        window.display();
    }

    return 0;
}
