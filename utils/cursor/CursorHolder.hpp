#pragma once
#include <SFML/Graphics.hpp>

struct CursorHolder {

    static auto setSimpleCursor(sf::Window &window) -> void;

    static auto setHandCursor(sf::Window &window) -> void;

private:
    static sf::Cursor appCursor;

};