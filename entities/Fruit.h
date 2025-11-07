//
// Created by siebe on 02/11/2025.
//

#ifndef FRUIT_H
#define FRUIT_H

#include "Entity.h"
#include <iostream>

class Fruit : public Entity {
public:
	Fruit(float x, float y) : Entity(x, y, 'f') {}

	bool isCollectible() const override;
	void onCollect(Pacman& pacman) override;
};



#endif //FRUIT_H
