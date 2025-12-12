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
#include "../renderer/PacmanView.h"
#include "../renderer/GhostView.h"
#include "../renderer/Observer.h"
#include <unordered_map>
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
private:
	std::vector<std::unique_ptr<EntityView>> views;

	// Map entities to their views for easy lookup
	std::unordered_map<Entity*, EntityView*> entityToView;
public:
	std::unique_ptr<Wall> createWall(float x, float y) override;
	std::unique_ptr<Coin> createCoin(float x, float y) override;
	std::unique_ptr<Fruit> createFruit(float x, float y) override;
	std::unique_ptr<Pacman> createPacman(float x, float y) override;
	std::unique_ptr<RedGhost> createRedGhost(float x, float y) override;
	std::unique_ptr<BlueGhost> createBlueGhost(float x, float y, float delay) override;
	std::unique_ptr<PinkGhost> createPinkGhost(float x, float y, float delay) override;
};
#endif //ENTITYFACTORY_H
