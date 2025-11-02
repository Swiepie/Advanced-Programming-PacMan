//
// Created by Siebe Haché on 15/10/2025.
//

#ifndef COIN_H
#define COIN_H

#include "Entity.h"

class Coin : public Entity {
public:
    Coin(float x, float y) : Entity(x, y, '.') {}
};

#endif //COIN_H
