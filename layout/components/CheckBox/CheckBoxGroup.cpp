#include "./CheckBoxGroup.hpp"

std::vector<std::unique_ptr<Component>> CheckBoxGroup::groups;
sf::Vector2i CheckBoxGroup::clickedPosition;

auto CheckBoxGroup::getPosition() const -> sf::Vector2f {
    return {0, 0};
}

auto CheckBoxGroup::getSize() const -> sf::Vector2f {
    return {0, 0};
}

auto CheckBoxGroup::getClickedPosition() const -> sf::Vector2i {
    return clickedPosition;
}

auto CheckBoxGroup::setPosition(const sf::Vector2f &position) -> void {
    //
}

auto CheckBoxGroup::setSize(const sf::Vector2f &size) -> void {
    //
}

auto CheckBoxGroup::setClickedPosition(sf::Vector2i const &mousePosition) -> void {
    clickedPosition = mousePosition;
}

auto CheckBoxGroup::isMouseOver(const sf::Vector2i &mousePosition) const -> bool {
    for (auto const &checkBoxPtr: checkBoxGroup)
        if (checkBoxPtr->isMouseOver(mousePosition) || checkBoxPtr->getLabel().isMouseOver(mousePosition))
            return true;

    return false;
}

auto CheckBoxGroup::onClick() -> void {
    for (auto const &checkBoxPtr: checkBoxGroup) {
        if (checkBoxPtr->isMouseOver(clickedPosition) || checkBoxPtr->getLabel().isMouseOver(clickedPosition)) {
            if (checkBoxPtr != currentActive) {
                currentActive->off();
                currentActive = checkBoxPtr;
                currentActive->on();
            }
        }
    }

}

auto CheckBoxGroup::onMouseOver() -> void {
    if (Cursor::getCurrentHolder() == CursorHolder::CHECK_BOX ||
        Cursor::getCurrentHolder() == CursorHolder::NO_ONE) {
        Cursor::setCurrentHolder(CursorHolder::CHECK_BOX);
        Cursor::setHandCursor();
    }
}

auto CheckBoxGroup::onMouseLeave() -> void {
    if (Cursor::getCurrentHolder() == CursorHolder::CHECK_BOX) {
        Cursor::setCurrentHolder(CursorHolder::NO_ONE);
        Cursor::setSimpleCursor();
    }
}

auto CheckBoxGroup::show() -> void {
    if (!checkBoxGroup.empty()) {
        currentActive = checkBoxGroup[0];
        currentActive->on();

        for (auto const& cb : checkBoxGroup)
            cb->show();
    }

    groups.push_back(std::make_unique<CheckBoxGroup>(*this));
}

auto CheckBoxGroup::hide() -> void {
    auto groupExistenceIterator = std::find_if(
            groups.begin(),
            groups.end(),
            [this](std::unique_ptr<Component> const &group) -> bool {
                return group->getComponentId() == getComponentId();
            }
    );

    if (groupExistenceIterator != groups.end()) {
        auto group = dynamic_cast<CheckBoxGroup *>((*groupExistenceIterator).get());
        group->hideLabels();

        groups.erase(groupExistenceIterator);
    }
}

auto CheckBoxGroup::hideLabels() -> void {
    for (auto const& checkBox : checkBoxGroup)
        checkBox->hide();
}

auto CheckBoxGroup::draw(sf::RenderWindow &renderWindow) -> void {
    for (auto const &checkBoxPtr: checkBoxGroup)
        checkBoxPtr->draw(renderWindow);
}

auto CheckBoxGroup::getActiveCheckBoxActionContext() const -> const std::string & {
    return currentActive->getActionContext();
}

auto CheckBoxGroup::addCheckBox(CheckBox &checkBox) -> void {
    checkBoxGroup.push_back(&checkBox);
}

