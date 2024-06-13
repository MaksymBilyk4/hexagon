#pragma once

#include "SFML/Graphics.hpp"
#include "../../layout/components/Button/Button.hpp"
#include "../../layout/components/CheckBox/CheckBoxGroup.hpp"
#include "../cursor/Cursor.hpp"
#include "../../layout/components/Button/Button.hpp"
#include "../../layout/components/Game/components/Hexagon.hpp"
#include "../../layout/components/CheckBox/CheckBoxGroup.hpp"
#include "../../model/GameField/GameField.hpp"
#include "../../layout/components/TextField/TextField.hpp"

struct EventHandler {

    auto handle_event(sf::Event const &event, sf::Window &window) -> void;

private:

    auto close_window(sf::Window &window) -> void;

    auto resize_window(sf::Window &window) -> void;

    auto mouse_move(sf::Window &window) -> void;

    auto mouse_click(sf::Window &window) -> void;

};