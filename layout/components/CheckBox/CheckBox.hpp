#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include "../TextWrapper/TextWrapper.hpp"
#include "../Box.hpp"
#include "../../../utils/ComponentUtil.hpp"
#include "../../../utils/cursor/Cursor.hpp"
#include "../../../utils/cursor/CursorHolder.hpp"

struct CheckBox : Box {

    CheckBox(
            sf::Vector2f const &position,
            sf::Vector2f const &size,
            std::string const &labelText
    );

    auto getPosition() const -> sf::Vector2f override;

    auto getSize() const -> sf::Vector2f override;

    auto setPosition(const sf::Vector2f &position) -> void override;

    auto setSize(const sf::Vector2f &size) -> void override;

    auto isMouseOver(const sf::Vector2i &mousePosition) const -> bool override;

    auto onClick() -> void override;

    auto onMouseOver() -> void override;

    auto onMouseLeave() -> void override;

    auto show() -> void override;

    auto hide() -> void override;

    auto draw(sf::RenderWindow &renderWindow) -> void override;

    auto getLabel() const -> const TextWrapper&;

    auto getColor() const -> sf::Color override;

    auto getBorderColor() const -> sf::Color override;

    auto getBorderWidth() const -> float override;

    auto getColorActive() const -> sf::Color;

    auto getBorderColorActive() const -> sf::Color;

    auto getLabelGap() const -> sf::Vector2f;

    auto getLabelPosition() const -> sf::Vector2f;

    auto getLabelSize() const -> sf::Vector2f;

    auto getLabelColor() const -> sf::Color;

    auto getLabelFontSize() const -> unsigned int;

    auto getActionContext() const -> const std::string&;

    auto getIsActive() const -> bool;

    auto setColor(const sf::Color &color) -> void override;

    auto setBorderColor(const sf::Color &color) -> void override;

    auto setBorderWidth(float borderWidth) -> void override;

    auto setColorActive(sf::Color const& color) -> void;

    auto setBorderColorActive(sf::Color const& color) -> void;

    auto setLabelGap(sf::Vector2f const& gap) -> void;

    auto setLabelColor(sf::Color const& color) -> void;

    auto setLabelFontSize(unsigned int fontSize) -> void;

    auto setLabelFont(Fonts const& font) -> void;

    auto setActionContext(std::string const& context) -> void;

    auto setIsActive(bool state) -> void;

    auto on() -> void;

    auto off() -> void;

private:

    bool isActive;
    std::string actionContext;

    sf::RectangleShape checkBoxBase;
    TextWrapper label;

    sf::Color boxColor;
    sf::Color boxBorderColor;

    sf::Color boxColorActive;
    sf::Color boxBorderColorActive;

};