#pragma once

#include <SFML/Graphics.hpp>
#include "../../../util/random/RandomGenerator.hpp"

struct PlayerData {

    PlayerData();

    PlayerData(int fieldCount, sf::Color const& playerColor);

    auto getFieldCount() const -> int;

    auto getAbleToMove() const -> bool;

    auto getPlayerColor() const -> sf::Color;

    auto disableMove() -> void;

    auto ableMove() -> void;

    auto setFieldCount(int count) -> void;

    auto increaseFieldCount(int fields) -> void;

    auto decreaseFieldCount(int fields) -> void;

    auto setPlayerColor(sf::Color const& color) -> void;

private:

    int fieldCount;

    bool ableToMove;

    sf::Color playerColor;


};