#pragma once

#include "SFML/Graphics.hpp"
#include <memory>
#include <vector>
#include <string>

#include "CheckBox.hpp"

struct CheckBoxGroup : Component {

    auto getPosition() const -> sf::Vector2f override;

    auto getSize() const -> sf::Vector2f override;

    auto getClickedPosition() const -> sf::Vector2i;

    auto setPosition(sf::Vector2f const &position) -> void override;

    auto setSize(sf::Vector2f const &size) -> void override;

    static auto setClickedPosition(sf::Vector2i const& mousePosition) -> void;

    auto isMouseOver(const sf::Vector2i &mousePosition) const -> bool override;

    auto onClick() -> void override;

    auto onMouseOver() -> void override;

    auto onMouseLeave() -> void override;

    auto show() -> void override;

    auto hide() -> void override;

    auto draw(sf::RenderWindow &renderWindow) -> void override;

    auto getActiveCheckBoxActionContext() const -> const std::string&;

    auto addCheckBox(CheckBox &checkBox) -> void;

    static std::vector<std::unique_ptr<Component>> groups;

private:

//    std::vector<std::unique_ptr<CheckBox>> checkBoxGroup;
    std::vector<CheckBox*> checkBoxGroup;

    CheckBox* currentActive;

    static sf::Vector2i clickedPosition;
};