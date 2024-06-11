#pragma once

#include "SFML/Graphics.hpp"

#include <vector>
#include <string>
#include <functional>
#include <memory>
#include <string>
#include <algorithm>

#include "../../../utils/ComponentUtil.hpp"
#include "../Box.hpp"
#include "../TextWrapper/TextWrapper.hpp"
#include "../../../utils/cursor/Cursor.hpp"

struct Button : Box {

    Button(sf::Vector2f const& position, sf::Vector2f const& size, std::string const& btnText);

    ~Button() override = default;

    auto getPosition() const -> sf::Vector2f override;

    auto getSize() const -> sf::Vector2f override;

    auto getColor() const -> sf::Color override;

    auto getBorderColor() const -> sf::Color override;

    auto getBorderWidth() const -> float override;

    auto setPosition(const sf::Vector2f& position) -> void override;

    auto setSize(const sf::Vector2f& size) -> void override;

    auto setColor(sf::Color const& color) -> void override;

    auto setBorderColor(sf::Color const& color) -> void override;

    auto setBorderWidth(float borderWidth) -> void override;

    auto getHoverColor() const -> sf::Color;

    auto getHoverBorderColor() const -> sf::Color;

    auto getButtonText() const -> const TextWrapper&;

    auto getButtonTextPosition() const -> sf::Vector2f;

    auto getButtonTextSize() const -> sf::Vector2f;

    auto getButtonTextFont() const -> sf::Font;

    auto getButtonTextFontSize() const -> unsigned int;

    auto getButtonTextColor() const -> sf::Color;

    auto getButtonTextLetterSpacing() const -> float;

    auto setHoverColor(sf::Color const& color) -> void;

    auto setHoverBorderColor(sf::Color const& color) -> void;

    auto setButtonTextFont(Fonts const& font) -> void;

    auto setButtonTextPosition(sf::Vector2f const& position) -> void;

    auto setButtonTextFontSize(unsigned int fontSize) -> void;

    auto setButtonTextColor(sf::Color const& color) -> void;

    auto setButtonTextLetterSpacing(float letterSpacing) -> void;

    auto bindOnClick(std::function<void()> const &onButtonClickHandler) -> void;

    auto onClick() -> void override;

    auto onMouseOver() -> void override;

    auto onMouseLeave() -> void override;

    auto isMouseOver(const sf::Vector2i &mousePosition) const -> bool override;

    auto show() -> void override;

    auto hide() -> void override;

    auto draw(sf::RenderWindow &renderWindow) -> void override;

    auto hover() -> void;

    auto unhover() -> void;

    static std::vector<std::unique_ptr<Component>> buttons;

private:

    std::function<void()> clickHandler;

    sf::RectangleShape buttonBase;
    TextWrapper buttonText;

    sf::Color hoverColor;
    sf::Color hoverBorderColor;

    sf::Color innerColorCopy;
    sf::Color innerBorderColorCopy;
};