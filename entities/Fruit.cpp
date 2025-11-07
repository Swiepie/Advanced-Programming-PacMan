//
// Created by siebe on 02/11/2025.
//

#include "Fruit.h"

bool Fruit::isCollectible() const {
    return true;
}

void Fruit::onCollect(Pacman& pacman) {
    std::cout << "Fruit collected at (" << position.x << ", " << position.y << ")\n";
    // eventueel score verhogen:
    // pacman.addScore(10);
};