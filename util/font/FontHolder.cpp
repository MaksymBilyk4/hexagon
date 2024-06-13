#include "./FontHolder.hpp"

sf::Font FontHolder::ROBOTO_MEDIUM;
sf::Font FontHolder::ROBOTO_REGULAR;
sf::Font FontHolder::SIXTY_FOUR_REGULAR;

FontHolder::FontHolder() {
    auto R_M = Path::FONTS + "/Roboto-Medium.ttf";
    auto R_R = Path::FONTS + "/Roboto-Regular.ttf";
    auto S_R = Path::FONTS + "/Sixtyfour-Regular.ttf";
    ROBOTO_MEDIUM.loadFromFile(R_M);
    ROBOTO_REGULAR.loadFromFile(R_R);
    SIXTY_FOUR_REGULAR.loadFromFile(S_R);
}

auto FontHolder::getFont(Fonts const& font) -> sf::Font& {
    switch (font) {
        case ROBOTO_REGULAR_FONT:
            return ROBOTO_REGULAR;
        case ROBOTO_MEDIUM_FONT:
            return ROBOTO_MEDIUM;
        case SIXTY_FOUR_REGULAR_FONT:
            return SIXTY_FOUR_REGULAR;
    }
}