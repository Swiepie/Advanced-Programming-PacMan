//
// Created by siebe on 13/12/2025.
//

#include "WallView.h"

void WallView::update(float time) { render(); }

void WallView::render() {
    Camera& camera = Camera::getInstance();

    // Step 2: Get window dimensions
    float windowWidth = static_cast<float>(window->getSize().x);
    float windowHeight = static_cast<float>(window->getSize().y);

    // Step 3: Get screen info (this calculates everything you need)
    auto info = camera.getScreenInfo(windowWidth, windowHeight);
    // info now contains: rectSize, w, h, heightFlag

    // Step 4: Convert your entity's world position to screen position
    auto worldPos = wall->getPosition();
    auto screenPos = Camera::worldToScreen(worldPos.x, worldPos.y, info,
                                         windowWidth, windowHeight);
    sf::RectangleShape rect({info.rectSize, info.rectSize});
    rect.setFillColor(sf::Color::Blue);
    rect.setPosition(screenPos);
    window->draw(rect);
}

void WallView::updateTexture(float time) {}
