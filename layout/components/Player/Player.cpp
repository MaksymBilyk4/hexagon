#include "./PlayerData.hpp"

PlayerData::PlayerData() :
        fieldCount(0),
        ableToMove(false),
        playerColor(sf::Color::Red) {}

PlayerData::PlayerData(int fieldCount, sf::Color const &playerColor) : fieldCount(fieldCount), ableToMove(false),
                                                                       playerColor(playerColor) {}

auto PlayerData::getFieldCount() const -> int {
    return fieldCount;
}

auto PlayerData::getAbleToMove() const -> bool {
    return ableToMove;
}

auto PlayerData::getPlayerColor() const -> sf::Color {
    return playerColor;
}

auto PlayerData::disableMove() -> void {
    ableToMove = false;
}

auto PlayerData::ableMove() -> void {
    ableToMove = true;
}

auto PlayerData::setFieldCount(int count) -> void {
    fieldCount = count;
}

auto PlayerData::increaseFieldCount(int fields) -> void {
    fieldCount += fields;
}

auto PlayerData::decreaseFieldCount(int fields) -> void {
    fieldCount += fields;
}

auto PlayerData::setPlayerColor(const sf::Color &color) -> void {
    playerColor = color;
}