#pragma once
#include "SFML/Graphics.hpp"

#include <algorithm>
#include <memory>
#include <vector>
#include "fmt/core.h"
#include "fmt/format.h"
#include "../../layout/components/Component.hpp"
#include "../cursor/Cursor.hpp"

struct ComponentUtil {

    static auto listenOnMouseClick(std::vector<std::unique_ptr<Component>> const& components, sf::Vector2i const& mousePosition) -> void;

    static auto listenOnMouseMove(std::vector<std::unique_ptr<Component>> const& components, sf::Vector2i const& mousePosition) -> void;

    static auto isMouseOver(sf::Vector2f const &elementPosition, sf::Vector2f const &elementSize, sf::Vector2i const &mousePosition) -> bool;

    static auto isMouseOver(Component const &component, sf::Vector2i const &mousePosition) -> bool;

};