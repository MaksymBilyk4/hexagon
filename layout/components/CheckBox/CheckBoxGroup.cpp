#include "CheckBoxGroup.hpp"
#include "../../../utils/cursor/CursorHolder.hpp"
#include <fmt/core.h>
#include <fmt/format.h>

std::vector<CheckBoxGroup *> CheckBoxGroup::groups;

auto CheckBoxGroup::drawCheckBoxGroups(sf::RenderWindow &window) -> void {
    for (auto &cbGroup: groups) {
//        fmt::println("draw {}", fmt::ptr(cbGroup));
        for (auto &cb: cbGroup->checkBoxGroup) {
            cb.draw(window);
//            fmt::println("draw cb {} {}", fmt::ptr(&cb), fmt::ptr(&cb));
        }
    }
}

auto CheckBoxGroup::catchOnMouseClick(const sf::Vector2i &mousePos) -> void {
    for (auto &group: groups) {
        for (auto &cb: group->checkBoxGroup) {
            if (cb.isMouseOver(mousePos) || cb.getLabel().isMouseOver(mousePos)) {
//                fmt::println("clicked on check box");
//                fmt::println("cur: {}, clicked: {}", fmt::ptr(group->currentActive), fmt::ptr(&cb));
                if (group->currentActive != nullptr) group->currentActive->off();
                group->currentActive = &cb;
                group->currentActive->on();
//                cb.on();
//                fmt::println("Current active: {}", group->currentActive->getActiveContextAction());
            }
        }
    }
}

auto CheckBoxGroup::catchOnMouseOver(sf::Window &window) -> void {
    auto mousePos = sf::Mouse::getPosition(window);
    bool cursorSet = false;

    for (auto &group : groups) {
        for (auto &cb : group->checkBoxGroup) {
            if ((cb.isMouseOver(mousePos) || cb.getLabel().isMouseOver(mousePos)) &&
                (CursorHolder::getCurrentHolder() == CurrentHolder::NO_ONE ||
                 CursorHolder::getCurrentHolder() == CurrentHolder::CHECK_BOX)) {
                CursorHolder::setHandCursor(window);
                CursorHolder::setCurrentHolder(CurrentHolder::CHECK_BOX);
                cursorSet = true;
            }
        }
    }

    if (!cursorSet && CursorHolder::getCurrentHolder() == CurrentHolder::CHECK_BOX) {
        CursorHolder::setSimpleCursor(window);
        CursorHolder::setCurrentHolder(CurrentHolder::NO_ONE);
    }
}

auto CheckBoxGroup::add(CheckBox const &checkBox) -> void {
    checkBoxGroup.push_back(checkBox);
}

auto CheckBoxGroup::show() -> void {
    groups.push_back(this);
    currentActive = &checkBoxGroup[0];
    currentActive->on();
}

auto CheckBoxGroup::hide() -> void {
    auto existenceIterator = std::ranges::find_if(groups.begin(), groups.end(),
                                                  [this](CheckBoxGroup const *cbg) -> bool {
                                                      return cbg == this;
                                                  });

    groups.erase(existenceIterator);
}

auto CheckBoxGroup::getActiveContext() const -> const std::string & {
    return currentActive->getActiveContextAction();
}

auto CheckBoxGroup::getActiveCheckBox() const -> const CheckBox * {
    return currentActive;
}

auto CheckBoxGroup::setDefaultActive(CheckBox &checkBox) -> void {
    currentActive = &checkBox;
}