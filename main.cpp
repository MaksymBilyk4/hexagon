#include <SFML/Graphics.hpp>
#include <iostream>

#include "layout/components/Button/Button.hpp"
#include "layout/components/TextWrapper/TextWrapper.hpp"
#include "layout/components/CheckBox/CheckBoxGroup.hpp"
#include "layout/components/Modal/Modal.hpp"
#include "layout/components/GameField/components/Hexagon.hpp"
#include "layout/components/GameField/components/PlayerFigure.hpp"
#include "layout/components/TextField/TextField.hpp"

#include "layout/builders/BackgroundBuilder.hpp"
#include "layout/builders/HomeLayoutBuilder.hpp"
#include "layout/builders/GameLayoutBuilder.hpp"
#include "layout/builders/GameInfo/GameInfoLayoutBuilder.hpp"

#include "layout/drawer/Drawer.hpp"

#include "utils/font/FontHolder.hpp"
#include "utils/EventHandler.hpp"

#include "./utils/Game/GameFileStore.hpp"


int main() {
    auto window = sf::RenderWindow(sf::VideoMode(1400, 1000), "Hexxagon", sf::Style::Default);
    window.setFramerateLimit(60);

    auto fontHolder = FontHolder();
    auto eventHandler = EventHandler();

    Cursor::setAppWindow(window);


    BackgroundBuilder::generateFigures(window);

    HomeLayoutBuilder::initHomeScreen(window);

    GameInfoLayoutBuilder::initInfoScreen(window);

    GameLayoutBuilder::prepareGameField(window);

    GameField::printStateMatrix();

//    GameFileStore::uploadGame("/Users/maksymbilyk/Desktop/programming/PJAIT/hexagon/assets/saved_game_data/game_101.txt");

    HomeLayoutBuilder::build();

    while (window.isOpen()) {

        auto event = sf::Event();
        while (window.pollEvent(event))
            eventHandler.handle_event(event, window);

        window.clear(sf::Color::Black);

        BackgroundBuilder::drawBackground(window);

        Drawer::draw(PlayerFigure::playerFigures, window);

        if (GameField::drawState) {
            Drawer::draw(GameField::fieldMatrix, window);
            Drawer::draw(GameField::playerFigures, window);
            GameField::playerOneCountBar->draw(window);
            GameField::movePlayerLabel->draw(window);
            GameField::playerTwoCountBar->draw(window);
        }

        Drawer::draw(Modal::modals, window);

        Drawer::draw(TextField::textFields, window);

        Drawer::draw(Button::buttons, window);

        Drawer::draw(TextWrapper::textWrappers, window);

        Drawer::draw(CheckBoxGroup::groups, window);

        window.display();
    }

    return 0;
}
