//
// Created by Siebe Haché on 15/10/2025.
//

#include "WorldView.h"
#include "../Wall.h"
#include "../Coin.h"

sf::Vector2f normalizeToScreen(float x, float y, int screenWidth, int screenHeight) {
    float px = (x + 1.0f) * 0.5f * screenWidth;
    float py = (y + 1.0f) * 0.5f * screenHeight;
    return {px, py};
}

void WorldView::render(const World& world, sf::RenderWindow& window) {
    int w = window.getSize().x;
    int h = window.getSize().y;

    for (auto& e : world.getEntities()) {
        auto pos = e->getPosition();
        auto screenPos = normalizeToScreen(pos.x, pos.y, w, h);

        char symbol = e->getSymbol();
        if (symbol == '#') {
            sf::RectangleShape rect({32, 32});
            rect.setFillColor(sf::Color::Blue);
            rect.setPosition(screenPos);
            window.draw(rect);
        } else if (symbol == '.') {
            sf::CircleShape circle(4);
            circle.setFillColor(sf::Color::Yellow);
            circle.setPosition(screenPos);
            window.draw(circle);
        }
    }
}