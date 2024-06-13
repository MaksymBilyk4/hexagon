#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>

#include "../Box.hpp"
#include "../../../util/component/ComponentUtil.hpp"
#include "../../../util/font/Fonts.hpp"
#include "../../../util/font/FontHolder.hpp"


struct TextField : Box {

    TextField(sf::Vector2f const& position, sf::Vector2f const& size);

    auto getColor() const -> sf::Color override;

    auto getBackgroundColor() const -> sf::Color;

    auto getFocusBackgroundColor() const -> sf::Color;

    auto getFocusBorderColor() const -> sf::Color;

    auto getBorderColor() const -> sf::Color override;

    auto getBorderWidth() const -> float override;

    auto getFont() const -> sf::Font;

    auto getFontSize() const -> int;

    auto setColor(const sf::Color &color) -> void override;

    auto setBackgroundColor(sf::Color const& color) -> void;

    auto setFocusBackgroundColor(sf::Color const& color) -> void;

    auto setFocusBorderColor(sf::Color const& color) -> void;

    auto setBorderColor(const sf::Color &color) -> void override;

    auto setBorderWidth(float borderWidth) -> void override;

    auto setFont(Fonts font) -> void;

    auto setFontSize(int fontSize) -> void;

    auto getPosition() const -> sf::Vector2f override;

    auto getSize() const -> sf::Vector2f override;

    auto setPosition(const sf::Vector2f &position) -> void override;

    auto setSize(const sf::Vector2f &size) -> void override;

    auto isMouseOver(const sf::Vector2i &mousePosition) const -> bool override;

    auto onClick() -> void override;

    auto show() -> void override;

    auto hide() -> void override;

    auto draw(sf::RenderWindow &renderWindow) -> void override;

    auto getContent() const -> std::string;

    auto getFocus() const -> bool;

    auto setContent(std::string const& data) -> void;

    auto setFocus(bool focusState) -> void;

    auto addSymbol(char symbol) -> void;

    auto focus() -> void;

    static auto disableFocus(sf::Vector2i const& mousePosition) -> void;

    static std::vector<std::unique_ptr<Component>> textFields;

private:
    sf::Text content;
    sf::RectangleShape textFieldBase;
    bool hasFocus;

    sf::Color backgroundColor;
    sf::Color borderColor;

    sf::Color backgroundFocusColor;
    sf::Color borderFocusColor;
};