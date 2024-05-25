#include <vector>

#include "./Modal.hpp"

std::vector<Modal> Modal::modals;

Modal::Modal(sf::Window &window, int width, int height) {
    auto windowMidX = window.getSize().x / 2;
    auto windowMidY = window.getSize().y / 2;

    modalBase = sf::VertexArray(sf::Quads, 4);

    // left upper point/corner
    modalBase[0].position = sf::Vector2f(windowMidX - width / 2, windowMidY - height / 2);
    // right upper point/corner
    modalBase[1].position = sf::Vector2f(windowMidX + width / 2, windowMidY - height / 2);
    // bottom right point/corner
    modalBase[2].position = sf::Vector2f(windowMidX + width / 2, windowMidY + height / 2);
    // bottom left point/corner
    modalBase[3].position = sf::Vector2f(windowMidX - width / 2, windowMidY + height / 2);

    for (int i = 0; i < 3; ++i) {
        modalBase[i].color = sf::Color(255, 255, 255, 150);
    }
}

auto Modal::getPosition() -> sf::Vector2f {
    return modalBase[0].position;
}

auto Modal::getSize() -> sf::Vector2f {
    return {modalBase[1].position.x - modalBase[0].position.x, modalBase[2].position.y - modalBase[1].position.y};
}

auto Modal::setVerticalGradient(sf::Color &upperColor, sf::Color &bottomColor) -> void {
    modalBase[0].color = upperColor;
    modalBase[1].color = upperColor;
    modalBase[2].color = bottomColor;
    modalBase[3].color = bottomColor;
}

auto Modal::setHorizontalGradient(sf::Color &leftColor, sf::Color &rightColor) -> void {
    modalBase[0].color = leftColor;
    modalBase[3].color = leftColor;
    modalBase[1].color = rightColor;
    modalBase[2].color = rightColor;
}

auto Modal::setColor(sf::Color &color) -> void {
    modalBase[0].color = color;
    modalBase[1].color = color;
    modalBase[2].color = color;
    modalBase[3].color = color;
}

auto Modal::drawModals(sf::RenderWindow &window) -> void {
    for (Modal &m: modals)
        window.draw(m.modalBase);
}

auto Modal::show() -> void {
    modals.push_back(*this);
}

auto Modal::hide() -> void {
    auto modal = std::ranges::find_if(modals.begin(), modals.end(), [this](Modal &m) -> bool {
        return &m == this;
    });

    modals.erase(modal);
}