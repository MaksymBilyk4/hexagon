#include <fmt/core.h>

#include "EventHandler.hpp"

auto EventHandler::close_window(sf::Window &window) -> void {
    fmt::println("Window closed");
    window.close();
}

auto EventHandler::handle_event(sf::Event &event, sf::Window &window) -> void {

    if (event.type == sf::Event::Closed)
        close_window(window);

}