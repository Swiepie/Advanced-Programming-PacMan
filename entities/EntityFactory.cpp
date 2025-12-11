//
// Created by siebe on 04/12/2025.
//

#include "EntityFactory.h"
std::unique_ptr<Wall> DefaultEntityFactory::createWall(float x, float y)  {
	return std::make_unique<Wall>(x, y);
}

std::unique_ptr<Coin> DefaultEntityFactory::createCoin(float x, float y)  {
	return std::make_unique<Coin>(x, y);
}

std::unique_ptr<Fruit> DefaultEntityFactory::createFruit(float x, float y)  {
	return std::make_unique<Fruit>(x, y);
}

std::unique_ptr<Pacman> DefaultEntityFactory::createPacman(float x, float y)  {
	return std::make_unique<Pacman>(x, y);
}

std::unique_ptr<RedGhost> DefaultEntityFactory::createRedGhost(float x, float y)  {
	return std::make_unique<RedGhost>(x, y);
}

std::unique_ptr<BlueGhost> DefaultEntityFactory::createBlueGhost(float x, float y, float delay)  {
	return std::make_unique<BlueGhost>(x, y, delay);
}

std::unique_ptr<PinkGhost> DefaultEntityFactory::createPinkGhost(float x, float y, float delay)  {
	return std::make_unique<PinkGhost>(x, y, delay);
}
// observer toevoegen en logic linken aan visualsa