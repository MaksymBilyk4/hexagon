#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "./CursorHolder.hpp"
#include <fmt/core.h>

struct Cursor {

    static auto getCurrentHolder() -> CursorHolder;

    static auto setCurrentHolder(CursorHolder const& ch) -> void;

    static auto setAppWindow(sf::RenderWindow &renderWindow) -> void;

    static auto setSimpleCursor() -> void;

    static auto setHandCursor() -> void;

private:
    static sf::RenderWindow* appWindow;

    static sf::Cursor appCursor;

    static CursorHolder currentHolder;
};