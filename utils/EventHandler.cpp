#include "EventHandler.hpp"


auto EventHandler::close_window(sf::Window &window) -> void {
    window.close();
}

auto EventHandler::resize_window(sf::Window &window) -> void {
    auto currentWindowWidth = window.getSize().x;
    auto currentWindowHeight = window.getSize().y;

    if (currentWindowWidth < 800 || currentWindowHeight < 600) {
        window.setSize({800, 600});
    }
}

auto EventHandler::mouse_move(sf::Window &window) -> void {
    auto mousePosition = sf::Mouse::getPosition(window);

    ComponentUtil::listenOnMouseMove(Button::buttons, mousePosition);
    ComponentUtil::listenOnMouseMove(CheckBoxGroup::groups, mousePosition);
}

auto EventHandler::mouse_click(sf::Window &window) -> void {
    auto mousePosition = sf::Mouse::getPosition(window);

    ComponentUtil::listenOnMouseClick(Button::buttons, mousePosition);

    CheckBoxGroup::setClickedPosition(mousePosition);
    ComponentUtil::listenOnMouseClick(CheckBoxGroup::groups, mousePosition);
}


auto EventHandler::handle_event(sf::Event const &event, sf::Window &window) -> void {

    switch (event.type) {
        case sf::Event::Closed:
            close_window(window);
            break;
        case sf::Event::Resized:
            resize_window(window);
            break;
        case sf::Event::MouseMoved:
            mouse_move(window);
            break;
        case sf::Event::MouseButtonPressed:
            mouse_click(window);
            break;
    }


}