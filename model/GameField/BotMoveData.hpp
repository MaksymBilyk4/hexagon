#pragma once

#include <vector>
#include <string>
#include <fmt/core.h>

struct BotMoveData {

    BotMoveData();

    BotMoveData(int row, int col, int enemies, int loose, int gain, bool greenStep);

    int goRow;

    int goCol;

    int enemiesAround;

    int looseIfGo;

    int gain; // the same as 'enemiesAround' but if we go to green hex, we loose nothing and gain additional field + enemiesAround

    bool greenStep;

    auto getDataString() const -> std::string;

};