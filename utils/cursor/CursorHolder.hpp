#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "./CurrentHolder.hpp"

struct CursorHolder {

    static auto setSimpleCursor(sf::Window &window) -> void;

    static auto setHandCursor(sf::Window &window) -> void;

    static auto getCurrentHolder() -> CurrentHolder;

    static auto setCurrentHolder(CurrentHolder const& ch) -> void;

    static auto setSimpleCursor() -> void;

    static auto setHandCursor() -> void;

    static auto setAppWindow(sf::RenderWindow &renderWindow) -> void;

    static auto getAppWindow() -> sf::RenderWindow&;

private:
    static sf::RenderWindow* appWindow;

    static sf::Cursor appCursor;

    static CurrentHolder currentHolder;
};