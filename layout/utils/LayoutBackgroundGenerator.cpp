#include <SFML/Graphics.hpp>
#include <algorithm>

#include "./LayoutBackgroundGenerator.hpp"

LayoutBackgroundGenerator::LayoutBackgroundGenerator(
        int figureCount,
        sf::Color figureColor
) :
        figureCount(figureCount),
        figureColor(figureColor),
        random(RandomGenerator()) {}

LayoutBackgroundGenerator::LayoutBackgroundGenerator() : figureCount(30), figureColor(sf::Color::White) {}

auto LayoutBackgroundGenerator::generate(sf::RenderWindow &window) -> void {

    for (int i = 0; i < figureCount; i++) {
        float x = static_cast<float> (random.generate(0, window.getSize().x));
        float y = static_cast<float> (random.generate(30, window.getSize().y - 30));

        float depth = 0.3f + static_cast<float>  (random.generate(0, 100)) / 100.f;
        float speedModifier = 0.3f * depth;
        float xVelocity = speedModifier * (static_cast<float>(0 - random.generate(0, 100)) * 0.1f);
        float radius = 8.f * speedModifier;

        figures.emplace_back(sf::Vector2f(x, y), sf::Vector2f(xVelocity, 0), radius, depth, sf::Color::White);
    }

}

auto LayoutBackgroundGenerator::drawBackground(sf::RenderWindow &window) -> void {

    auto maxRadiusCircle = std::ranges::max(figures, {}, [](LayoutCircle lc) -> float { return lc.radius; });

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

auto LayoutBackgroundGenerator::setFigureColor(sf::Color color) -> void {
    figureColor = color;
}

auto LayoutBackgroundGenerator::setFigureCount(int count) -> void {
    figureCount = count;
}
