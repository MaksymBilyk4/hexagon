#include <SFML/Graphics.hpp>

#include "./Cursor.hpp"

sf::RenderWindow* Cursor::appWindow = nullptr;
sf::Cursor Cursor::appCursor;
CursorHolder Cursor::currentHolder = CursorHolder::NO_ONE;

auto Cursor::getCurrentHolder() -> CursorHolder {
    return currentHolder;
}

auto Cursor::setCurrentHolder(const CursorHolder &ch) -> void {
    currentHolder = ch;
}

auto Cursor::setAppWindow(sf::RenderWindow &renderWindow) -> void {
    appWindow = &renderWindow;
}

auto Cursor::setSimpleCursor() -> void {
    if (appCursor.loadFromSystem(sf::Cursor::Arrow))
        appWindow->setMouseCursor(appCursor);
}

auto Cursor::setHandCursor() -> void {
    if (appCursor.loadFromSystem(sf::Cursor::Hand))
        appWindow->setMouseCursor(appCursor);
}