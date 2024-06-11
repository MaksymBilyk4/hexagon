#pragma once

#include <string>
#include <filesystem>
#include <fstream>
#include <memory>
#include "../../layout/components/GameField/GameField.hpp"
#include "../../layout/components/GameField/components/CountBar.hpp"
#include "../../layout/components/GameField/components/PlayerFigure.hpp"
#include "../../layout/components/GameField/constants/FieldState.hpp"
#include "../../layout/components/GameField/constants/CurrentMovePlayer.hpp"
#include "../../layout/builders/GameLayoutBuilder.hpp"

struct GameFileStore {

    static auto saveNewGame() -> void;

    static auto saveOldGame(const std::string &loadedGameNumber) -> void;

    static auto uploadGame(std::string const& filename) -> void;

    static auto getGameNumber(std::string const& filename) -> std::string;

private:

};