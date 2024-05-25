#include "./CheckBox.hpp"

#include "fmt/format.h"

CheckBox::CheckBox(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &labelText)
        : isActive(false) {
    checkBoxBase.setPosition(position);
    checkBoxBase.setSize(size);

    actionContext = "Default Action Context";

    boxColorActive = sf::Color::White;
    boxBorderColorActive = sf::Color(237, 19, 186);
    boxColor = sf::Color(168, 168, 168);
    boxBorderColor = sf::Color::Black;

    checkBoxBase.setFillColor(boxColor);
    checkBoxBase.setOutlineColor(boxBorderColor);
    checkBoxBase.setOutlineThickness(4);

    label.setFontSize(35);
    label.setFont(Fonts::ROBOTO_REGULAR_FONT);
    label.setColor(sf::Color::White);

    label.setText(labelText);
    setLabelGap({100, -10});
}

auto CheckBox::getPosition() const -> sf::Vector2f {
    return checkBoxBase.getPosition();
}

auto CheckBox::getSize() const -> sf::Vector2f {
    return checkBoxBase.getSize();
}

auto CheckBox::setPosition(const sf::Vector2f &position) -> void {
    checkBoxBase.setPosition(position);
}

auto CheckBox::setSize(const sf::Vector2f &size) -> void {
    checkBoxBase.setSize(size);
}

auto CheckBox::isMouseOver(const sf::Vector2i &mousePosition) const -> bool {
    return ComponentUtil::isMouseOver(*this, mousePosition);
}

auto CheckBox::onClick() -> void {
    Component::onClick();
}

auto CheckBox::onMouseOver() -> void {
    Component::onMouseOver();
}

auto CheckBox::onMouseLeave() -> void {
    Component::onMouseLeave();
}

auto CheckBox::show() -> void {
    // no need to be implemented
}

auto CheckBox::hide() -> void {
    // no need to be implemented
}

auto CheckBox::draw(sf::RenderWindow &renderWindow) -> void {
    renderWindow.draw(checkBoxBase);
    label.show();
}

auto CheckBox::getLabel() const -> const TextWrapper& {
    return label;
}

auto CheckBox::getColor() const -> sf::Color {
    return checkBoxBase.getFillColor();
}

auto CheckBox::getBorderColor() const -> sf::Color {
    return checkBoxBase.getOutlineColor();
}

auto CheckBox::getBorderWidth() const -> float {
    return checkBoxBase.getOutlineThickness();
}

auto CheckBox::getColorActive() const -> sf::Color {
    return boxColorActive;
}

auto CheckBox::getBorderColorActive() const -> sf::Color {
    return boxBorderColorActive;
}

auto CheckBox::getLabelGap() const -> sf::Vector2f {
    auto boxPosition = getPosition();
    auto labelPosition = label.getPosition();
    return {boxPosition.x - labelPosition.x, boxPosition.y - labelPosition.y};
}

auto CheckBox::getLabelPosition() const -> sf::Vector2f {
    return label.getPosition();
}

auto CheckBox::getLabelSize() const -> sf::Vector2f {
    return label.getSize();
}

auto CheckBox::getLabelColor() const -> sf::Color {
    return label.getColor();
}

auto CheckBox::getLabelFontSize() const -> unsigned int {
    return label.getFontSize();
}

auto CheckBox::getActionContext() const -> const std::string & {
    return actionContext;
}

auto CheckBox::getIsActive() const -> bool {
    return isActive;
}

auto CheckBox::setColor(const sf::Color &color) -> void {
    boxColor = color;
    checkBoxBase.setFillColor(boxColor);
}

auto CheckBox::setBorderColor(const sf::Color &color) -> void {
    boxBorderColor = color;
    checkBoxBase.setOutlineColor(boxBorderColor);
}

auto CheckBox::setBorderWidth(float borderWidth) -> void {
    checkBoxBase.setOutlineThickness(borderWidth);
}

auto CheckBox::setColorActive(const sf::Color &color) -> void {
    boxColorActive = sf::Color(color);
}

auto CheckBox::setBorderColorActive(const sf::Color &color) -> void {
    boxBorderColorActive = color;
}

auto CheckBox::setLabelGap(const sf::Vector2f &gap) -> void {
    auto boxPosition = getPosition();
    label.setPosition({boxPosition.x + gap.x, boxPosition.y + gap.y});
}

auto CheckBox::setLabelColor(const sf::Color &color) -> void {
    label.setColor(color);
}

auto CheckBox::setLabelFontSize(unsigned int fontSize) -> void {
    label.setFontSize(fontSize);
}

auto CheckBox::setLabelFont(const Fonts &font) -> void {
    label.setFont(font);
}

auto CheckBox::setActionContext(const std::string &context) -> void {
    actionContext = context;
}

auto CheckBox::setIsActive(bool state) -> void {
    isActive = state;
}

auto CheckBox::on() -> void {
    checkBoxBase.setFillColor(boxColorActive);
    checkBoxBase.setOutlineColor(boxBorderColorActive);

    isActive = true;
}

auto CheckBox::off() -> void {
    checkBoxBase.setFillColor(boxColor);
    checkBoxBase.setOutlineColor(boxBorderColor);

    isActive = false;
}