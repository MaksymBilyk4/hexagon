#include "./FontHolder.hpp"

sf::Font FontHolder::ROBOTO_MEDIUM;
sf::Font FontHolder::ROBOTO_REGULAR;
sf::Font FontHolder::SIXTY_FOUR_REGULAR;

FontHolder::FontHolder() {
    ROBOTO_MEDIUM.loadFromFile("/Users/maksymbilyk/Desktop/programming/PJAIT/hexagon/assets/fonts/Roboto-Medium.ttf");
    ROBOTO_REGULAR.loadFromFile("/Users/maksymbilyk/Desktop/programming/PJAIT/hexagon/assets/fonts/Roboto-Regular.ttf");
    SIXTY_FOUR_REGULAR.loadFromFile("/Users/maksymbilyk/Desktop/programming/PJAIT/hexagon/assets/fonts/Sixtyfour-Regular.ttf");
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