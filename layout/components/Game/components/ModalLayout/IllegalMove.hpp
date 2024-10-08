#pragma once

#include <memory>

#include "../../../Modal/Modal.hpp"
#include "../../../TextWrapper/TextWrapper.hpp"
#include "../../../Button/Button.hpp"
#include "../../../../../model/GameField/GameField.hpp"
#include "../../../../builders/GameLayoutBuilder.hpp"

struct IllegalMove {

    static bool isOpened;
    static bool lockBackground;

    static std::unique_ptr<Modal> modal;
    static std::unique_ptr<TextWrapper> title;
    static std::unique_ptr<TextWrapper> message;
    static std::unique_ptr<Component> closeButton;

    static auto show() -> void;

    static auto hide() -> void;

    static auto setTitle(std::string const& t) -> void;

    static auto setMessage(std::string const& msg) -> void;

    static auto buildIllegalMoveLayout(sf::RenderWindow& renderWindow) -> void;

};