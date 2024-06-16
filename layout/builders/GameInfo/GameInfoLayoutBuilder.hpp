#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <filesystem>
#include "../../components/Modal/Modal.hpp"
#include "../../components/TextWrapper/TextWrapper.hpp"
#include "../../components/Button/Button.hpp"
#include "../HomeLayoutBuilder.hpp"
#include "../GameLayoutBuilder.hpp"

#include <fmt/ranges.h>

struct GameInfoLayoutBuilder {

    static auto build() -> void;

    static auto unbuild() -> void;

    static auto initGameInfoComponents(sf::RenderWindow& renderWindow) -> void;

    static auto buildBestGames() -> void;

    static auto buildSavedGames() -> void;

    static auto buildFinishedGameInfo() -> void;

    static auto renderInfoButtons(std::string const& path) -> void;

    static std::vector<std::unique_ptr<Component>> buttons;

    static bool gameFinishedModalOpen;

private:

    static sf::Vector2f middlePos;

    static std::unique_ptr<Modal> infoModal;

    static std::unique_ptr<TextWrapper> infoTitle;

    static std::unique_ptr<Button> infoLeaveButton;

    static std::vector<std::unique_ptr<Component>> components;

};