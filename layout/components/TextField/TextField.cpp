#include "./TextField.hpp"

std::vector<std::unique_ptr<Component>> TextField::textFields;

TextField::TextField(sf::Vector2f const& size) : isActive(false), hasLimit(false), limit(0), activeColor(sf::Color::Green), defaultColor(sf::Color::White) {
    textFieldBase.setFillColor(sf::Color::White);
    textFieldBase.setFont(FontHolder::getFont(Fonts::ROBOTO_MEDIUM_FONT));
    textFieldBase.setCharacterSize(18);

    borderBase.setOutlineThickness(3);
    borderBase.setOutlineColor(defaultColor);
    borderBase.setFillColor(sf::Color(0 ,0, 0, 0));
    borderBase.setSize(size);
}

TextField::TextField(
        sf::Vector2f const &position,
        sf::Vector2f const &size,
        int fontSize
) : isActive(false), hasLimit(false), limit(0) {

    textFieldBase.setFillColor(sf::Color::White);
    textFieldBase.setFont(FontHolder::getFont(Fonts::ROBOTO_MEDIUM_FONT));
    textFieldBase.setCharacterSize(fontSize);

    borderBase.setOutlineThickness(3);
    borderBase.setOutlineColor(defaultColor);
    borderBase.setFillColor(sf::Color(0 ,0, 0, 0));
    borderBase.setSize(size);

    borderBase.setPosition(position);
    textFieldBase.setPosition({
        position.x + borderBase.getOutlineThickness() + 3,
        position.y + borderBase.getOutlineThickness() + 3
    });
}

TextField::TextField(TextField const &field) {
    textFieldBase = field.textFieldBase;
    content << field.content.str();
    isActive = field.isActive;
    hasLimit = field.hasLimit;
    limit = field.limit;
}

auto TextField::getPosition() const -> sf::Vector2f {
    return borderBase.getPosition();
}

auto TextField::getSize() const -> sf::Vector2f {
    return borderBase.getSize();
}

auto TextField::getColor() const -> sf::Color {
    return textFieldBase.getFillColor();
}

auto TextField::getBorderColor() const -> sf::Color {
    return borderBase.getOutlineColor();
}

auto TextField::getBorderWidth() const -> float {
    return borderBase.getOutlineThickness();
}

auto TextField::getFontSize() const -> int {
    return textFieldBase.getCharacterSize();
}

auto TextField::setPosition(const sf::Vector2f &position) -> void {
    borderBase.setPosition(position);
    textFieldBase.setPosition(
            {position.x + borderBase.getOutlineThickness() + 3, position.y + borderBase.getOutlineThickness() + 3});
}

auto TextField::setSize(const sf::Vector2f &size) -> void {
    borderBase.setSize(size);
}

auto TextField::setColor(const sf::Color &color) -> void {
    textFieldBase.setFillColor(color);
}

auto TextField::setBorderColor(const sf::Color &color) -> void {
    borderBase.setOutlineColor(color);
}

auto TextField::setBorderWidth(float borderWidth) -> void {
    borderBase.setOutlineThickness(borderWidth);
}

auto TextField::setFontSize(int fontSize) -> void {
    textFieldBase.setCharacterSize(fontSize);
}

auto TextField::show() -> void {
    textFields.push_back(std::make_unique<TextField>(*this));
}

auto TextField::hide() -> void {
    auto textFieldExistenceIterator = std::find_if(
            textFields.begin(),
            textFields.end(),
            [this](std::unique_ptr<Component> const &tf) -> bool {
                return tf->getComponentId() == getComponentId();
            }
    );

    if (textFieldExistenceIterator < textFields.end()) {
        textFields.erase(textFieldExistenceIterator);
    }
}

auto TextField::isMouseOver(const sf::Vector2i &mousePosition) const -> bool {
    return ComponentUtil::isMouseOver(
            borderBase.getPosition(),
            borderBase.getSize(),
            mousePosition
    );
}

auto TextField::draw(sf::RenderWindow &renderWindow) -> void {
    renderWindow.draw(borderBase);
    renderWindow.draw(textFieldBase);
}

auto TextField::getContent() const -> std::string {
    return content.str();
}

auto TextField::getIsActive() const -> bool {
    return isActive;
}

auto TextField::getHasLimit() const -> bool {
    return hasLimit;
}

auto TextField::getLimit() const -> int {
    return limit;
}

auto TextField::setFont(const Fonts &font) -> void {
    textFieldBase.setFont(FontHolder::getFont(font));
}

auto TextField::setLimit(bool limitState, int limitNum) -> void {
    hasLimit = limitState;
    limit = limitNum;
}

auto TextField::setIsActive(bool selectedState) -> void {
    isActive = selectedState;

    if (!isActive) {
        setBorderColor(defaultColor);
        textFieldBase.setString(content.str());
    } else setBorderColor(activeColor);
}

auto TextField::onCharEntered(sf::Event event) -> void {
    if (isActive) {
        int charTyped = event.text.unicode;

        if (
                charTyped == 46 ||
                charTyped == 95 ||
                (charTyped >= 49 && charTyped <= 57) ||
                (charTyped >= 97 && charTyped <= 122) ||
                (charTyped >= 65 && charTyped <= 90) ||
                (charTyped == 8)
                ) {
            if (hasLimit) {
                if (charTyped == 8 && !content.str().empty()) removeChar();
                else if (content.str().size() < limit) pushBackChar(charTyped);
            } else pushBackChar(charTyped);
        }

        if (hasLimit) {
            if (content.str().size() != limit) {
                textFieldBase.setString(content.str() + "_");
                setBorderColor(activeColor);
            }
            else {
                textFieldBase.setString(content.str());
                setBorderColor(sf::Color::Red);
            }
        } else textFieldBase.setString(content.str() + "_");
    }
}

auto TextField::resetContent() -> void {
    content.str("");
    textFieldBase.setString(content.str());
}

auto TextField::pushBackChar(int charTyped) -> void {
    if (charTyped != 8) content << static_cast<char>(charTyped);
    else if (!content.str().empty()) removeChar();

    textFieldBase.setString(content.str() + "_");
}

auto TextField::removeChar() -> void {
    auto tmp = content.str();
    tmp.pop_back();

    content.str("");
    content << tmp;

    textFieldBase.setString(content.str());
}
