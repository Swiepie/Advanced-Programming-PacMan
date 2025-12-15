//
// Created by siebe on 13/12/2025.
//

#include "WallView.h"

void WallView::update(float time) { render(); }

void WallView::render() {
    auto pos = wall->getPosition();
    Camera camera;
    float windowWidth = static_cast<float>(window->getSize().x);
    float windowHeight = static_cast<float>(window->getSize().y);

    float rectSize = std::min(windowWidth / width, windowHeight / height);

    float w, h;
    bool heightFlag;

    if (width / height <= windowWidth / windowHeight) {
        h = windowHeight;
        w = width * windowHeight / height;
        heightFlag = false;
    } else {
        h = (height / width) * windowWidth;
        w = windowWidth;
        heightFlag = true;
    }

    auto screenPos = camera.normalizeToScreen(pos.x, pos.y, windowWidth, windowHeight, heightFlag, h, w);

    sf::RectangleShape rect({rectSize, rectSize});
    rect.setFillColor(sf::Color::Blue);
    rect.setPosition(screenPos);
    window->draw(rect);
}

void WallView::updateTexture(float time) {}
