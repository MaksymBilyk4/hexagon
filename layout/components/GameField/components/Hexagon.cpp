#include "./Hexagon.hpp"

std::vector<std::unique_ptr<Component>> Hexagon::items;
float Hexagon::defaultRadius = 50;
sf::Color Hexagon::defaultColor = sf::Color(151, 40, 199);
sf::Color Hexagon::defaultBorderColor = sf::Color(99, 8, 138);

Hexagon::Hexagon() : hexagon(sf::CircleShape(defaultRadius, 6)), state(FieldState::EMPTY) {

    hexagon.setOutlineThickness(9);
    hexagon.setFillColor(defaultColor);
    hexagon.setOutlineColor(defaultBorderColor);
    hexagon.rotate(30);

}

auto Hexagon::getPosition() const -> sf::Vector2f {
    return hexagon.getPosition();
}

auto Hexagon::getSize() const -> sf::Vector2f {
    return hexagon.getGlobalBounds().getSize();
}

auto Hexagon::getFieldState() const -> FieldState {
    return state;
}

auto Hexagon::getFieldRow() const -> int {
    return fieldRow;
}

auto Hexagon::getFieldCol() const -> int {
    return fieldCol;
}

auto Hexagon::getColor() const -> sf::Color {
    return hexagon.getFillColor();
}

auto Hexagon::getBorderColor() const -> sf::Color {
    return hexagon.getOutlineColor();
}

auto Hexagon::getBorderWidth() const -> float {
    return hexagon.getOutlineThickness();
}

auto Hexagon::getIsSelectedByBot() const -> bool {
    return isSelectedByBot;
}

auto Hexagon::setPosition(const sf::Vector2f &position) -> void {
    hexagon.setPosition(position);
}

auto Hexagon::setSize(const sf::Vector2f &size) -> void {
    // no implementation needed
}

auto Hexagon::setFieldSate(const FieldState &fieldState) -> void {
    state = fieldState;
}

auto Hexagon::setFieldRow(int row) -> void {
    fieldRow = row;
}

auto Hexagon::setFieldCol(int col) -> void {
    fieldCol = col;
}

auto Hexagon::setColor(const sf::Color &color) -> void {
    hexagon.setFillColor(color);
}

auto Hexagon::setBorderColor(const sf::Color &color) -> void {
    hexagon.setOutlineColor(color);
}

auto Hexagon::setBorderWidth(float borderWidth) -> void {
    hexagon.setOutlineThickness(borderWidth);
}

auto Hexagon::setIsSelectedByBot(bool isSelected) -> void {
    isSelectedByBot = isSelected;
}

auto Hexagon::isMouseOver(const sf::Vector2i &mousePosition) const -> bool {
    sf::Transform transform = hexagon.getTransform().getInverse();
    sf::Vector2f localMousePosition = transform.transformPoint(static_cast<sf::Vector2f>(mousePosition));

    return hexagon.getLocalBounds().contains(localMousePosition);
}

auto Hexagon::onClick() -> void {
    // can't handle here because of circular dependencies of GameField.hpp Hexagon.hpp
}

auto Hexagon::onMouseOver() -> void {
    Component::onMouseOver();
}

auto Hexagon::onMouseLeave() -> void {
    Component::onMouseLeave();
}

auto Hexagon::show() -> void {
    items.push_back(std::make_unique<Hexagon>(*this));
}

auto Hexagon::hide() -> void {
    auto hexagonExistenceIterator = std::find_if(
            items.begin(),
            items.end(),
            [this](std::unique_ptr<Component> const &hex) -> bool {
                return hex->getComponentId() == getComponentId();
            }
    );

    if (hexagonExistenceIterator != items.end())
        items.erase(hexagonExistenceIterator);
}

auto Hexagon::draw(sf::RenderWindow &window) -> void {
    window.draw(hexagon);
}

auto Hexagon::drawGreenBorder() -> void {
    hexagon.setOutlineColor(sf::Color::Green);
}

auto Hexagon::drawYellowBorder() -> void {
    hexagon.setOutlineColor(sf::Color::Yellow);
}

auto Hexagon::drawDefaultBorder() -> void {
    hexagon.setOutlineColor(Hexagon::defaultBorderColor);
}