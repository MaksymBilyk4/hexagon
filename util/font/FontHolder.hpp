#pragma once

#include "SFML/Graphics.hpp"
#include "./Fonts.hpp"
#include "../game/Path.hpp"

struct FontHolder {

    FontHolder();

    static auto getFont(Fonts const& font) -> sf::Font&;

private:
    static sf::Font ROBOTO_MEDIUM;

    static sf::Font ROBOTO_REGULAR;

    static sf::Font SIXTY_FOUR_REGULAR;

};