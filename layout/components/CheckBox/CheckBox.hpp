#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../../../utils/font/Fonts.hpp"
#include "../TextWrapper/TextWrapper.hpp"
//#include "CheckBoxGroup.hpp"
#include <fmt/core.h>


struct CheckBox {

    CheckBox(
            sf::Vector2f const& position,
            sf::Vector2f const& size,
            std::string const& labelText
    );

    auto getIsActive() const -> bool;

    auto getActiveContextAction() const -> const std::string&;

    auto getSize() const -> sf::Vector2f;

    auto getPosition() const -> sf::Vector2f;

    auto getLabel() const -> const TextWrapper&;

    auto setBoxInnerColor(sf::Color const& color) -> void;

    auto setBoxBorderColor(sf::Color const& color) -> void;

    auto setBorderWidth(float width) -> void;

    auto setBoxInnerColorActive(sf::Color const& color) -> void;

    auto setBoxBorderColorActive(sf::Color const& color) -> void;

    auto setLabelText(std::string const& labelText) -> void;

    auto setLabelTextColor(sf::Color const& color) -> void;

    auto setLabelTextFontSize(int fontSize) -> void;

    auto setLabelFont(Fonts const& font) -> void;

    auto setPosition(sf::Vector2f const& position) -> void;

    auto setActiveContext(std::string const& context) -> void;

    auto isMouseOver(sf::Vector2i const &mousePos) -> bool;

    auto on() -> void;

    auto off() -> void;

    auto draw(sf::RenderWindow &renderWindow) -> void;

private:

    bool isActive;
    std::string activeContextAction;

    sf::RectangleShape checkBoxBase;
    TextWrapper label;

    sf::Color boxInnerColor;
    sf::Color boxBorderColor;

    sf::Color boxInnerColorActive;
    sf::Color boxBorderColorActive;

    auto initBaseProperties() -> void;
// TODO logic of addition: CheckBoxGroup group;
};

