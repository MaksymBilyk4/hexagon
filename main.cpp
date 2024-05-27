#include <SFML/Graphics.hpp>
#include <iostream>

#include "layout/components/TextWrapper/TextWrapper.hpp"
#include "layout/figures/Circle.hpp"
#include "layout/builders/LayoutBuilder.hpp"
#include "layout/builders/HomeLayoutBuilder.hpp"
#include "layout/builders/GameLayoutBuilder.hpp"

#include "utils/font/FontHolder.hpp"
#include "utils/EventHandler.hpp"
#include "layout/drawer/Drawer.hpp"

#include "layout/components/Modal/Modal.hpp"
#include "layout/components/Button/Button.hpp"
#include "layout/components/TextWrapper/TextWrapper.hpp"
#include "layout/components/CheckBox/CheckBoxGroup.hpp"

int main() {
    auto window = sf::RenderWindow(sf::VideoMode(1400, 1000), "Hexxagon", sf::Style::Default);
    window.setFramerateLimit(60);

    auto fontHolder = FontHolder();
    auto eventHandler = EventHandler();

    Cursor::setAppWindow(window);

    LayoutBuilder::generateFigures(window);

    HomeLayoutBuilder::initHomeScreen(window);
//    GameLayoutBuilder::initGameField();

    HomeLayoutBuilder::build();

    fmt::println("Buttons {}", Button::buttons.size());
    fmt::println("Modals {}", Modal::modals.size());
    fmt::println("Check Box {}", CheckBoxGroup::groups.size());
    fmt::println("Text {}", TextWrapper::textWrappers.size());

    while (window.isOpen()) {

        auto event = sf::Event();
        while (window.pollEvent(event))
            eventHandler.handle_event(event, window);

        window.clear(sf::Color::Black);

        LayoutBuilder::drawBackground(window);

        Drawer::draw(Modal::modals, window);

        Drawer::draw(Button::buttons, window);

        Drawer::draw(TextWrapper::textWrappers, window);

        Drawer::draw(CheckBoxGroup::groups, window);

        window.display();
    }

    return 0;
}
