#include "./BackgroundBuilder.hpp"

RandomGenerator BackgroundBuilder::random;
std::vector<Circle> BackgroundBuilder::figures;


auto BackgroundBuilder::drawBackground(sf::RenderWindow &renderWindow) -> void {
    auto maxRadiusCircle = std::ranges::max(figures, {}, [](Circle &lc) -> float { return lc.radius; });

    for (auto &layoutCircle: figures) {
        layoutCircle.position.x += layoutCircle.velocity.x;

        if (layoutCircle.position.x < -layoutCircle.radius) {
            layoutCircle.position.x = renderWindow.getSize().x + maxRadiusCircle.radius;
            layoutCircle.position.y = static_cast<float> (random.generate(30, renderWindow.getSize().y - 30));
        }

        auto shape = sf::CircleShape(layoutCircle.radius);
        shape.setFillColor(layoutCircle.circleColor);
        shape.setPosition(layoutCircle.position);
        renderWindow.draw(shape);
    }
}

auto BackgroundBuilder::generateFigures(sf::RenderWindow &renderWindow) -> void {
    for (int i = 0; i < 100; i++) {
        float x = static_cast<float> (random.generate(0, renderWindow.getSize().x));
        float y = static_cast<float> (random.generate(30, renderWindow.getSize().y - 30));

        float depth = 0.3f + static_cast<float>  (random.generate(0, 100)) / 100.f;
        float speedModifier = 0.3f * depth;
        float xVelocity = speedModifier * (static_cast<float>(0 - random.generate(0, 100)) * 0.1f);
        float radius = 8.f * speedModifier;

        figures.emplace_back(sf::Vector2f(x, y), sf::Vector2f(xVelocity, 0), radius, sf::Color::White);
    }
}