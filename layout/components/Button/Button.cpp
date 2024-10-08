#include "./Button.hpp"

std::vector<std::unique_ptr<Component>> Button::buttons;

Button::Button(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &btnText) {
    buttonBase.setPosition(position);
    buttonBase.setSize(size);

    buttonBase.setOutlineThickness(3);

    innerColorCopy = sf::Color(190, 190, 190);
    buttonBase.setFillColor(innerColorCopy);

    innerBorderColorCopy = sf::Color(194, 31, 188);
    buttonBase.setOutlineColor(innerBorderColorCopy);

    hoverColor = sf::Color(255, 255, 255);
    hoverBorderColor = sf::Color(194, 31, 188);

    buttonText.setText(btnText);
    buttonText.setFontSize(20);
    buttonText.setColor(sf::Color::Black);
    buttonText.setFont(Fonts::ROBOTO_MEDIUM_FONT);
    buttonText.centerBothAxis(position, size);

    clickHandler = [this]() -> void { fmt::println("Button on click. Component: {}", getComponentId()); };
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

auto Button::getText() const -> std::string {
    return buttonText.getText();
}

auto Button::getIsCursorOver() const -> bool {
    return isCursorOver;
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

auto Button::setButtonTextPosition(const sf::Vector2f &position) -> void {
    buttonText.setPosition(position);
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

auto Button::setText(const std::string &text) -> void {
    buttonText.setText(text);
}

auto Button::setIsCursorOver(bool state) -> void {
    isCursorOver = state;
}

auto Button::bindOnClick(const std::function<void()> &onButtonClickHandler) -> void {
    clickHandler = onButtonClickHandler;
}

auto Button::onClick() -> void {
    if (clickHandler != nullptr) clickHandler();
    else Component::onClick();
}

auto Button::onMouseOver() -> void {
    isCursorOver = true;
    if (Cursor::getCurrentHolder() == CursorHolder::NO_ONE || Cursor::getCurrentHolder() == CursorHolder::BUTTON) {
        Cursor::setCurrentHolder(CursorHolder::BUTTON);
        Cursor::setHandCursor();
        hover();
    }
}

auto Button::onMouseLeave() -> void {
    if (isCursorOver) {
        if (Cursor::getCurrentHolder() == CursorHolder::BUTTON) {
            Cursor::setCurrentHolder(CursorHolder::NO_ONE);
            Cursor::setSimpleCursor();
        }
        isCursorOver = false;
        unhover();
    }
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
                return button->getComponentId() == getComponentId();
            }
    );


    if (buttonExistenceIterator < buttons.end()) {
        if (Cursor::getCurrentHolder() == CursorHolder::BUTTON) {
            Cursor::setCurrentHolder(CursorHolder::NO_ONE);
            Cursor::setSimpleCursor();
        }

        buttonText.hide();
        buttons.erase(buttonExistenceIterator);
    }
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