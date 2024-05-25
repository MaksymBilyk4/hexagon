#pragma once

#include <SFML/Graphics.hpp>
#include "../layout/components/Button/Button.hpp"
#include "../layout/components/CheckBox/CheckBoxGroup.hpp"
#include "./cursor/CursorHolder.hpp"
#include "../layout/components/version2/ButtonVer2.hpp"
#include "../layout/components/version2/CheckBoxGroupVer2.hpp"

struct EventHandler {

    auto handle_event(sf::Event const &event, sf::Window &window) -> void;

private:

    auto close_window(sf::Window &window) -> void;

    auto resize_window(sf::Window &window) -> void;

    auto mouse_move(sf::Window &window) -> void;

    auto mouse_click(sf::Window &window) -> void;

};