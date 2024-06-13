#include "./CountBar.hpp"

CountBar::CountBar(sf::Vector2f const& position, sf::Color const& barColor, int initCountedNumbers) : countedItems(initCountedNumbers), barColor(barColor) {
    barBase.setPosition(position);
    barBase.setSize({20, 50});
    barBase.setFillColor(barColor);

    barText.setText(std::to_string(countedItems));
    barText.setColor(sf::Color::White);
    barText.setPosition({position.x + 25, position.y + 5});
    barText.setFontSize(30);
}

auto CountBar::getColor() const -> sf::Color {
    return barColor;
}

auto CountBar::getBorderColor() const -> sf::Color {
    return barBase.getOutlineColor();
}

auto CountBar::getBorderWidth() const -> float {
    return barBase.getOutlineThickness();
}

auto CountBar::setColor(const sf::Color &color) -> void {
    barColor = color;
    barBase.setFillColor(barColor);
}

auto CountBar::setBorderColor(const sf::Color &color) -> void {
    barBase.setOutlineColor(color);
}

auto CountBar::setBorderWidth(float borderWidth) -> void {
    barBase.setOutlineThickness(borderWidth);
}

auto CountBar::getPosition() const -> sf::Vector2f {
    return barBase.getPosition();
}

auto CountBar::getSize() const -> sf::Vector2f {
    return barBase.getSize();
}

auto CountBar::setPosition(const sf::Vector2f &position) -> void {
    barBase.setPosition(position);
    barText.setPosition({position.x + 5, position.y + 5});
}

auto CountBar::setSize(const sf::Vector2f &size) -> void {
    barBase.setSize(size);
}

auto CountBar::isMouseOver(const sf::Vector2i &mousePosition) const -> bool {
    return ComponentUtil::isMouseOver(barBase.getPosition(), barBase.getSize(), mousePosition);
}

auto CountBar::onClick() -> void {
    Component::onClick();
}

auto CountBar::onMouseOver() -> void {
    Component::onMouseOver();
}

auto CountBar::onMouseLeave() -> void {
    Component::onMouseLeave();
}

auto CountBar::show() -> void {}
auto CountBar::hide() -> void {}

auto CountBar::draw(sf::RenderWindow &renderWindow) -> void {
    renderWindow.draw(barBase);
    barText.draw(renderWindow);
}

auto CountBar::getCountedItems() const -> int {
    return countedItems;
}

auto CountBar::setCountedItems(int items) -> void {
    countedItems = items;
    barText.setText(std::to_string(countedItems));
}

auto CountBar::increaseCounter(int number) -> void {
    countedItems += number;
    barText.setText(std::to_string(countedItems));
}

auto CountBar::decreaseCounter(int number) -> void {
    countedItems -= number;
    barText.setText(std::to_string(countedItems));
}