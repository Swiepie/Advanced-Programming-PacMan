//
// Created by Siebe Haché on 15/10/2025.
//

#include "WorldView.h"
#include "../logic/entities/Coin.h"
#include "../logic/entities/Wall.h"
#include <iostream>

sf::View getWorldView(unsigned int windowWidth, unsigned int windowHeight) {
    sf::View view;
    view.setSize(windowWidth, windowHeight);

    view.setCenter(windowWidth / 2.f, windowHeight / 2.f);
    return view;
}

sf::Vector2f normalizeToScreen(float x, float y, float screenWidth, float screenHeight, bool flag, float h, float w) {
    float whitespaceH = (screenHeight - h) / 2.f;
    float whitespaceW = (screenWidth - w) / 2.f;

    if (!flag) {
        float px = (x + 1.0f) * 0.5f * w + whitespaceW;
        float py = (y + 1.0f) * 0.5f * h;
        return {px, py};
    } else {
        float px = (x + 1.0f) * 0.5f * w;
        float py = (y + 1.0f) * 0.5f * h + whitespaceH;
        return {px, py};
    }
}

void WorldView::render(std::shared_ptr<World> world, std::shared_ptr<sf::RenderWindow> window, float windowWidth,
                       float windowHeight) {

    sf::View view = getWorldView(windowWidth, windowHeight);
    window->setView(view);

    float time = world->getTime();

    for (auto& wall : world->getWalls()) {
        Observer* observer = wall->getObserver();
        if (observer) {
            observer->update(time);
        }
    }

    for (auto& collectible : world->getCollectibles()) {
        Observer* observer = collectible->getObserver();
        if (observer) {
            observer->update(time);
        }
    }

    std::shared_ptr<Pacman> pacman = world->getPacman();
    if (pacman) {
        Observer* observer = pacman->getObserver();
        if (observer) {
            observer->update(time);
        }
    }

    for (auto& ghost : world->getGhosts()) {
        Observer* observer = ghost->getObserver();
        if (observer) {
            observer->update(time);
        }
    }
}