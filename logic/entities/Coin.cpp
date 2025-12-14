//
// Created by Siebe Haché on 15/10/2025.
//

#include "Coin.h"

#include "../World.h"

bool Coin::isCollectible() const { return true; }

void Coin::onCollect(World &world) {
  world.getScore().addCoin(world.getTime());
  world.decreaseCoins();
};

void Coin::accept(Visitor &visitor) { visitor.visit(*this); }