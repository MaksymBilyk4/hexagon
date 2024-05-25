#include "./TextWrapperVer2.hpp"

std::vector<std::unique_ptr<Component>>TextWrapperVer2::textWrappers;

TextWrapperVer2::TextWrapperVer2() {
    text.setPosition({0, 0});
    text.setString("Text");
    initDefaultProperties();
}

TextWrapperVer2::TextWrapperVer2(const sf::Vector2f &position, const std::string &txt) {
    text.setPosition(position);
    text.setString(txt);
    initDefaultProperties();
}

auto TextWrapperVer2::getPosition() const -> sf::Vector2f {
    return text.getPosition();
}

auto TextWrapperVer2::getSize() const -> sf::Vector2f {
    return text.getGlobalBounds().getSize();
}

auto TextWrapperVer2::setPosition(const sf::Vector2f &position) -> void {
    text.setPosition(position);
}

auto TextWrapperVer2::setSize(const sf::Vector2f &size) -> void {
    // no implementation for this component
}

auto TextWrapperVer2::getFont() const -> sf::Font {
    return *text.getFont();
}

auto TextWrapperVer2::getFontSize() const -> unsigned int {
    return text.getCharacterSize();
}

auto TextWrapperVer2::getColor() const -> sf::Color {
    return text.getFillColor();
}

auto TextWrapperVer2::getText() const -> std::string {
    return text.getString();
}

auto TextWrapperVer2::getLetterSpacing() const -> float {
    return text.getLetterSpacing();
}

auto TextWrapperVer2::setFont(const Fonts &font) -> void {
    text.setFont(FontHolder::getFont(font));
}

auto TextWrapperVer2::setFontSize(unsigned int fontSize) -> void {
    text.setCharacterSize(fontSize);
}

auto TextWrapperVer2::setColor(const sf::Color &color) -> void {
    text.setFillColor(color);
}

auto TextWrapperVer2::setText(const std::string &txt) -> void {
    text.setString(txt);
}

auto TextWrapperVer2::setLetterSpacing(float letterSpacing) -> void {
    text.setLetterSpacing(letterSpacing);
}

auto TextWrapperVer2::centerBothAxis(sf::Vector2f const& parentPosition, sf::Vector2f const& parentSize) -> void {
    text.setPosition({
        parentPosition.x + (parentSize.x / 2) - text.getGlobalBounds().width / 2,
        parentPosition.y + (parentSize.y / 3) - text.getGlobalBounds().height / 2,
    });
}

auto TextWrapperVer2::centerHorizontalAxis(float parentXPosition, float parentWidth, float positionY) -> void {
    text.setPosition({
        parentXPosition + (parentWidth / 2) - (text.getGlobalBounds().width / 2),
        positionY
    });
}

auto TextWrapperVer2::bindOnClick(const std::function<void()> &onTextClickHandler) -> void {
    clickHandler = onTextClickHandler;
}

auto TextWrapperVer2::onClick() -> void {
    if (clickHandler) clickHandler();
    else Component::onClick();
}

auto TextWrapperVer2::isMouseOver(const sf::Vector2i &mousePosition) const -> bool {
    return ComponentUtil::isMouseOver(*this, mousePosition);
}

auto TextWrapperVer2::show() -> void {
    textWrappers.push_back(std::make_unique<TextWrapperVer2>(*this));
}

auto TextWrapperVer2::hide() -> void {
    auto textWrapperExistenceIterator = std::find_if(
            textWrappers.begin(),
            textWrappers.end(),
            [this](std::unique_ptr<Component> const &textWrapper) -> bool {
                return textWrapper.get() == this;
            }
    );

    if (textWrapperExistenceIterator != textWrappers.end())
        textWrappers.erase(textWrapperExistenceIterator);
}

auto TextWrapperVer2::draw(sf::RenderWindow &renderWindow) -> void {
    renderWindow.draw(text);
}


auto TextWrapperVer2::initDefaultProperties() -> void {
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(20);
    text.setFont(FontHolder::getFont(Fonts::ROBOTO_REGULAR_FONT));
}