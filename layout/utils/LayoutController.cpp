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

    auto maxRadiusCircle = std::ranges::max(figures, {}, [](Circle lc) -> float { return lc.radius; });

    for (auto &lc: figures) {
        lc.position.x += lc.velocity.x;

        if (lc.position.x < -lc.radius) {
            lc.position.x = window.getSize().x + maxRadiusCircle.radius;
            lc.position.y = static_cast<float> (random.generate(30, window.getSize().y - 30));
        }

        auto shape = sf::CircleShape(lc.radius);
        shape.setFillColor(lc.circleColor);
        shape.setPosition(lc.position);
        window.draw(shape);
    }

}

auto LayoutController::init() -> void {
    LayoutConstructor::makeMainModal(globalWindow);
    LayoutConstructor::makeStartGameButton(globalWindow);

    generateFigures();
}

auto LayoutController::generateFigures() -> void {

    for (int i = 0; i < figureCount; i++) {
        float x = static_cast<float> (random.generate(0, globalWindow.getSize().x));
        float y = static_cast<float> (random.generate(30, globalWindow.getSize().y - 30));

        float depth = 0.3f + static_cast<float>  (random.generate(0, 100)) / 100.f;
        float speedModifier = 0.3f * depth;
        float xVelocity = speedModifier * (static_cast<float>(0 - random.generate(0, 100)) * 0.1f);
        float radius = 8.f * speedModifier;

        figures.emplace_back(sf::Vector2f(x, y), sf::Vector2f(xVelocity, 0), radius, depth, figureColor);
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

auto LayoutController::setFigureColor(sf::Color const& color) -> void {
    figureColor = color;
}

auto LayoutController::setFigureCount(int count) -> void {
    figureCount = count;
}
