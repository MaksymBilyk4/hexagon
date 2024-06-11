#include "./Player.hpp"

Player::Player() :
        fieldCount(0),
        ableToMove(false),
        playerColor(sf::Color::Red) {}

Player::Player(int fieldCount, sf::Color const &playerColor) : fieldCount(fieldCount), ableToMove(false),
                                                               playerColor(playerColor) {}

auto Player::getFieldCount() const -> int {
    return fieldCount;
}

auto Player::getAbleToMove() const -> bool {
    return ableToMove;
}

auto Player::getPlayerColor() const -> sf::Color {
    return playerColor;
}

auto Player::disableMove() -> void {
    ableToMove = false;
}

auto Player::ableMove() -> void {
    ableToMove = true;
}

auto Player::setFieldCount(int count) -> void {
    fieldCount = count;
}

auto Player::increaseFieldCount(int fields) -> void {
    fieldCount += fields;
}

auto Player::decreaseFieldCount(int fields) -> void {
    fieldCount += fields;
}

auto Player::setPlayerColor(const sf::Color &color) -> void {
    playerColor = color;
}