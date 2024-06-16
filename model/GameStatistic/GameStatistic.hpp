#pragma once

#include "../../layout/components/Game/constants/Player.hpp"
#include "../../layout/components/Game/constants/GameMode.hpp"
#include "../GameField/GameField.hpp"
#include <string>

struct GameStatistic {

    static inline int stepsDone = 0;

    static inline int allFiguresEaten = 0;

    static inline int firstPlayerAte = 0;

    static inline int secondPlayerAte = 0;

    static inline int spaceLeft = 58;

    static inline Player winner = Player::FIRST;

    static inline GameMode gameMode = GameMode::PLAYER_VS_COMPUTER;

    static auto resetGameStatistic() -> void;

    static auto updateGameStatistic(bool isGreenStep) -> void;

    static auto printStatistic() -> void;

};