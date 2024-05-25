#include "./ButtonVer2.hpp"

std::vector<std::unique_ptr<Component>> ButtonVer2::buttons;

ButtonVer2::ButtonVer2(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &btnText) {
    buttonBase.setPosition(position);
    buttonBase.setSize(size);

    buttonText.setText(btnText);
    buttonText.setFontSize(20);
    buttonText.setColor(sf::Color::Black);
    buttonText.setFont(Fonts::ROBOTO_MEDIUM_FONT);
    buttonText.centerBothAxis(position, size);
}

auto ButtonVer2::getPosition() const -> sf::Vector2f {
    return buttonBase.getPosition();
}

auto ButtonVer2::getSize() const -> sf::Vector2f {
    return buttonBase.getSize();
}

auto ButtonVer2::getColor() const -> sf::Color {
    return buttonBase.getFillColor();
}

auto ButtonVer2::getBorderColor() const -> sf::Color {
    return buttonBase.getOutlineColor();
}

auto ButtonVer2::getBorderWidth() const -> float {
    return buttonBase.getSize().x;
}

auto ButtonVer2::setPosition(const sf::Vector2f &position) -> void {
    buttonBase.setPosition(position);
    buttonText.centerBothAxis(position, getSize());
}

auto ButtonVer2::setSize(const sf::Vector2f &size) -> void {
    buttonBase.setSize(size);
}

auto ButtonVer2::setColor(const sf::Color &color) -> void {
    innerColorCopy = color;
    buttonBase.setFillColor(color);
}

auto ButtonVer2::setBorderColor(const sf::Color &color) -> void {
    innerBorderColorCopy = color;
    buttonBase.setOutlineColor(color);
}

auto ButtonVer2::setBorderWidth(float borderWidth) -> void {
    buttonBase.setOutlineThickness(borderWidth);
}

auto ButtonVer2::getHoverColor() const -> sf::Color {
    return hoverColor;
}

auto ButtonVer2::getHoverBorderColor() const -> sf::Color {
    return hoverBorderColor;
}

auto ButtonVer2::getButtonText() const -> const TextWrapperVer2 & {
    return buttonText;
}

auto ButtonVer2::getButtonTextPosition() const -> sf::Vector2f {
    return buttonText.getPosition();
}

auto ButtonVer2::getButtonTextSize() const -> sf::Vector2f {
    return buttonText.getSize();
}

auto ButtonVer2::getButtonTextFont() const -> sf::Font {
    return buttonText.getFont();
}

auto ButtonVer2::getButtonTextFontSize() const -> unsigned int {
    return buttonText.getFontSize();
}

auto ButtonVer2::getButtonTextColor() const -> sf::Color {
    return buttonText.getColor();
}

auto ButtonVer2::getButtonTextLetterSpacing() const -> float {
    return buttonText.getLetterSpacing();
}

auto ButtonVer2::setHoverColor(const sf::Color &color) -> void {
    hoverColor = color;
}

auto ButtonVer2::setHoverBorderColor(const sf::Color &color) -> void {
    hoverBorderColor = color;
}

auto ButtonVer2::setButtonTextFont(const Fonts &font) -> void {
    buttonText.setFont(font);
}

auto ButtonVer2::setButtonTextFontSize(unsigned int fontSize) -> void {
    buttonText.setFontSize(fontSize);
}

auto ButtonVer2::setButtonTextColor(const sf::Color &color) -> void {
    buttonText.setColor(color);
}

auto ButtonVer2::setButtonTextLetterSpacing(float letterSpacing) -> void {
    buttonText.setLetterSpacing(letterSpacing);
}

auto ButtonVer2::bindOnClick(const std::function<void()> &onButtonClickHandler) -> void {
    clickHandler = onButtonClickHandler;
}

auto ButtonVer2::onClick() -> void {
    if (clickHandler) clickHandler();
    else Component::onClick();
}

auto ButtonVer2::onMouseOver() -> void {
    if (CursorHolder::getCurrentHolder() == CurrentHolder::BUTTON || CursorHolder::getCurrentHolder() == CurrentHolder::NO_ONE) {
        CursorHolder::setCurrentHolder(CurrentHolder::BUTTON);
        CursorHolder::setHandCursor();
    }
    hover();
}

auto ButtonVer2::onMouseLeave() -> void {
    if (CursorHolder::getCurrentHolder() == CurrentHolder::BUTTON) {
        CursorHolder::setCurrentHolder(CurrentHolder::NO_ONE);
        CursorHolder::setSimpleCursor();
    }
    unhover();
}

auto ButtonVer2::isMouseOver(const sf::Vector2i &mousePosition) const -> bool {
    return ComponentUtil::isMouseOver(*this, mousePosition);
}

auto ButtonVer2::show() -> void {
    buttons.push_back(std::make_unique<ButtonVer2>(*this));
    buttonText.show();
}

auto ButtonVer2::hide() -> void {
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

auto ButtonVer2::draw(sf::RenderWindow &renderWindow) -> void {
    renderWindow.draw(buttonBase);
//    buttonText.draw(renderWindow);
}

auto ButtonVer2::hover() -> void {
    buttonBase.setFillColor(hoverColor);
    buttonBase.setOutlineColor(hoverBorderColor);
}

auto ButtonVer2::unhover() -> void {
    buttonBase.setFillColor(innerColorCopy);
    buttonBase.setOutlineColor(innerBorderColorCopy);
}