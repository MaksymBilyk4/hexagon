#include "./Modal.hpp"

std::vector<std::unique_ptr<Component>> Modal::modals;

Modal::Modal(const sf::RenderWindow &renderWindow, int width, int height) {
    auto windowMidX = renderWindow.getSize().x / 2;
    auto windowMidY = renderWindow.getSize().y / 2;

    modalBase = sf::VertexArray(sf::Quads, 4);

    // left upper point/corner
    modalBase[0].position = sf::Vector2f(windowMidX - (width / 2), windowMidY - (height / 2));

    // right upper point/corner
    modalBase[1].position = sf::Vector2f(windowMidX + (width / 2), windowMidY - (height / 2));

    // bottom right point/corner
    modalBase[2].position = sf::Vector2f(windowMidX + (width / 2), windowMidY + (height / 2));

    // bottom left point/corner
    modalBase[3].position = sf::Vector2f(windowMidX - (width / 2), windowMidY + (height / 2));


    setVerticalGradient(sf::Color(191, 64, 191, 150), sf::Color(75, 0, 130, 150));

}

auto Modal::getPosition() const -> sf::Vector2f {
    return modalBase[0].position;
}

auto Modal::getSize() const -> sf::Vector2f {
    return {modalBase[1].position.x - modalBase[0].position.x, modalBase[2].position.y - modalBase[1].position.y};
}

auto Modal::setPosition(sf::Vector2f const &position) -> void {
    auto modalSize = getSize();

    modalBase[0].position = position;

    modalBase[1].position = {position.x + modalSize.x, position.y};

    modalBase[2].position = {position.x + modalSize.x, position.y + modalSize.y};

    modalBase[3].position = {position.x, position.y + modalSize.y};

}

auto Modal::setSize(const sf::Vector2f &size) -> void {

    modalBase[1].position = {modalBase[0].position.x + size.x, modalBase[0].position.y};

    modalBase[2].position = {modalBase[1].position.x, modalBase[0].position.y + size.y};

    modalBase[2].position = {modalBase[0].position.x, modalBase[0].position.y + size.y};

}

auto Modal::isMouseOver(const sf::Vector2i &mousePosition) const -> bool {
    return ComponentUtil::isMouseOver(*this, mousePosition);
}

auto Modal::show() -> void {
    modals.push_back(std::make_unique<Modal>(*this));
}

auto Modal::hide() -> void {
    auto modalExistenceIterator = std::find_if(
            modals.begin(),
            modals.end(),
            [this](std::unique_ptr<Component> const &modal) -> bool {
                return modal->getComponentId() == getComponentId();
            }
    );

    if (modalExistenceIterator != modals.end()) {
        modals.erase(modalExistenceIterator);
    }
}

auto Modal::draw(sf::RenderWindow &renderWindow) -> void {
    renderWindow.draw(modalBase);
}

auto Modal::setVerticalGradient(const sf::Color &upperColor, const sf::Color &bottomColor) -> void {
    modalBase[0].color = upperColor;
    modalBase[1].color = upperColor;
    modalBase[2].color = bottomColor;
    modalBase[3].color = bottomColor;
}

auto Modal::setHorizontalGradient(const sf::Color &leftColor, const sf::Color &rightColor) -> void {
    modalBase[0].color = leftColor;
    modalBase[3].color = leftColor;
    modalBase[1].color = rightColor;
    modalBase[2].color = rightColor;
}

auto Modal::setInlineColor(const sf::Color &color) -> void {
    for (int i = 0; i < vertexCount; i++)
        modalBase[i].color = color;
}
