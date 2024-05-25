#include <SFML/Graphics.hpp>
#include <vector>

#include "./LayoutController.hpp"
#include "LayoutConstructor.hpp"

RandomGenerator LayoutController::random = RandomGenerator();
std::vector<Circle> LayoutController::figures;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LayoutController::LayoutController(
        sf::RenderWindow &window, int figureCount, sf::Color const &figureColor
) :
        figureCount(figureCount),
        figureColor(figureColor),
        globalWindow(window) {}

LayoutController::LayoutController(sf::RenderWindow &window, int figureCount) :
        figureCount(figureCount),
        figureColor(sf::Color::White),
        globalWindow(window) {}

LayoutController::LayoutController(sf::RenderWindow &window) :
        figureCount(30),
        figureColor(sf::Color::White),
        globalWindow(window) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

auto LayoutController::drawBackground(sf::RenderWindow &window) -> void {


    auto maxRadiusCircle = std::ranges::max(figures, {}, [](Circle &lc) -> float { return lc.radius; });

    for (auto &layoutCircle: figures) {
        layoutCircle.position.x += layoutCircle.velocity.x;

        if (layoutCircle.position.x < -layoutCircle.radius) {
            layoutCircle.position.x = window.getSize().x + maxRadiusCircle.radius;
            layoutCircle.position.y = static_cast<float> (random.generate(30, window.getSize().y - 30));
        }

        auto shape = sf::CircleShape(layoutCircle.radius);
        shape.setFillColor(layoutCircle.circleColor);
        shape.setPosition(layoutCircle.position);
        window.draw(shape);
    }

}

auto LayoutController::generateFigures() -> void {

    for (int i = 0; i < figureCount; i++) {
        float x = static_cast<float> (random.generate(0, globalWindow.getSize().x));
        float y = static_cast<float> (random.generate(30, globalWindow.getSize().y - 30));

        float depth = 0.3f + static_cast<float>  (random.generate(0, 100)) / 100.f;
        float speedModifier = 0.3f * depth;
        float xVelocity = speedModifier * (static_cast<float>(0 - random.generate(0, 100)) * 0.1f);
        float radius = 8.f * speedModifier;

        figures.emplace_back(sf::Vector2f(x, y), sf::Vector2f(xVelocity, 0), radius, figureColor);
    }

}

// Game window panel to store whole components in one place and to controll them (show/hide)

auto LayoutController::initGameWindow() -> void {
    LayoutConstructor::buildHomeScreen(globalWindow);

    generateFigures();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

auto LayoutController::setFigureColor(sf::Color const &color) -> void {
    figureColor = color;
}

auto LayoutController::setFigureCount(int count) -> void {
    figureCount = count;
}
