#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <memory>
#include <algorithm>
#include <fmt/core.h>

#include "../Box.hpp"

#include "../../../util/font/Fonts.hpp"
#include "../../../util/font/FontHolder.hpp"
#include "../../../util/component/ComponentUtil.hpp"


struct TextField : Box {

    TextField(sf::Vector2f const& size);

    TextField(
            sf::Vector2f const& position,
            sf::Vector2f const& size,
            int fontSize
    );

    ~TextField() override = default;

    TextField(TextField const &field);

    auto getPosition() const -> sf::Vector2f override;

    auto getSize() const -> sf::Vector2f override;

    auto getColor() const -> sf::Color override;

    auto getBorderColor() const -> sf::Color override;

    auto getBorderWidth() const -> float override;

    auto getFontSize() const -> int;

    auto setPosition(sf::Vector2f const &position) -> void override;

    auto setSize(const sf::Vector2f &size) -> void override;

    auto setColor(const sf::Color &color) -> void override;

    auto setBorderColor(const sf::Color &color) -> void override;

    auto setBorderWidth(float borderWidth) -> void override;

    auto setFontSize(int fontSize) -> void;

    auto show() -> void override;

    auto hide() -> void override;

    auto draw(sf::RenderWindow &renderWindow) -> void override;

    auto isMouseOver(const sf::Vector2i &mousePosition) const -> bool override;

    auto getContent() const -> std::string;

    auto getIsActive() const -> bool;

    auto getHasLimit() const -> bool;

    auto getLimit() const -> int;

    auto setFont(Fonts const &font) -> void;

    auto setLimit(bool limitState, int limitNum) -> void;

    auto setIsActive(bool selectedState) -> void;

    auto onCharEntered(sf::Event event) -> void;

    auto resetContent() -> void;

    static std::vector<std::unique_ptr<Component>> textFields;

private:

    sf::RectangleShape borderBase;

    sf::Text textFieldBase;

    std::ostringstream content;

    sf::Color activeColor;

    sf::Color defaultColor;

    bool isActive;

    bool hasLimit;

    int limit;

    auto pushBackChar(int charTyped) -> void;

    auto removeChar() -> void;

};