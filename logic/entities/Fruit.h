//
// Created by siebe on 02/11/2025.
//

#ifndef FRUIT_H
#define FRUIT_H

#include "../Visitor.h"
#include "../World.h"
#include "Entity.h"
#include <iostream>

class Fruit : public Entity {
private:
    int worth = 50;

public:
    Fruit(float x, float y) : Entity(x, y) {}

    bool isCollectible() const override;
    void onCollect(World& world) override;

    void accept(Visitor& visitor) override;
};

#endif // FRUIT_H
