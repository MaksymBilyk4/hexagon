#include <fmt/core.h>

#include "EventHandler.hpp"

auto EventHandler::close_window(sf::Window &window) -> void {
    fmt::println("Window closed");
    window.close();
}

auto EventHandler::resize_window(sf::Window &window) -> void {
    auto currentWindowWidth = window.getSize().x;
    auto currentWindowHeight = window.getSize().y;

    if (currentWindowWidth < 800 || currentWindowHeight < 600) {
        window.setSize({800, 600});
    }
}

auto EventHandler::mouse_move(sf::Window &window) -> void {
    Button::catchOnMouseOver(window);
}

auto EventHandler::mouse_click(sf::Window &window) -> void {
    auto mousePosition = sf::Mouse::getPosition(window);
    Button::catchOnMouseClick(mousePosition);
}


auto EventHandler::handle_event(sf::Event const &event, sf::Window &window) -> void {

    switch (event.type) {
        case sf::Event::Closed: // window closing
            close_window(window);
            break;
        case sf::Event::Resized: // window resizing
            resize_window(window);
            break;
        case sf::Event::MouseMoved: // mouse moving
            mouse_move(window);
            break;
        case sf::Event::MouseButtonPressed:
            mouse_click(window);
            break;
    }


}