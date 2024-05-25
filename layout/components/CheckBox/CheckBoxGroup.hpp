#pragma once

#include <vector>
#include "CheckBox.hpp"

#include <fmt/core.h>
#include <fmt/format.h>


struct CheckBoxGroup {

    CheckBoxGroup() {}

    // ASK
//    ~CheckBoxGroup() {
//        for (auto &group: groups) {
//            fmt::println("destroyed {}", fmt::ptr(group));
//            delete group;
//        }
//
//        delete currentActive;
//    }

    auto add(CheckBox const &checkBox) -> void;

    auto show() -> void;

    auto hide() -> void;

    static auto catchOnMouseClick(sf::Vector2i const &mousePos) -> void;

    static auto catchOnMouseOver(sf::Window &window) -> void;

    auto getActiveContext() const -> const std::string &;

    auto getActiveCheckBox() const -> const CheckBox *;

    auto setDefaultActive(CheckBox &checkBox) -> void;

    static auto drawCheckBoxGroups(sf::RenderWindow &window) -> void;

private:

    static std::vector<CheckBoxGroup *> groups;
    std::vector<CheckBox> checkBoxGroup;

    CheckBox *currentActive;

};