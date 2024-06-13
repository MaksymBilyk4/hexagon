#include "./BotMoveData.hpp"

BotMoveData::BotMoveData() :
        goRow(0), goCol(0), enemiesAround(0), looseIfGo(0), gain(0), greenStep(false) {}

BotMoveData::BotMoveData(int row, int col, int enemies, int loose, int gain, bool greenStep) :
        goRow(row), goCol(col), enemiesAround(enemies), looseIfGo(loose), gain(gain), greenStep(greenStep) {}

auto BotMoveData::getDataString() const -> std::string {
    auto str = fmt::format("( {}, {} ). Enemies: {}. Loose if go: {}. Gain: {}. Green step: {}", goRow, goCol, enemiesAround, looseIfGo, gain, greenStep);
    return str;
}