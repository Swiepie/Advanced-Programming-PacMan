//
// Created by Siebe Haché on 15/10/2025.
//

#include "Coin.h"
bool Coin::isCollectible() const {
    return true;
}

void Coin::onCollect(Pacman& pacman) {
    std::cout << "Coin collected at (" << position.x << ", " << position.y << ")\n";
    // eventueel score verhogen:
    // pacman.addScore(10);
};