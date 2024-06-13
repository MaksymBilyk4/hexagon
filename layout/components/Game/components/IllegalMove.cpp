#include "./IllegalMove.hpp"

bool IllegalMove::isOpened = false;
bool IllegalMove::lockBackground = false;

std::unique_ptr<Modal> IllegalMove::modal;
std::unique_ptr<TextWrapper> IllegalMove::title;
std::unique_ptr<TextWrapper> IllegalMove::message;
std::unique_ptr<Button> IllegalMove::closeButton;

auto IllegalMove::show() -> void {
    isOpened = true;
    lockBackground = true;
    modal->show();
    title->show();
    message->show();
    closeButton->show();
}

auto IllegalMove::hide() -> void {
    isOpened = false;
    modal->hide();
    title->hide();
    message->hide();
    closeButton->hide();
}

auto IllegalMove::setTitle(const std::string &t) -> void {
    title->setText(t);
}

auto IllegalMove::setMessage(const std::string &msg) -> void {
    message->setText(msg);
}