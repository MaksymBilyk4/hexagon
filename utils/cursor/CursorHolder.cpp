#include <SFML/Graphics.hpp>

#include "./CursorHolder.hpp"

sf::Cursor CursorHolder::appCursor;

auto CursorHolder::setSimpleCursor(sf::Window &window) -> void {
    if (appCursor.loadFromSystem(sf::Cursor::Arrow))
        window.setMouseCursor(appCursor);
}

auto CursorHolder::setHandCursor(sf::Window &window) -> void {
    if (appCursor.loadFromSystem(sf::Cursor::Hand))
        window.setMouseCursor(appCursor);
}