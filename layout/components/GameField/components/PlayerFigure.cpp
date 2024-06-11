#include "./PlayerFigure.hpp"

std::vector<std::unique_ptr<Component>> PlayerFigure::playerFigures;

PlayerFigure::PlayerFigure(sf::Color const& color) {
    figure = sf::CircleShape(Hexagon::defaultRadius - 15);
    figure.setFillColor(color);
}

auto PlayerFigure::getPosition() const -> sf::Vector2f {
    return figure.getPosition();
}

auto PlayerFigure::getSize() const -> sf::Vector2f {
    return figure.getGlobalBounds().getSize();
}

auto PlayerFigure::getColor() const -> sf::Color {
    return figure.getFillColor();
}

auto PlayerFigure::getBorderColor() const -> sf::Color {
    return figure.getOutlineColor();
}

auto PlayerFigure::getBorderWidth() const -> float {
    return figure.getOutlineThickness();
}

auto PlayerFigure::setPosition(const sf::Vector2f &position) -> void {
    figure.setPosition(position);
}

auto PlayerFigure::setSize(const sf::Vector2f &size) -> void {

}

auto PlayerFigure::setColor(const sf::Color &color) -> void {
    figure.setFillColor(color);
}

auto PlayerFigure::setBorderColor(const sf::Color &color) -> void {
    figure.setOutlineColor(color);
}

auto PlayerFigure::setBorderWidth(float borderWidth) -> void {
    figure.setOutlineThickness(borderWidth);
}

auto PlayerFigure::setRadius(float radius) -> void {
    figure.setRadius(radius);
}

auto PlayerFigure::isMouseOver(const sf::Vector2i &mousePosition) const -> bool {
    return ComponentUtil::isMouseOver(*this, mousePosition);
}

auto PlayerFigure::show() -> void {
    playerFigures.push_back(std::move(std::make_unique<PlayerFigure>(*this)));
}

auto PlayerFigure::hide() -> void {
    auto playerFigureExistenceIterator = std::find_if(
            playerFigures.begin(),
            playerFigures.end(),
            [this](std::unique_ptr<Component> const &playerFigure) -> bool {
                return playerFigure->getComponentId() == getComponentId();
            }
    );

    if (playerFigureExistenceIterator != playerFigures.end()) {
        playerFigures.erase(playerFigureExistenceIterator);
    }
}

auto PlayerFigure::draw(sf::RenderWindow &renderWindow) -> void {
    renderWindow.draw(figure);
}