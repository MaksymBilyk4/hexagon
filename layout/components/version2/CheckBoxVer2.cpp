#include "./CheckBoxVer2.hpp"

#include <fmt/format.h>

CheckBoxVer2::CheckBoxVer2(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &labelText)
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

auto CheckBoxVer2::getPosition() const -> sf::Vector2f {
    return checkBoxBase.getPosition();
}

auto CheckBoxVer2::getSize() const -> sf::Vector2f {
    return checkBoxBase.getSize();
}

auto CheckBoxVer2::setPosition(const sf::Vector2f &position) -> void {
    checkBoxBase.setPosition(position);
}

auto CheckBoxVer2::setSize(const sf::Vector2f &size) -> void {
    checkBoxBase.setSize(size);
}

auto CheckBoxVer2::isMouseOver(const sf::Vector2i &mousePosition) const -> bool {
    return ComponentUtil::isMouseOver(*this, mousePosition);
}

auto CheckBoxVer2::onClick() -> void {
    Component::onClick();
}

auto CheckBoxVer2::onMouseOver() -> void {
    Component::onMouseOver();
}

auto CheckBoxVer2::onMouseLeave() -> void {
    Component::onMouseLeave();
}

auto CheckBoxVer2::show() -> void {
    // no need to be implemented
}

auto CheckBoxVer2::hide() -> void {
    // no need to be implemented
}

auto CheckBoxVer2::draw(sf::RenderWindow &renderWindow) -> void {
    renderWindow.draw(checkBoxBase);
    label.show();
}

auto CheckBoxVer2::getLabel() const -> const TextWrapperVer2& {
    return label;
}

auto CheckBoxVer2::getColor() const -> sf::Color {
    return checkBoxBase.getFillColor();
}

auto CheckBoxVer2::getBorderColor() const -> sf::Color {
    return checkBoxBase.getOutlineColor();
}

auto CheckBoxVer2::getBorderWidth() const -> float {
    return checkBoxBase.getOutlineThickness();
}

auto CheckBoxVer2::getColorActive() const -> sf::Color {
    return boxColorActive;
}

auto CheckBoxVer2::getBorderColorActive() const -> sf::Color {
    return boxBorderColorActive;
}

auto CheckBoxVer2::getLabelGap() const -> sf::Vector2f {
    auto boxPosition = getPosition();
    auto labelPosition = label.getPosition();
    return {boxPosition.x - labelPosition.x, boxPosition.y - labelPosition.y};
}

auto CheckBoxVer2::getLabelPosition() const -> sf::Vector2f {
    return label.getPosition();
}

auto CheckBoxVer2::getLabelSize() const -> sf::Vector2f {
    return label.getSize();
}

auto CheckBoxVer2::getLabelColor() const -> sf::Color {
    return label.getColor();
}

auto CheckBoxVer2::getLabelFontSize() const -> unsigned int {
    return label.getFontSize();
}

auto CheckBoxVer2::getActionContext() const -> const std::string & {
    return actionContext;
}

auto CheckBoxVer2::getIsActive() const -> bool {
    return isActive;
}

auto CheckBoxVer2::setColor(const sf::Color &color) -> void {
    boxColor = color;
    checkBoxBase.setFillColor(boxColor);
}

auto CheckBoxVer2::setBorderColor(const sf::Color &color) -> void {
    boxBorderColor = color;
    checkBoxBase.setOutlineColor(boxBorderColor);
}

auto CheckBoxVer2::setBorderWidth(float borderWidth) -> void {
    checkBoxBase.setOutlineThickness(borderWidth);
}

auto CheckBoxVer2::setColorActive(const sf::Color &color) -> void {
    boxColorActive = sf::Color(color);
}

auto CheckBoxVer2::setBorderColorActive(const sf::Color &color) -> void {
    boxBorderColorActive = color;
}

auto CheckBoxVer2::setLabelGap(const sf::Vector2f &gap) -> void {
    auto boxPosition = getPosition();
    label.setPosition({boxPosition.x + gap.x, boxPosition.y + gap.y});
}

auto CheckBoxVer2::setLabelColor(const sf::Color &color) -> void {
    label.setColor(color);
}

auto CheckBoxVer2::setLabelFontSize(unsigned int fontSize) -> void {
    label.setFontSize(fontSize);
}

auto CheckBoxVer2::setLabelFont(const Fonts &font) -> void {
    label.setFont(font);
}

auto CheckBoxVer2::setActionContext(const std::string &context) -> void {
    actionContext = context;
}

auto CheckBoxVer2::setIsActive(bool state) -> void {
    isActive = state;
}

auto CheckBoxVer2::on() -> void {
    checkBoxBase.setFillColor(boxColorActive);
    checkBoxBase.setOutlineColor(boxBorderColorActive);

    isActive = true;
}

auto CheckBoxVer2::off() -> void {
    checkBoxBase.setFillColor(boxColor);
    checkBoxBase.setOutlineColor(boxBorderColor);

    isActive = false;
}