//
// Created by Siebe Haché on 15/10/2025.
//

#ifndef COIN_H
#define COIN_H

#include "Entity.h"
#include <iostream>
class Coin : public Entity {
public:
    Coin(float x, float y) : Entity(x, y, '.') {}

    bool isCollectible() const override;

    void onCollect(Pacman& pacman) override;

};

#endif //COIN_H
