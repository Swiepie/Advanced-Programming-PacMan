//
// Created by siebe on 09/11/2025.
//

#include "GhostView.h"
#include <iostream>

GhostView::GhostView(Ghost* g, std::shared_ptr<sf::RenderWindow> window, int height, int width)
    : EntityView(g, std::move(window), height, width), ghost(g) {
    if (!texture.loadFromFile("../sprites/pacman.png")) {
        std::cerr << "Failed to load ghost spritesheet" << std::endl;
    }
    sprite.setTexture(texture);
}

void GhostView::update(float time) {
    updateTexture(time);
    render();
}
void GhostView::render() {
    auto pos = ghost->getPosition();
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

    sprite.setPosition(screenPos);
    sprite.setScale(rectSize / 16.f, rectSize / 16.f);

    window->draw(sprite);
}
void GhostView::updateTexture(float time) {
    if (ghost->getFearState()) {
        chooseFearTexture(time);
    }
    if (!ghost->getFearState()) {
        chooseTexture(ghost->getDirection(), time);
    }
}

void GhostView::chooseTexture(char direction, float time) {
    // Base implementation
}

void GhostView::chooseFearTexture(float time) {
    if (readyFrame(time)) {
        mouthOpen = !mouthOpen;
        sf::IntRect rect;
        rect = mouthOpen ? sf::IntRect(128, 64, 16, 16) : sf::IntRect(144, 64, 16, 16);

        sprite.setTextureRect(rect);
        recordFrameTime(time);
    }
}
// RedGhostView
RedGhostView::RedGhostView(RedGhost* g, std::shared_ptr<sf::RenderWindow> window, int height, int width)
    : GhostView(g, std::move(window), height, width) {
    sprite.setTextureRect(sf::IntRect(64, 64, 16, 16));
}

void RedGhostView::chooseTexture(char direction, float time) {
    if (readyFrame(time)) {
        mouthOpen = !mouthOpen;
        sf::IntRect rect;
        switch (direction) {
        case 'N':
            rect = mouthOpen ? sf::IntRect(64, 64, 16, 16) : sf::IntRect(80, 64, 16, 16);
            break;
        case 'Z':
            rect = mouthOpen ? sf::IntRect(96, 64, 16, 16) : sf::IntRect(112, 64, 16, 16);
            break;
        case 'W':
            rect = mouthOpen ? sf::IntRect(32, 64, 16, 16) : sf::IntRect(48, 64, 16, 16);
            break;
        case 'O':
            rect = mouthOpen ? sf::IntRect(0, 64, 16, 16) : sf::IntRect(16, 64, 16, 16);
            break;
        }
        sprite.setTextureRect(rect);
        recordFrameTime(time);
    }
}

// BlueGhostView
BlueGhostView::BlueGhostView(BlueGhost* g, std::shared_ptr<sf::RenderWindow> window, int height, int width)
    : GhostView(g, std::move(window), height, width) {
    sprite.setTextureRect(sf::IntRect(64, 96, 16, 16));
}

void BlueGhostView::chooseTexture(char direction, float time) {
    if (readyFrame(time)) {
        mouthOpen = !mouthOpen;
        sf::IntRect rect;
        switch (direction) {
        case 'N':
            rect = mouthOpen ? sf::IntRect(64, 96, 16, 16) : sf::IntRect(80, 96, 16, 16);
            break;
        case 'Z':
            rect = mouthOpen ? sf::IntRect(96, 96, 16, 16) : sf::IntRect(112, 96, 16, 16);
            break;
        case 'W':
            rect = mouthOpen ? sf::IntRect(32, 96, 16, 16) : sf::IntRect(48, 96, 16, 16);
            break;
        case 'O':
            rect = mouthOpen ? sf::IntRect(0, 96, 16, 16) : sf::IntRect(16, 96, 16, 16);
            break;
        }
        sprite.setTextureRect(rect);
        recordFrameTime(time);
    }
}

// PinkGhostView
PinkGhostView::PinkGhostView(PinkGhost* g, std::shared_ptr<sf::RenderWindow> window, int height, int width)
    : GhostView(g, std::move(window), height, width) {
    sprite.setTextureRect(sf::IntRect(64, 80, 16, 16));
}

void PinkGhostView::chooseTexture(char direction, float time) {
    if (readyFrame(time)) {
        mouthOpen = !mouthOpen;
        sf::IntRect rect;
        switch (direction) {
        case 'N':
            rect = mouthOpen ? sf::IntRect(64, 80, 16, 16) : sf::IntRect(80, 80, 16, 16);
            break;
        case 'Z':
            rect = mouthOpen ? sf::IntRect(96, 80, 16, 16) : sf::IntRect(112, 80, 16, 16);
            break;
        case 'W':
            rect = mouthOpen ? sf::IntRect(32, 80, 16, 16) : sf::IntRect(48, 80, 16, 16);
            break;
        case 'O':
            rect = mouthOpen ? sf::IntRect(0, 80, 16, 16) : sf::IntRect(16, 80, 16, 16);
            break;
        }
        sprite.setTextureRect(rect);
        recordFrameTime(time);
    }
}

// FearGhostView
