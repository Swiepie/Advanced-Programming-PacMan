//
// Created by siebe on 13/12/2025.
//

#include "CollectibleView.h"

void FruitView::update(float time) { render(); }

void FruitView::render() {
    Camera& camera = Camera::getInstance();

    float windowWidth = static_cast<float>(window->getSize().x);
    float windowHeight = static_cast<float>(window->getSize().y);

    auto info = camera.getScreenInfo(windowWidth, windowHeight);

    auto pos = fruit->getPosition();
    auto screenPos = Camera::worldToScreen(pos.x, pos.y, info, windowWidth, windowHeight);

    float radius = info.rectSize / 7.f;

    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Magenta);
    circle.setPosition(screenPos.x + info.rectSize / 2.f - radius, screenPos.y + info.rectSize / 2.f - radius);

    window->draw(circle);
}

void FruitView::updateTexture(float time) {}

void CoinView::update(float time) { render(); }

void CoinView::render() {
    // Get the camera singleton
    Camera& camera = Camera::getInstance();

    // Get window dimensions
    float windowWidth = static_cast<float>(window->getSize().x);
    float windowHeight = static_cast<float>(window->getSize().y);

    auto info = camera.getScreenInfo(windowWidth, windowHeight);

    auto pos = coin->getPosition();
    auto screenPos = Camera::worldToScreen(pos.x, pos.y, info, windowWidth, windowHeight);

    float radius = info.rectSize / 10.f;

    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Yellow);
    circle.setPosition(screenPos.x + info.rectSize / 2.f - radius, screenPos.y + info.rectSize / 2.f - radius);

    window->draw(circle);
}

void CoinView::updateTexture(float time) {}
