#pragma once

#include <SFML/Graphics.hpp>

struct EventHandler {

    auto handle_event(sf::Event &event, sf::Window &window) -> void;

private:
    auto close_window(sf::Window &window) -> void;

};