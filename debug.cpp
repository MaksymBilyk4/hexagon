#include <fmt/printf.h>
#include <fmt/core.h>

#include <string>
#include <fstream>
#include <iostream>

auto main () -> int {

    auto file = std::fstream("../assets/saved_game_data/game_10.txt", std::ios::in);

    auto data1 = std::string();
    auto data2 = std::string();

//    getline(file, data1);
//    getline(file, data2);

    file >> data1;
    file >> data2;

    fmt::println("{}", data1);
    fmt::println("{}", data2);

//    fmt::println("Hello world");

    return 0;
}