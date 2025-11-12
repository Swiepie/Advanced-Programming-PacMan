//
// Created by Siebe Haché on 15/10/2025.
//

#ifndef COIN_H
#define COIN_H

#include "Entity.h"
#include <iostream>
class Coin : public Entity {
private:
    int worth = 10;
public:
    Coin(float x, float y) : Entity(x, y, '.') {}

    bool isCollectible() const override;

    void onCollect(World& wprld) override;

};

#endif //COIN_H
