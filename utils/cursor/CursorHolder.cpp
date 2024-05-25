#include <SFML/Graphics.hpp>

#include "./CursorHolder.hpp"

sf::RenderWindow* CursorHolder::appWindow = nullptr;
sf::Cursor CursorHolder::appCursor;
CurrentHolder CursorHolder::currentHolder = CurrentHolder::NO_ONE;


// UPDATED ============
auto CursorHolder::setSimpleCursor() -> void {
    if (appCursor.loadFromSystem(sf::Cursor::Arrow))
        appWindow->setMouseCursor(appCursor);
}

auto CursorHolder::setHandCursor() -> void {
    if (appCursor.loadFromSystem(sf::Cursor::Hand))
        appWindow->setMouseCursor(appCursor);
}

auto CursorHolder::setAppWindow(sf::RenderWindow &renderWindow) -> void {
    appWindow = &renderWindow;
}

auto CursorHolder::getAppWindow() -> sf::RenderWindow & {
    return *appWindow;
}

auto CursorHolder::setSimpleCursor(sf::Window &window) -> void {
    if (appCursor.loadFromSystem(sf::Cursor::Arrow)) {
        window.setMouseCursor(appCursor);
    }
}
// ========================

auto CursorHolder::setHandCursor(sf::Window &window) -> void {
    if (appCursor.loadFromSystem(sf::Cursor::Hand)) {
        window.setMouseCursor(appCursor);
    }
}

auto CursorHolder::getCurrentHolder() -> CurrentHolder {
    return currentHolder;
}

auto CursorHolder::setCurrentHolder(const CurrentHolder &ch) -> void {
    currentHolder = ch;
}