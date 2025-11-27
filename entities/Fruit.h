//
// Created by siebe on 02/11/2025.
//

#ifndef FRUIT_H
#define FRUIT_H

#include "Entity.h"
#include <iostream>
#include "../World.h"

class Fruit : public Entity {
private:
	int worth = 50;
public:
	Fruit(float x, float y) : Entity(x, y, 'f') {}

	bool isCollectible() const override;
	void onCollect(World& world) override;
};



#endif //FRUIT_H
