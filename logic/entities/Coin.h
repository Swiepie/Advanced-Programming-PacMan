//
// Created by Siebe Haché on 15/10/2025.
//

#ifndef COIN_H
#define COIN_H

#include "../Visitor.h"
#include "Entity.h"
#include <iostream>
class Coin : public Entity {
private:
    int worth = 10;

public:
    Coin(float x, float y) : Entity(x, y) {}

    bool isCollectible() const override;

    void onCollect(World& world) override;

    void accept(Visitor& visitor) override;
};

#endif // COIN_H
