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
	auto pacman = std::make_unique<Pacman>(x, y);

	// Create view and attach it
	auto view = std::make_unique<PacmanView>(pacman.get());
	pacman->attach(view.get());

	// Store view to keep it alive
	views.push_back(std::move(view));

	return pacman;
}

std::unique_ptr<RedGhost> DefaultEntityFactory::createRedGhost(float x, float y)  {
	auto ghost = std::make_unique<RedGhost>(x, y);

	auto view = std::make_unique<RedGhostView>(ghost.get());
	ghost->attach(view.get());

	views.push_back(std::move(view));

	return ghost;
}

std::unique_ptr<BlueGhost> DefaultEntityFactory::createBlueGhost(float x, float y, float delay)  {
	auto ghost = std::make_unique<BlueGhost>(x, y, delay);

	auto view = std::make_unique<BlueGhostView>(ghost.get());
	ghost->attach(view.get());

	views.push_back(std::move(view));

	return ghost;
}

std::unique_ptr<PinkGhost> DefaultEntityFactory::createPinkGhost(float x, float y, float delay)  {
	auto ghost = std::make_unique<PinkGhost>(x, y, delay);

	auto view = std::make_unique<PinkGhostView>(ghost.get());
	ghost->attach(view.get());

	views.push_back(std::move(view));

	return ghost;
}
// observer toevoegen en logic linken aan visualsa