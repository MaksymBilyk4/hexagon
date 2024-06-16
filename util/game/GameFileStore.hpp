#pragma once

#include <string>
#include <filesystem>
#include <fstream>
#include <memory>
#include "../../layout/components/Game/components/CountBar.hpp"
#include "../../layout/components/Game/components/PlayerFigure.hpp"
#include "../../layout/components/Game/constants/FieldState.hpp"
#include "../../layout/components/Game/constants/Player.hpp"
#include "../../layout/builders/GameLayoutBuilder.hpp"
#include "../../model/GameField/GameField.hpp"
#include "./Path.hpp"
#include "./SaveMode.hpp"

struct GameFileStore {

    static auto saveNewGame(std::string const& filename, SaveMode const& saveMode) -> void;

    static auto saveOldGame(const std::string &loadedGameNumber) -> void;

    static auto uploadGame(std::string const& filename) -> void;

};