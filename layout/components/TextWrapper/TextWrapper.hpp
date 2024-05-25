#pragma once

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include "../Component.hpp"
#include "../../../utils/ComponentUtil.hpp"
#include "../../../utils/font/FontHolder.hpp"
#include "../../../utils/font/Fonts.hpp"

struct TextWrapper : Component {

    TextWrapper();

    TextWrapper(sf::Vector2f const &position, std::string const &txt);

    ~TextWrapper() override = default;

    auto getPosition() const -> sf::Vector2f override;

    auto getSize() const -> sf::Vector2f override;

    auto setPosition(sf::Vector2f const &position) -> void override;

    auto setSize(sf::Vector2f const &size) -> void override;

    auto getFont() const -> sf::Font;

    auto getFontSize() const -> unsigned int;

    auto getColor() const -> sf::Color;

    auto getText() const -> std::string;

    auto getLetterSpacing() const -> float;

    auto setFont(Fonts const &font) -> void;

    auto setFontSize(unsigned int fontSize) -> void;

    auto setColor(sf::Color const &color) -> void;

    auto setText(std::string const &txt) -> void;

    auto setLetterSpacing(float letterSpacing) -> void;

    auto centerBothAxis(sf::Vector2f const& parentPosition, sf::Vector2f const& parentSize) -> void;

    auto centerHorizontalAxis(float parentXPosition, float parentWidth, float positionY) -> void;

    auto bindOnClick(std::function<void()> const &onTextClickHandler) -> void;

    auto onClick() -> void override;

    auto isMouseOver(const sf::Vector2i &mousePosition) const -> bool override;

    auto show() -> void override;

    auto hide() -> void override;

    auto draw(sf::RenderWindow &renderWindow) -> void override;

    static std::vector<std::unique_ptr<Component>> textWrappers;

private:

    std::function<void()> clickHandler;

    sf::Text text;

    auto initDefaultProperties() -> void;

};
