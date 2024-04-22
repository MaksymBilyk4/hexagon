#pragma once

#include "SFML/Graphics.hpp"
#include "./Fonts.hpp"

struct FontHolder {

    FontHolder();

    static auto getFont(Fonts font) -> sf::Font&;

private:
    static sf::Font ROBOTO_MEDIUM;

    static sf::Font ROBOTO_REGULAR;

    static sf::Font SIXTY_FOUR_REGULAR;

};