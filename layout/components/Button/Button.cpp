#include "./Button.hpp"

std::vector<std::unique_ptr<Component>> Button::buttons;

Button::Button(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &btnText) {
    buttonBase.setPosition(position);
    buttonBase.setSize(size);

    buttonText.setText(btnText);
    buttonText.setFontSize(20);
    buttonText.setColor(sf::Color::Black);
    buttonText.setFont(Fonts::ROBOTO_MEDIUM_FONT);
    buttonText.centerBothAxis(position, size);
}

auto Button::getPosition() const -> sf::Vector2f {
    return buttonBase.getPosition();
}

auto Button::getSize() const -> sf::Vector2f {
    return buttonBase.getSize();
}

auto Button::getColor() const -> sf::Color {
    return buttonBase.getFillColor();
}

auto Button::getBorderColor() const -> sf::Color {
    return buttonBase.getOutlineColor();
}

auto Button::getBorderWidth() const -> float {
    return buttonBase.getSize().x;
}

auto Button::setPosition(const sf::Vector2f &position) -> void {
    buttonBase.setPosition(position);
    buttonText.centerBothAxis(position, getSize());
}

auto Button::setSize(const sf::Vector2f &size) -> void {
    buttonBase.setSize(size);
}

auto Button::setColor(const sf::Color &color) -> void {
    innerColorCopy = color;
    buttonBase.setFillColor(color);
}

auto Button::setBorderColor(const sf::Color &color) -> void {
    innerBorderColorCopy = color;
    buttonBase.setOutlineColor(color);
}

auto Button::setBorderWidth(float borderWidth) -> void {
    buttonBase.setOutlineThickness(borderWidth);
}

auto Button::getHoverColor() const -> sf::Color {
    return hoverColor;
}

auto Button::getHoverBorderColor() const -> sf::Color {
    return hoverBorderColor;
}

auto Button::getButtonText() const -> const TextWrapper & {
    return buttonText;
}

auto Button::getButtonTextPosition() const -> sf::Vector2f {
    return buttonText.getPosition();
}

auto Button::getButtonTextSize() const -> sf::Vector2f {
    return buttonText.getSize();
}

auto Button::getButtonTextFont() const -> sf::Font {
    return buttonText.getFont();
}

auto Button::getButtonTextFontSize() const -> unsigned int {
    return buttonText.getFontSize();
}

auto Button::getButtonTextColor() const -> sf::Color {
    return buttonText.getColor();
}

auto Button::getButtonTextLetterSpacing() const -> float {
    return buttonText.getLetterSpacing();
}

auto Button::setHoverColor(const sf::Color &color) -> void {
    hoverColor = color;
}

auto Button::setHoverBorderColor(const sf::Color &color) -> void {
    hoverBorderColor = color;
}

auto Button::setButtonTextFont(const Fonts &font) -> void {
    buttonText.setFont(font);
}

auto Button::setButtonTextFontSize(unsigned int fontSize) -> void {
    buttonText.setFontSize(fontSize);
}

auto Button::setButtonTextColor(const sf::Color &color) -> void {
    buttonText.setColor(color);
}

auto Button::setButtonTextLetterSpacing(float letterSpacing) -> void {
    buttonText.setLetterSpacing(letterSpacing);
}

auto Button::bindOnClick(const std::function<void()> &onButtonClickHandler) -> void {
    clickHandler = onButtonClickHandler;
}

auto Button::onClick() -> void {
    if (clickHandler) clickHandler();
    else Component::onClick();
}

auto Button::onMouseOver() -> void {
    if (Cursor::getCurrentHolder() == CursorHolder::BUTTON || Cursor::getCurrentHolder() == CursorHolder::NO_ONE) {
        Cursor::setCurrentHolder(CursorHolder::BUTTON);
        Cursor::setHandCursor();
    }
    hover();
}

auto Button::onMouseLeave() -> void {
    if (Cursor::getCurrentHolder() == CursorHolder::BUTTON) {
        Cursor::setCurrentHolder(CursorHolder::NO_ONE);
        Cursor::setSimpleCursor();
    }
    unhover();
}

auto Button::isMouseOver(const sf::Vector2i &mousePosition) const -> bool {
    return ComponentUtil::isMouseOver(*this, mousePosition);
}

auto Button::show() -> void {
    buttons.push_back(std::make_unique<Button>(*this));
    buttonText.show();
}

auto Button::hide() -> void {
    auto buttonExistenceIterator = std::find_if(
            buttons.begin(),
            buttons.end(),
            [this](std::unique_ptr<Component> const &button) -> bool {
                return button.get() == this;
            }
    );

    if (buttonExistenceIterator != buttons.end())
        buttons.erase(buttonExistenceIterator);
}

auto Button::draw(sf::RenderWindow &renderWindow) -> void {
    renderWindow.draw(buttonBase);
//    buttonText.draw(renderWindow);
}

auto Button::hover() -> void {
    buttonBase.setFillColor(hoverColor);
    buttonBase.setOutlineColor(hoverBorderColor);
}

auto Button::unhover() -> void {
    buttonBase.setFillColor(innerColorCopy);
    buttonBase.setOutlineColor(innerBorderColorCopy);
}