#include <SFML/Graphics.hpp>
#include <fmt/core.h>

#include "./LayoutConstructor.hpp"
#include "../../utils/font/FontHolder.hpp"
sf::Font LayoutConstructor::sixtyFourRegular = sf::Font();

auto LayoutConstructor::makeMainModal(sf::RenderWindow &window) -> Modal {
    auto mainModal = Modal(window, 950, 750);
    auto topGradient = sf::Color(191, 64, 191, 150);
    auto bottomGradient = sf::Color(75, 0, 130, 150);
    mainModal.setVerticalGradient(topGradient, bottomGradient);
    mainModal.show();
    return mainModal;
}

auto LayoutConstructor::makeStartGameButton(sf::RenderWindow &window) -> Button {
    auto startGameButton = Button({500, 50}, "START GAME");
    startGameButton.setBorderColor({194, 31, 188});
    startGameButton.setHoverBorderColor({255, 0, 229});
    startGameButton.setBorderWidth(3);
    startGameButton.setFontSize(40);
    startGameButton.setInnerColor({190, 190, 190});
    startGameButton.setHoverInnerColor({255, 255, 255});
    startGameButton.setPosition({static_cast<float>(window.getSize().x / 2 - startGameButton.getWidth() / 2), 725});
    startGameButton.onClick([]() -> void { fmt::println("test"); });
    startGameButton.show();

    return startGameButton;
}

auto LayoutConstructor::mainText() -> sf::Text {
    auto text = sf::Text("Hello world", FontHolder::getFont(Fonts::SIXTY_FOUR_REGULAR_FONT), 20);
    return text;
}