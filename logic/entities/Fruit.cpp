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
    world.setFearModeStart(world.getTime());
    world.getScore().addFruit(worth);
    world.decreaseCoins();
};

void Fruit::accept(Visitor& visitor)  {
    visitor.visit(*this);
}