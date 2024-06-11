#include "./TextField.hpp"

TextField::TextField(const sf::Vector2f &position, const sf::Vector2f &size) :
hasFocus(false),
backgroundColor(sf::Color::White),
borderColor(sf::Color(150,28,130)),
backgroundFocusColor(sf::Color(240,240,240)),
borderFocusColor(sf::Color(194,31,188))
{

    textFieldBase.setSize(size);
    textFieldBase.setPosition(position);
    textFieldBase.setFillColor(backgroundColor);
    textFieldBase.setOutlineColor(borderColor);
    textFieldBase.setOutlineThickness(3);

    content.setPosition({position.x + 10, position.y + 5});
    content.setFont(FontHolder::getFont(Fonts::ROBOTO_MEDIUM_FONT));
    content.setCharacterSize(20);
    content.setFillColor(sf::Color::Black);

}

std::vector<std::unique_ptr<Component>> TextField::textFields;

sf::Color TextField::getColor() const {
    return content.getFillColor();
}

auto TextField::getBackgroundColor() const -> sf::Color {
    return backgroundColor;
}

auto TextField::getFocusBackgroundColor() const -> sf::Color {
    return backgroundFocusColor;
}

auto TextField::getFocusBorderColor() const -> sf::Color {
    return borderFocusColor;
}

sf::Color TextField::getBorderColor() const {
    return textFieldBase.getOutlineColor();
}

auto TextField::getBorderWidth() const -> float {
    return textFieldBase.getOutlineThickness();
}

auto TextField::getFont() const -> sf::Font {
    return *content.getFont();
}

auto TextField::getFontSize() const -> int {
    return content.getCharacterSize();
}

auto TextField::setColor(const sf::Color &color) -> void {
    content.setFillColor(color);
}

auto TextField::setBackgroundColor(const sf::Color &color) -> void {
    backgroundColor = color;
    textFieldBase.setFillColor(backgroundColor);
}

auto TextField::setFocusBackgroundColor(const sf::Color &color) -> void {
    backgroundFocusColor = color;
}

auto TextField::setFocusBorderColor(const sf::Color &color) -> void {
    borderFocusColor = color;
}

auto TextField::setBorderColor(const sf::Color &color) -> void {
    borderColor = color;
    textFieldBase.setOutlineColor(color);
}

auto TextField::setBorderWidth(float borderWidth) -> void {
    textFieldBase.setOutlineThickness(borderWidth);
}

auto TextField::setFont(Fonts font) -> void {
    content.setFont(FontHolder::getFont(font));
}

auto TextField::setFontSize(int fontSize) -> void {
    content.setCharacterSize(fontSize);
}

auto TextField::getPosition() const -> sf::Vector2f{
    return textFieldBase.getPosition();
}

auto TextField::getSize() const -> sf::Vector2f{
    return textFieldBase.getSize();
}

auto TextField::setPosition(const sf::Vector2f &position) -> void {
    textFieldBase.setPosition(position);
    content.setPosition({position.x + 10, position.y + 5});
}

auto TextField::setSize(const sf::Vector2f &size) -> void {
    textFieldBase.setSize(size);
}

auto TextField::isMouseOver(const sf::Vector2i &mousePosition) const -> bool {
    return ComponentUtil::isMouseOver(getPosition(), getSize(), mousePosition);
}

auto TextField::onClick() -> void {
    focus();
    hasFocus = true;
}

auto TextField::show() -> void {
    textFields.push_back(std::make_unique<TextField>(*this));
}

auto TextField::hide() -> void {
    auto textFieldExistenceIterator = std::find_if(
            textFields.begin(),
            textFields.end(),
            [this](std::unique_ptr<Component> const &comp) -> bool {
                return comp->getComponentId() == getComponentId();
            }
    );

    if (textFieldExistenceIterator < textFields.end()) {
        textFields.erase(textFieldExistenceIterator);
    }
}

auto TextField::draw(sf::RenderWindow &renderWindow) -> void{
    renderWindow.draw(textFieldBase);
    renderWindow.draw(content);
}


auto TextField::getContent() const -> std::string {
    return content.getString();
}

auto TextField::getFocus() const -> bool {
    return hasFocus;
}

auto TextField::setContent(std::string const &data) -> void {
    content.setString(data);
}

auto TextField::setFocus(bool focusState) -> void {
    hasFocus = focusState;
}

auto TextField::addSymbol(char symbol) -> void {
    content.setString(content.getString() + symbol);
}

auto TextField::focus() -> void {
    textFieldBase.setFillColor(backgroundFocusColor);
    textFieldBase.setOutlineColor(borderFocusColor);
}

auto TextField::disableFocus(sf::Vector2i const& mousePosition) -> void {
    for (auto &comp : textFields) {
        auto field = dynamic_cast<TextField*>(comp.get());
        if (field->isMouseOver(mousePosition) && field->hasFocus) {
            fmt::println("works");
            field->hasFocus = false;
            field->setBackgroundColor(sf::Color::Black);
            field->setBorderColor(sf::Color::Green);
        }
    }
}