#include "./CheckBoxGroupVer2.hpp"

std::vector<std::unique_ptr<Component>> CheckBoxGroupVer2::groups;
sf::Vector2i CheckBoxGroupVer2::clickedPosition;

auto CheckBoxGroupVer2::getPosition() const -> sf::Vector2f {
    return {0, 0};
}

auto CheckBoxGroupVer2::getSize() const -> sf::Vector2f {
    return {0, 0};
}

auto CheckBoxGroupVer2::getClickedPosition() const -> sf::Vector2i {
    return clickedPosition;
}

auto CheckBoxGroupVer2::setPosition(const sf::Vector2f &position) -> void {
    //
}

auto CheckBoxGroupVer2::setSize(const sf::Vector2f &size) -> void {
    //
}

auto CheckBoxGroupVer2::setClickedPosition(sf::Vector2i const &mousePosition) -> void {
    clickedPosition = mousePosition;
}

auto CheckBoxGroupVer2::isMouseOver(const sf::Vector2i &mousePosition) const -> bool {
    for (auto const &checkBoxPtr: checkBoxGroup)
        if (checkBoxPtr->isMouseOver(mousePosition) || checkBoxPtr->getLabel().isMouseOver(mousePosition))
            return true;

    return false;
}

auto CheckBoxGroupVer2::onClick() -> void {
    for (auto const &checkBoxPtr : checkBoxGroup) {
        if (checkBoxPtr->isMouseOver(clickedPosition) || checkBoxPtr->getLabel().isMouseOver(clickedPosition)) {
            if (checkBoxPtr != currentActive) {
                currentActive->off();
                currentActive = checkBoxPtr;
                currentActive->on();
            }
        }
    }

}

auto CheckBoxGroupVer2::onMouseOver() -> void {
    if (CursorHolder::getCurrentHolder() == CurrentHolder::CHECK_BOX ||
        CursorHolder::getCurrentHolder() == CurrentHolder::NO_ONE) {
        CursorHolder::setCurrentHolder(CurrentHolder::CHECK_BOX);
        CursorHolder::setHandCursor();
    }
}

auto CheckBoxGroupVer2::onMouseLeave() -> void {
    if (CursorHolder::getCurrentHolder() == CurrentHolder::CHECK_BOX) {
        CursorHolder::setCurrentHolder(CurrentHolder::NO_ONE);
        CursorHolder::setSimpleCursor();
    }
}

auto CheckBoxGroupVer2::show() -> void {
    if (!checkBoxGroup.empty()) {
        currentActive = checkBoxGroup[0];
        currentActive->on();
    }

    groups.push_back(std::make_unique<CheckBoxGroupVer2>(*this));
}

auto CheckBoxGroupVer2::hide() -> void {
    auto groupExistenceIterator = std::find_if(
            groups.begin(),
            groups.end(),
            [this](std::unique_ptr<Component> const &group) -> bool {
                return group.get() == this;
            }
    );

    if (groupExistenceIterator != groups.end()) {
        groups.erase(groupExistenceIterator);
    }
}

auto CheckBoxGroupVer2::draw(sf::RenderWindow &renderWindow) -> void {
    for (auto const &checkBoxPtr: checkBoxGroup)
        checkBoxPtr->draw(renderWindow);
}

auto CheckBoxGroupVer2::getActiveCheckBoxActionContext() const -> const std::string & {
    return currentActive->getActionContext();
}

auto CheckBoxGroupVer2::addCheckBox(CheckBoxVer2 &checkBox) -> void {
    checkBoxGroup.push_back(&checkBox);
}

