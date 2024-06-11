#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <filesystem>
#include "../../components/Modal/Modal.hpp"
#include "../../components/TextWrapper/TextWrapper.hpp"
#include "../../components/Button/Button.hpp"
#include "./GameInfo.hpp"
#include "../HomeLayoutBuilder.hpp"
#include "../GameLayoutBuilder.hpp"

#include <fmt/ranges.h>

struct GameInfoLayoutBuilder {

    static auto build() -> void;

    static auto unbuild() -> void;

    static auto initInfoScreen(sf::RenderWindow& renderWindow) -> void;

    static auto buildBestGames() -> void;

    static auto buildSavedGames() -> void;

    static std::vector<std::unique_ptr<Component>> buttons;

private:

    static GameInfo infoRenderType;

    static std::unique_ptr<TextWrapper> infoTitle;

    static std::vector<std::unique_ptr<Component>> components;

};