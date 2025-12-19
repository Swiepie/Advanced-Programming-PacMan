//
// Created by siebe on 13/12/2025.
//

#include "WallView.h"

void WallView::update(float time) { render(); }

void WallView::render() {
    Camera& camera = Camera::getInstance();

    // Get window dimensions
    float windowWidth = static_cast<float>(window->getSize().x);
    float windowHeight = static_cast<float>(window->getSize().y);

    auto info = camera.getScreenInfo(windowWidth, windowHeight);

    auto worldPos = wall->getPosition();
    auto screenPos = Camera::worldToScreen(worldPos.x, worldPos.y, info, windowWidth, windowHeight);
    sf::RectangleShape rect({info.rectSize, info.rectSize});
    rect.setFillColor(sf::Color::Blue);
    rect.setPosition(screenPos);
    window->draw(rect);
}

void WallView::updateTexture(float time) {}
