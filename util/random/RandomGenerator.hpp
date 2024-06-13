#pragma once

#include <random>

struct RandomGenerator {

    RandomGenerator();

    auto generate(int low, int high) -> int;

private:

    std::mt19937 gen;

    std::random_device random;

};