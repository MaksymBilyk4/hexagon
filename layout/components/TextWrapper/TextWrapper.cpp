#include "./TextWrapper.hpp"

std::vector<std::unique_ptr<Component>>TextWrapper::textWrappers;

TextWrapper::TextWrapper() {
    text.setPosition({0, 0});
    text.setString("Text");
    initDefaultProperties();
}

TextWrapper::TextWrapper(const sf::Vector2f &position, const std::string &txt) {
    text.setPosition(position);
    text.setString(txt);
    initDefaultProperties();
}

auto TextWrapper::getPosition() const -> sf::Vector2f {
    return text.getPosition();
}

auto TextWrapper::getSize() const -> sf::Vector2f {
    return text.getGlobalBounds().getSize();
}

auto TextWrapper::setPosition(const sf::Vector2f &position) -> void {
    text.setPosition(position);
}

auto TextWrapper::setSize(const sf::Vector2f &size) -> void {
    // no implementation for this component
}

auto TextWrapper::getFont() const -> sf::Font {
    return *text.getFont();
}

auto TextWrapper::getFontSize() const -> unsigned int {
    return text.getCharacterSize();
}

auto TextWrapper::getColor() const -> sf::Color {
    return text.getFillColor();
}

auto TextWrapper::getText() const -> std::string {
    return text.getString();
}

auto TextWrapper::getLetterSpacing() const -> float {
    return text.getLetterSpacing();
}

auto TextWrapper::setFont(const Fonts &font) -> void {
    text.setFont(FontHolder::getFont(font));
}

auto TextWrapper::setFontSize(unsigned int fontSize) -> void {
    text.setCharacterSize(fontSize);
}

auto TextWrapper::setColor(const sf::Color &color) -> void {
    text.setFillColor(color);
}

auto TextWrapper::setText(const std::string &txt) -> void {
    text.setString(txt);
}

auto TextWrapper::setLetterSpacing(float letterSpacing) -> void {
    text.setLetterSpacing(letterSpacing);
}

auto TextWrapper::centerBothAxis(sf::Vector2f const& parentPosition, sf::Vector2f const& parentSize) -> void {
    text.setPosition({
        parentPosition.x + (parentSize.x / 2) - text.getGlobalBounds().width / 2,
        parentPosition.y + (parentSize.y / 3) - text.getGlobalBounds().height / 2,
    });
}

auto TextWrapper::centerHorizontalAxis(float parentXPosition, float parentWidth, float positionY) -> void {
    text.setPosition({
        parentXPosition + (parentWidth / 2) - (text.getGlobalBounds().width / 2),
        positionY
    });
}

auto TextWrapper::bindOnClick(const std::function<void()> &onTextClickHandler) -> void {
    clickHandler = onTextClickHandler;
}

auto TextWrapper::onClick() -> void {
    if (clickHandler) clickHandler();
    else Component::onClick();
}

auto TextWrapper::isMouseOver(const sf::Vector2i &mousePosition) const -> bool {
    return ComponentUtil::isMouseOver(*this, mousePosition);
}

auto TextWrapper::show() -> void {
    textWrappers.push_back(std::make_unique<TextWrapper>(*this));
}

auto TextWrapper::hide() -> void {
    auto textWrapperExistenceIterator = std::find_if(
            textWrappers.begin(),
            textWrappers.end(),
            [this](std::unique_ptr<Component> const &textWrapper) -> bool {
                return textWrapper->getComponentId() == getComponentId();
            }
    );

    if (textWrapperExistenceIterator != textWrappers.end())
        textWrappers.erase(textWrapperExistenceIterator);
}

auto TextWrapper::draw(sf::RenderWindow &renderWindow) -> void {
    renderWindow.draw(text);
}


auto TextWrapper::initDefaultProperties() -> void {
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(20);
    text.setFont(FontHolder::getFont(Fonts::ROBOTO_REGULAR_FONT));
}