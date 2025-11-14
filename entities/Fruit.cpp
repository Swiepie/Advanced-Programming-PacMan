//
// Created by siebe on 02/11/2025.
//

#include "Fruit.h"

bool Fruit::isCollectible() const {
    return true;
}

void Fruit::onCollect(World& world) {
    std::cout << "Fruit collected at (" << position.x << ", " << position.y << ")\n";
    world.setFearMode(true);
    world.setFearModeStart(Stopwatch::getInstance().GetElapsedTime());
    // eventueel score verhogen:
    // pacman.addScore(10);
};