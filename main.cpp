#include <SFML/Graphics.hpp>
#include <iostream>

#include "layout/components/TextWrapper/TextWrapper.hpp"
#include "layout/figures/Circle.hpp"
#include "layout/utils/LayoutController.hpp"
#include "layout/builders/LayoutBuilder.hpp"
#include "layout/builders/HomeLayoutBuilder.hpp"

#include "utils/font/FontHolder.hpp"
#include "utils/EventHandler.hpp"
#include "utils/Drawer.hpp"

#include "layout/components/version2/ModalVer2.hpp"
#include "layout/components/version2/ButtonVer2.hpp"
#include "layout/components/version2/TextWrapperVer2.hpp"
#include "layout/components/version2/CheckBoxGroupVer2.hpp"

int main() {
    auto window = sf::RenderWindow(sf::VideoMode(1400, 1000), "Hexxagon", sf::Style::Default);
    window.setFramerateLimit(60);

    auto fontHolder = FontHolder();
    auto eventHandler = EventHandler();

    CursorHolder::setAppWindow(window);

    LayoutBuilder::generateFigures(window);
    HomeLayoutBuilder::initHomeScreen(window);
    HomeLayoutBuilder::build();

    while (window.isOpen()) {

        auto event = sf::Event();
        while (window.pollEvent(event))
            eventHandler.handle_event(event, window);

        window.clear(sf::Color::Black);

        LayoutBuilder::drawBackground(window);

        Drawer::draw(ModalVer2::modals, window);

        Drawer::draw(ButtonVer2::buttons, window);

        Drawer::draw(TextWrapperVer2::textWrappers, window);

        Drawer::draw(CheckBoxGroupVer2::groups, window);

        window.display();
    }

    return 0;
}
