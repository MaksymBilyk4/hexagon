#include "./Component.hpp"

int Component::idCounter = 0;

Component::Component() {
    idCounter++;
    componentId = idCounter;
}

auto Component::getComponentId() const -> int {
    return componentId;
}