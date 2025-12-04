//
// Created by siebe on 04/12/2025.
//

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "Entity.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Coin.h"
#include "Wall.h"
class Wall;
class Coin;
class Fruit;
class RedGhost;
class BlueGhost;
class PinkGhost;
class PacMan;

class EntityFactory {
public:
	virtual ~EntityFactory() = default;

	virtual std::unique_ptr<Wall> createWall(float x, float y) = 0;
	virtual std::unique_ptr<Coin> createCoin(float x, float y) = 0;
	virtual std::unique_ptr<Fruit> createFruit(float x, float y) = 0;
	virtual std::unique_ptr<Pacman> createPacman(float x, float y) = 0;

	virtual std::unique_ptr<RedGhost> createRedGhost(float x, float y) = 0;
	virtual std::unique_ptr<BlueGhost> createBlueGhost(float x, float y, float delay) = 0;
	virtual std::unique_ptr<PinkGhost> createPinkGhost(float x, float y, float delay) = 0;
};



class DefaultEntityFactory : public EntityFactory {
public:
	std::unique_ptr<Wall> createWall(float x, float y) override {
		return std::make_unique<Wall>(x, y);
	}

	std::unique_ptr<Coin> createCoin(float x, float y) override {
		return std::make_unique<Coin>(x, y);
	}

	std::unique_ptr<Fruit> createFruit(float x, float y) override {
		return std::make_unique<Fruit>(x, y);
	}

	std::unique_ptr<Pacman> createPacman(float x, float y) override {
		return std::make_unique<Pacman>(x, y);
	}

	std::unique_ptr<RedGhost> createRedGhost(float x, float y) override {
		return std::make_unique<RedGhost>(x, y);
	}

	std::unique_ptr<BlueGhost> createBlueGhost(float x, float y, float delay) override {
		return std::make_unique<BlueGhost>(x, y, delay);
	}

	std::unique_ptr<PinkGhost> createPinkGhost(float x, float y, float delay) override {
		return std::make_unique<PinkGhost>(x, y, delay);
	}
};
#endif //ENTITYFACTORY_H
