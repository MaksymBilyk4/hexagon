#include <random>

#include "RandomGenerator.hpp"

RandomGenerator::RandomGenerator() : gen(random()) {}

auto RandomGenerator::generate(int low, int high) -> int {
    std::uniform_int_distribution<> distrib(low, high);
    return distrib(gen);
}
