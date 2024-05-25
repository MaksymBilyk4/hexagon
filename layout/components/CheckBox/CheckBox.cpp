#include "CheckBox.hpp"
#include "../../../utils/ComponentUtil.hpp"

CheckBox::CheckBox(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &labelText) : isActive(
        false) {
    checkBoxBase.setPosition(position);
    checkBoxBase.setSize(size);

    initBaseProperties();

    label.setPosition({position.x + 100, position.y - 10});
    label.setText(labelText);
}

auto CheckBox::getSize() const -> sf::Vector2f {
    return checkBoxBase.getSize();
}

auto CheckBox::getPosition() const -> sf::Vector2f {
    return checkBoxBase.getPosition();
}

auto CheckBox::getLabel() const -> const TextWrapper & {
    return label;
}

auto CheckBox::setBoxInnerColor(const sf::Color &color) -> void {
    boxInnerColor = color;
    checkBoxBase.setFillColor(color);
}

auto CheckBox::setPosition(const sf::Vector2f &position) -> void {
    checkBoxBase.setPosition(position);
    label.setPosition({position.x + 100, position.y});
}

auto CheckBox::setBoxBorderColor(const sf::Color &color) -> void {
    boxBorderColor = color;
    checkBoxBase.setOutlineColor(color);
}

auto CheckBox::setBorderWidth(float width) -> void {
    checkBoxBase.setOutlineThickness(width);
}

auto CheckBox::setBoxInnerColorActive(const sf::Color &color) -> void {
    boxInnerColorActive = color;
}

auto CheckBox::setBoxBorderColorActive(sf::Color const &color) -> void {
    boxBorderColorActive = color;
}

auto CheckBox::setLabelText(const std::string &labelText) -> void {
    label.setText(labelText);
}

auto CheckBox::setLabelTextColor(const sf::Color &color) -> void {
    label.setColor(color);
}

auto CheckBox::setLabelTextFontSize(int fontSize) -> void {
    label.setFontSize(fontSize);
}

auto CheckBox::setLabelFont(Fonts const &font) -> void {
    label.setFont(font);
}

auto CheckBox::setActiveContext(const std::string &context) -> void {
    activeContextAction = context;
}

auto CheckBox::isMouseOver(const sf::Vector2i &mousePos) -> bool {
    return ComponentUtil::isMouseOver(checkBoxBase.getPosition(), checkBoxBase.getSize(), mousePos);
}

auto CheckBox::on() -> void {
    checkBoxBase.setOutlineColor(boxBorderColorActive);
    checkBoxBase.setFillColor(boxInnerColorActive);

    isActive = true;
}

auto CheckBox::off() -> void {
    checkBoxBase.setOutlineColor(boxBorderColor);
    checkBoxBase.setFillColor(boxInnerColor);

    isActive = false;
}

auto CheckBox::draw(sf::RenderWindow &renderWindow) -> void {
    renderWindow.draw(checkBoxBase);
    label.show();
}

auto CheckBox::getIsActive() const -> bool {
    return isActive;
}

auto CheckBox::getActiveContextAction() const -> const std::string & {
    return activeContextAction;
}


auto CheckBox::initBaseProperties() -> void {

    boxInnerColorActive = sf::Color::White;
    boxBorderColorActive = sf::Color(237, 19, 186);
    boxInnerColor = sf::Color(168, 168, 168);
    boxBorderColor = sf::Color::Black;

    checkBoxBase.setFillColor(boxInnerColor);
    checkBoxBase.setOutlineColor(boxBorderColor);
    checkBoxBase.setOutlineThickness(4);

    label.setFontSize(35);
    label.setFont(Fonts::ROBOTO_REGULAR_FONT);
    label.setColor(sf::Color::White);
}