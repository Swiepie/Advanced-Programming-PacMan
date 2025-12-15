//
// Created by siebe on 02/11/2025.
//

#include "PacmanView.h"
#include <iostream>
#include <utility>
PacmanView::PacmanView(Pacman* pacman, std::shared_ptr<sf::RenderWindow> window, int height, int width)
    : EntityView(pacman, std::move(window), static_cast<float>(height), static_cast<float>(width)), pacman(pacman) {
    if (!texture.loadFromFile("../sprites/pacman.png")) {
        std::cerr << "Failed to load pacman spritesheet" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(30, 0, 15, 15));
}

void PacmanView::update() {
    // Called automatically when entity notifies
    // Can be used for immediate reactions to state changes
}

void PacmanView::updateTexture(float time) { chooseTexture(pacman->getDirection(), time); }

void PacmanView::chooseTexture(char direction, float time) {
    if (readyFrame(time)) {
        mouthOpen = !mouthOpen;
        sf::IntRect rect;

        switch (direction) {
        case 'N':
            rect = mouthOpen ? sf::IntRect(0, 30, 15, 15) : sf::IntRect(15, 30, 15, 15);
            break;
        case 'Z':
            rect = mouthOpen ? sf::IntRect(0, 45, 15, 15) : sf::IntRect(15, 45, 15, 15);
            break;
        case 'W':
            rect = mouthOpen ? sf::IntRect(0, 15, 15, 15) : sf::IntRect(15, 15, 15, 15);
            break;
        case 'O':
            rect = mouthOpen ? sf::IntRect(0, 0, 15, 15) : sf::IntRect(15, 0, 15, 15);
            break;
        case ' ':
            rect = sf::IntRect(30, 0, 15, 15);
            break;
        case 'D': {
            rect = sf::IntRect(15 * i, 0, 15, 15);
            i++;
            if (i == 14) {
                i = 2;
            }
            break;
        }
        }
        sprite.setTextureRect(rect);
        recordFrameTime(time);
    }
}

void PacmanView::render() {
    auto pos = pacman->getPosition();
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
    sprite.setScale(rectSize / 15.f, rectSize / 15.f);

    window->draw(sprite);
}

void PacmanView::update(float time) {

    updateTexture(time);
    render();
}
