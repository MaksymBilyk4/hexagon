#pragma once

#include "SFML/Graphics.hpp"
#include <vector>
#include <memory>
#include <algorithm>
#include "../../Box.hpp"
#include "../constants/FieldState.hpp"
#include "../../../../util/component/ComponentUtil.hpp"

struct Hexagon : Box {

    Hexagon();

    auto getPosition() const -> sf::Vector2f override;

    auto getSize() const -> sf::Vector2f override;

    auto getFieldState() const -> FieldState;

    auto getFieldRow() const -> int;

    auto getFieldCol() const -> int;

    auto getColor() const -> sf::Color override;

    auto getBorderColor() const -> sf::Color override;

    auto getBorderWidth() const -> float override;

    auto getIsSelectedByBot() const -> bool;

    auto setPosition(sf::Vector2f const &position) -> void override;

    auto setSize(sf::Vector2f const &size) -> void override;

    auto setFieldSate(FieldState const &fieldState) -> void;

    auto setFieldRow(int row) -> void;

    auto setFieldCol(int col) -> void;

    auto setColor(sf::Color const& color) -> void override;

    auto setBorderColor(sf::Color const& color) -> void override;

    auto setBorderWidth(float borderWidth) -> void override;

    auto setIsSelectedByBot(bool isSelected) -> void;

    auto isMouseOver(const sf::Vector2i &mousePosition) const -> bool override;

    auto onClick() -> void override;

    auto onMouseOver() -> void override;

    auto onMouseLeave() -> void override;

    auto show() -> void override;

    auto hide() -> void override;

    auto draw(sf::RenderWindow &window) -> void override;

    auto drawGreenBorder() -> void;

    auto drawYellowBorder() -> void;

    auto drawDefaultBorder() -> void;

    static std::vector<std::unique_ptr<Component>> items;

    static float defaultRadius;

    static sf::Color defaultColor;

    static sf::Color defaultBorderColor;

private:

    int fieldRow;

    int fieldCol;

    bool isSelectedByBot;

    sf::CircleShape hexagon;

    FieldState state;

};