#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "../components/TextWrapper/TextWrapper.hpp"
#include "../../utils/font/Fonts.hpp"

struct GameLayoutBuilder {

    static auto build() -> void;

    static auto unbuild() -> void;

    static auto initGameField() -> void;

private:
    static std::unique_ptr<TextWrapper> test;

};