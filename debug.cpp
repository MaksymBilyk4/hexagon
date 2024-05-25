#include "fmt/core.h"
#include "fmt/format.h"
#include <string>
#include <vector>
#include <memory>

struct Person {

    std::string name;
    std::string sayText;

    Person(std::string const &name, std::string const& sayText) : name(name), sayText(sayText) {}

    auto say() -> void {
        fmt::println("{} is saying: {}", name, sayText);
    }

};

auto fun1(std::vector<std::unique_ptr<Person>> &persons) -> void {
    for (auto const& p : persons) {
        fmt::println("{}", fmt::ptr(p));
    }
}

auto fun2(std::vector<std::unique_ptr<Person>> &persons) -> void {
    for (auto const& p : persons) {
        fmt::println("{}", fmt::ptr(p.get()));
    }
}

auto main() -> int {

    auto p1 = std::make_unique<Person>("Maksym", "I can");
    auto p2 = std::make_unique<Person>("David", "I am motherfucker");
    auto p3 = std::make_unique<Person>("Ihor", "Why not?");

    auto persons = std::vector<std::unique_ptr<Person>>();

    fmt::println("{}", fmt::ptr(p1));
    fmt::println("{}", fmt::ptr(p2));
    fmt::println("{}", fmt::ptr(p3));
    fmt::println("");

    persons.push_back(std::move(p1));
    persons.push_back(std::move(p2));
    persons.push_back(std::move(p3));


    for (auto const& p : persons) {
        fmt::println("{}", fmt::ptr(p));
    }
    fmt::println("");
    fun1(persons);
    fmt::println("");
    fun2(persons);

    return 0;
}