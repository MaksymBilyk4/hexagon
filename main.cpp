#include <SFML/Graphics.hpp>

#include "layout/components/Button/Button.hpp"
#include "layout/components/TextWrapper/TextWrapper.hpp"
#include "layout/components/CheckBox/CheckBoxGroup.hpp"
#include "layout/components/Modal/Modal.hpp"
#include "layout/components/Game/components/PlayerFigure.hpp"
#include "layout/components/TextField/TextField.hpp"

#include "layout/builders/BackgroundBuilder.hpp"
#include "layout/builders/HomeLayoutBuilder.hpp"
#include "layout/builders/GameLayoutBuilder.hpp"
#include "layout/builders/GameInfo/GameInfoLayoutBuilder.hpp"

#include "layout/drawer/Drawer.hpp"

#include "util/font/FontHolder.hpp"
#include "util/event/EventHandler.hpp"

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

    HomeLayoutBuilder::build();

    while (window.isOpen()) {

        auto event = sf::Event();
        while (window.pollEvent(event))
            eventHandler.handle_event(event, window);

        window.clear(sf::Color::Black);

        BackgroundBuilder::drawBackground(window);


        if (GameField::drawState) {
            Drawer::draw(PlayerFigure::playerFigures, window);
            Drawer::draw(GameField::fieldMatrix, window);
            Drawer::draw(GameField::playerFigures, window);
            GameField::playerOneCountBar->draw(window);
            GameField::movePlayerLabel->draw(window);
            GameField::playerTwoCountBar->draw(window);
            GameField::freeSpaceLabel->draw(window);
            GameField::gameModeLabel->draw(window);
            GameField::gameModeLabel->draw(window);
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
